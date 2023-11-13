#include "rdma_ctrl.hpp"
#include <stdio.h>
#include <assert.h>
using namespace rdmaio;
//read from server
int main(int argc, char *argv[])
{
    int node_id=12;
    const char* local_ip="localhost";
    const char* remote_ip="10.0.0.62";
    int l_port=17620,r_port=17621;
    int l_mrid=60,r_mrid=73;

    RdmaCtrl *c = new RdmaCtrl(node_id,l_port);
    std::vector<RNicInfo> devs = c->query_devs_helper();
    bool flag=0;
    RdmaCtrl::DevIdx idx;
    for(int i=0;i<devs.size();i++){
        devs[i].print();
        if(devs[i].active_ports.size()==0) continue;
        if(flag==0){
            idx.dev_id=i;
            idx.port_id=1;
            flag=1;
        }
    }
    if(flag==0){
        printf("No active RNic");
        return 0;
    }
    c->open_thread_local_device(idx);
    //寻找可用RNic和端口，默认最小的

    char *buffer = (char*)malloc(4096); memset(buffer, 0, 4096);
    RDMA_ASSERT(c->register_memory(l_mrid, buffer, 4096,c->get_device()) == true);
    //注册自己的MR，默认赋予IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_READ |IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_REMOTE_ATOMIC
    
    MemoryAttr remote_mr; //记录了mr的索引和对应权限的key
    while(QP::get_remote_mr(remote_ip, r_port, r_mrid, &remote_mr)!=SUCC){
        usleep(1000);
    }
    //得到对方mr的R_key ??
    
    MemoryAttr local_mr = c->get_local_mr(l_mrid);
    RCQP *qp = c->create_rc_qp(create_rc_idx(1,1), c->get_device(), &local_mr);
    qp -> bind_remote_mr(remote_mr);
    while(qp->connect(remote_ip,r_port)!=SUCC)  usleep(1000);
    printf("client:RCQP for READ connected!\n");
    //传入本地mr建立RCQP并绑定相应的远程mr，尝试连接远程

    ibv_wc wc1;//可以多次使用
    char *local_buf = buffer;
    uint64_t address = 0;
    int msg_len = 0;
    
    // auto Recv = qp->post_send(IBV_WR_RDMA_READ, local_buf, msg_len, address, IBV_SEND_SIGNALED);
    // //上传WQ，具体参数不懂，以后再看
    // if(Recv == SUCC){
    //     printf("client:RCQP post READ WR ok!\n");
    // }else{
    //     printf("clinet:client:RCQP post READ WR Failed, Recv = %d\n",Recv);
    //     return 0;
    // }
    // //提交WQ

    // Recv = qp->poll_till_completion(wc,no_timeout);//no_timeout永远轮询,但是一定时间还是会退出
    // if(Recv==SUCC){
    //     printf("client: poll ok\n");
    //     printf("msg READ: %s\n", local_buf);
    // } else {
    //     printf("client: poll fail. rc=%d\n", Recv);
    // }
    qp->post_send(IBV_WR_RDMA_READ, local_buf, 2, address, IBV_SEND_SIGNALED);
    qp->poll_till_completion(wc1,no_timeout);
    unsigned short len = *((unsigned short*)(local_buf+address));
    address += 2;
    printf("length1: %u\n",len);
    qp->post_send(IBV_WR_RDMA_READ, local_buf+address, len, address, IBV_SEND_SIGNALED); //此处address是指的在远端MR的偏移
    qp->poll_till_completion(wc1,no_timeout);
    printf("msg1 READ: %s\n", local_buf+address);
    address +=len;

    local_buf[address]=0;    
    while(local_buf[address]==0){//不轮询就会读到0，然后直接认为没话说
        usleep(500);
        qp->post_send(IBV_WR_RDMA_READ, local_buf+address, 2, address, IBV_SEND_SIGNALED);
        qp->poll_till_completion(wc1,no_timeout);
    }
    len = *((unsigned short*)(local_buf+address));
    address += 2;
    printf("length2: %u\n",len);
    qp->post_send(IBV_WR_RDMA_READ, local_buf+address, len, address, IBV_SEND_SIGNALED);
    qp->poll_till_completion(wc1,no_timeout);
    printf("msg2 READ: %s\n", local_buf+address);
    address +=len;
    return 0;
}

