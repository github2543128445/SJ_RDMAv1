
#include "rdma_ctrl.hpp"
#include <stdio.h>
#include <string.h>


/**
 * Note, RDMA usually uses some other communication method (e.g. TCP/IP) to exchange QP informations.
 * RLib uses TCP for the pre-communication.
 */
using namespace rdmaio;

int main(int argc, char *argv[])
{
    int node_id=12;
    const char* local_ip="localhost";
    const char* remote_ip="10.0.0.62";
    int l_port=17621,r_port=17620;
    int l_mrid=73,r_mrid=60;
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

    char *buffer = (char* )malloc(4096);
    memset(buffer, 0, 4096);
    RDMA_ASSERT(c->register_memory(l_mrid, buffer, 4096, c->get_device()) == true);
    //申请并注册MR
    
    char *local_buffer = buffer;
    MemoryAttr local_mr = c->get_local_mr(l_mrid);
    RCQP *qp = c->create_rc_qp(create_rc_idx(1,1), c->get_device(), &local_mr);
    while(qp->connect(remote_ip, r_port)!=SUCC) usleep(1000);
    printf("Server: QP connected!\n");

    unsigned short len = ((unsigned short*)local_buffer)[0];
    while(len==0){
        usleep(2000);
        len = ((unsigned short*)local_buffer)[0];
    }
    local_buffer+=2;
    printf("msg1: Remote WRITE:\n%s\n",local_buffer);
    local_buffer+=len;
    
    len = ((unsigned short*)local_buffer)[0];
    while(len==0){
        usleep(2000);
        len = ((unsigned short*)local_buffer)[0];
    }
    local_buffer+=2;
    printf("msg2: Remote WRITE:\n%s\n",local_buffer);
    local_buffer+=len;
    return 0;
}
