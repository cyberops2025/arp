// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
#include "../include/includes.h"
#include "../include/get_raw_socket.h"

int get_iface_index(int raw_sock, char* iface_name);
unsigned char* get_iface_mac(int raw_sock, char* iface_name);
void print_mac(unsigned char* iface_mac);

int main(int argc, char* argv[]) {
    
    char* test_iface = argv[1]; // Need to validate

    int raw_sock = get_raw_socket();

    int iface_index = get_iface_index(raw_sock, test_iface);
    printf("Interface Index = %d\n", iface_index);

    unsigned char* iface_mac = get_iface_mac(raw_sock, test_iface);
    print_mac(iface_mac);
    free(iface_mac);

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

void print_mac(unsigned char* iface_mac) {

    printf("Interface MAC address = ");
    for (int i = 0; i < 6; i++) {
        printf("%.2x ", iface_mac[i]);
    }
    printf("\n");
    
}
