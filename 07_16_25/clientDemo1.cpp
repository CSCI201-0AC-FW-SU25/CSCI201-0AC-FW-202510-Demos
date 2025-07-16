#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>

void resetStream();

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *servinfo;
    char s[INET_ADDRSTRLEN];
    int rv;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket

    if (argc != 2)
    {
        std::cerr << "Usage: ./client <server ip address>" << std::endl;
        return 1;
    }

    try
    {
        rv = getaddrinfo(argv[1], "9431", &hints, &servinfo);
        if (rv != 0)
        {
            throw std::runtime_error("getaddrinfo error ");
        }
        int sock;
        sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
        if (sock == -1)
        {
            throw std::logic_error("Unable to open socket");
        }
        inet_ntop(servinfo->ai_family, (struct sockaddr_in *)servinfo->ai_addr, s, sizeof(s));
        std::cout << "client: attempting connection to " << s << std::endl;
        rv = connect(sock, servinfo->ai_addr, servinfo->ai_addrlen);
        if (rv == -1)
        {
            close(sock);
            throw std::logic_error("Unable to connect client");
        }
        inet_ntop(servinfo->ai_family, (struct sockaddr_in *)servinfo->ai_addr, s, sizeof(s));
        std::cout << "client: connected to " << s << std::endl;

        int input = 0;
        std::cout << "Enter the starting number: ";
        std::cin >> input;
        while (!std::cin)
        {
            resetStream();
            std::cout << "Enter the starting number: ";
            std::cin >> input;
        }
        uint32_t val = static_cast<uint32_t>(input);
        val = htonl(val);
        rv = send(sock, &val, sizeof(val), 0);
        if (rv == -1)
        {
            close(sock);
            throw std::logic_error("Client is unable to send");
        }
        int numbytes = recv(sock, &val, sizeof(val), 0);
        if (numbytes == -1)
        {
            close(sock);
            throw std::logic_error("Client is unable to receive");
        }
        val = ntohl(val);
        std::cout << "Server Response: " << val << std::endl;
        close(sock);
    }
    catch (std::runtime_error e)
    {
        std::cerr << e.what() << gai_strerror(rv) << std::endl;
    }
    catch (std::logic_error e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}