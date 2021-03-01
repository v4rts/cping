#include "icmp_sendrecv.h"
#include "calc_checksum.h"
#include <errno.h>
struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PKT_S-sizeof(struct icmphdr)];
};
int sendrecv_icmp(in_addr_t dst_addr, int sockfd) {
        struct ping_pkt icmp_pckt;
        memset(&dst_addr_s, 0, sizeof(dst_addr_s));
        dst_addr_s.sin_family = AF_INET;
        dst_addr_s.sin_port = htons(PORT_NO);
        dst_addr_s.sin_addr.s_addr = dst_addr;
        int i = 0, msg_count = 0;
        memset(&icmp_pckt, 0, sizeof(icmp_pckt));
        icmp_pckt.hdr.type = ICMP_ECHO;
        icmp_pckt.hdr.un.echo.id = getpid();
        memset(&icmp_pckt.msg, 0, sizeof(icmp_pckt.msg));
        icmp_pckt.msg[i] = 0;
        icmp_pckt.hdr.un.echo.sequence = htons(msg_count++);
        icmp_pckt.hdr.checksum = checksum((unsigned short *)&icmp_pckt.hdr, sizeof(icmp_pckt));
        if (sendto(sockfd, &icmp_pckt, sizeof(icmp_pckt), 0, (struct sockaddr *) &dst_addr_s, sizeof(dst_addr_s)) <= 0) {
                printf("%s\n", "Sent failed and error is: ");
                perror("");
                return(SENT_FAILED);
        }
        char dst_addr_str[256];
        inet_ntop(AF_INET, &dst_addr, dst_addr_str, sizeof(dst_addr_str));
        printf("%s%s\n", "Successfully sent packet to ", dst_addr_str);
        sock_len = sizeof(r_addr);
        if (recvfrom(sockfd, &icmp_pckt, sizeof(icmp_pckt), 0, (struct sockaddr *) &r_addr, &sock_len) < 0) {
                if (errno == EAGAIN) {
                        printf("%s\n", "Receive timeout exceeded");
                }
                return(RCV_FAILED);
        } 
        printf("%s%s\n", "Successfully received packet from ", dst_addr_str);
        return 0;
};
