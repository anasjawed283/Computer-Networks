#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>
int main()
{
    int sd,sd2,nsd,clilen,sport=6000,len,port;

    int check=1;
    time_t ticks;
    sd = socket(AF_INET,SOCK_STREAM,0);

    if(sd<0)
        printf("Can't create\n");
    else
        printf("Socket is created\n");

    struct sockaddr_in  serveraddr;    
    struct sockaddr_in  servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);

    sd2 = bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    if(sd2<0)
        printf("Can't bind\n");
    else
        printf("Binded\n");

 

    listen(sd,5);

 

    struct sockaddr_in cliaddr;
    clilen = sizeof(cliaddr);
    nsd = accept(sd,(struct sockaddr*)&cliaddr,&clilen);
    if(nsd<0)
        printf("Can't accept\n");
    else
        printf("Accepted\n");

    printf("Client addres:%s",inet_ntoa(cliaddr.sin_addr));
    printf("\n");

   char sendmsg[100];char rcvmsg[100];
   while(strcmp(rcvmsg,"BYE"))
{
    recv(nsd,rcvmsg,20,0);
    printf("Client msg : %s\n",rcvmsg);

    if(!strcmp(rcvmsg,"time"))
        {   
            ticks = time(NULL);
            strcpy(sendmsg,ctime(&ticks));
            printf("Time Sent\n");
        }
        else
        {

            printf("Enter Message: ");
            fgets(sendmsg,20,stdin);
        }


    len=strlen(sendmsg);
    sendmsg[len-1]='\0';
    send(nsd,sendmsg,20,0);
}

    printf("Chat Terminated\n");
    close(sd);
    close(nsd);
    return 0;

}
