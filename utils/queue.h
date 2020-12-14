/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 University of Washington
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// The queue base class has a limit on its size, in terms of number of
// packets or number of bytes depending on the operating mode.
// The base class implements tracing and basic statistics calculations.

#ifndef QUEUE_H
#define QUEUE_H

#include "ns3/packet.h"
#include "ns3/object.h"
#include "ns3/traced-callback.h"
#include "ns3/traced-value.h"
#include "ns3/unused.h"
#include "ns3/log.h"
#include "ns3/queue-size.h"
#include <string>
#include <sstream>
#include <list>
#include <deque>

namespace ns3 {

/**
 * \ingroup network
 * \defgroup queue Queue
 */

/**
 * \ingroup queue
 * \brief Abstract base class for packet Queues
 *
 * This class defines the subset of the base APIs for packet queues in the ns-3 system
 * that is independent of the type of enqueued objects
 */
class QueueBase : public Object
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  QueueBase ();
  virtual ~QueueBase ();

  static void AppendItemTypeIfNotPresent (std::string& typeId, const std::string& itemType);

  bool IsEmpty (void) const;

  uint32_t GetNPackets (void) const;

  uint32_t GetNBytes (void) const;

  QueueSize GetCurrentSize (void) const;

  uint32_t GetCurrentDRAMSize(void) const;

  uint32_t GetTotalReceivedBytes (void) const;

  uint32_t GetTotalReceivedPackets (void) const;

  uint32_t GetTotalDroppedBytes (void) const;

  /**
   * \return The total number of bytes dropped before enqueue by this Queue
   * since the simulation began, or since ResetStatistics was called, according
   * to whichever happened more recently
   */
  uint32_t GetTotalDroppedBytesBeforeEnqueue (void) const;

  /**
   * \return The total number of bytes dropped after dequeue by this Queue
   * since the simulation began, or since ResetStatistics was called, according
   * to whichever happened more recently
   */
  uint32_t GetTotalDroppedBytesAfterDequeue (void) const;

  /**
   * \return The total number of packets dropped by this Queue since the
   * simulation began, or since ResetStatistics was called, according to
   * whichever happened more recently
   */
  uint32_t GetTotalDroppedPackets (void) const;

  /**
   * \return The total number of packets dropped before enqueue by this Queue
   * since the simulation began, or since ResetStatistics was called, according
   * to whichever happened more recently
   */
  uint32_t GetTotalDroppedPacketsBeforeEnqueue (void) const;

  /**
   * \return The total number of packets dropped after dequeue by this Queue
   * since the simulation began, or since ResetStatistics was called, according
   * to whichever happened more recently
   */
  uint32_t GetTotalDroppedPacketsAfterDequeue (void) const;

  /**
   * Resets the counts for dropped packets, dropped bytes, received packets, and
   * received bytes.
   */
  void ResetStatistics (void);

  /**
   * \brief Enumeration of the modes supported in the class.
   * \deprecated This enum will go away in future versions of ns-3.
   *
   */
  enum QueueMode
  {
    QUEUE_MODE_PACKETS,     /**< Use number of packets for maximum queue size */
    QUEUE_MODE_BYTES,       /**< Use number of bytes for maximum queue size */
  };

  void SetMode (QueueBase::QueueMode mode);

  /**
   * Get the operating mode of this device.
   *
   * \returns The operating mode of this device.
   * \deprecated This method will go away in future versions of ns-3.
   * See instead GetMaxSize()
   */
  QueueBase::QueueMode GetMode (void) const;

  /**
   * \brief Set the maximum amount of packets that can be stored in this queue
   *
   * \param maxPackets amount of packets
   * \deprecated This method will go away in future versions of ns-3.
   * See instead SetMaxSize()
   */
  void SetMaxPackets (uint32_t maxPackets);

  /**
   * \return the maximum amount of packets that can be stored in this queue
   * \deprecated This method will go away in future versions of ns-3.
   * See instead GetMaxSize()
   */
  uint32_t GetMaxPackets (void) const;

