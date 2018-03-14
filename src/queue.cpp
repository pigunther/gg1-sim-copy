#include "queue.h"
#include <iostream>
#include <functional>

Queue::Queue ():m_refusedPackets(1),m_allPackets(1) {
  m_verbose = false;
    k=10;
}

Queue::Queue(unsigned int k) : m_refusedPackets(1),m_allPackets(1), k(k) {}

int Queue::GetQueueSize () {
  return m_queue.size ();
}

void Queue::SetVerbose (bool verbose) {
  m_verbose = verbose;
}

void Queue::AddPacket (std::shared_ptr<Packet> packet) {
  m_stats.queueSizeHist[m_queue.size ()] += Simulator::Now () - m_stats.lastQueueChange;
  m_stats.totalBusyTime += (!m_queue.empty()) ? (Simulator::Now () - m_stats.lastQueueChange) : 0;
  m_stats.lastQueueChange = Simulator::Now ();

  //comment: queue size
    m_allPackets++;

    if (m_queue.size() <= k) {
        m_queue.push_back(packet);
    } else {
        m_refusedPackets++;
    }

    if (m_queue.size () == 1) {
  //if (m_queue.size () < k+1) {
      std::function <void ()> callback = std::bind (&Queue::RemoveFirstPacket, this);
      Simulator::Schedule (packet->GetServiceTime (), callback);
    }
}

void Queue::RemoveFirstPacket () {
  m_stats.sumServiceTime += Simulator::Now () - m_queue.front()->GetArrivalTime ();
  m_stats.sumWaitingTime += Simulator::Now () - m_queue.front()->GetArrivalTime () - m_queue.front()->GetServiceTime ();
  m_stats.totalServedPackets ++;
  m_stats.queueSizeHist[m_queue.size ()] += Simulator::Now () - m_stats.lastQueueChange; 
  m_stats.totalBusyTime += (!m_queue.empty()) ? (Simulator::Now () - m_stats.lastQueueChange) : 0;
  m_stats.lastQueueChange = Simulator::Now ();

  m_queue.erase (m_queue.begin ());

   // std::cout << m_queue.size() << " m_queue size " << std::endl;

  //comment: queue could be not empty after erasing first element
    //todo че это делает
  if (!m_queue.empty ()) {
    std::function <void ()> callback = std::bind (&Queue::RemoveFirstPacket, this);
    Simulator::Schedule (m_queue.front()->GetServiceTime (), callback);
  }
}

Queue::~Queue () {
  m_stats.queueSizeHist[m_queue.size ()] += Simulator::Now () - m_stats.lastQueueChange;
  m_stats.totalBusyTime += (!m_queue.empty()) ? (Simulator::Now () - m_stats.lastQueueChange) : 0;

  double avgQueueSize = 0;
  for (const auto& it : m_stats.queueSizeHist) {
    avgQueueSize += it.first * it.second / Simulator::Now();
  }
 
  if (m_verbose) {
    std::cout << "====================PRINT QUEUE STATS======================" << std::endl;
    std::cout << "Total served packets: " << m_stats.totalServedPackets << std::endl;
    std::cout << "Average service time: " << m_stats.sumServiceTime / m_stats.totalServedPackets << std::endl;
    std::cout << "Average waiting time: " << m_stats.sumWaitingTime / m_stats.totalServedPackets << std::endl;
    std::cout << "Average queue size: "   << avgQueueSize << std::endl; 
    std::cout << "Utilization: " << m_stats.totalBusyTime / Simulator::Now () << std::endl;
    std::cout << "===========================================================" << std::endl;
  } else {
    std::cout << m_stats.totalServedPackets << ' '
              << m_stats.sumServiceTime / m_stats.totalServedPackets << ' '
              << m_stats.sumWaitingTime / m_stats.totalServedPackets << ' ' << avgQueueSize
              << ' ' << m_stats.totalBusyTime / Simulator::Now ()
              << ' ' << ((double)m_refusedPackets)/((double)m_allPackets) << std::endl;


//    std::cout << m_stats.totalServedPackets << std::endl;
//    std::cout <<  m_stats.sumServiceTime  << std::endl;
//    std::cout << m_stats.sumWaitingTime << std::endl;
//    std::cout << avgQueueSize << std::endl;
//      std::cout << ((double)m_refusedPackets)/((double)m_allPackets) << std::endl;
  }

  m_queue.clear ();
}


