#include "../include/includes.h"
#include "../include/get_iface_mac.h"

unsigned char* get_iface_mac(int raw_sock, char* iface_name) {

    unsigned char* mac_address = malloc(6 * sizeof(unsigned char));

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

