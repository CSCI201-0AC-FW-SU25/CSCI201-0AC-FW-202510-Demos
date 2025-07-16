#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <bits/stdc++.h>

const int BACKLOG = 10;

int main(int argc, char *arv[])
{
    int sockfd, clientfd;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    int yes = 1;
    char s[INET_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_flags = AI_PASSIVE;     // use my IP

    try
    {
        rv = getaddrinfo(NULL, "9431", &hints, &servinfo);
        if (rv != 0)
        {
            throw std::runtime_error("getaddrinfo error");
        }
        sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
        if (sockfd == -1)
        {
            throw std::invalid_argument("There was an error creating the socket");
        }
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        rv = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
        if (rv == -1)
        {
            close(sockfd);
            throw std::invalid_argument("Server is unable to bind");
        }
        rv = listen(sockfd, BACKLOG);
        if (rv == -1)
        {
            throw std::invalid_argument("Server is unable to listen");
        }
        std::cout << "server: waiting for connections..." << std::endl;
        while (true)
        {
            sin_size = sizeof(their_addr);
            clientfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
            if (clientfd == -1)
            {
                throw std::invalid_argument("Error accpeting client");
            }
            inet_ntop(their_addr.ss_family, (struct sockaddr_in *)&their_addr, s, sizeof(s));
            std::cout << "server: got connection from " << s << std::endl;
            uint32_t val;
            rv = recv(clientfd, &val, sizeof(val), 0);
            if (rv == sizeof(val))
            {
                val = ntohl(val);
                std::cout << "receiving: " << val << std::endl;
                val++;
                val = htonl(val);
                rv = send(clientfd, &val, sizeof(val), 0);
            }
            close(clientfd);
        }
    }
    catch (std::runtime_error e)
    {
        std::cerr << e.what() << " " << gai_strerror(rv) << std::endl;
    }
    catch (std::invalid_argument e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}