// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
#include "../include/includes.h"
#include "../include/get_raw_socket.h"
#include "../include/get_and_print_iface_info.h"

int main(int argc, char* argv[]) {
    
    char* iface_arg = argv[1]; // Need to validate

    int raw_sock = get_raw_socket();
    struct iface_info iface;
    strncpy(iface.name, iface_arg, strlen(iface_arg)+1);

    get_and_print_iface_info(raw_sock, &iface);

    // Craft ethernet packets.
    unsigned char* sendbuff = malloc(64);
    memset(sendbuff, 0, 64);

    struct ethhdr *eth = (struct ethhdr*) (sendbuff);

    printf("Source MAC: ");
    for (int i = 0; i < 6; i++) {
        eth->h_source[i] = (unsigned char) (iface.mac[i]);
        printf("%.2x ", eth->h_source[i]);
    }
    printf("\n");

    printf("Destination MAC: ");
    for (int i = 0; i < 6; i++) {
        eth->h_dest[i] = 0xff;
        printf("%.2x ", eth->h_dest[i]);
    }
    printf("\n");

    eth->h_proto = htons(ETH_P_IP);

    int total_len = sizeof(struct ethhdr);

    struct sockaddr_ll sadr_ll;
    sadr_ll.sll_ifindex = iface.index;
    sadr_ll.sll_halen = ETH_ALEN;
    for (int i = 0; i < 6; i++) {
        sadr_ll.sll_addr[i] = 0xff;
    }

    printf("sending...\n");
    int send_len = sendto(raw_sock, sendbuff, 64, 0, (const struct sockaddr*) &sadr_ll, sizeof(struct sockaddr_ll));

    free(sendbuff);

    close(raw_sock);

    return 0;

}

