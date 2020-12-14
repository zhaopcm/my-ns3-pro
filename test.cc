#include <fstream>
#include "ns3/gnuplot.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/random-variable-stream.h"
#include "ns3/rng-seed-manager.h"
#include <iostream>
#include "ns3/gnuplot.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/netanim-module.h"
#include "ns3/address.h"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/data-rate.h"
#include "ns3/traced-callback.h"
#include "ns3/log.h"
#include "ns3/address.h"
#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/packet-socket-address.h"
#include "ns3/node.h"
#include "ns3/nstime.h"
#include "ns3/data-rate.h"
#include "ns3/random-variable-stream.h"
#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/onoff-application.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/on-off-helper.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet-socket-address.h"
#include "ns3/string.h"
#include "ns3/data-rate.h"
#include "ns3/uinteger.h"
#include "ns3/names.h"
#include "ns3/random-variable-stream.h"
#include <stdint.h>
#include <string>
#include "ns3/object-factory.h"
#include "ns3/address.h"
#include "ns3/attribute.h"
#include "ns3/net-device.h"
#include "ns3/node-container.h"
#include "ns3/application-container.h"
#include "ns3/onoff-application.h"
#include <fstream>
#include "ns3/gnuplot.h"
#include "algorithm"
#include <string>
#include "ns3/object-factory.h"
#include "ns3/net-device-container.h"
#include "ns3/node-container.h"
#include "ns3/trace-helper.h"

#include "ns3/abort.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/point-to-point-net-device.h"
#include "ns3/point-to-point-channel.h"
#include "ns3/point-to-point-remote-channel.h"
#include "ns3/queue.h"
#include "ns3/config.h"
#include "ns3/packet.h"
#include "ns3/names.h"
#include "ns3/mpi-interface.h"
#include "ns3/mpi-receiver.h"

#include "ns3/trace-helper.h"

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


#include "ns3/abort.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"

using namespace std;
using namespace ns3;
///统计画图模块/
// Gnuplot2dDataset dataset_interval2;
std::string fileNameWithNoExtension = "interval";
std::string graphicsFileName        = fileNameWithNoExtension + ".png";
std::string plotFileName            = fileNameWithNoExtension + ".plt";
std::string plotTitle               = "interval";
std::string dataTitle               = "uniform-D Data";
// Instantiate the plot and set its title.
Gnuplot plot (graphicsFileName);
Gnuplot2dDataset dataset_interval;

std::string fileNameWithNoExtension2 = "packetsize";
std::string graphicsFileName2        = fileNameWithNoExtension2 + ".png";
std::string plotFileName2            = fileNameWithNoExtension2 + ".plt";
std::string plotTitle2               = "packetsizes ";
std::string dataTitle2               = "uniform-D Data";

// Instantiate the plot and set its title.
Gnuplot plot2 (graphicsFileName2);
Gnuplot2dDataset dataset_packetsize;
//dataset_interval.SetTitle (dataTitle);
//dataset_interval.SetStyle (Gnuplot2dDataset::LINES_POINTS);
int count_packets=0;
double data_interval[100];
int    data_packetsize[100];

// pointtopointhelper.h
namespace ns3 {

    class NetDevice;
    class Node;

/**
 * \brief Build a set of PointToPointNetDevice objects
 *
 * Normally we eschew multiple inheritance, however, the classes
 * PcapUserHelperForDevice and AsciiTraceUserHelperForDevice are
 * "mixins".
 */
    class myPointToPointHelper : public PcapHelperForDevice,
                               public AsciiTraceHelperForDevice
    {
    public:
        /**
         * Create a PointToPointHelper to make life easier when creating point to
         * point networks.
         */
        myPointToPointHelper ();
        virtual ~myPointToPointHelper () {}

        void SetQueue (std::string type,
                       std::string n1 = "", const AttributeValue &v1 = EmptyAttributeValue (),
                       std::string n2 = "", const AttributeValue &v2 = EmptyAttributeValue (),
                       std::string n3 = "", const AttributeValue &v3 = EmptyAttributeValue (),
                       std::string n4 = "", const AttributeValue &v4 = EmptyAttributeValue ());


        void SetDeviceAttribute (std::string name, const AttributeValue &value);


        void SetChannelAttribute (std::string name, const AttributeValue &value);


        NetDeviceContainer Install (NodeContainer c);


        NetDeviceContainer Install (Ptr<Node> a, Ptr<Node> b);

        NetDeviceContainer Install (Ptr<Node> a, std::string bName);

        NetDeviceContainer Install (std::string aName, Ptr<Node> b);

        NetDeviceContainer Install (std::string aNode, std::string bNode);

        Ptr<Queue<Packet> > queueA;
        Ptr<Queue<Packet> > queueB;

    private:

        virtual void EnablePcapInternal (std::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename);

        virtual void EnableAsciiInternal (
                Ptr<OutputStreamWrapper> stream,
                std::string prefix,
                Ptr<NetDevice> nd,
                bool explicitFilename);

        ObjectFactory m_queueFactory;         //!< Queue Factory
        ObjectFactory m_channelFactory;       //!< Channel Factory
        ObjectFactory m_remoteChannelFactory; //!< Remote Channel Factory
        ObjectFactory m_deviceFactory;        //!< Device Factory
    };

} // namespace ns3

