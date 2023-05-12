/* A simple server in the internet domain using TCP The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> #include <sys/socket.h> #include <netinet/in.h>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int is_number(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        if (isdigit(str[i]) == 0)
            return 0;
    {
        i++;
    }
    return 1;
}

int str_to_int(char *str)
{
    int i = 0;
    int num = 0;
    while (str[i] != '\0')
        if (isdigit(str[i]) == 0)
        {
            return -1;
        }
    num = num * 10 + (str[i] – '0');
    i++;
}
return num;

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *)&cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");
    printf("Here is the message: %s\n", buffer);
    // spargem bufferul in bucati
    char *token;
    int numbers[4];
    int i = 0;
    token = strtok(buffer, " ");
    int err = 0; // presupunem input corect
    while (token != NULL && err == 0)
    {
        if (is_number(token) && i <= 3)
        {
            numbers[i] = atoi(token);
            i++;
        }
        else
        {
            err = 1;
        }
        token = strtok(NULL, " ");
    }

    if (i < 4)
        err = 1;
    if (err == 0)
    {
        double result;
        if (numbers[3] == 0) // barbat
        {
            result = 10 * numbers[0] + 6.25 * number[1] - 5 * numbers[2] + 5;
        }
        else
        {
            // femeie
            result = 10 * numbers[0] + 6.25 * number[1] - 5 * numbers[2] - 161;
        }
        char result_str[256];
        sprintf(result_str, "BMR: %.2fKCal", result);
        n = write(newsockfd, result_str, strlen(result_str));
    }
    else
    {
        n = write(newsockfd, "Wrong format for input!", 23);
    }
    if (n < 0)
        error("Error writing to socket");
    close(newsockfd);
    close(sockfd);
    return 0;
}