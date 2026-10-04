// ??0ConnectionManager@@QAE@XZ
// partial score=0.98 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /Og /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0ConnectionManager@@QAE@XZ @ 0x004D274B 263B
// ConnectionManager::ConnectionManager: vtable + history[9] via ??_H + transport/localSlot/router + maps/set/array via ??_L + 8-way loop.
// Evidence: offsets match getFileTransferProgress layout 0x12138/0x12150; rowed ctors map<int void*> 0x33C432 set<AsciiString> 0xD3A71 ??_H ??_L; donor ConnectionManagerConstructor.cpp same init and loop.
#include <map>
#include <set>
#include <string.h>
#include "ascii_string.h"

struct CommandHistory
{
	unsigned int words[0x800];
	CommandHistory() { memset(words, 0, sizeof(words)); words[0] = 0; }
};

class Connection;
class DisconnectManager;
class FrameDataManager;
class NetCommandList;
class NetCommandWrapperList;

class ConnectionManager
{
public:
	ConnectionManager();
	virtual void init();
	virtual void reset();
	virtual void update(bool isInGame, bool phase);
	Connection *m_connections[8];
	CommandHistory m_history[9];
	void *m_transport;
	int m_localSlot;
	int m_packetRouterSlot;
	int m_packetRouterFallback[8];
	unsigned int m_12050;
	unsigned short m_12054;
	char m_12056pad[2];
	AsciiString m_12058;
	unsigned int m_1205c;
	unsigned int m_12060[8];
	unsigned int m_12080[8];
	unsigned int m_120a0[8];
	unsigned int m_120c0[8];
	unsigned int m_120e0[8];
	unsigned int m_12100;
	unsigned int m_12104[8];
	unsigned int m_12124;
	unsigned int m_12128;
	unsigned int m_1212c;
	unsigned int m_12130;
	bool m_12134;
	bool m_12135;
	char m_12136pad[2];
	_STL::map<int, void *> m_12138;
	_STL::set<AsciiString> m_12144;
	_STL::map<int, void *> m_12150[8];
};

// ??0ConnectionManager@@QAE@XZ present-unmatched
ConnectionManager::ConnectionManager()
	: m_transport(0), m_localSlot(-1), m_packetRouterSlot(0),
	  m_12050(0), m_12054(0), m_1205c(0),
	  m_12100(0), m_12124(0), m_12128(0), m_1212c(0), m_12130(0),
	  m_12134(false), m_12135(true)
{
	for (int i = 0; i < 8; ++i)
	{
		m_connections[i] = 0;
		m_packetRouterFallback[i] = -1;
		m_12104[i] = 0;
		m_12060[i] = 0;
		m_120c0[i] = 0;
		m_120e0[i] = 0;
		m_12080[i] = 0;
		m_120a0[i] = 1;
	}
}
