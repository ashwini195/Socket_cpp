#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <cstring>



int main ( int argc, int argv[] )
{
	
MSG* newMsg = new MSG;
    newMsg->type = 1;
    newMsg->priority = 9;
    newMsg->sender = 2;
    strcpy(newMsg->message, "hello from server\0");
char data[PACKETSIZE];
char data2[PACKETSIZE];
    serialize(newMsg, data);
MSG* temp1 = new MSG;
deserialize(data, temp1);
printMsg(temp1);
//std::string var1 = converttostring(data);
//std::string reply;
//std::cout << "var1 after string conversion:" << var1 << std::endl;	
  try
    {

      ClientSocket client_socket ( "localhost", 30000 );

      

      try
	{
	  client_socket << data;
	  client_socket >>data2 ;
	}
      catch ( SocketException& ) {}

      std::cout << "We received this response from the server:\n\"" << data2 << "\"\n";;

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }
//char data1[PACKETSIZE];

MSG* temp = new MSG;
deserialize(data2, temp);
printMsg(temp);
  return 0;
}
