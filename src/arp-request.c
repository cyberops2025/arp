// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
#include "../include/includes.h"
#include "../include/get_raw_socket.h"
#include "../include/get_and_print_iface_info.h"

void create_eth_header(struct iface_info* iface, unsigned char* sendbuff);
void send_packet(int raw_sock, struct iface_info* iface, unsigned char* sendbuff); 

int main(int argc, char* argv[]) {
    
    char* iface_arg = argv[1]; // Need to validate

    int raw_sock = get_raw_socket();
    struct iface_info iface;
    strncpy(iface.name, iface_arg, strlen(iface_arg)+1);
    get_and_print_iface_info(raw_sock, &iface);

    unsigned char* sendbuff = malloc(64);
    memset(sendbuff, 0, 64);
    create_eth_header(&iface, sendbuff); 
    send_packet(raw_sock, &iface, sendbuff);
    free(sendbuff);

    close(raw_sock);

    return 0;

}

void create_eth_header(struct iface_info* iface, unsigned char* sendbuff) {
    
    struct ethhdr *eth = (struct ethhdr*) (sendbuff);
    for (int i = 0; i < 6; i++) {
        eth->h_source[i] = (unsigned char) (iface->mac[i]);
    }
    for (int i = 0; i < 6; i++) {
        eth->h_dest[i] = 0xff;
    }
    eth->h_proto = htons(ETH_P_IP);

}

void send_packet(int raw_sock, struct iface_info* iface, unsigned char* sendbuff) {
    
    struct sockaddr_ll sadr_ll;
    sadr_ll.sll_ifindex = iface->index;
    sadr_ll.sll_halen = ETH_ALEN;
    for (int i = 0; i < 6; i++) {
        sadr_ll.sll_addr[i] = 0xff;
    }

    printf("sending...\n");
    sendto(raw_sock, sendbuff, 64, 0, (const struct sockaddr*) &sadr_ll, sizeof(struct sockaddr_ll));

}

