#include "utils/errors.h"
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "utils/utils.h"
#include <arpa/inet.h>
#include "utils/validate_ip.h"
#include "utils/validate_args.h"
#include <string>

int main (int argc, char *argv[]) {
        bool is_dnsname = false; // Boolean for check if dns name promted or ip address
        bool valid_args = false; // Boolean for check if args are valid
        struct sockaddr_in sa;   // Stuct which holds ip address. More in netinet/in.h. https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
        struct hostent *he;      // Stuct which holds ip info from gethostbyname. More in netdb.h. https://www.gta.ufrj.br/ensino/eel878/sockets/gethostbynameman.html
        int sockfd;
        in_addr_t dst_addr;
        bool verbose_output;
        char *dst_hostname;
        char *dst_ip;

        printf("%s\n", "Ping starts");
        if (argc < 2) {
                printf("%s\n", "You have not specified address to send ICMP packets");
                exit(NO_ADDR);
        }
        printf("%s\n", "Validate other args");
        valid_args = validate_args(&is_dnsname, &dst_hostname, &dst_ip ,argc, argv, &verbose_output);
        
        printf("%s\n", "Check if next arg is dns name or ip address");

        printf("%s\n","----------------Validation results----------------");
        printf("%s","verbose output: ");
        printf("%d\n", verbose_output);
        printf("%s","is hostname: ");
        printf("%d\n", is_dnsname);
        printf("%s","hostname: ");
        if (is_dnsname){
                printf("%s\n",dst_hostname); 
        } else {
                printf("%s\n", "-");
        }
        printf("%s","ip: ");
        if (dst_ip){
                 printf("%s\n",dst_ip); 
        } else {
                printf("%s\n", "-");
        }
        
        printf("%s\n","--------------------------------------------------");
        
        if (!valid_args) {
                printf("%s\n", "Args are not valid. More complex output will be in validate_args function. Program will exit now!");
                exit(ARGS_NOT_VALID);
        }


        if (is_dnsname) {
                he = gethostbyname(dst_hostname);
        }
        if (validateIP(dst_ip)) {
                printf("%s\n", "IP address is valid. Continuing");
        } else {
                printf("%s\n", "IP address is invalid. Program will exit now");
                exit(IP_NOT_VALID);
        }
        dst_addr = inet_addr(argv[1]);
        sockfd = create_socket();
        int result = sendrecv_icmp(dst_addr, sockfd);
        // Next will be inet_pton(AF_INET, "1.1.1.1", &(sa.sin_addr));
        return 0;
}
