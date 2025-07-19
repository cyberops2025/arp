#include "../include/includes.h"
#include "../include/get_iface_mac.h"

void get_iface_mac(int raw_sock, struct iface_info* iface) {

    struct ifreq iface_mac;

    memset(&iface_mac, 0, sizeof(iface_mac));
    strncpy(iface_mac.ifr_name, iface->name, IFNAMSIZ-1);

    if ((ioctl(raw_sock, SIOCGIFHWADDR, &iface_mac)) < 0) {
        fprintf(stderr, "ioctl() failed. (%d)\n", errno);
        exit(1);
    }

    for (int i = 0; i < 6; i++) {
        iface->mac[i] = iface_mac.ifr_hwaddr.sa_data[i];
    }
    
}