// pointtopoint.cc
namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("myPointToPointHelper");

    // LogComponentEnable("myPointToPointHelper", LOG_LEVEL_INFO);
    // NS_OBJECT_ENSURE_REGISTERED(myPointToPointHelper);

    // NS_OBJECT_ENSURE_REGISTERED (myPointToPointHelper);

    myPointToPointHelper::myPointToPointHelper ()
    {
        m_queueFactory.SetTypeId ("ns3::DropTailQueue<Packet>");
        m_deviceFactory.SetTypeId ("ns3::PointToPointNetDevice");
        m_channelFactory.SetTypeId ("ns3::PointToPointChannel");
        m_remoteChannelFactory.SetTypeId ("ns3::PointToPointRemoteChannel");
    }

    void
    myPointToPointHelper::SetQueue (std::string type,
                                  std::string n1, const AttributeValue &v1,
                                  std::string n2, const AttributeValue &v2,
                                  std::string n3, const AttributeValue &v3,
                                  std::string n4, const AttributeValue &v4)
    {
        QueueBase::AppendItemTypeIfNotPresent (type, "Packet");
        cout << "setqueue done" <<endl;

        m_queueFactory.SetTypeId (type);
        m_queueFactory.Set (n1, v1);
        m_queueFactory.Set (n2, v2);
        m_queueFactory.Set (n3, v3);
        m_queueFactory.Set (n4, v4);
    }

    void
    myPointToPointHelper::SetDeviceAttribute (std::string n1, const AttributeValue &v1)
    {
        m_deviceFactory.Set (n1, v1);
    }

    void
    myPointToPointHelper::SetChannelAttribute (std::string n1, const AttributeValue &v1)
    {
        m_channelFactory.Set (n1, v1);
        m_remoteChannelFactory.Set (n1, v1);
    }

    void
    myPointToPointHelper::EnablePcapInternal (std::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename)
    {
        //
        // All of the Pcap enable functions vector through here including the ones
        // that are wandering through all of devices on perhaps all of the nodes in
        // the system.  We can only deal with devices of type PointToPointNetDevice.
        //
        Ptr<PointToPointNetDevice> device = nd->GetObject<PointToPointNetDevice> ();
        if (device == 0)
        {
            NS_LOG_INFO ("myPointToPointHelper::EnablePcapInternal(): Device " << device << " not of type ns3::PointToPointNetDevice");
            return;
        }

        PcapHelper pcapHelper;

        std::string filename;
        if (explicitFilename)
        {
            filename = prefix;
        }
        else
        {
            filename = pcapHelper.GetFilenameFromDevice (prefix, device);
        }

        Ptr<PcapFileWrapper> file = pcapHelper.CreateFile (filename, std::ios::out,
                                                           PcapHelper::DLT_PPP);
        pcapHelper.HookDefaultSink<PointToPointNetDevice> (device, "PromiscSniffer", file);
    }

    void
    myPointToPointHelper::EnableAsciiInternal (
            Ptr<OutputStreamWrapper> stream,
            std::string prefix,
            Ptr<NetDevice> nd,
            bool explicitFilename)
    {
        //
        // All of the ascii enable functions vector through here including the ones
        // that are wandering through all of devices on perhaps all of the nodes in
        // the system.  We can only deal with devices of type PointToPointNetDevice.
        //
        Ptr<PointToPointNetDevice> device = nd->GetObject<PointToPointNetDevice> ();
        if (device == 0)
        {
            NS_LOG_INFO ("myPointToPointHelper::EnableAsciiInternal(): Device " << device <<
                                                                              " not of type ns3::PointToPointNetDevice");
            return;
        }

        //
        // Our default trace sinks are going to use packet printing, so we have to
        // make sure that is turned on.
        //
        Packet::EnablePrinting ();


        if (stream == 0)
        {
            AsciiTraceHelper asciiTraceHelper;

            std::string filename;
            if (explicitFilename)
            {
                filename = prefix;
            }
            else
            {
                filename = asciiTraceHelper.GetFilenameFromDevice (prefix, device);
            }

            Ptr<OutputStreamWrapper> theStream = asciiTraceHelper.CreateFileStream (filename);

            //
            // The MacRx trace source provides our "r" event.
            //
            asciiTraceHelper.HookDefaultReceiveSinkWithoutContext<PointToPointNetDevice> (device, "MacRx", theStream);

            //
            // The "+", '-', and 'd' events are driven by trace sources actually in the
            // transmit queue.
            //
            Ptr<Queue<Packet> > queue = device->GetQueue ();
            asciiTraceHelper.HookDefaultEnqueueSinkWithoutContext<Queue<Packet> > (queue, "Enqueue", theStream);
            asciiTraceHelper.HookDefaultDropSinkWithoutContext<Queue<Packet> > (queue, "Drop", theStream);
            asciiTraceHelper.HookDefaultDequeueSinkWithoutContext<Queue<Packet> > (queue, "Dequeue", theStream);

            // PhyRxDrop trace source for "d" event
            asciiTraceHelper.HookDefaultDropSinkWithoutContext<PointToPointNetDevice> (device, "PhyRxDrop", theStream);

            return;
        }

        uint32_t nodeid = nd->GetNode ()->GetId ();
        uint32_t deviceid = nd->GetIfIndex ();
        std::ostringstream oss;

        oss << "/NodeList/" << nd->GetNode ()->GetId () << "/DeviceList/" << deviceid << "/$ns3::PointToPointNetDevice/MacRx";
        Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultReceiveSinkWithContext, stream));

        oss.str ("");
        oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::PointToPointNetDevice/TxQueue/Enqueue";
        Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultEnqueueSinkWithContext, stream));

        oss.str ("");
        oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::PointToPointNetDevice/TxQueue/Dequeue";
        Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultDequeueSinkWithContext, stream));

        oss.str ("");
        oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::PointToPointNetDevice/TxQueue/Drop";
        Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultDropSinkWithContext, stream));

        oss.str ("");
        oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::PointToPointNetDevice/PhyRxDrop";
        Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultDropSinkWithContext, stream));
    }

    NetDeviceContainer
    myPointToPointHelper::Install (NodeContainer c)
    {
        NS_ASSERT (c.GetN () == 2);
        return Install (c.Get (0), c.Get (1));
    }

    NetDeviceContainer
    myPointToPointHelper::Install (Ptr<Node> a, Ptr<Node> b)
    {
        NetDeviceContainer container;

        Ptr<PointToPointNetDevice> devA = m_deviceFactory.Create<PointToPointNetDevice> ();
        devA->SetAddress (Mac48Address::Allocate ());
        a->AddDevice (devA);
        queueA = m_queueFactory.Create<Queue<Packet>> ();
        queueA->SetMode(QueueBase::QueueMode::QUEUE_MODE_BYTES);
        queueA->SetMaxBytes(65536*100);
        devA->SetQueue (queueA);

        Ptr<PointToPointNetDevice> devB = m_deviceFactory.Create<PointToPointNetDevice> ();
        devB->SetAddress (Mac48Address::Allocate ());
        b->AddDevice (devB);
        queueB = m_queueFactory.Create<Queue<Packet> > ();
        queueB->SetMaxBytes(65536*100);
        devB->SetQueue (queueB);

        bool useNormalChannel = true;
        Ptr<PointToPointChannel> channel = 0;

        if (MpiInterface::IsEnabled ())
        {
            uint32_t n1SystemId = a->GetSystemId ();
            uint32_t n2SystemId = b->GetSystemId ();
            uint32_t currSystemId = MpiInterface::GetSystemId ();
            if (n1SystemId != currSystemId || n2SystemId != currSystemId)
            {
                useNormalChannel = false;
            }
        }
        if (useNormalChannel)
        {
            channel = m_channelFactory.Create<PointToPointChannel> ();
        }
        else
        {
            channel = m_remoteChannelFactory.Create<PointToPointRemoteChannel> ();
            Ptr<MpiReceiver> mpiRecA = CreateObject<MpiReceiver> ();
            Ptr<MpiReceiver> mpiRecB = CreateObject<MpiReceiver> ();
            mpiRecA->SetReceiveCallback (MakeCallback (&PointToPointNetDevice::Receive, devA));
            mpiRecB->SetReceiveCallback (MakeCallback (&PointToPointNetDevice::Receive, devB));
            devA->AggregateObject (mpiRecA);
            devB->AggregateObject (mpiRecB);
        }

        devA->Attach (channel);
        devB->Attach (channel);
        container.Add (devA);
        container.Add (devB);

        return container;
    }

    NetDeviceContainer
    myPointToPointHelper::Install (Ptr<Node> a, std::string bName)
    {
        Ptr<Node> b = Names::Find<Node> (bName);
        return Install (a, b);
    }

    NetDeviceContainer
    myPointToPointHelper::Install (std::string aName, Ptr<Node> b)
    {
        Ptr<Node> a = Names::Find<Node> (aName);
        return Install (a, b);
    }

    NetDeviceContainer
    myPointToPointHelper::Install (std::string aName, std::string bName)
    {
        Ptr<Node> a = Names::Find<Node> (aName);
        Ptr<Node> b = Names::Find<Node> (bName);
        return Install (a, b);
    }

} // namespace ns3



