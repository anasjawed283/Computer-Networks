//SERVER------------------------------------------------------------------------
//This code is contributed by Anas Jawed
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(){
	int sd,sd2,client_socket,count=0,val,clilen,sport=6000,i,len,port;
    char data[50],senderdata[50];
    int window_size, frame=0, ACK;
	sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
		printf("cant create\n");
	else
		printf("Socket is created\n");
  
	struct sockaddr_in  servaddr;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(sport);
	sd2 = bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	if(sd2<0)
		printf("cant bind\n");
	else
		printf("Binded\n"); 

    listen(sd,5);

    struct sockaddr_in cliaddr;
    clilen = sizeof(cliaddr);
    client_socket = accept(sd,(struct sockaddr*)&cliaddr,&clilen);
    if(client_socket<0)
        printf("can't accept\n");
    else
        printf("accepted\n");
    
    recv(client_socket,&window_size,sizeof(window_size),0);
    while(frame<window_size){
        for(i=0;i<window_size;i++){
            recv(client_socket,&frame,sizeof(frame),0);
            printf("Transmitted Frames Recieved from Client is %d\n",frame);
            frame++;
            if(frame==window_size)
                break;
        }
        printf("Enter the negative Acknowledgement to be sent to the client\n");
        scanf("%d",&ACK);
        send(client_socket,&ACK,sizeof(ACK),0);
        if(ACK == window_size)
            break;
        else
            frame = ACK;

    }
    return 0;	
}
