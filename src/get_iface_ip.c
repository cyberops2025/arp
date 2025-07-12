#include "../include/includes.h"
#include "../include/get_iface_ip.h"

char* get_iface_ip(int raw_sock, char* iface_name) {

    char* ip_address = malloc(100 * sizeof(char));

    struct ifreq iface_ip;

    memset(&iface_ip, 0, sizeof(iface_ip));
    strncpy(iface_ip.ifr_name, iface_name, IFNAMSIZ-1);

    if ((ioctl(raw_sock, SIOCGIFADDR, &iface_ip)) < 0) {
        fprintf(stderr, "ioctl() failed. (%d)\n", errno);
        exit(1);
    }

    char* temp = inet_ntoa(((struct sockaddr_in*) &(iface_ip.ifr_addr))->sin_addr);
    strncpy(ip_address, temp, strlen(temp));

    return ip_address;

}

