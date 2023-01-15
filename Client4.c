#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>
int main()
{
    int csd,nsd,clilen,cport=6000;

    char revmsg[100];

    int len,check=1;
    csd = socket(AF_INET,SOCK_STREAM,0);

    if(csd<0)
        printf("Can't create\n");
    else
        printf("Client's socket is created\n");

    struct sockaddr_in  servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(cport);

    nsd = connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    if(nsd<0)
        printf("Can''t connect\n");
    else
        printf("Connected\n");

 

    char sendmsg[100];
    while(strcmp(revmsg,"BYE"))
   {

 

    fgets(sendmsg,20,stdin);
    len = strlen(sendmsg);
    sendmsg[len-1]='\0';
    send(csd,sendmsg,20,0);
    recv(csd,revmsg,20,0);
    printf("Server msg: %s\n",revmsg);

}

    printf("Chat Terminated\n");
    close(csd);
    return 0;
}
