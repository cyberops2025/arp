#include "../include/includes.h"
#include "../include/get_raw_socket.h"

int get_raw_socket() {

    int raw_sock = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);

    if (raw_sock == -1) {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        exit(1);
    }

    return raw_sock;

}