// onoff-application .h  类声明
namespace ns3 {

    class Address;
    class RandomVariableStream;
    class Socket;

    class myOnOffApplication : public Application
    {
    public:
        /**
         * \brief Get the type ID.
         * \return the object TypeId
         */
        static TypeId GetTypeId (void);

        myOnOffApplication ();

        virtual ~myOnOffApplication();

        /**
         * \brief Set the total number of bytes to send.
         *
         * Once these bytes are sent, no packet is sent again, even in on state.
         * The value zero means that there is no limit.
         *
         * \param maxBytes the total number of bytes to send
         */
        void SetMaxBytes (uint32_t maxBytes);

        /**
         * \brief Return a pointer to associated socket.
         * \return pointer to associated socket
         */
        Ptr<Socket> GetSocket (void) const;

        /**
         * \brief Assign a fixed random variable stream number to the random variables
         * used by this model.
         *
         * \param stream first stream index to use
         * \return the number of stream indices assigned by this model
         */
        int64_t AssignStreams (int64_t stream);

    protected:
        virtual void DoDispose (void);
    private:
        // inherited from Application base class.
        virtual void StartApplication (void);    // Called at time specified by Start
        virtual void StopApplication (void);     // Called at time specified by Stop

        //helpers
        /**
         * \brief Cancel all pending events.
         */
        void CancelEvents ();
        void StartSending ();
        /**
         * \brief Start an Off period
         */
        void StopSending ();

