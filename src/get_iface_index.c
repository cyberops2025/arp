#include "../include/includes.h"
#include "../include/get_iface_index.h"

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

