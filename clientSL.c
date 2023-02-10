#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //for close()

int main(int argc, char *argv[])
{
int client_socket;
struct sockaddr_in server_address;
int window_size;
int frame=0;
int ACK;
int val;
int i, count;
char sentdata[50];
char recvdata[50];


client_socket = socket(AF_INET, SOCK_STREAM, 0);

server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080);
server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

//connect() instead of recv()
connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

printf("Enter the Window Size\n");
scanf("%d",&window_size);
send(client_socket,&window_size,sizeof(window_size),0);

while(frame<window_size)
{
    for(i=0;i<window_size;i++)
    {
        printf("Transmitted Frames to the server %d\n", frame);
        send(client_socket, &frame,sizeof(frame),0);
        frame++;
        if(frame==window_size)
            break;
    }
    recv(client_socket,&ACK,sizeof(ACK),0);
    printf("The negative Acknowledgement received from the server is %d\n", ACK);
    if(ACK==window_size)
    break;
    else frame=ACK;
}

while(1)
{
    printf("\n\nEnter Frame Number : ");
    scanf("%d", &val);
    send(client_socket, &val,sizeof(val),0);
    printf("Enter data: ");
    scanf("%s", sentdata);
    send(client_socket,sentdata,strlen(sentdata),0);
    if(strcmp(sentdata,"end")==0)
    break;
    recv(client_socket, &count,sizeof(count),0);
    i=recv(client_socket,recvdata,50,0);
    recvdata[i]='\0';
    printf("\n %s %d", recvdata,count);

}

close(client_socket);
return 0;
}
