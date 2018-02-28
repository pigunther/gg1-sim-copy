#include "server.h"
#include <stdlib.h>
//
//Server::Server () :m_queue(nullptr){
//  //m_queue = (Queue*)malloc(100*sizeof(Queue));
//  m_queue= nullptr;
//}

Server::Server(std::shared_ptr<Queue>& q):m_queue(q) {
  m_queue = q;
}

void Server::AddPacket (std::shared_ptr<Packet> p) {
  m_queue->AddPacket (p);
}