        void SendPacket ();

        Ptr<Socket>     m_socket;       //!< Associated socket
        Address         m_peer;         //!< Peer address
        bool            m_connected;    //!< True if connected
        Ptr<RandomVariableStream>  m_onTime;       //!< rng for On Time
        Ptr<RandomVariableStream>  m_offTime;      //!< rng for Off Time
        Ptr<RandomVariableStream>  m_interval;
        Ptr<RandomVariableStream>  m__packetsize;
        DataRate        m_cbrRate;      //!< Rate that data is generated
        DataRate        m_cbrRateFailSafe;      //!< Rate that data is generated (check copy)
        uint32_t        m_pktSize;      //!< Size of packets
        uint32_t        m_residualBits; //!< Number of generated, but not sent, bits
        Time            m_lastStartTime; //!< Time last packet sent
        uint32_t        m_maxBytes;     //!< Limit total number of bytes sent
        uint32_t        m_totBytes;     //!< Total bytes sent so far
        EventId         m_startStopEvent;     //!< Event id for next start or stop event
        EventId         m_sendEvent;    //!< Event id of pending "send packet" event
        TypeId          m_tid;          //!< Type of the socket used
        // int             count_packets;
        /// Traced Callback: transmitted packets.
        TracedCallback<Ptr<const Packet> > m_txTrace;

    private:
        /**
         * \brief Schedule the next packet transmission
         */
        void ScheduleNextTx ();
        /**
         * \brief Schedule the next On period start
         */
        void ScheduleStartEvent ();
        /**
         * \brief Schedule the next Off period start
         */
        void ScheduleStopEvent ();
        void ConnectionSucceeded (Ptr<Socket> socket);
        /**
         * \brief Handle a Connection Failed event
         * \param socket the not connected socket
         */
        void ConnectionFailed (Ptr<Socket> socket);
    };

} // namespace ns3



///onoff-application.cc  类的实现
namespace ns3 {

    //LogComponentEnable("myOnOffApplication", LOG_INFO);

    //NS_LOG_COMPONENT_DEFINE ("myOnOffApplication");

    NS_OBJECT_ENSURE_REGISTERED (myOnOffApplication);

