#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>     // Necessário para o strncpy
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>     // Onde a struct ifreq vive
#include <unistd.h>

#include <linux/if.h>
#include "cap_sdk_defs.h"


int wifi_set_power(wifi_state_t state)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0 /*TCP*/ );
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(ifr));

    //strncpy(ifr.ifr_ifrn.ifrn_name, "wlan0", IFNAMSIZ - 1);
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);
   
    if(ioctl(sock, SIOCGIFFLAGS, &ifr) < 0){
        close(sock);
        return RET_NOTOK;
    }

    switch (state)
    {
    case WIFI_ON:
        ifr.ifr_ifru.ifru_flags |= (IFF_UP | IFF_RUNNING | IFF_DEBUG);
        break;
    case WIFI_OFF:
        ifr.ifr_ifru.ifru_flags &= ~IFF_UP;
        break;
    default:
        return RET_INVALID_PARAMS;
        break;
    }
   
    if(ioctl(sock, SIOCSIFFLAGS, &ifr) < 0){
        close(sock);
        return RET_NOTOK;
    }else {
        close(sock);
        return RET_OK;
    }
}

int wifi_get_info(wifi_info_t info, char *output)
{

    // https://gist.github.com/cedriczirtacic/e631a8e7facbf725659ba667ad3e6642
    // https://www.geeksforgeeks.org/c/socket-programming-cc/

    struct ifreq ifr;
    int socket_client = socket(AF_INET, SOCK_DGRAM, 0);

    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);

    switch (info)
    {
    case WIFI_MACADDRESS:
        ioctl(socket_client, SIOCGIFHWADDR, &ifr);

        unsigned char *mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        sprintf(output, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        break;
    case WIFI_IP:
        ioctl(socket_client, SIOCGIFADDR, &ifr);

        struct sockaddr_in *pV4Addr = (struct sockaddr_in *)&ifr.ifr_ifru.ifru_addr;
        struct in_addr ipAddr = pV4Addr->sin_addr;

        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
        sprintf(output, "%s", str);
        break;
    default:
        break;
    }

    close(socket_client);
    return RET_OK;

    /*
     * NETWORK STACK TERMINOLOGY & LOGIC:
     * struct ifreq: A standard interface request buffer used to exchange data between user-space and the kernel network stack.
     *
     * socket(AF_INET, SOCK_DGRAM, 0): Opens a UDP socket handle. Not used for traffic here, but as a control interface (File Descriptor) to query the NIC driver.
     *
     * ioctl(fd, request, &ifr): Input/Output Control system call. It requests hardware-specific information (like MAC or IP) and populates the ifreq structure.
     *
     * struct sockaddr_in: An IPv4-specific address structure. Used to cast generic socket address data into readable IP fields.
     *
     * struct in_addr: A sub-structure containing the 32-bit IPv4 address in Network Byte Order (Big-endian).
     *
     * inet_ntop(): "Network to Presentation". Converts raw binary network bytes into a human-readable ASCII string (e.g., "192.168.1.1").
     */

}