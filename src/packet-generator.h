#pragma once

#include "simulator.h"
#include "queue.h"
#include "packet.h"

template <typename ArrivalDistribution, typename ServiceDistribution>
class PacketGenerator
{
  using ArrivalParamType = typename ArrivalDistribution::param_type;
  using ServiceParamType = typename ServiceDistribution::param_type;
public:
  PacketGenerator (const ArrivalParamType&, const ServiceParamType&);
  void Start ();
  void NewPacket ();
  void PacketServed ();

private:
  ArrivalDistribution m_arrivalGen;
  ServiceDistribution m_serviceGen;
  Queue queue;  
};

template <typename ArrivalDistribution, typename ServiceDistribution>
PacketGenerator<ArrivalDistribution, ServiceDistribution>::PacketGenerator (const ArrivalParamType& arrivalParams, const ServiceParamType& serviceParams)
: m_arrivalGen (arrivalParams),
  m_serviceGen (serviceParams)
{
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::Start ()
{
  std::function <void ()> callback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket, this); 
  Simulator::Schedule (m_arrivalGen (Simulator::Engine ()), callback);
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket ()
{
  std::shared_ptr<Packet> p (new Packet (Simulator::Now (), m_serviceGen (Simulator::Engine ())));
  queue.AddPacket (p);
  std::function <void ()> callback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket, this); 
  Simulator::Schedule (m_arrivalGen (Simulator::Engine ()), callback);
}


