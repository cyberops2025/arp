// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
#include "../include/includes.h"
#include "../include/get_raw_socket.h"
#include "../include/get_iface_index.h"
#include "../include/get_iface_mac.h"
#include "../include/print_mac.h"

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

