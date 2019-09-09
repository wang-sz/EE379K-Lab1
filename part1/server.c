#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 12000
#define BUFSIZE 1024

void to_upper(char s[]);

int main(int argc, char **argv)
{
  int server_socket_fd; // listening server socket
  int conn_socket_fd; // connection socket
  struct sockaddr_in server_addr; // server's address
  struct sockaddr_in client_addr; // client's address
  int client_len; // size of client_addr
  char buf[BUFSIZE]; // data buffer
  int optval; // flag val for setsockopt
  int byte_size; // message byte size

  bzero(&server_socket_fd, sizeof(server_socket_fd));
  if((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("ERROR opening socket");
    exit(EXIT_FAILURE);
  }


  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

  // associate listening socket to port
  bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // allow 1 request
  if((listen(server_socket_fd, 1)) < 0)
  {
    perror("ERROR on listen");
    exit(EXIT_FAILURE);
  }

  printf("The server is ready to receive\n");

  client_len = sizeof(client_addr);

  while(1)
  {
    // wait for connection request
    conn_socket_fd = accept(server_socket_fd, (struct sockaddr *)&client_addr, &client_len);
    printf("(\'%s\', %d)\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

    // clear buffer and read from client
    bzero(buf, BUFSIZE);
    if((byte_size = read(conn_socket_fd, buf, BUFSIZE)) < 0)
    {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
    }
    // printf("Received:%s\n", buf);

    // convert to all uppercase and send to client
    to_upper(buf);
    // printf("Send:%s\n", buf);
    if((byte_size = write(conn_socket_fd, buf, strlen(buf))) < 0)
    {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
    }
  }

}

void to_upper(char s[])
{
  int i = 0;
  while(s[i] != (char)'\0')
  {
    if(s[i] >= 'a' && s[i] <= 'z')
    {
      s[i] = s[i] - 32;
    }
    i++;
  }
}