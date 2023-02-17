//CLIENT---------------------------------------------------------------------------------------
//This code is contributed by Anas Jawed
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int csd,sock,i,count,val,clilen,cport=6000;
    char sentdata[50],recvdata[50];
    int window_size, frame=0, ACK;
    sock = socket(AF_INET,SOCK_STREAM,0);

	if(sock<0)
		printf("cant create\n");
	else
		printf("Client's 'Socket is created\n");
	struct sockaddr_in  servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(cport);
	
	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		printf("cant connect\n");
	else
		printf("connected\n"); 

    printf("Enter the Window Size\n");
    scanf("%d",&window_size);
    send(sock,&window_size,sizeof(window_size),0);

    while(frame<window_size){
        for(i=0;i<window_size;i++){
            printf("Transmitted Frames to the Server %d\n",frame);
            send(sock,&frame,sizeof(frame),0);
            frame++;
            if(frame == window_size)
                break;
        }
        recv(sock,&ACK,sizeof(ACK),0);
        printf("The negative Acknowledgement recieved from the server is %d\n",ACK);
        if(ACK == window_size)
            break;
        else
            frame = ACK;
    }    
    return 0;
}
