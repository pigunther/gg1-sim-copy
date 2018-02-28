#pragma once

#include "queue.h"
#include <memory>

class Server {
public:
//  Server ();
  Server(std::shared_ptr<Queue>& q);
  void AddPacket (std::shared_ptr<Packet> packet);
  
private:
    std::shared_ptr<Queue>&  m_queue;
};
