
#include "rdma_ctrl.hpp"
#include <stdio.h>
#include <string.h>


/**
 * Note, RDMA usually uses some other communication method (e.g. TCP/IP) to exchange QP informations.
 * RLib uses TCP for the pre-communication.
 */
int server_node_id = 1;
int tcp_port       = 17621;
int client_port    = 17620; //remote port
const char* remote_ip = "10.0.0.62";
int local_mr_id = 73;//whatever ~?
using namespace rdmaio;

int main(int argc, char *argv[])
{
    RdmaCtrl *c = new RdmaCtrl(server_node_id,tcp_port);
    RdmaCtrl::DevIdx idx {.dev_id = 1,.port_id = 1 }; // using the second RNIC's first port -------实验室机器就用这个
    c->open_thread_local_device(idx);

    // register a buffer to the previous opened device, using id = 73
    char *buffer = (char *)malloc(4096);
    memset(buffer, 0, 4096);
    RDMA_ASSERT(c->register_memory(local_mr_id, buffer, 4096, c->get_device()) == true);//buffer绑定到mr，可以被远端持有key的结点访问

    char s[] = "hello faker";
    memcpy(buffer, s, strlen(s));

    MemoryAttr local_mr = c->get_local_mr(local_mr_id);
    RCQP *qp = c->create_rc_qp(create_rc_idx(2,0), c->get_device(), &local_mr);//用qp ID，设备，本地MR创建一个可靠连接QP
    //create_rc_idx，设定了qp的连接号和任务号。经过测试，必须收发两端的两个号必须完全一样才能进行通信

    // server also needs to "connect" clinet.
    while(qp->connect(remote_ip, client_port, create_rc_idx(2,0)) != SUCC)  {//该过程仅仅是为了可靠连接传输进行的SEND&RCEV
        usleep(2000);
    }

    printf("server: QP connected!\n");
    //这之后才真正进行RDMA READ，server是CPU无感知的
    while(true) {
        // This is RDMA, server does not need to do anything :)
        sleep(1);
    }

    return 0;
}
