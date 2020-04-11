#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


using namespace std;

int main()
{

    //create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return -1;
    }

    //Create a hint structure for the server we are connecting with.
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //Connect to the server on the socket
    int connctRes = connect(sock, (sockaddr*)&hint, sizeof(hint));

    if (connctRes == -1)
    {
        return 1;
    }

    //while loop
    char buf[4096];
    string userINput;

    do{
      //Enter lines of text
      cout << ">";
      getline(cin, userINput);

      //Send to server

      int sendRes = send(sock, userINput.c_str(), userINput.size() + 1, 0);
      if (sendRes == -1)
      {
          cout<< "Could not send to server! Whoops! \r\n";
          continue;
      }

      memset(buf, 0, 4096);
      int bytesReceived = recv(sock,buf,4096, 0);

      //Display Response
      cout<< "SERVER> " << string(buf,bytesReceived) << "\r\n";

    }while(true);

    //Close the socket
    close(sock);







    return 0;
}
