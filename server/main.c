/****************** SERVER CODE ****************/
//codice riccardo
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  int opt_val = 1;
  setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  /*---- Bind the address struct to the socket ----*/
  int err = bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  
  if (err < 0) fprintf(stderr, "Could not bind socket\n");

  fprintf(stderr, "Passato\n");
  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

    fprintf(stderr, "In attesa\n");
  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  int i = 0;

  while(i<5){
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    /*---- Send message to the socket of the incoming connection ----*/
    char command[50];
    fgets(command, 50, stdin);
    fprintf(stderr, "%d\n", strlen(command));
    send(newSocket, command, strlen(command), 0);
    i++;
    close(newSocket);
  }
  close(welcomeSocket);

  return 0;
}