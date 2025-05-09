#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>		/* for NF_ACCEPT */
#include <errno.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

#include "packet_structs.h"
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <sstream>

#define RUN_CONTINUE 1
#define RUN_BREAK 2
#define SUCCESS_SET_HOSTLIST 0
#define FILE_NOT_OPEN 1

class NetFilterConf {
    public:
        NetFilterConf();
        ~NetFilterConf();

        void SetNetFilterOpening();
        int RunNetFilter();
        void SetNetFilterEnding();

        static int SetHostList(char* listFile);

        private:
        static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data);
        static std::string FindHost(std::string httpData);
        static u_int32_t pkt_filter(struct nfq_data *tb, int& NF_FLAGS);
        
        // static size_t hostname_;
        static std::unordered_set<std::string> hostnames_;

        struct nfq_handle *h_;
        struct nfq_q_handle *qh_;
        struct nfnl_handle *nh_;
        int fd_;
        int rv_;
        char buf_[4096] __attribute__ ((aligned));

};