    TypeId
    myOnOffApplication::GetTypeId (void)
    {
        static TypeId tid = TypeId ("ns3::myOnOffApplication")
                .SetParent<Application> ()
                .SetGroupName("Applications")
                .AddConstructor<myOnOffApplication> ()
                .AddAttribute ("DataRate", "The data rate in on state.",
                               DataRateValue (DataRate ("500kb/s")),
                               MakeDataRateAccessor (&myOnOffApplication::m_cbrRate),
                               MakeDataRateChecker ())
                .AddAttribute ("PacketSize", "The size of packets sent in on state",
                               StringValue ("ns3::ConstantRandomVariable[Constant=137]"),
                               MakePointerAccessor (&myOnOffApplication::m__packetsize),
                               MakePointerChecker <RandomVariableStream>())

                .AddAttribute ("Interval", "The time between packets sent in on state",
                               StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"),
                               MakePointerAccessor (&myOnOffApplication::m_interval),
                               MakePointerChecker <RandomVariableStream>())


                .AddAttribute ("Remote", "The address of the destination",
                               AddressValue (),
                               MakeAddressAccessor (&myOnOffApplication::m_peer),
                               MakeAddressChecker ())
                .AddAttribute ("OnTime", "A RandomVariableStream used to pick the duration of the 'On' state.",
                               StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"),
                               MakePointerAccessor (&myOnOffApplication::m_onTime),
                               MakePointerChecker <RandomVariableStream>())
                .AddAttribute ("OffTime", "A RandomVariableStream used to pick the duration of the 'Off' state.",
                               StringValue ("ns3::ConstantRandomVariable[Constant=1.0]"),
                               MakePointerAccessor (&myOnOffApplication::m_offTime),
                               MakePointerChecker <RandomVariableStream>())
                .AddAttribute ("MaxBytes",
                               "The total number of bytes to send. Once these bytes are sent, "
                               "no packet is sent again, even in on state. The value zero means "
                               "that there is no limit.",
                               UintegerValue (0),
                               MakeUintegerAccessor (&myOnOffApplication::m_maxBytes),
                               MakeUintegerChecker<uint32_t> ())
                .AddAttribute ("Protocol", "The type of protocol to use.",
                               TypeIdValue (UdpSocketFactory::GetTypeId ()),
                               MakeTypeIdAccessor (&myOnOffApplication::m_tid),
                               MakeTypeIdChecker ())
                .AddTraceSource ("Tx", "A new packet is created and is sent",
                                 MakeTraceSourceAccessor (&myOnOffApplication::m_txTrace),
                                 "ns3::Packet::TracedCallback")
        ;
        return tid;
    }
    myOnOffApplication::myOnOffApplication ()
            : m_socket (0),
              m_connected (false),
              m_residualBits (0),
              m_lastStartTime (Seconds (0)),
              //count_packets(0),
              m_totBytes (0)
    {
        NS_LOG_FUNCTION (this);
    }

    myOnOffApplication::~myOnOffApplication()
    {
        NS_LOG_FUNCTION (this);
    }

    void
    myOnOffApplication::SetMaxBytes (uint32_t maxBytes)
    {
        NS_LOG_FUNCTION (this << maxBytes);
        m_maxBytes = maxBytes;
    }

    Ptr<Socket>
    myOnOffApplication::GetSocket (void) const
    {
        NS_LOG_FUNCTION (this);
        return m_socket;
    }

    int64_t
    myOnOffApplication::AssignStreams (int64_t stream)
    {
        NS_LOG_FUNCTION (this << stream);
        m_onTime->SetStream (stream);
        m_offTime->SetStream (stream + 1);
        m_interval->SetStream (stream + 2);
        m__packetsize->SetStream (stream + 3);
        return 4;
    }

    void
    myOnOffApplication::DoDispose (void)
    {
        NS_LOG_FUNCTION (this);

        m_socket = 0;
        // chain up
        Application::DoDispose ();
    }

// Application Methods
    void myOnOffApplication::StartApplication () // Called at time specified by Start
    {
        NS_LOG_FUNCTION (this);

        // Create the socket if not already
        if (!m_socket)
        {
            m_socket = Socket::CreateSocket (GetNode (), m_tid);
            if (Inet6SocketAddress::IsMatchingType (m_peer))
            {
                m_socket->Bind6 ();
            }
            else if (InetSocketAddress::IsMatchingType (m_peer) ||
                     PacketSocketAddress::IsMatchingType (m_peer))
            {
                m_socket->Bind ();
            }
            m_socket->Connect (m_peer);
            m_socket->SetAllowBroadcast (true);
            m_socket->ShutdownRecv ();

            m_socket->SetConnectCallback (
                    MakeCallback (&myOnOffApplication::ConnectionSucceeded, this),
                    MakeCallback (&myOnOffApplication::ConnectionFailed, this));
        }
        m_cbrRateFailSafe = m_cbrRate;

        // Insure no pending event
        CancelEvents ();
        // If we are not yet connected, there is nothing to do here
        // The ConnectionComplete upcall will start timers at that time
        //if (!m_connected) return;
        ScheduleStartEvent ();
    }