  /**
   * \brief Set the maximum amount of bytes that can be stored in this queue
   *
   * \param maxBytes amount of bytes
   * \deprecated This method will go away in future versions of ns-3.
   * See instead SetMaxSize()
   */
  void SetMaxBytes (uint32_t maxBytes);

  /**
   * \return the maximum amount of bytes that can be stored in this queue
   * \deprecated This method will go away in future versions of ns-3.
   * See instead GetMaxSize()
   */
  uint32_t GetMaxBytes (void) const;

  /**
   * \brief Set the maximum size of this queue
   *
   * Trying to set a null size has no effect.
   *
   * \param size the maximum size
   */
  void SetMaxSize (QueueSize size);

  /**
   * \return the maximum size of this queue
   */
  QueueSize GetMaxSize (void) const;

#if 0
  // average calculation requires keeping around
  // a buffer with the date of arrival of past received packets
  // which are within the average window
  // so, it is quite costly to do it all the time.
  // Hence, it is disabled by default and must be explicitly
  // enabled with this method which specifies the size
  // of the average window in time units.
  void EnableRunningAverage (Time averageWindow);
  void DisableRunningAverage (void);
  // average
  double GetQueueSizeAverage (void);
  double GetReceivedBytesPerSecondAverage (void);
  double GetReceivedPacketsPerSecondAverage (void);
  double GetDroppedBytesPerSecondAverage (void);
  double GetDroppedPacketsPerSecondAverage (void);
  // variance
  double GetQueueSizeVariance (void);
  double GetReceivedBytesPerSecondVariance (void);
  double GetReceivedPacketsPerSecondVariance (void);
  double GetDroppedBytesPerSecondVariance (void);
  double GetDroppedPacketsPerSecondVariance (void);
#endif

private:
  TracedValue<uint32_t> m_nBytes;               //!< Number of bytes in the queue
  uint32_t  ;               //!< Total received bytes
  TracedValue<uint32_t> m_nPackets;             //!< Number of packets in the queue
  uint32_t m_nTotalReceivedPackets;             //!< Total received packets
  uint32_t m_nTotalDroppedBytes;                //!< Total dropped bytes
  uint32_t m_nTotalDroppedBytesBeforeEnqueue;   //!< Total dropped bytes before enqueue
  uint32_t m_nTotalDroppedBytesAfterDequeue;    //!< Total dropped bytes after dequeue
  uint32_t m_nTotalDroppedPackets;              //!< Total dropped packets
  uint32_t m_nTotalDroppedPacketsBeforeEnqueue; //!< Total dropped packets before enqueue
  uint32_t m_nTotalDroppedPacketsAfterDequeue;  //!< Total dropped packets after dequeue

  TracedValue<uint32_t> m_nBytes_dram;               //!< Number of bytes in the dram queue
  uint32_t m_nTotalReceivedBytes_dram;               //!< Total received bytes
  TracedValue<uint32_t> m_nPackets_dram;             //!< Number of packets in the queue
  uint32_t m_nTotalReceivedPackets_dram;             //!< Total received packets
  uint32_t m_nSendpktInDram;                         //!< num of send pkt into Dram;
  uint32_t m_nSendBytesInDram;                         //!< num of send pkt into Dram;
  uint32_t m_nTotalSendPktIndRram;                   //!< Total dropped bytes before enqueue
  uint32_t m_nTotalSendByteIndRram;                   //!< Total dropped bytes before enqueue


  uint32_t m_maxPackets;              //!< max packets in the queue
  uint32_t m_maxPackets_dram;         // dram_max packets in the queue
  uint32_t m_maxBytes;                //!< max bytes in the queue
  uint32_t m_maxBytes_dram;           // max bytes in the dram queue
  QueueSize m_maxSize;                //!< max queue size
  QueueSize m_maxSize_dram;           //!< max queue size in dram

  /// Friend class
  template <typename Item>
  friend class Queue;
};


