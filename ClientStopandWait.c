//client
//This code is contributed by Anas Jawed
#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
    int sock,cport,val,count,i;
    char sentdata[50],recvdata[50];
    struct sockaddr_in servaddr;
    printf("Enter the port");
    printf("\n");
    scanf("%d",&cport);
    printf("%d\n",cport);
    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
        printf("Can't create\n");
    else
        printf("Socket is created\n");
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(cport);
    if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        printf("Can't connect\n");
    else
        printf("Connected\n");
    
    while(1)
    {
        printf("\n\nEnter Frame Number: ");
        scanf("%d",&val);
        send(sock,&val,sizeof(val),0);
        printf("Enter data: ");
        scanf("%s",sentdata);
        send(sock,sentdata,strlen(sentdata),0);
        if(strcmp(sentdata,"end")==0)
            break;
        recv(sock,&count,sizeof(count),0);
        i=recv(sock,recvdata,50,0);
        recvdata[i]='\0';
        printf("\n %s %d",recvdata,count);
    }
    return 0;
}
