// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// NetPacket::readWrapperMessage ported from Open-BFME-1's
// GameNetwork/NetPacket.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way the body places uniquely on unclaimed game.dat .text at 0x0058E0E2
// (299B) by masked whole-.text search, and ./build.sh reproduces it byte for
// byte. Its NetWrapperCommandMsg setter callees are read off retail's call
// sites; four of them are ICF-folded one-store setters already rowed under
// other names. Only this body is carried; the donor's other definitions are
// omitted.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

////////// NetPacket.cpp ///////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "GameNetwork/NetPacket.h"
#include "GameNetwork/NetCommandMsg.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/NetworkUtil.h"
#include "GameNetwork/GameMessageParser.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// BFME's NetCommandRef holds the command pointer at +0x00 and the relay at
// +0x0c; the reference header puts them at +0x04 and +0x10. Every buffer-fill
// body below reaches both through this view rather than the accessors.
struct BfmeNetCommandRef
{
	NetCommandMsg *m_command;
	UnsignedByte m_unreconstructed_04[0x0c - 4];
	UnsignedByte m_relay;
};

// BFME's frame command carries three payload words after the header, at +0x1c,
// +0x20 and +0x24 of the message.
struct BfmeNetFrameCommandMsg
{
	UnsignedByte getNetCommandType() const { return (UnsignedByte)m_commandType; }
	UnsignedByte getPlayerID() const { return (UnsignedByte)m_playerID; }
	UnsignedShort getID() const { return m_id; }

	UnsignedByte m_unreconstructed_00[0x0c];
	UnsignedInt m_playerID;					///< retail this+0x0c
	UnsignedShort m_id;					///< retail this+0x10
	UnsignedShort m_unreconstructed_12;
	Int m_commandType;					///< retail this+0x14
	Int m_referenceCount;					///< retail this+0x18
	UnsignedInt m_frame;					///< retail this+0x1c
	UnsignedInt m_unreconstructed_20;			///< retail this+0x20
	UnsignedInt m_commandCount;				///< retail this+0x24
};

// BFME packs the destination port next to the address instead of leaving it
// after m_lastFrame, so the reference class cannot express the retail store
// offsets used by init and the command builders below.
struct BfmeNetPacketAddress
{
	BfmeNetPacketAddress() { m_ip = 0; m_port = 0; }

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct BfmeNetPacketFields
{
	UnsignedByte m_unreconstructed_00[0x04];
	UnsignedByte m_packet[0x1dc];
	Int m_packetLen;
	BfmeNetPacketAddress m_dest;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;			///< retail this+0x1f0
	UnsignedInt m_lastFrame;			///< retail this+0x1f4
	UnsignedShort m_lastCommandID;			///< retail this+0x1f8
	UnsignedByte m_lastPlayerID;			///< retail this+0x1fa
	UnsignedByte m_lastCommandType;			///< retail this+0x1fb
	UnsignedByte m_lastRelay;			///< retail this+0x1fc
};

// BFME's string buffers cache the character count in the block header, so its
// getLength() is a two-byte load; the reference header has no such field and
// its getLength() calls strlen. Every body below that measures a string a
// message returns reads the cached count instead.
struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;				///< retail m_data+0x04
	UnsignedShort m_unreconstructed_06;
};


// BFME's ACK messages carry the acking player's ID at +0x20, a field the
// reference class does not have, and every repeat test compares it.
struct BfmeNetAckCommandMsg
{
	UnsignedByte m_unreconstructed_00[0x20];
	UnsignedInt m_ackPlayerID;
};


NetCommandMsg * NetPacket::readWrapperMessage(UnsignedByte *data, Int &i) {
	NetWrapperCommandMsg *msg = newInstance(NetWrapperCommandMsg);

	// get the wrapped command ID
	UnsignedShort wrappedCommandID = 0;
	memcpy(&wrappedCommandID, data + i, sizeof(wrappedCommandID));
	msg->setWrappedCommandID(wrappedCommandID);
	i += sizeof(wrappedCommandID);
	DEBUG_LOG(("NetPacket::readWrapperMessage - wrapped command ID == %d\n", wrappedCommandID));

	// get the chunk number.
	UnsignedInt chunkNumber = 0;
	memcpy(&chunkNumber, data + i, sizeof(chunkNumber));
	msg->setChunkNumber(chunkNumber);
	i += sizeof(chunkNumber);
	DEBUG_LOG(("NetPacket::readWrapperMessage - chunk number = %d\n", chunkNumber));

	// get the number of chunks
	UnsignedInt numChunks = 0;
	memcpy(&numChunks, data + i, sizeof(numChunks));
	msg->setNumChunks(numChunks);
	i += sizeof(numChunks);
	DEBUG_LOG(("NetPacket::readWrapperMessage - number of chunks = %d\n", numChunks));

	// get the total data length
	UnsignedInt totalDataLength = 0;
	memcpy(&totalDataLength, data + i, sizeof(totalDataLength));
	msg->setTotalDataLength(totalDataLength);
	i += sizeof(totalDataLength);
	DEBUG_LOG(("NetPacket::readWrapperMessage - total data length = %d\n", totalDataLength));

	// get the data length for this chunk
	UnsignedInt dataLength = 0;
	memcpy(&dataLength, data + i, sizeof(dataLength));
	i += sizeof(dataLength);
	DEBUG_LOG(("NetPacket::readWrapperMessage - data length = %d\n", dataLength));

	UnsignedInt dataOffset = 0;
	memcpy(&dataOffset, data + i, sizeof(dataOffset));
	msg->setDataOffset(dataOffset);
	i += sizeof(dataOffset);
	DEBUG_LOG(("NetPacket::readWrapperMessage - data offset = %d\n", dataOffset));

	msg->setData(data + i, dataLength);
	i += dataLength;

	return msg;
}


