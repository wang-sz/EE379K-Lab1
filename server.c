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

int main(int argc, char **argv) {
  int server_socket_fd; // listening server socket
  int conn_socket_fd; // connection socket
  struct sockaddr_in server_addr; // server's address
  struct sockaddr_in client_addr; // client's address
  char buf[BUFSIZE]; // data buffer
  int optval; // flag val for setsockopt
  int byte_size; // message byte size

  server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if((server_socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    perror("ERROR opening socket");
    exit(EXIT_FAILURE);
  }

  optval = 1;
  setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // associate listening socket to port
  bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(server_socket_fd, 1); // allow 1 request
  // if(listen(server_socket_fd, 1) < 0) {
  //   perror("ERROR on listen");
  // }

  printf("The server is ready to receive");

  while(1) {
    // wait for connection request
    conn_socket_fd = accept(server_socket_fd, (struct sockaddr *)&client_addr.sin_addr.s_addr, sizeof(client_addr));
    printf(client_addr.sin_addr.s_addr);
    printf(conn_socket_fd, client_addr.sin_port);

    // clear buffer and read from client
    bzero(buf, BUFSIZE);
    byte_size = read(conn_socket_fd, buf, BUFSIZE);
    if(byte_size < 0) {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
    }

    // convert to all uppercase and send to client
    to_upper(buf);
    byte_size = write(conn_socket_fd, buf, BUFSIZ);
    if(byte_size < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
    }
  }

}

void to_upper(char s[]) {
  int i = 0;
  while(s[i] != '\0') {
    if(s[i] >= 'a' && s[i] <= 'z') {
      s[i] = s[i] - 32;
    }
    i++;
  }
}