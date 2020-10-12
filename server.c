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

// C does not provide a built in functionality for string replace thus reference for the code to replace a string in C : https://www.faceprep.in/c/program-to-replace-a-substring-in-a-string/
void replaceSubstring(char string[],char sub[],char new_str[])
{
int stringLen,subLen,newLen;
int i=0,j,k;
int flag=0,start,end;
stringLen=strlen(string);
subLen=strlen(sub);
newLen=strlen(new_str);

for(i=0;i<stringLen;i++)
{
flag=0;
start=i;
for(j=0;string[i]==sub[j];j++,i++)
if(j==subLen-1)
flag=1;
end=i;
if(flag==0)
i-=j;
else
{
for(j=start;j<end;j++)
{
for(k=start;k<stringLen;k++)
string[k]=string[k+1];
stringLen--;
i--;
}

for(j=start;j<start+newLen;j++)
{
for(k=stringLen;k>=j;k--)
string[k+1]=string[k];
string[j]=new_str[j-start];
stringLen++;
i++;
}
}
}
}
// end of reference code


int main( int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 3) {
        fprintf(stderr,"ERROR, no port or directory path provided provided\n");
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

    char filepath[1000] ;
    strcpy(filepath, argv[2]);
    //= "/home/mininet/MIS596A_Cloud/Cloud/Cloud";
    char path[100];
    int start_pos;
    int end_pos;
    int l=0;
    int m;
    
    int k;
    int p;
    int q;
   
    int r=0;
    
    char type[10];
    char name[20];
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
        if(buffer[p]=='H'){
            end_pos = p-1;
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

    //get name of file
    int e=0;
    for(q=strlen(path); q>0; q-- ){
        if(path[q]=='.'){
            q--;
            while(q>0){
                
                name[e]=path[q];
                e++;
                q--;
            }
        }
    }
    //printf("name is: %s\n", name);

    int typeflag=0;
    result = strcmp(type, ".png");
    if (result == 0){
        strcpy(contenttype, "image/png");
        typeflag=1;
    }
    result = strcmp(type, ".jpg");
    if (result == 0){
        strcpy(contenttype, "image/jpg");
        typeflag=1;
    }
    result = strcmp(type, ".jpeg");
    if (result == 0){
        strcpy(contenttype, "image/jpeg");
        typeflag=1;
    }
    result = strcmp(type, ".gif");
    if (result == 0){
        strcpy(contenttype, "image/gif");
        typeflag=1;
    }
    result = strcmp(type, ".html");
    if (result == 0){
        strcpy(contenttype, "text/html");
        typeflag=1;
    }
    result = strcmp(type, ".htm");
    if (result == 0){
        strcpy(contenttype, "text/html");
        typeflag=1;
    }
    result = strcmp(type, ".txt");
    if (result == 0){
        strcpy(contenttype, "text/plain");
        typeflag=1;
    }
    if (typeflag == 0){
        strcpy(contenttype, "text/plain");
        typeflag=1;
    }

    //replacing space characted %20 with space in the file name
    replaceSubstring(path,"%20"," ");
  
    // adding 32 to ascii value for hard convert to lowecase
       int y;
       int fileflag=0;
       for(y=0;y<strlen(name);y++){
          if(name[y]>=65 && name[y]<=90)
             name[y]=name[y]+32;
       }
       strcat(filepath, "/");
       strcat(filepath, name);
       strcat(filepath, type);
       if( access( filepath, F_OK ) != -1 ){
        fileflag=1;
       }

       // hard convert to upper case
        int w;
        if (fileflag==0){
            strcpy(filepath, argv[2]);
          for(w=0;w<strlen(name);w++){
          if(name[w]>=97 && name[w]<=122)
             name[w]=name[w]-32;
       }  
       strcat(filepath, "/");
       strcat(filepath, name);
       strcat(filepath, type);
       if( access( filepath, F_OK ) != -1 ){
        fileflag=1;
       }
    }

       
    //strcat(filepath, path);
    //printf("filepath is: %s\n", filepath);


    // checking if file exists or not
    char rsp[1000];
    if( fileflag==1) {
    FILE *filepointer = fopen(filepath, "rb"); 

      
    fseek(filepointer, 0L, SEEK_END);
    long filelength = (long) ftell(filepointer);
    fseek(filepointer, 0L, SEEK_SET);

    //Prepare header    
    sprintf(rsp, "HTTP/1.1 200 OK\nContent-Length: %ld\nContent-Type: %s\n\n", filelength, contenttype);
    n = write(newsockfd, rsp, strlen(rsp));
    if (n < 0) error("ERROR writing to socket");
     
    //read content of file
    char* filecontent = (char* ) malloc(sizeof(char) * filelength);
    fread(filecontent, 1, filelength, filepointer);

    n = write(newsockfd, filecontent, filelength);
    if (n < 0) error("ERROR writing to socket");

    free(filecontent); 
    fclose(filepointer);

    } else {
    //printf("file not found");
    //sprintf(rsp, "HTTP/1.1 404 Not Found\nConnection: Close\n\nContent-Length: 0\nContent-Type: text/html\n");
    int len = strlen("<html><body><h1>404 Not Found</h1></body></html>");
    sprintf(rsp, "HTTP/1.1 404 Not Found\nContent-Length: %d\nContent-Type: %s\n\n<html><body><h1>404 Not Found</h1></body></html>", len, "text/html");
    n = write(newsockfd, rsp, strlen(rsp));
    if (n < 0) error("ERROR writing to socket");
    }
        
    

    close(newsockfd);  // close connection
    close(sockfd);

    return 0;


}
