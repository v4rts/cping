#include <netinet/in.h> 
int create_socket();
int sendrecv_icmp(in_addr_t dst_addr, int sockfd);