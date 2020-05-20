// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"
#include <cstring>
#include <iostream>
#include <string>





ClientSocket::ClientSocket ( std::string host, int port )
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create client socket." );
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw SocketException ( "Could not bind to port." );
    }

}


const ClientSocket& ClientSocket::operator << ( const char* s ) const
{std::cout << " in client_socket.cpp\n" <<std::endl;
MSG* temp1 = new MSG;
deserialize(s, temp1);
printMsg(temp1);
  if ( ! Socket::send ( s ) )
    {
      throw SocketException ( "Could not write to socket." );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( char* s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw SocketException ( "Could not read from socket." );
    }

  return *this;
}