    void myOnOffApplication::StopApplication () // Called at time specified by Stop
    {
        NS_LOG_FUNCTION (this);

        CancelEvents ();
        if(m_socket != 0)
        {
            m_socket->Close ();
        }
        else
        {
            NS_LOG_WARN ("myOnOffApplication found null socket to close in StopApplication");
        }
    }
    void myOnOffApplication::CancelEvents ()
    {
        NS_LOG_FUNCTION (this);

        if (m_sendEvent.IsRunning () && m_cbrRateFailSafe == m_cbrRate )
        { // Cancel the pending send packet event
            // Calculate residual bits since last packet sent
            Time delta (Simulator::Now () - m_lastStartTime);
            int64x64_t bits = delta.To (Time::S) * m_cbrRate.GetBitRate ();
            m_residualBits += bits.GetHigh ();
        }
        m_cbrRateFailSafe = m_cbrRate;
        Simulator::Cancel (m_sendEvent);
        Simulator::Cancel (m_startStopEvent);
    }

// Event handlers
    void myOnOffApplication::StartSending ()
    {
        NS_LOG_FUNCTION (this);
        m_lastStartTime = Simulator::Now ();
        ScheduleNextTx ();  // Schedule the send packet event
        ScheduleStopEvent ();
    }

    void myOnOffApplication::StopSending ()
    {
        NS_LOG_FUNCTION (this);
        CancelEvents ();

        ScheduleStartEvent ();
    }

    void myOnOffApplication::ScheduleNextTx ()
    {
        NS_LOG_FUNCTION (this);

        if (m_maxBytes == 0 || m_totBytes < m_maxBytes)
        {
            cout<<"第几次进入 ScheduleNextTx ()"<<endl;
            m_pktSize=m__packetsize->GetValue();   // 添加这一个数据包大小控制语句

            data_packetsize[count_packets]=m_pktSize;

            uint32_t bits = m_pktSize * 8 - m_residualBits;
            NS_LOG_LOGIC ("bits = " << bits);

            double myinterval=m_interval->GetValue();
            cout << "the interval is "<<myinterval<<endl;
            data_interval[count_packets]=myinterval;
            count_packets++;

            // dataset_interval.Add(
            // ,myinterval);

            Time nextTime (Seconds (bits /
                                    static_cast<double>(m_cbrRate.GetBitRate ())+myinterval)); // Time till next packet
            NS_LOG_LOGIC ("nextTime = " << nextTime);
            m_sendEvent = Simulator::Schedule (nextTime,
                                               &myOnOffApplication::SendPacket, this);
        }

        else
        { // All done, cancel any pending events
            StopApplication ();
        }
    }

    void myOnOffApplication::ScheduleStartEvent ()
    {  // Schedules the event to start sending data (switch to the "On" state)
        NS_LOG_FUNCTION (this);

        Time offInterval = Seconds (m_offTime->GetValue ());
        NS_LOG_LOGIC ("start at " << offInterval);
        m_startStopEvent = Simulator::Schedule (offInterval, &myOnOffApplication::StartSending, this);
    }

    void myOnOffApplication::ScheduleStopEvent ()
    {  // Schedules the event to stop sending data (switch to "Off" state)
        NS_LOG_FUNCTION (this);

        Time onInterval = Seconds (m_onTime->GetValue ());
        NS_LOG_LOGIC ("stop at " << onInterval);
        m_startStopEvent = Simulator::Schedule (onInterval, &myOnOffApplication::StopSending, this);
    }

    void myOnOffApplication::SendPacket ()
    {
        NS_LOG_FUNCTION (this);

        NS_ASSERT (m_sendEvent.IsExpired ());
        Ptr<Packet> packet = Create<Packet> (m_pktSize);
        m_txTrace (packet);
        m_socket->Send (packet);
        m_totBytes += m_pktSize;
        if (InetSocketAddress::IsMatchingType (m_peer))
        {
            NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds ()
                                    << "s on-off application sent "
                                    <<  packet->GetSize () << " bytes to "
                                    << InetSocketAddress::ConvertFrom(m_peer).GetIpv4 ()
                                    << " port " << InetSocketAddress::ConvertFrom (m_peer).GetPort ()
                                    << " total Tx " << m_totBytes << " bytes");
        }
        else if (Inet6SocketAddress::IsMatchingType (m_peer))
        {
            NS_LOG_INFO ("At time " << Simulator::Now ().GetSeconds ()
                                    << "s on-off application sent "
                                    <<  packet->GetSize () << " bytes to "
                                    << Inet6SocketAddress::ConvertFrom(m_peer).GetIpv6 ()
                                    << " port " << Inet6SocketAddress::ConvertFrom (m_peer).GetPort ()
                                    << " total Tx " << m_totBytes << " bytes");
        }
        m_lastStartTime = Simulator::Now ();
        m_residualBits = 0;
        ScheduleNextTx ();
    }


    void myOnOffApplication::ConnectionSucceeded (Ptr<Socket> socket)
    {
        NS_LOG_FUNCTION (this << socket);
        m_connected = true;
    }

    void myOnOffApplication::ConnectionFailed (Ptr<Socket> socket)
    {
        NS_LOG_FUNCTION (this << socket);
    }


} // Namespace ns3


