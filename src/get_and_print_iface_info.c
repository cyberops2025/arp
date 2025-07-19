#include "../include/includes.h"
#include "../include/get_and_print_iface_info.h"
#include "../include/get_iface_index.h"
#include "../include/get_iface_mac.h"
#include "../include/print_mac.h"
#include "../include/get_iface_ip.h"

void get_and_print_iface_info(int raw_sock, struct iface_info* iface) {

    get_iface_index(raw_sock, iface);
    printf("Interface Index = %d\n", iface->index);

    get_iface_mac(raw_sock, iface);
    print_mac(iface->mac);

    get_iface_ip(raw_sock, iface);
    printf("Interface IP Address = %s\n", iface->ip);

}

