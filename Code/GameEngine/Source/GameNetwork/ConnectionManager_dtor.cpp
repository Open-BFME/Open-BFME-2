// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ConnectionManager::~ConnectionManager, retail 0x004D2344, 350 bytes.
//
// Reference: Zero Hour GameEngine/Source/GameNetwork/ConnectionManager.cpp
// ~ConnectionManager (free the transport, every frame data ring and
// connection, the disconnect menu and manager and the three command lists,
// then empty the file-transfer maps).
// BFME 2 differences read from this body: there is no local user; the pointers
// are freed without being cleared; frame data and connection are freed in one
// loop; the disconnect menu goes through 0x00512C88; the command lists and the
// disconnect manager (0x28C bytes, built by init with 0x004D376A) are freed
// with the global delete after their virtual destructors; and the file maps
// are members (+0x12138, +0x12144 and eight at +0x12150), destroyed after the
// body, with the local player's name at +0x12058.
// Layout: the vtable is 0xC601C0 (init, reset, update, ...), as stored by the
// matched constructor 0x004D274B; offsets agree with init 0x004D24A2 and
// disconnectPlayer 0x004D13F8.

#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

enum
{
	MAX_SLOTS = 8
};

#include "../../Include/GameNetwork/Transport.h"

// Connection, held in the ledger under its destructor's address name.
class Rva004D060B
{
public:
	~Rva004D060B();
};

class FrameDataManager
{
public:
	virtual ~FrameDataManager();
};

class NetCommandList
{
public:
	virtual ~NetCommandList();
};

class NetCommandWrapperList
{
public:
	virtual ~NetCommandWrapperList();
};

// The disconnect manager, held in the ledger under its constructor's address
// name.
class Rva004D376A
{
public:
	virtual ~Rva004D376A();
};

struct Rva004D1B38Mapped
{
	AsciiString m_name;
};

// The file recipient-mask map's tree (clear 0x004D0F82, destructor 0x004D1AC3).
class Rva004D0545
{
public:
	~Rva004D0545();
	void rva004D0F82();

private:
	void *m_header;
	Int m_nodeCount;
	Int m_compare;
};

// One file-progress map's tree (clear 0x004D0FAB, destructor 0x004D1B00).
class Rva004D0572
{
public:
	~Rva004D0572();
	void rva004D0FAB();

private:
	void *m_header;
	Int m_nodeCount;
	Int m_compare;
};

// The map around it; its destructor is the tail jump 0x004D1D32 that the
// member array's teardown is given.
class Rva004D1D32
{
public:
	void clear() { m_tree.rva004D0FAB(); }

private:
	Rva004D0572 m_tree;
};

void Rva00512C88Shutdown();

class ConnectionManager
{
public:
	~ConnectionManager();
	virtual void init();
	virtual void reset();
	virtual void update(bool isInGame, int frameAdvanced);

private:
	Rva004D060B *m_connections[MAX_SLOTS];
	char m_pad00024[0x12024 - 0x24];
	Transport *m_transport;
	char m_pad12028[0x12058 - 0x12028];
	UnicodeString m_localPlayerName;
	char m_pad1205C[0x12100 - 0x1205c];
	Rva004D376A *m_disconnectManager;
	FrameDataManager *m_frameData[MAX_SLOTS];
	NetCommandList *m_pendingCommands;
	NetCommandList *m_relayedCommands;
	NetCommandWrapperList *m_netCommandWrapperList;
	char m_pad12130[0x12138 - 0x12130];
	_STL::map<Int, Rva004D1B38Mapped> m_fileCommandMap;
	Rva004D0545 m_fileRecipientMaskMap;
	Rva004D1D32 m_fileProgressMap[MAX_SLOTS];
};

ConnectionManager::~ConnectionManager()
{
	if (m_transport != 0)
		delete m_transport;

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (m_frameData[i] != 0)
			::delete m_frameData[i];
		if (m_connections[i] != 0)
			delete m_connections[i];
	}

	Rva00512C88Shutdown();

	if (m_disconnectManager != 0)
		::delete m_disconnectManager;
	if (m_pendingCommands != 0)
		::delete m_pendingCommands;
	if (m_relayedCommands != 0)
		::delete m_relayedCommands;
	if (m_netCommandWrapperList != 0)
		::delete m_netCommandWrapperList;

	m_fileCommandMap.clear();
	m_fileRecipientMaskMap.rva004D0F82();
	for (Int j = 0; j < MAX_SLOTS; ++j)
		m_fileProgressMap[j].clear();
}
