#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in serwer;
    char message[2000] , serwer_reply[2000];


    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        puts("Nie mozna otworzyc gniazda");
    }
    puts("gniazdo otwarte");

    serwer.sin_addr.s_addr = inet_addr("127.0.0.1");
    serwer.sin_family = AF_INET;
    serwer.sin_port = htons( 6770 );


    if (connect(sock , (struct sockaddr *)&serwer , sizeof(serwer)) < 0)
    {
        perror("blad polaczenia");
        return 1;
    }

    puts("Polaczono\n");


    while(1)
    {
        puts("Wprowadz sobie wiadomosc (nie wiecej niz 2k znakow) : ");

        fgets (message, 2000, stdin);



        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("blad wysylania");
            return 1;
        }


        if( recv(sock , serwer_reply , 2000 , 0) < 0)
        {
            puts("blad odbierania");
            break;
        }

        puts("Odpowiedz :");



        puts(serwer_reply);


        bzero(serwer_reply,2000);

    }

    shutdown(sock, SHUT_RDWR);
    return 0;
}
