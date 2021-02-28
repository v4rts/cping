#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
struct hostent *he;
struct in_addr **addr_list;
struct in_addr addr;
extern int h_errno;
char *my_gethostbyname(char *dnsname) {
	char *ip=(char*)malloc(NI_MAXHOST*sizeof(char)); 
	he = gethostbyname(dnsname);
	if (he == NULL) {
		switch(h_errno) {
			case HOST_NOT_FOUND:
				printf("%s\n", "Hostname not found");
				break;
			case NO_ADDRESS:
				printf("%s\n", "The requested hostname exists but does not have an IP address");
				break;
			case NO_RECOVERY:
				printf("%s\n", "Fatal name server error");
				break;
			case TRY_AGAIN:
				printf("%s\n", "Temporary error on the DNS server. Please try again later");
				break;
		}
		return NULL;
	}
	strcpy(ip, inet_ntoa(*(struct in_addr *) he->h_addr)); 
	return ip;
}
int main(int argc, char *argv[]) {
	char *resolved = my_gethostbyname(argv[1]);
	if (resolved == NULL) {
		printf("%s\n", "Error occured while resolving dns name. Program will exit now!");
		exit(1);
	}
	printf("%s\n", resolved);
	exit(0);
}
