#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <netinet/ip_icmp.h> 
#include <time.h> 
#include <fcntl.h> 
#include <signal.h> 
#include <time.h>
#define PING_PKT_S 64
#define PORT_NO 0
struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PKT_S-sizeof(struct icmphdr)];
};
unsigned short checksum(unsigned short *b, int len) {
        unsigned short *buf = b;
        unsigned int sum = 0;
        unsigned short result;
        for ( sum = 0; len > 1; len -= 2 ) {
                sum += *buf++;
        }
        if ( len == 1 ) {
                sum += *(unsigned char*)buf;
        }
        sum = (sum >> 16) + (sum & 0xFFFF);
        sum += (sum >> 16);
        result = ~sum;
        return result;
}
int ttl_val = 64;
struct ping_pkt icmp_pckt;
char *dst_addr = "1.1.1.1";
int sockfd;
int main (int argc, char *argv[]) {
struct sockaddr_in dst_addr_s;
memset(&dst_addr_s, 0, sizeof(dst_addr_s));
dst_addr_s.sin_family = AF_INET;
dst_addr_s.sin_port = htons (PORT_NO);
dst_addr_s.sin_addr.s_addr = inet_addr("1.1.1.1");
int i = 0;
socklen_t sock_len;
u_int16_t msg_count = 1;
struct timeval timeout;
timeout.tv_sec = 1;
timeout.tv_usec = 0;
sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 
if (sockfd < 0) 
{ 
	printf("%s\n", "Socket file descriptor not received"); 
	return 100; 
}
if (setsockopt(sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0) {
	printf("%s\n", "Can not set TTL socket option");
	return 101;
}
if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) != 0) {
        printf("%s\n", "Can not set timeout socket option");
        return 102;
}
memset(&icmp_pckt, 0, sizeof(icmp_pckt));
icmp_pckt.hdr.type = ICMP_ECHO;
icmp_pckt.hdr.un.echo.id = getpid();
memset(&icmp_pckt.msg, 0, sizeof(icmp_pckt.msg));
icmp_pckt.msg[i] = 0;
icmp_pckt.hdr.un.echo.sequence = htons(msg_count++);
icmp_pckt.hdr.checksum = checksum((unsigned short *)&icmp_pckt.hdr, sizeof(icmp_pckt));
if (sendto(sockfd, &icmp_pckt, sizeof(icmp_pckt), 0, (struct sockaddr *) &dst_addr_s, sizeof(dst_addr_s)) <= 0) {
	printf("%s\n", "Sent failed and error is: ");
	perror("sendto error");
}
struct sockaddr_in r_addr;
sock_len = sizeof(r_addr);
if (recvfrom(sockfd, &icmp_pckt, sizeof(icmp_pckt), 0, (struct sockaddr *) &r_addr, &sock_len) < 0)  
        { 
            printf("\nPacket receive failed!\n");
	    perror("recvfrom error: ");
        } 
return 0;
}
