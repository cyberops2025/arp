#include "../include/includes.h"
#include "../include/get_and_print_iface_info.h"
#include "../include/get_iface_index.h"
#include "../include/get_iface_mac.h"
#include "../include/print_mac.h"
#include "../include/get_iface_ip.h"

void get_and_print_iface_info(int raw_sock, char* iface_name) {

    int iface_index = get_iface_index(raw_sock, iface_name);
    printf("Interface Index = %d\n", iface_index);

    unsigned char* iface_mac = get_iface_mac(raw_sock, iface_name);
    print_mac(iface_mac);
    free(iface_mac);

    char* ip_address = get_iface_ip(raw_sock, iface_name);
    printf("Interface IP Address = %s\n", ip_address);
    free(ip_address);

}

