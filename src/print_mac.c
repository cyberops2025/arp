#include "../include/includes.h"
#include "../include/print_mac.h"

void print_mac(unsigned char* iface_mac) {

    printf("Interface MAC Address = ");
    for (int i = 0; i < 6; i++) {
        printf("%.2x ", iface_mac[i]);
    }
    printf("\n");
    
}

