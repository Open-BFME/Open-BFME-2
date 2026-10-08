#pragma once
#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_
#include "GameNetwork/NetworkDefs.h"
struct TransportAddress;
// BFME2 Transport constructor/destructor providers establish a nonvirtual object
// of 0x41148 bytes (new in native004CF692). TransportCtor.cpp proves the
// message-ring layout; the existing transport/NetworkDefs.h supplies their
// 0x40E stride. Keep the unaccessed tail opaque in this TU-scoped call view.
class Transport {
public:
 Transport(); ~Transport();
 Bool init(AsciiString,UnsignedShort); Bool init(UnsignedInt,UnsignedShort);
 Bool init(const TransportAddress*);
 void reset(); void Rva004D5496(); Bool update(); Bool doRecv(); Bool doSend();
 Bool queueSend(UnsignedInt,UnsignedShort,const UnsignedByte*,Int);
 Bool allowBroadcasts(Bool); void setLatency(Bool); void setPacketLoss(Bool);
 Real getIncomingBytesPerSecond(); Real getIncomingPacketsPerSecond();
 Real getOutgoingBytesPerSecond(); Real getOutgoingPacketsPerSecond();
 Real getUnknownBytesPerSecond(); Real getUnknownPacketsPerSecond();
TransportMessage m_outBuffer[128];
 TransportMessage m_inBuffer[128];
private: char nativeTail[0x348];
};
typedef char TransportExtentCheck[sizeof(Transport)==0x41148?1:-1];
#endif
