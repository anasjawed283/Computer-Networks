#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main()
{
    int cd,cd2,clilen,port,len,sport=5001,dport=5000;

    cd = socket(AF_INET,SOCK_DGRAM,0);
    
    if(cd<0)
        printf("Can't Create\n");
    else
        printf("Socket is created\n");

    struct sockaddr_in servaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(sport);
    
    cd2 = bind(cd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    
    if(cd2<0)
		printf("cant bind\n");
	else
		printf("Binded\n");

    struct sockaddr_in cliaddr;

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliaddr.sin_port = htons(dport);

    char sendmsg[100],recvmsg[100];
    len = sizeof(cliaddr);
    while(1)
    {
        bzero(recvmsg,80);
        
        recvfrom(cd,recvmsg,sizeof(recvmsg),0,(struct sockaddr*)&cliaddr,&len);
        
        printf("\nFrom Client1: %s\n",recvmsg);
        
        if(!strncmp(recvmsg,"exit",4))
        {
            break;
        }

        printf("Enter the message: ");
        fgets(sendmsg,20,stdin);
        sendto(cd,sendmsg,sizeof(sendmsg),0,(struct sockaddr*)&cliaddr,len);
        if(!strncmp(sendmsg,"bye",4))
        {
            break;
        }
    }
    
    printf("\nChat is terminated\n");
    close(cd);
    return 0;

}
