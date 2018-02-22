#include "server.h"

Server::Server ()
{
}

void
Server::AddPacket (std::shared_ptr<Packet> p)
{
  m_queue.AddPacket (p);
}
