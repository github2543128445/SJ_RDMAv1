#include "rdma_ctrl.hpp"
#include <stdio.h>
#include <assert.h>

int client_node_id = 0;
int tcp_port       = 17620;
int server_port = 17621;
const char* remote_ip = "10.0.0.61";
int local_mr_id = 60;
int remote_mr_id = 73;
using namespace rdmaio;
//read from server
int main(int argc, char *argv[])
{
    RdmaCtrl *c = new RdmaCtrl(client_node_id,tcp_port);
    RdmaCtrl::DevIdx idx {.dev_id = 1,.port_id = 1 }; // using the second RNIC's first port
    c->open_thread_local_device(idx);

    // register a buffer to the previous opened device, using id = 60
    char *buffer = (char *)malloc(4096);
    memset(buffer, 0, 4096);
    RDMA_ASSERT(c->register_memory(local_mr_id, buffer, 4096, c->get_device()) == true);

    // get remote server's memory information
    MemoryAttr remote_mr;
    while(QP::get_remote_mr(remote_ip, server_port, remote_mr_id, &remote_mr) != SUCC) {
        usleep(2000);
    }

    // create the RC qp to access remote server's memory, using the previous registered memory
    MemoryAttr local_mr = c->get_local_mr(local_mr_id);
    RCQP *qp = c->create_rc_qp(create_rc_idx(1,0), c->get_device(), &local_mr);
    qp->bind_remote_mr(remote_mr); // bind to the previous allocated mr

    while(qp->connect(remote_ip,server_port) != SUCC)  {
        usleep(2000);
    }
    printf("client: QP connected!\n");
    //以上过程完成可靠传输“连接”，实际上应该是QP的绑定和key的获取，这个过程后，server就不管了

    ibv_wc wc;
    char *local_buf  = buffer;
    uint64_t address = 0;
    int msg_len = 11;   // length of "hello world"

    // read an uint64_t from the server
    auto rc = qp->post_send(IBV_WR_RDMA_READ, local_buf, msg_len, address, IBV_SEND_SIGNALED);
    if (rc == SUCC) {
        printf("client: post ok\n");
    } else {
        printf("client: post fail. rc=%d\n", rc);
    }
    rc = qp->poll_till_completion(wc, no_timeout);
    // then get the results, stored in the local_buffer
    if (rc == SUCC) {
        printf("client: poll ok\n");
        printf("msg read: %s\n", local_buf);
    } else {
        printf("client: poll fail. rc=%d\n", rc);
    }

    return 0;

}

