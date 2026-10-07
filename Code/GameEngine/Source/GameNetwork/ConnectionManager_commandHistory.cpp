// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// The relay loop's duplicate filter:
//   BFMECommandIDHistory::accept,             retail 0x004D2164, 75 bytes
//   BFMEConnectionManager::isDuplicateCommand, retail 0x004D2667, 127 bytes
//
// Reference: Open-BFME-1 native_connection_timing.cpp, the two functions of
// the same names (BFME 1 0x006688D0 and 0x006693C0); names are carried from
// that donor. A router filters each originating player's command IDs through
// that player's history; a client filters the router's stream through the
// ninth. A true result means the copy was already accepted.
// Target evidence: the relay loop 0x004D316A skips processNetCommand when
// 0x004D2667 returns true; 0x004D2667 calls 0x004D2164 on this+0x24+slot*0x2000
// or this+0x10024, the nine 0x2000-byte histories the matched destructor
// layout leaves at +0x24.
// BFME 2 differences read from these bodies: the history is an STL bitset
// whose test is the out-of-line, folded _Unchecked_test 0x001E37E8 (rowed
// under bitset<45>) while the set is inline; the clear window is the rowed
// 0x004D1EB1; the router passes the next logic frame.
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

enum
{
	MAX_SLOTS = 8
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_pad00[0x40];
	UnsignedInt m_frame;
};

class GlobalData
{
public:
	char m_pad000[0xd24];
	Bool m_commandIDFiltering;
};

extern GameLogic *TheGameLogic;
extern GlobalData *TheGlobalData;

class NetCommandMsg
{
public:
	UnsignedInt getExecutionFrame() const { return m_executionFrame; }
	UnsignedInt getPlayerID() const { return m_playerID; }
	UnsignedShort getID() const { return m_id; }
	NetCommandType getNetCommandType() const { return m_commandType; }

protected:
	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

Bool DoesCommandRequireACommandID(NetCommandType type);

// The clear window ahead of a command ID, rowed under its address name.
class Rva004D1EB1
{
public:
	void rva004D1EB1(UnsignedShort commandID);
};

typedef _STL::bitset<45> Rva001E37E8Bits;

class BFMECommandIDHistory
{
public:
	Bool accept(UnsignedShort commandID, UnsignedInt frame);

private:
	Bool isSet(UnsignedInt id) const { return ((const Rva001E37E8Bits *)this)->_Unchecked_test(id); }
	void set(UnsignedInt id) { m_bits[id >> 5] |= 1u << (id & 31); }

	UnsignedInt m_bits[0x800];
};

class BFMEConnectionManager
{
public:
	Bool isDuplicateCommand(NetCommandMsg *msg);

private:
	char m_pad00000[0x24];
	BFMECommandIDHistory m_commandHistory[9];
	char m_pad12024[0x12028 - 0x12024];
	Int m_localSlot;
	Int m_packetRouterSlot;
};

Bool BFMECommandIDHistory::accept(UnsignedShort commandID, UnsignedInt frame)
{
	if (TheGlobalData->m_commandIDFiltering)
	{
		((Rva004D1EB1 *)this)->rva004D1EB1(commandID);
		UnsignedInt id = commandID;
		if (isSet(id))
			return false;
		set(commandID);
	}
	return true;
}

Bool BFMEConnectionManager::isDuplicateCommand(NetCommandMsg *msg)
{
	if (m_localSlot == m_packetRouterSlot)
	{
		if (msg->getPlayerID() != m_packetRouterSlot && msg->getPlayerID() < MAX_SLOTS &&
			DoesCommandRequireACommandID(msg->getNetCommandType()))
		{
			if (!m_commandHistory[msg->getPlayerID()].accept(msg->getID(), TheGameLogic->getFrame() + 1))
				return true;
		}
	}
	else
	{
		if (msg->getPlayerID() == m_packetRouterSlot &&
			DoesCommandRequireACommandID(msg->getNetCommandType()))
		{
			if (!m_commandHistory[8].accept(msg->getID(), msg->getExecutionFrame()))
				return true;
		}
	}
	return false;
}
