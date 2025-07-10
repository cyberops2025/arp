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

int get_iface_index(int raw_sock, char* iface_name);
char* get_iface_mac(int raw_sock, char* iface_name);

int main() {
    
    char* test_iface = "vboxnet0";

    printf("Here we go...\n");

    int raw_sock = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (raw_sock == -1) {
        fprintf(stderr, "socket() failed. (%d)\n", errno);
        exit(1);
    }

    int iface_index = get_iface_index(raw_sock, test_iface);
    printf("Interface Index = %d\n", iface_index);

    char* iface_mac = get_iface_mac(raw_sock, test_iface);
    printf("Interface MAC address = ");
    for (int i = 0; i < 6; i++) {
        printf("%.2x ", iface_mac[i]);
    }
    printf("\n");
    
    close(raw_sock);

    return 0;

}

int get_iface_index(int raw_sock, char* iface_name) {

    struct ifreq iface_index;

    memset(&iface_index, 0, sizeof(iface_index));
    strncpy(iface_index.ifr_name, iface_name, IFNAMSIZ-1);

    if ((ioctl(raw_sock, SIOCGIFINDEX, &iface_index)) < 0) {
        fprintf(stderr, "ioctl() failed. (%d)\n", errno);
        exit(1);
    }
    
    return iface_index.ifr_ifindex;

}

char* get_iface_mac(int raw_sock, char* iface_name) {

    char* mac_address = malloc(6 * sizeof(char));

    struct ifreq iface_mac;

    memset(&iface_mac, 0, sizeof(iface_mac));
    strncpy(iface_mac.ifr_name, iface_name, IFNAMSIZ-1);

    if ((ioctl(raw_sock, SIOCGIFHWADDR, &iface_mac)) < 0) {
        fprintf(stderr, "ioctl() failed. (%d)\n", errno);
        exit(1);
    }

    for (int i = 0; i < 6; i++) {
        mac_address[i] = iface_mac.ifr_hwaddr.sa_data[i];
    }
    
    return mac_address;

}