//on-off helper .h   头文件

namespace ns3 {

    class DataRate;

/**
 * \ingroup onoff
 * \brief A helper to make it easier to instantiate an ns3::myOnOffApplication
 * on a set of nodes.
 */
    class myOnOffHelper
    {
    public:

        myOnOffHelper (std::string protocol, Address address);

        void SetAttribute (std::string name, const AttributeValue &value);

        void SetConstantRate (DataRate dataRate, uint32_t packetSize = 512);

        ApplicationContainer Install (NodeContainer c) const;

        ApplicationContainer Install (Ptr<Node> node) const;

        ApplicationContainer Install (std::string nodeName) const;

        int64_t AssignStreams (NodeContainer c, int64_t stream);

    private:
        Ptr<Application> InstallPriv (Ptr<Node> node) const;

        ObjectFactory m_factory; //!< Object factory.
    };

} // namespace ns3


//  onoff helper.cc   实现
namespace ns3 {

    myOnOffHelper::myOnOffHelper (std::string protocol, Address address)
    {
        m_factory.SetTypeId ("ns3::myOnOffApplication");
        m_factory.Set ("Protocol", StringValue (protocol));
        m_factory.Set ("Remote", AddressValue (address));
    }

    void
    myOnOffHelper::SetAttribute (std::string name, const AttributeValue &value)
    {
        m_factory.Set (name, value);
    }

    ApplicationContainer
    myOnOffHelper::Install (Ptr<Node> node) const
    {
        return ApplicationContainer (InstallPriv (node));
    }

    ApplicationContainer
    myOnOffHelper::Install (std::string nodeName) const
    {
        Ptr<Node> node = Names::Find<Node> (nodeName);
        return ApplicationContainer (InstallPriv (node));
    }

    ApplicationContainer
    myOnOffHelper::Install (NodeContainer c) const
    {
        ApplicationContainer apps;
        for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
        {
            apps.Add (InstallPriv (*i));
        }
        return apps;
    }

    Ptr<Application>
    myOnOffHelper::InstallPriv (Ptr<Node> node) const
    {
        Ptr<Application> app = m_factory.Create<Application> ();
        node->AddApplication (app);
        return app;
    }

    int64_t
    myOnOffHelper::AssignStreams (NodeContainer c, int64_t stream)
    {
        int64_t currentStream = stream;
        Ptr<Node> node;
        for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
        {
            node = (*i);
            for (uint32_t j = 0; j < node->GetNApplications (); j++)
            {
                Ptr<myOnOffApplication> onoff = DynamicCast<myOnOffApplication> (node->GetApplication (j));
                if (onoff)
                {
                    currentStream += onoff->AssignStreams (currentStream);
                }
            }
        }
        return (currentStream - stream);
    }

    void
    myOnOffHelper::SetConstantRate (DataRate dataRate, uint32_t packetSize)
    {
        m_factory.Set ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1000]"));
        m_factory.Set ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
        m_factory.Set ("DataRate", DataRateValue (dataRate));
        // m_factory.Set ("PacketSize", UintegerValue (packetSize));

        m_factory.Set ("PacketSize",StringValue ("ns3::ConstantRandomVariable[Constant=532]"));
        m_factory.Set ("Interval", StringValue ("ns3::ConstantRandomVariable[Constant=0.1]"));

    }

} // namespace ns3


//
// Network topology

//     n0--- -----n1


//NS_LOG_COMPONENT_DEFINE ("tcp-one-point2one-point");

int

main (int argc, char *argv[])

