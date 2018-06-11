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
  fprintf(stderr, "Welcome! This is the server!\n");
  
  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening for new connections...\n");
  else
    printf("Error\n");
  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  int i = 0;

  while(i<5){
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    /*---- Send message to the socket of the incoming connection ----*/
    
    struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&serverStorage;
    struct in_addr ipAddr = pV4Addr->sin_addr;
    char nameip[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &ipAddr, nameip, INET_ADDRSTRLEN );
    fprintf(stderr, "New client connected: %s\n", nameip);
    int counter = 0;
    while (counter >= 0) {
      fprintf(stderr, "Write new command:\n");
      char command[50];
      fgets(command, 50, stdin);
      int result = send(newSocket, command, strlen(command), 0);
      if(strcmp("close\n", command) == 0 ||result < 0)
      {
        fprintf(stderr, "Closing connection...");
        break;
      }
      counter++;
    }
    i++;
    close(newSocket);
    fprintf(stderr, "Closed.\n");
  }
  close(welcomeSocket);

  return 0;
}