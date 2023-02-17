//Code is contributed by Anas Jawed
//server
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int sd, sd2, clilen,sport,i,connect,count=0,val;
    int port;
    char data[50], senderdata[50];
    struct sockaddr_in servaddr,cliaddr;
    printf("enter the server port\n");
    scanf("%d\n",&sport);
    printf("%d\n",sport);
    sd=socket(AF_INET,SOCK_STREAM,0);
    if(sd<0)
            printf("can't create\n");
    else
            printf("socket created\n");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(sport);
    sd2=bind(sd,(struct sockaddr*)&servaddr, sizeof(servaddr));
    if(sd2<0)
            printf("can't bind\n");
    else
            printf("binded\n");
    listen(sd,5);
    
    clilen=sizeof(cliaddr);
    connect=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
    if(connect<0)
        printf("can't accept\n");
    else
        printf("Accepted\n");
    
    while(1){
        recv(connect,&val,sizeof(val),0);
        i=recv(connect,&data,sizeof(data),0);
        data[i]='\0';
        if(strcmp(data,"end")==0){
            printf("\n\t Finished");
            break;
        }
        if(count!=val){
            strcpy(senderdata,"frame missing");
            send(connect,&count,sizeof(count),0);
            send(connect,senderdata,strlen(senderdata),0);
        }
        else{
            printf("\n The frame number is:%d",val);
            printf("\n the data is: %s", data);
            count++;
            strcpy(senderdata,"send nextdata");
            send(connect,&count,sizeof(count),0);
            send(connect,senderdata,strlen(senderdata),0);
        }
        printf("\n The expected frame now is:  %d\n",count);
    }
    return 0;
}
