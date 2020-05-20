#include <unistd.h> 
#include <iostream> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 


#define PORT 8080
using namespace std;
int main(int argc, char const *argv[]) 
{ 
    int server_fd, valread; 
    struct sockaddr_in servaddr,cliaddr; //IPV4 address is stored in sockaddr_in,
    int opt = 1; 
   // int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 

       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) <0) //IPV4 socket AF_INET
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }
	
    memset(&servaddr,0,sizeof(servaddr));
	memset(&cliaddr,0,sizeof(cliaddr));
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY; //ip address of 127.0.0.1
    servaddr.sin_port = htons( PORT );   
	
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
	
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&servaddr,  
                                 sizeof(servaddr))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
	int n;
	socklen_t len;
	len=sizeof(cliaddr);   
    while(1)
    {
	cout << " waiting to recieve the data..............." << endl;
	n = recvfrom(server_fd, (char *)buffer,1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                (socklen_t*)&len);  
    buffer[n] = '\0'; 
    

	cout << buffer << endl;
	sendto(server_fd, (const char *)buffer, strlen(buffer),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
             len);  

	cout << "Packet sent" << endl;
    }
    return 0; 
}  
