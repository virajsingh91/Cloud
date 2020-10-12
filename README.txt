A README File which will contain student name and the student ID,
and other information regarding compiling, executing and testing that you want us to know.

Group 2:

Team Members:

Ailani, Pawan Anil Student ID: 23553825 pailani2@email.arizona.edu
Nagpal, Navni Student ID: 23552004 nnagpal@email.arizona.edu
Anandanathan, Devi Student ID: 23549761 devimis2019@email.arizona.edu
Saragadam, Amit Kumar Student ID: 23551335 amitsaragadam@email.arizona.edu
Kalisetty, Sri Sagar Student ID: 23496045 kalisets@email.arizona.edu
Singh, Viraj Student ID: 23553525 virajsingh91@email.arizona.edu

Tar File: 23553525.tar.gz
File Name: server.c
Programming language : C
Makefile will work with make command

How to Run:
Step 1
In the terminal Go to the directory of the untared folder and type make

Step 2
command line parameters usage[] : ./server.out [port] [existing dir path]
for eg: If you are at D:/Assignment1/cloud and port is 1572 the command will look like
./server.out 1572 D:/Assignment1/cloud

Step 3
Open the browser and search for the file using the same port number given in step 2.
For example: http://localhost:1572/index.html

Step 4
Check the terminal for HTTP message

Step 5
If you need to check for another file from web browser
You will need to execute this "./server.out 1572 D:/Assignment1/cloud"
again as the connection closes after one request is served.

PS: 
1.) For every HTTP request the server needs to be started again using command in step 2.
2.) As discussed with the professor we have used a function called replaceSubstring()from an online resource
which we have referenced in the comments in server.c file
