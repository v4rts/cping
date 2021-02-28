#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
int main (int argc, char *argv[]) {
        bool is_dnsname = false;
        bool valid_args = false;
        struct sockaddr_in sa;
        struct hostent *he;
        printf("%s\n", "Ping starts");
        if (argc < 2) {
                printf("%s\n", "You have not specified adress to send ICMP packets");
                exit(137);
        }
        printf("%s\n", "Validate other args");
        // valid_args = validate_args();
        if (!valid_args) {
                printf("%s\n", "Args are not valid. More complex output will be in validate_args function. Program will exit now!");
                exit(100);
        }
        printf("%s\n", "Check if next arg is dns name or ip address");
        // is_dnsname = check_arg();
        if (is_dnsname) {
                he = gethostbyname(argv[1]);
        }
        // Next will be inet_pton(AF_INET, "1.1.1.1", &(sa.sin_addr));
        return 0;
}
