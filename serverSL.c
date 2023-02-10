#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int window_size, frame = 0, ACK, i, client_socket, connect, val, count = 0;
    char data[100], senderdata[100];
    
    recv(client_socket, &window_size, sizeof(window_size), 0);
    while (frame < window_size)
    {
        for (i = 0; i < window_size; i++)
        {
            recv(client_socket, &frame, sizeof(frame), 0);
            printf("Transmitted and received from the client is %d\n", frame);
            frame++;
            if (frame == window_size)
                break;
        }
        printf("Enter the negative Acknowledgement to be sent to the client\n");
        scanf("%d", &ACK);
        send(client_socket, &ACK, sizeof(ACK), 0);
        if (ACK == window_size)
            break;
    }

    while (1)
    {
        recv(connect, &val, sizeof(val), 0);
        i = recv(connect, &data, sizeof(data), 0);
        data[i] = '\0';
        if (strcmp(data, "end") == 0)
        {
            printf("\n\t Failed");
            break;
        }
        if (count != val)
        {
            strcpy(senderdata, "frame missing");
            send(connect, &count, sizeof(count), 0);
            send(connect, senderdata, strlen(senderdata), 0);
        }
        else
        {
            printf("\n The frame Number is: %d", val);
            printf("\n The data is: %s", data);
            count++;
            strcpy(senderdata, "send nextdata");
            send(connect, &count, sizeof(count), 0);
            send(connect, senderdata, strlen(senderdata), 0);
        }
        printf("\n The expected frame now is %d\n", count);
    }

    return 0;
}