template <typename Item>
class Queue : public QueueBase
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  Queue ();
  virtual ~Queue ();

  /**
   * Place an item into the Queue (each subclass defines the position)
   * \param item item to enqueue
   * \return True if the operation was successful; false otherwise
   */
  virtual bool Enqueue (Ptr<Item> item) = 0;

  uint16_t Classify (Ptr<Item> item);

  /**
   * Remove an item from the Queue (each subclass defines the position),
   * counting it as dequeued
   * \return 0 if the operation was not successful; the item otherwise.
   */
  virtual Ptr<Item> Dequeue (void) = 0;

  /**
   * Remove an item from the Queue (each subclass defines the position),
   * counting it as dropped
   * \return 0 if the operation was not successful; the item otherwise.
   */
  virtual Ptr<Item>  Remove (void) = 0;

  /**
   * Get a copy of an item in the queue (each subclass defines the position)
   * without removing it
   * \return 0 if the operation was not successful; the item otherwise.
   */
  virtual Ptr<const Item> Peek (void) const = 0;

  /**
   * Flush the queue.
   */
  void Flush (void);

protected:

  /// Const iterator.
  typedef typename std::list<Ptr<Item> >::const_iterator ConstIterator;

  ConstIterator Head (void) const;

  ConstIterator Tail (void) const;

  bool DoEnqueue (ConstIterator pos, Ptr<Item> item);


  Ptr<Item> DoDequeue (ConstIterator pos);

  void DoDramDequeue();

  /**
   * Pull the item to drop from the queue
   * \param pos the position of the item to remove
   * \return the item.
   */
  Ptr<Item> DoRemove (ConstIterator pos);

  /**
   * Peek the front item in the queue
   * \param pos the position of the item to peek
   * \return the item.
   */
  Ptr<const Item> DoPeek (ConstIterator pos) const;

  void DropBeforeEnqueue (Ptr<Item> item);

  // Send the congest pkt in to dram queue;

  void SendIntoDramqueue (Ptr<Item> item);

  /**
   * \brief Drop a packet after dequeue
   * \param item item that was dropped
   *d This method is called by the base class when a Remove operation is requested
   * and by the subclasses to notify parent (this class) that a packet has been
   * dropped for other reasons after being dequeued.
   */
  void DropAfterDequeue (Ptr<Item> item);

  void DropAfterDequeueDram (Ptr<Item> item);

private:
  std::list<Ptr<Item> > m_packets;          //!< the items in the queue
  std::deque<Ptr<Item> > m_packets_dram;     //<the dram queue>

  NS_LOG_TEMPLATE_DECLARE;                  //!< the log component

  /// Traced callback: fired when a packet is enqueued
  TracedCallback<Ptr<const Item> > m_traceEnqueue;
  /// Traced callback: fired when a packet is dequeued
  TracedCallback<Ptr<const Item> > m_traceDequeue;
  /// Traced callback: fired when a packet is dropped
  TracedCallback<Ptr<const Item> > m_traceDrop;
  /// Traced callback: fired when a packet is dropped before enqueue
  TracedCallback<Ptr<const Item> > m_traceDropBeforeEnqueue;
  /// Traced callback: fired when a packet is dropped after dequeue
  TracedCallback<Ptr<const Item> > m_traceDropAfterDequeue;
};


/**
 * Implementation of the templates declared above.
 */

template <typename Item>
TypeId
Queue<Item>::GetTypeId (void)
{
  std::string name = GetTypeParamName<Queue<Item> > ();
  static TypeId tid = TypeId (("ns3::Queue<" + name + ">").c_str ())
    .SetParent<QueueBase> ()
    .SetGroupName ("Network")
    .AddTraceSource ("Enqueue", "Enqueue a packet in the queue.",
                     MakeTraceSourceAccessor (&Queue<Item>::m_traceEnqueue),
                     "ns3::" + name + "::TracedCallback")
    .AddTraceSource ("Dequeue", "Dequeue a packet from the queue.",
                     MakeTraceSourceAccessor (&Queue<Item>::m_traceDequeue),
                     "ns3::" + name + "::TracedCallback")
    .AddTraceSource ("Drop", "Drop a packet (for whatever reason).",
                     MakeTraceSourceAccessor (&Queue<Item>::m_traceDrop),
                     "ns3::" + name + "::TracedCallback")
    .AddTraceSource ("DropBeforeEnqueue", "Drop a packet before enqueue.",
                     MakeTraceSourceAccessor (&Queue<Item>::m_traceDropBeforeEnqueue),
                     "ns3::" + name + "::TracedCallback")
    .AddTraceSource ("DropAfterDequeue", "Drop a packet after dequeue.",
                     MakeTraceSourceAccessor (&Queue<Item>::m_traceDropAfterDequeue),
                     "ns3::" + name + "::TracedCallback")
  ;
  return tid;
}

