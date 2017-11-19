#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc , char *argv[])
{
    int deskryptor , gniazdo_klienta , c , read_size; //zadeklarowanie zmiennych do obslugi gniazd
    struct sockaddr_in serwer , klient;
    char wiadomosc[2000];

    deskryptor = socket(AF_INET , SOCK_STREAM , 0); //otwarcie gniazda

    if (deskryptor == -1) //obsluga bledu
    {
        puts("blad podczas otwierania gniazda");
    }
    puts("Gniazdo odpalilo");


    serwer.sin_family = AF_INET;
    serwer.sin_addr.s_addr = INADDR_ANY;
    serwer.sin_port = htons( 6770 );


    if( bind(deskryptor,(struct sockaddr *)&serwer , sizeof(serwer)) < 0)
    {

        perror("blad bindowania");
        return 0;
    }
    puts("bind zrobiony");


    listen(deskryptor , 3);


    puts("Czekam. ");
    c = sizeof(struct sockaddr_in);


    gniazdo_klienta = accept(deskryptor, (struct sockaddr *)&klient, (socklen_t*)&c);
    if (gniazdo_klienta < 0)
    {
        perror("blad");
        return 1;
    }
    puts("polaczenie zaakceptowane");


    while( (read_size = recv(gniazdo_klienta , wiadomosc , 2000 , 0)) > 0 )
    {

        write(gniazdo_klienta , wiadomosc , strlen(wiadomosc)); //odeslanie wiadomosci
	puts("Otrzymana wiadomosc: ");  
	puts(wiadomosc);      
	bzero(wiadomosc,2000);
	


    }

    if(read_size == 0) //gdy klient sie odlaczy
    {
        puts("Klient sie odlaczyl");
        fflush(stdout);
    }
    else if(read_size == -1) //obsluga bledu
    {
    	puts("blad odbierania");
    }

    return 0;
}
