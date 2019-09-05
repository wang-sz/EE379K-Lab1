#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 12000
#define BUFSIZE 1024

int main(int argc, char **argv)
{
  int client_socket_fd;
  struct sockaddr_in server_addr;
  char *message = "Input lowercase sentence:";
  char buf[BUFSIZE]; // data buffer
  int byte_size;

  if((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("ERROR opening socket");
    exit(EXIT_FAILURE);
  }

  // establish server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  if(inet_pton(AF_INET, "127.0.0.2", &server_addr.sin_addr) <= 0)
  {
    perror("ERROR converting address");
    exit(EXIT_FAILURE);
  }

  if(connect(client_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("ERROR connecting to server");
    exit(EXIT_FAILURE);
  }

  if((byte_size = write(client_socket_fd, message, strlen(message))) < 0)
  {
    perror("ERROR writing to socket");
    exit(EXIT_FAILURE);
  }

  bzero(buf, BUFSIZE);
  if((byte_size = read(client_socket_fd, buf, BUFSIZE)) < 0)
  {
    perror("ERROR reading from socket");
    exit(EXIT_FAILURE);
  }

  printf("From Server:%s\n", buf);
}