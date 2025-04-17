#include "main.h"

volatile sig_atomic_t g_running = 1;

void signalHandler(int signum) {
    if (signum == SIGINT) {
        printf("\nCtrl+C\n");
        g_running = 0;
    }
}

void usage() {
    printf("syntax : 1m-block <site list file>\n");
    printf("sample : 1m-block top-1m.txt");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        return 1;
    }
    signal(SIGINT, signalHandler);
    NetFilterConf NFConf;

    if (NetFilterConf::SetHostList(argv[1])) { return 1; }

    NFConf.SetNetFilterOpening();    

    while (g_running) {
        switch (NFConf.RunNetFilter()) {
            case RUN_CONTINUE:
                continue;
            case RUN_BREAK:
                break;
            default:
                printf("Error");
                break;
        }
    }

    NFConf.SetNetFilterEnding();

    return 0;
}