#pragma once

#include "packet.h"
#include "simulator.h"
#include <memory>
#include <vector>

class Queue {
public:
  Queue ();
  explicit Queue(int len);

    Queue(unsigned int k);

    int GetQueueSize ();
  void SetVerbose (bool verbose);
  void AddPacket (std::shared_ptr<Packet>);
  void RemoveFirstPacket ();
//    void updateAllPackets() {
//        allPackets++;
//    }
//    void updateRefusedPackets() {
//        refusedPackets++;
//    }
  ~Queue ();


  struct stats_t {
    double sumServiceTime;
    int totalServedPackets;

    double sumWaitingTime;
    double lastQueueChange;
    std::map<int, double> queueSizeHist;
    double totalBusyTime;

    stats_t ()
    : sumServiceTime (0),
      totalServedPackets (0),
      sumWaitingTime (0),
      lastQueueChange (0),
      totalBusyTime (0)
    {}
  };



private:

    int m_refusedPackets;
    int m_allPackets;
  std::vector<std::shared_ptr<Packet>> m_queue;
  stats_t m_stats;
  bool m_verbose;
  unsigned int k;
};
