#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
struct hostent *he;
struct in_addr **addr_list;
struct in_addr addr;
extern int h_errno;
int my_gethostbyname(char *dnsname) {
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
		return 100;
	}
	printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
	return 0;
}
int main(int argc, char *argv[]) {
	int resolved = my_gethostbyname(argv[1]);
	if (resolved != 0) {
		printf("%s\n", "Error occured while resolving dns name. Program will exit now!");
		exit(1);
	}
	exit(0);
}
