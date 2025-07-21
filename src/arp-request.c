// Found a useful resource here:
// https://www.opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
#include "../include/includes.h"
#include "../include/get_raw_socket.h"
#include "../include/get_and_print_iface_info.h"

struct udphdr* create_udp_header(int data);
struct iphdr* create_ip_header(struct iface_info* iface, struct udphdr* uh);
unsigned short checksum(unsigned short* buff, int _16bitword);
struct ethhdr* create_eth_header(struct iface_info* iface);
void send_packet(int raw_sock, struct iface_info* iface, unsigned char* sendbuff); 

int main(int argc, char* argv[]) {
    
    char* iface_arg = argv[1]; // Need to validate

    int raw_sock = get_raw_socket();
    struct iface_info iface;
    strncpy(iface.name, iface_arg, strlen(iface_arg)+1);
    get_and_print_iface_info(raw_sock, &iface);

    int data = 0x3713;
    int data_size = sizeof(data);
    //printf("data = %x, size = %d\n", data, data_size);

    int uh_size = sizeof(struct udphdr);
    struct udphdr* uh = create_udp_header(data);
    //printf("uh_size = %d\n", uh_size);

    int ih_size = sizeof(struct iphdr);
    struct iphdr* ih = create_ip_header(&iface, uh);
    //printf("ih_size = %d\n", ih_size);

    int eh_size = sizeof(struct ethhdr);
    struct ethhdr* eh = create_eth_header(&iface);
    //printf("eh_size = %d\n", eh_size);

    //printf("total_len = %d\n", data_size + uh_size + ih_size + eh_size);

    unsigned char* sendbuff = malloc(64);
    memset(sendbuff, 0, 64);
    memcpy(sendbuff, eh, eh_size);
    memcpy(sendbuff + eh_size, ih, ih_size);
    memcpy(sendbuff + eh_size + ih_size, uh, uh_size);
    memcpy(sendbuff + eh_size + ih_size + uh_size, &data, data_size);

    send_packet(raw_sock, &iface, sendbuff);

    free(eh);
    free(ih);
    free(uh);
    free(sendbuff);
    close(raw_sock);

    return 0;

}

struct udphdr* create_udp_header(int data) {

    int uh_size = sizeof(struct udphdr);
    struct udphdr* uh = malloc(uh_size);

    uh->source = htons(9001);
    uh->dest = htons(9002);
    uh->check = 0;
    uh->len = htons(uh_size + sizeof(data));
    //printf("uh_size = %d\n", uh_size);
    //printf("sizeof(data) = %ld\n", sizeof(data));
    //printf("uh->len = %d\n", uh->len);

    return uh;

}

struct iphdr* create_ip_header(struct iface_info* iface, struct udphdr* uh) {

    int ih_size = sizeof(struct iphdr);
    struct iphdr *ih = malloc(ih_size);

    ih->ihl = 5;
    ih->version = 4;
    ih->tos = 16;
    ih->id = htons(10201);
    ih->ttl = 64;
    ih->protocol = 17;
    ih->saddr = inet_addr(iface->ip);
    ih->daddr = inet_addr("192.168.0.255");
    ih->tot_len = htons(ih_size) + uh->len;

    //printf("ih_size = %d\n", ih_size);
    //printf("ih->tot_len = %d\n", ih->tot_len);
    //printf("ih_size + uh->len = %d\n", ih_size + uh->len);
    
    unsigned short* cs_arg1 = (unsigned short*) ih;
    int cs_arg2 = sizeof(struct iphdr) / 2;
    unsigned short chksum = checksum(cs_arg1, cs_arg2);

    ih->check = htons(chksum);

    return ih;

}

unsigned short checksum(unsigned short* buff, int _16bitword) {

    unsigned long sum;
    for (sum = 0; _16bitword > 0; _16bitword--) {
        sum += htons(*(buff)++);
    }

    do {
        sum = ((sum >> 16) + (sum & 0xFFFF));
    } while (sum & 0xFFFF0000);

    return (~sum);

}

struct ethhdr* create_eth_header(struct iface_info* iface) {
    
    int eh_size = sizeof(struct ethhdr);
    struct ethhdr *eh = malloc(eh_size);

    for (int i = 0; i < 6; i++) {
        eh->h_source[i] = (unsigned char) (iface->mac[i]);
    }

    for (int i = 0; i < 6; i++) {
        eh->h_dest[i] = 0xff;
    }

    eh->h_proto = htons(ETH_P_IP);

    return eh;

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

