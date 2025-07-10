// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/

#include <errno.h>
#include <netdb.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    
    printf("Here we go...\n");

    int raw_sock = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (raw_sock == -1) {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        exit(1);
    }

    char* test_iface = "vboxnet0";

    struct ifreq iface_index;
    memset(&iface_index, 0, sizeof(iface_index));
    strncpy(iface_index.ifr_name, test_iface, IFNAMSIZ-1);

    if ((ioctl(raw_sock, SIOCGIFINDEX, &iface_index)) < 0) {
        fprintf(stderr, "ioctl() failed. (%d)\n", errno);
        exit(1);
    }

    printf("index=%d\n", iface_index.ifr_ifindex);

    close(raw_sock);

    return 0;

}
