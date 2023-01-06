#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
    char rcvmsg[100];
    char sendmsg[100];
	int sd,sd2,nsd,clilen,sport=6000,len,port;
	
	sd = socket(AF_INET,SOCK_STREAM,0);
	
	if(sd<0)
		printf("cant create\n");
	else
		printf("Socket is created\n");
	
    struct sockaddr_in  serveraddr;	
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
    nsd = accept(sd,(struct sockaddr*)&cliaddr,&clilen);
    if(nsd<0)
        printf("can't accept\n");
    else
        printf("accepted\n");

    printf("client adress:%s",inet_ntoa(cliaddr.sin_addr));
    printf("\n");

    while(1){
        recv(nsd,rcvmsg,20,0);
        printf("%s\n",rcvmsg);
        fgets(sendmsg,20,stdin);
        len=strlen(sendmsg);
        sendmsg[len-1]='\0';
        send(nsd,sendmsg,20,0);
    }
    

    close(sd);
    close(nsd);
    return 0;
		
}
