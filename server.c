/* A simple server in the internet domain using TCP
   The port number is passed as an argument
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>  /* signal name macros, and the kill() prototype */


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);  // create socket
    if (sockfd < 0)
        error("ERROR opening socket");
    memset((char *) &serv_addr, 0, sizeof(serv_addr));   // reset memory

    // fill in address info
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd, 5);  // 5 simultaneous connection at most

    //accept connections
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0)
     error("ERROR on accept");

    int n;
    char buffer[256];

    memset(buffer, 0, 256);  // reset memory

    //read client's message
    n = read(newsockfd, buffer, 255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n", buffer);

    /*FILE *fp;*/
    FILE *filepointer;
    char filecontent;
    char filebuffer[1000];
    char rspheader[1000] = "HTTP/1.1 200 OK\nContent-Type: ";
    char filepath[1000] = "/home/mininet/MIS596A_Cloud/Cloud/Cloud";
    char path[100];
    int start_pos;
    int end_pos;
    int l=0;
    int m;
    int j;
    int k;
    int p;
    int q;
    int r=0;
    char type[10];
    int result;
    char contenttype[100];

    //code to fetch the path of file
    for (m=0; m<(strlen(buffer)) ; m++){
        if(buffer[m]=='/'){
            start_pos = m; 
            break;   
        }
        
    }

    for(p=m; p<(strlen(buffer)) ; p++){
        if(buffer[p]==' '){
            end_pos = p;
            break;    
        }
    }

    for(k = start_pos; k< end_pos;k++){
        path[l] = buffer[k];
        l++;
    }

    //dynamic content type
    for(q=0; q< strlen(path); q++ ){
        if(path[q]=='.'){
            while(q<strlen(path)){
                type[r]=path[q];
                r++;
                q++;
            }
        }
    }
    printf("type is: %s\n", type);

    result = strcmp(type, ".png");
    if (result == 0){
        strcpy(contenttype, "image/png");
    }
    result = strcmp(type, ".html");
    if (result == 0){
        strcpy(contenttype, "text/html");
    }
    strcat(rspheader, contenttype);
    strcat(rspheader, "\nContent-Length: ");


    strcat(filepath, path);
    printf("filepath is: %s\n", filepath);
    //<html><body><p>Hello, World! I’m the best MIS 596A website.</p><body></html>
    /*fp = fopen("/home/mininet/MIS596A_Cloud/Cloud/Cloud/index.html", "w+");
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);
    fclose(fp);*/

    // Open file 
    filepointer = fopen(filepath, "r"); 
      
    filecontent = fgetc(filepointer); 
    int i =0;
    while (filecontent != EOF) 
    { 
        printf ("%c", filecontent); 
        filebuffer[i] = filecontent;
        i++;
        filecontent = fgetc(filepointer); 
        
    } 
    //filebuffer = filecontent;
    char stringlen[5];
    int len = strlen(filebuffer);
    sprintf(stringlen, "%d", len);
    //printf("length of buffer is %d", len);
    strcat(rspheader, stringlen);
    strcat(rspheader, "\n\n");
    strcat(rspheader, filebuffer);
    //printf("file buffer is %s\n", rspheader);
    fclose(filepointer); 

    //reply to client
    //(char*)&reply
    //n = write(newsockfd, "I got your message", 18);
    //write(newsockfd, "HTTP/1.1 200 OK\n", 16);
    //write(newsockfd, "Content-length: 151\n", 19); ///here still is a problem mentioned above
    //write(newsockfd, "Content-Type: text/html\n\n", 25);
    n = write(newsockfd, (char*)&rspheader , strlen(rspheader));
    if (n < 0) error("ERROR writing to socket");

    close(newsockfd);  // close connection
    close(sockfd);

    return 0;


}
