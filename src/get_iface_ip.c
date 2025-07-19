#include "../include/includes.h"
#include "../include/get_iface_ip.h"

void get_iface_ip(int raw_sock, struct iface_info* iface) {

    struct ifreq iface_ip;

    memset(&iface_ip, 0, sizeof(iface_ip));
    strncpy(iface_ip.ifr_name, iface->name, IFNAMSIZ-1);

    if ((ioctl(raw_sock, SIOCGIFADDR, &iface_ip)) < 0) {
        fprintf(stderr, "ioctl() failed. (%d)\n", errno);
        exit(1);
    }

    char* temp = inet_ntoa(((struct sockaddr_in*) &(iface_ip.ifr_addr))->sin_addr);
    strncpy(iface->ip, temp, strlen(temp)+1);

}