{

    //LogComponentEnable("myOnOffApplication",LOG_LEVEL_INFO);

    //LogComponentEnable("myPointToPointHelper",LOG_LEVEL_INFO);
    //LogComponentEnable("myDropTailQueue",LOG_LEVEL_INFO);

    //LogComponentEnable("myQueue",LOG_LEVEL_ALL);

    LogLevel level = (LogLevel) (LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE | LOG_PREFIX_FUNC);

    LogComponentEnable ("Config", level);
    LogComponentEnable ("myPointToPointHelper", level);




    CommandLine cmd;
    cmd.Parse (argc, argv);

    NodeContainer nodes;
    nodes.Create (2);

    myPointToPointHelper pointToPoint;
    //pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    //pointToPoint.SetChannelAttribute ("Delay", StringValue ("1ms"));
    pointToPoint.SetQueue ("ns3::DropTailQueue");

    NetDeviceContainer devices;
    devices=pointToPoint.Install (nodes);



    //NS_LOG_INFO ("Install internet stack on all nodes.");
    InternetStackHelper stack;
    stack.Install (nodes);

    // NS_LOG_INFO ("Assign IP Addresses.");
    Ipv4AddressHelper address;
    address.SetBase ("10.1.1.0", "255.255.255.0");

    Ipv4InterfaceContainer interfaces = address.Assign (devices);


    //NS_LOG_INFO ("Create applications.");
    //
    // Create a packet sink on the star "hub" to receive packets.
    //
    uint16_t port = 50000;

    Address hubLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
    PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", hubLocalAddress);
    ApplicationContainer hubApp = packetSinkHelper.Install (nodes.Get (1));       //接收端 n1 节点
    hubApp.Start (Seconds (0.0));
    hubApp.Stop (Seconds (200.0));


    //
    // Create OnOff applications to send TCP to the hub, one on each spoke node.  //

    myOnOffHelper onOffHelper ("ns3::TcpSocketFactory", Address());
    onOffHelper.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=200]"));
    onOffHelper.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
    onOffHelper.SetAttribute ("MaxBytes",UintegerValue(0) );



   // onOffHelper.SetAttribute ("PacketSize", StringValue ("ns3::ConstantRandomVariable[Constant=137]"));

    onOffHelper.SetAttribute ("PacketSize", StringValue ("ns3::UniformRandomVariable[Min=100|Max=137]"));

    // onOffHelper.SetAttribute ("Interval", StringValue ("ns3::ConstantRandomVariable[Constant=2]"));

    // onOffHelper.SetAttribute ("Interval", StringValue ("ns3::UniformRandomVariable[Min=2.11|Max=8.55]"));

    onOffHelper.SetAttribute ("Interval", StringValue ("ns3::ExponentialRandomVariable[Mean=3.14|Bound=0.0]"));

    ApplicationContainer spokeApps;

    AddressValue remoteAddress (InetSocketAddress (interfaces.GetAddress(1), port));       //远端地址  也就是接收端的IP地址
    onOffHelper.SetAttribute ("Remote", remoteAddress);
    spokeApps.Add(onOffHelper.Install(nodes.Get(0)));
    spokeApps.Start (Seconds (0.0));
    spokeApps.Stop (Seconds (200.0));



    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

    //NS_LOG_INFO ("Enable pcap tracing.");
    //
    // Do pcap tracing on all point-to-point devices on all nodes.
    //
    pointToPoint.EnablePcapAll ("one-point2one-point");

    AnimationInterface::SetConstantPosition (nodes.Get(0),12,12);
    AnimationInterface::SetConstantPosition (nodes.Get(1),24,24);
    AnimationInterface anim ("one-point2one-point.xml");
    anim.EnablePacketMetadata();


// Add the dataset to the plot.
    plot.SetTitle (plotTitle);

    // Make the graphics file, which the plot file will create when it
    // is used with Gnuplot, be a PNG file.
    plot.SetTerminal ("png");

    // Set the labels for each axis.
    plot.SetLegend ("time %s", "delay %ms");

    // Set the range for the x axis.
    plot.AppendExtra ("set xrange [1:+50]");



    Simulator::Run ();
    sort(data_interval,data_interval+48);
    for (int i=0;i<48;i++)
    {

        dataset_interval.Add(i,data_interval[i]);
        dataset_packetsize.Add(i,data_packetsize[i]);
    }

    //  dataset_interval.Add(count_packets,myinterval);
    plot.AddDataset (dataset_interval);

    // Open the plot file.
    std::ofstream plotFile (plotFileName.c_str());

    // Write the plot file.
    plot.GenerateOutput (plotFile);

    // Close the plot file.
    plotFile.close();

    //

    plot2.SetTitle (plotTitle2);

    // Make the graphics file, which the plot file will create when it
    // is used with Gnuplot, be a PNG file.
    plot2.SetTerminal ("png");

    // Set the labels for each axis.
    plot2.SetLegend ("time %second", "bytes %ms");

    // Set the range for the x axis.
    plot2.AppendExtra ("set xrange [-5:+60]");
    plot2.AppendExtra ("set yrange [60:+200]");


    plot2.AddDataset (dataset_packetsize);
    std::ofstream plotFile2 (plotFileName2.c_str());

    // Write the plot file.
    plot2.GenerateOutput (plotFile2);

    // Close the plot file.
    plotFile2.close();



    Simulator::Destroy ();
    // NS_LOG_INFO ("Done.");

    return 0;
}
