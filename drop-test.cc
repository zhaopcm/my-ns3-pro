#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/random-variable-stream.h"
#include "ns3/random-variable-stream-helper.h"
using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE ("uplink-downlink-Example4");

static void RxDrop (Ptr<const Packet> p)
{
    NS_LOG_UNCOND ("RxDrop at " << Simulator::Now ().GetSeconds ());
}

int
main (int argc, char *argv[])
{
    Time::SetResolution (Time::NS);
    LogLevel level = (LogLevel) (LOG_LEVEL_ALL | LOG_PREFIX_TIME | LOG_PREFIX_NODE | LOG_PREFIX_FUNC);

    LogComponentEnable ("Config", level);
    LogComponentEnable ("Queue", level);

    LogComponentEnable ("uplink-downlink-Example4", level);

    //LogComponentEnable ("uplink-downlink-Example4", LOG_LEVEL_INFO);
    LogComponentEnable ("TcpL4Protocol", level);
//    LogComponentEnable ("TcpSocketImpl", LOG_LEVEL_ALL);
    LogComponentEnable ("PacketSink", level);

//Config::SetDefault ("ns3::OnOffApplication::PacketSize", UintegerValue (1024));
//Config::SetDefault ("ns3::OnOffApplication::DataRate", StringValue ("50Mb/s"));
    CommandLine cmd;
    cmd.Parse (argc,argv);

    NodeContainer nodes;
    nodes.Create (2);//创建2个节点

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("10Gbps"));
    pointToPoint.SetChannelAttribute ("Delay", StringValue ("0.002ms"));
    NetDeviceContainer devices;
    devices = pointToPoint.Install (nodes);
    InternetStackHelper stack;
    stack.Install (nodes);

    Ptr<UniformRandomVariable> x =CreateObject<UniformRandomVariable>();
    x->SetAttribute ("Min",DoubleValue(0));
    x->SetAttribute ("Max",DoubleValue(1));

    // Ptr<RateErrorModel> em = CreateObjectWithAttributes<RateErrorModel> ( "RanVar",  StringValue ("ns3::ConstantRandomVariable[Constant=0.000002583]"), "ErrorRate", DoubleValue (0.00001));
    Ptr<RateErrorModel> em_1 = CreateObjectWithAttributes<RateErrorModel> ( "RanVar", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=1.0]"),"ErrorRate", DoubleValue (0.0001));
    devices.Get(0)->SetAttribute("ReceiveErrorModel", PointerValue (em_1));

    devices.Get(0)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback (&RxDrop));


    Ptr<RateErrorModel> em_2 = CreateObjectWithAttributes<RateErrorModel> ( "RanVar", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=1.0]"),"ErrorRate", DoubleValue (0.0001));
    devices.Get(1)->SetAttribute("ReceiveErrorModel", PointerValue (em_2));

    devices.Get(1)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback (&RxDrop));
    //



    Ipv4AddressHelper address;
    address.SetBase ("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign (devices);

    uint16_t port_1 = 50000;
    ApplicationContainer sinkApp_1;
    Address sinkLocalAddress_1 (InetSocketAddress (Ipv4Address::GetAny (), port_1));
    PacketSinkHelper sinkHelper_1 ("ns3::TcpSocketFactory", sinkLocalAddress_1);
    sinkApp_1.Add(sinkHelper_1.Install(nodes.Get(1)));                // Packet sink 安装在第二个节点上

    sinkApp_1.Start (Seconds (0.0));
    sinkApp_1.Stop (Seconds (30.0));

    OnOffHelper clientHelper_1 ("ns3::TcpSocketFactory", Address ());

//clientHelper.SetAttribute ("OffTime", StringValue ("ns3::ExponentialRandomVariable[Mean=0.01|Variance=0.5|Bound=0.0]"));
    clientHelper_1.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0.0002583]"));

///注意是竖线分隔   各个不同的参数
    clientHelper_1.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=0.0001583]"));

    clientHelper_1.SetAttribute ("PacketSize", UintegerValue (1024));
    clientHelper_1.SetAttribute ("DataRate", StringValue ("1Mbps"));

    ApplicationContainer clientApps_1;
//节点1>节点2
    AddressValue remoteAddress_1
            (InetSocketAddress (interfaces.GetAddress (1), port_1));
    clientHelper_1.SetAttribute("Remote",remoteAddress_1);
    clientApps_1.Add(clientHelper_1.Install(nodes.Get(0)));


    clientApps_1.Start(Seconds(1.0));
    clientApps_1.Stop (Seconds(10.0));



    uint16_t port_2 = 50001;
    ApplicationContainer sinkApp_2;
    Address sinkLocalAddress_2 (InetSocketAddress (Ipv4Address::GetAny (), port_2));
    PacketSinkHelper sinkHelper_2 ("ns3::TcpSocketFactory", sinkLocalAddress_2);
    sinkApp_2.Add(sinkHelper_2.Install(nodes.Get(0)));                // Packet sink 安装在第二个节点上

    sinkApp_2.Start (Seconds (0.0));
    sinkApp_2.Stop (Seconds (30.0));

    OnOffHelper clientHelper_2 ("ns3::TcpSocketFactory", Address ());

//clientHelper.SetAttribute ("OffTime", StringValue ("ns3::ExponentialRandomVariable[Mean=0.01|Variance=0.5|Bound=0.0]"));
    clientHelper_2.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0.0002583]"));

///注意是竖线分隔   各个不同的参数
    clientHelper_2.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=0.0001583]"));

    clientHelper_2.SetAttribute ("PacketSize", UintegerValue (1024));
    clientHelper_2.SetAttribute ("DataRate", StringValue ("100Mbps"));

    ApplicationContainer clientApps_2;
//节点1>节点2
    AddressValue remoteAddress_2
            (InetSocketAddress (interfaces.GetAddress (0), port_2));
    clientHelper_2.SetAttribute("Remote",remoteAddress_2);
    clientApps_2.Add(clientHelper_2.Install(nodes.Get(1)));


    clientApps_2.Start(Seconds(1.0));
    clientApps_2.Stop (Seconds(10.0));




    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
//嗅探,记录所有节点相关的数据包
    pointToPoint.EnablePcapAll("uplink-downlink-Tcp4");

    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}
