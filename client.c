#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
    char revmsg[100];
    char sendmsg[100];
    int len;
    int csd,nsd,clilen,cport=6000;
    
    csd = socket(AF_INET,SOCK_STREAM,0);
	
	if(csd<0)
		printf("cant create\n");
	else
		printf("Client's 'Socket is created\n");
	
	struct sockaddr_in  servaddr;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(cport);
	
    nsd = connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	if(nsd<0)
		printf("cant connect\n");
	else
		printf("connected\n"); 
    

    fgets(sendmsg,20,stdin);
    len=strlen(sendmsg);
    sendmsg[len-1]='\0';
    send(csd,sendmsg,20,0);
    recv(csd,revmsg,20,0);
    printf("%s\n",revmsg);
    close(csd);
    return 0;
		
    
}