template <typename Item>
Queue<Item>::Queue ()
  : NS_LOG_TEMPLATE_DEFINE ("Queue")
{
}

template <typename Item>
Queue<Item>::~Queue ()
{
}

template <typename Item>
bool
Queue<Item>::DoEnqueue (ConstIterator pos, Ptr<Item> item)
{
  NS_LOG_FUNCTION (this << item);

  uint16_t priority = Classify (p);

  std::cout << GetNBytes () + item->GetSize() << " and " <<m_maxBytes * 0.8 << std::endl;

  if (GetNBytes () + item->GetSize() >= m_maxBytes * 0.5)
    {
      NS_LOG_LOGIC ("SRAM Queue full -- moving pkt in DRAM");
      //DropBeforeEnqueue (item);
      SendIntoDramqueue(item);
      //return true;
    }
  else{
      m_packets.insert (pos, item);

      uint32_t size = item->GetSize ();
      m_nBytes += size;
      m_nTotalReceivedBytes += size;

      m_nPackets++;
      m_nTotalReceivedPackets++;

      NS_LOG_LOGIC ("m_traceEnqueue (p)");
      m_traceEnqueue (item);
  }

  return true;
}

template <typename Item>
Ptr<Item>
Queue<Item>::DoDequeue (ConstIterator pos)
{
  NS_LOG_FUNCTION (this);

  if (m_nPackets.Get () == 0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  Ptr<Item> item = *pos;
  m_packets.erase (pos);

  if (item != 0)
    {
      NS_ASSERT (m_nBytes.Get () >= item->GetSize ());
      NS_ASSERT (m_nPackets.Get () > 0);

      m_nBytes -= item->GetSize ();
      m_nPackets--;

      NS_LOG_LOGIC ("m_traceDequeue (p)");
      m_traceDequeue (item);
    }
  std::cout << "Cur SRAM content: " << m_nPackets << " SIZE: " << m_nBytes << std::endl;

  //make sure the sram queue was only used 0.2
  if(m_nBytes_dram.Get() > 0 || m_nBytes.Get() < m_maxBytes * 0.5){
      DoDramDequeue();
  }
  return item;
}


template <typename Item>
void
Queue<Item>::DoDramDequeue()
{

    if (m_nPackets_dram.Get () == 0)
    {
        NS_LOG_LOGIC ("Queue empty");
        return;
    }

    Ptr<Item> item = m_packets_dram.front();
    m_packets_dram.pop_front();
    m_nPackets_dram--;
    m_nBytes_dram -= item->GetSize();
    std::cout << "DRAM has " << m_nPackets_dram.Get() <<" packets!" <<std::endl;
    std::cout << "Cur DRAM content: " << m_nPackets_dram << std::endl;

    DoEnqueue(Tail(), item);
}


template <typename Item>
Ptr<Item>
Queue<Item>::DoRemove (ConstIterator pos)
{
  NS_LOG_FUNCTION (this);

  if (m_nPackets.Get () == 0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  Ptr<Item> item = *pos;
  m_packets.erase (pos);

  if (item != 0)
    {
      NS_ASSERT (m_nBytes.Get () >= item->GetSize ());
      NS_ASSERT (m_nPackets.Get () > 0);

      m_nBytes -= item->GetSize ();
      m_nPackets--;

      // packets are first dequeued and then dropped
      NS_LOG_LOGIC ("m_traceDequeue (p)");
      m_traceDequeue (item);

      DropAfterDequeue (item);
    }
  return item;
}

template <typename Item>
void
Queue<Item>::Flush (void)
{
  NS_LOG_FUNCTION (this);
  while (!IsEmpty ())
    {
      Remove ();
    }
}

template <typename Item>
Ptr<const Item>
Queue<Item>::DoPeek (ConstIterator pos) const
{
  NS_LOG_FUNCTION (this);

  if (m_nPackets.Get () == 0)
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  return *pos;
}

template <typename Item>
typename Queue<Item>::ConstIterator Queue<Item>::Head (void) const
{
  return m_packets.cbegin ();
}

template <typename Item>
typename Queue<Item>::ConstIterator Queue<Item>::Tail (void) const
{
  return m_packets.cend ();
}


template <typename Item>
void
Queue<Item>::DropBeforeEnqueue (Ptr<Item> item)
{
  NS_LOG_FUNCTION (this << item);

  NS_LOG_LOGIC ("m_traceDropBeforeEnqueue (p)");
  m_traceDrop (item);
  m_traceDropBeforeEnqueue (item);
}


template <typename Item>
void
Queue<Item>::SendIntoDramqueue (Ptr <Item> item)
{
    NS_LOG_FUNCTION (this << item);

    std::cout << GetCurrentDRAMSize()+ item->GetSize() << " and " << m_maxBytes_dram << std::endl;

    if(GetCurrentDRAMSize()+ item->GetSize() > m_maxBytes_dram){
        NS_LOG_LOGIC ("DRAM is Full, Must Drop Packet!");
        return;
    }

    m_nSendpktInDram++;
    m_nSendBytesInDram += item->GetSize ();
    m_nTotalSendPktIndRram++;
    m_nTotalSendByteIndRram += item->GetSize ();

    m_packets_dram.push_back(item);
    m_nPackets_dram ++;
    m_nBytes_dram += item->GetSize();
    std::cout<<"There are "<<m_nSendpktInDram<<" Packets has been send into DRAM" <<std::endl;
}


template <typename Item>
void
Queue<Item>::DropAfterDequeue (Ptr<Item> item)
{
  NS_LOG_FUNCTION (this << item);

  m_nTotalDroppedPackets++;
  m_nTotalDroppedPacketsAfterDequeue++;
  m_nTotalDroppedBytes += item->GetSize ();
  m_nTotalDroppedBytesAfterDequeue += item->GetSize ();

  NS_LOG_LOGIC ("m_traceDropAfterDequeue (p)");
  m_traceDrop (item);
  m_traceDropAfterDequeue (item);
}


template <typename Item>
void
Queue<Item>::DropAfterDequeueDram (Ptr<Item> item)
{
    NS_LOG_FUNCTION (this << item);

    m_nTotalDroppedPackets++;
    m_nTotalDroppedPacketsAfterDequeue++;
    m_nTotalDroppedBytes += item->GetSize ();
    m_nTotalDroppedBytesAfterDequeue += item->GetSize ();

    NS_LOG_LOGIC ("DropAfterDequeueDram (p)");
    m_traceDrop (item);
    m_traceDropAfterDequeue (item);
}


template <typename Item>
uint16_t
PriorityQueue::Classify (Ptr<Item> item)
{
    NS_LOG_FUNCTION (this << item);
    UdpHeader ppp;
    p->RemoveHeader (ppp);
    Ipv4Header ip;
    p->RemoveHeader (ip);

    uint16_t priority;
    uint32_t protocol = ip.GetProtocol();

    if (protocol == 17)
    {
        UdpHeader udp;
        p->PeekHeader (udp);

        if (udp.GetDestinationPort() == m_priorityPort)
        {
            NS_LOG_INFO ("\tclassifier: high priority udp");
            priority = 1;
        }
        else
        {
            NS_LOG_INFO ("\tclassifier: low priority udp");
            priority = 0;
        }
    }
    else if (protocol == 6)
    {
        TcpHeader tcp;
        p->PeekHeader (tcp);
        if (tcp.GetDestinationPort() == m_priorityPort)
        {
            NS_LOG_INFO ("\tclassifier: high priority tcp");
            priority = 1;
        }
        else
        {
            NS_LOG_INFO ("\tclassifier: low priority tcp");
            priority = 0;
        }
    }
    else
    {
        NS_LOG_INFO ("\tclassifier: unrecognized transport protocol");
        priority = 0;
    }

    p->AddHeader (ip);
    p->AddHeader (ppp);

    return priority;
}


} // namespace ns3

#endif /* QUEUE_H */
