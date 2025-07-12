// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
#include "../include/includes.h"
#include "../include/get_raw_socket.h"
#include "../include/get_and_print_iface_info.h"

int main(int argc, char* argv[]) {
    
    char* test_iface = argv[1]; // Need to validate

    int raw_sock = get_raw_socket();
    get_and_print_iface_info(raw_sock, test_iface);

    // Craft ethernet packets.

    close(raw_sock);

    return 0;

}

