#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>

// https://www.jianshu.com/p/cbb3e21ef685

char *get_local_ip() {
    struct ifaddrs *ifaddr, *ifa;
    int family;
    char *ip;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;
        if (!strstr(ifa->ifa_name, "en"))
            continue;

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET) {
            ip = inet_ntoa(((struct sockaddr_in *) ifa->ifa_addr)->sin_addr);
            if (strlen(ip) > 0) {
                return ip;
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    char *ip;
    ip = get_local_ip();
    printf("%s", ip);
}
