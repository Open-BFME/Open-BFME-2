// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0025E75F@Rva0025E4CD@@QAEXXZ
// Retail 0x0025E75F..0x0025E970 (529 bytes): the network's command pump
// (Zero Hour Network::GetCommandsFromCommandList; WorldBuilder twin
// 0x00E961E0 by callgraph score 2.0 carries its NETWORK_PACKETROUTER and
// NETWORK_QUIT debug strings). Called by ?rva0025E970@Rva0025E4CD@@QAEXH@Z.
// Walks TheCommandList (+0x0C first; message +0x04 next and +0x10 type):
// transfer commands (1000 < type < 1999) go to the connection manager
// (+0x0C) unless it is the packet router while leaving (slot +0xFC) and
// only while in game (+0x10 == 1); type 0x1D (player leave) in game outside
// TheGameLogic's +0x71 state is handed to the manager (0x004D0A0A) when the
// mode word +0x114 is 3 or the message's single argument is 2; both kinds are
// removed (TheCommandList slot +0x40) and freed (slot 0 then operator delete).
// Then a lone living-world player (manager getNumPlayers <= 1; TheGameInfo
// slot +0x4C; multiplayer mode 0x00210C66; TheLivingWorldLogic +0xB4/+0xB5
// through the folded 0x0004253A) with at most one key from
// LivingWorldLogic::rva002B693F counts as leaving; when leaving (or the
// manager says 0x004CF3E1) in game it processes the local player's leave
// (slot +0xB8 is the local player id) queues a destroy-player command
// (Rva004D57AE 0x004D57AE) through 0x0025E539 and enters
// status 2.
#include "../Common/GameLogicObjectLookupView.h"

#include "../../Include/Common/MessageStream.h"

template <int N> class Rva0025E75FSlots : public Rva0025E75FSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0025E75FSlots<0>
{
};

class CommandList : public Rva0025E75FSlots<16>
{
public:
	virtual void removeMessage(GameMessage *msg);	// +0x40
	GameMessage *getFirstMessage() { return m_firstMessage; }
	unsigned char m_pad04[0x0C - 0x04];
	GameMessage *m_firstMessage;		// +0x0C
};
extern CommandList *TheCommandList;

#include "../../Include/GameNetwork/GameInfo.h"
extern GameInfo *TheGameInfo;

enum PlayerLeaveCode
{
	PLAYERLEAVECODE_UNKNOWN = 0
};

#include "../../Include/GameNetwork/ConnectionManager.h"
class BFMEConnectionManager
{
public:
	bool isPacketRouter();			// 0x004CF9CD
	int isPlayerSlotActive(int playerID);	// 0x004CF0CD
};
class Rva004CF0FB
{
public:
	int rva004CF0FB(int playerID);		// 0x004CF0FB
};

class NetCommandMsg
{
public:
	void detach();				// 0x004D55BC
};
class Rva004D57AE : public NetCommandMsg
{
public:
	Rva004D57AE();		// 0x004D57AE
	void setPlayerIndex(unsigned int playerIndex);	// 0x00318B09
	unsigned char m_pad00[0x0C];
	int m_0C;				// +0x0C
	unsigned char m_pad10[0x20 - 0x10];
};
class NetWrapperCommandMsg;

#include "../../Include/GameNetwork/Rva00210C66CmpBoolField.h"
#include "../../Include/Common/BfmeSelectionState.h"

// The int set LivingWorldLogic::rva002B693F fills: an STLport set<int>.
// Its ctor is the folded 0x000D3A71 (pinned as the opaque Rva002EE9B7 set
// ctor); its inline dtor destroys the tree (0x000730DE) in place while the
// unwind funclet calls the out-of-line set dtor 0x00073116 (a jmp to the
// tree dtor).
#include "../../Include/Common/Rva00072FE6.h"
// LINK: the folded ctor 0x000D3A71 is rowed as set<AsciiString>::set().
class AsciiString;
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class K, class C, class A> class set
{
public:
	set();
	void *m_header;
	unsigned int m_count;
	unsigned char m_compare;
};
}
class Rva00073116 : public _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> >
{
public:
	~Rva00073116() { ((Rva00072FE6 *)this)->~Rva00072FE6(); }
	unsigned int size() const { return m_count; }
};

#include "../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;
extern GameLogic *TheGameLogic;

struct Rva0025E75FLogic
{
	unsigned char m_pad00[0x71];
	bool m_71;				// +0x71
	unsigned char m_pad72[0x114 - 0x72];
	int m_114;				// +0x114
};

#include "../../Include/GameNetwork/NetworkInterfaceClass.h"

class Rva0025E4CD : public Rva0025E75FSlots<46>
{
public:
	virtual int getLocalPlayerID();		// +0xB8
	virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50();
	virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58();
	virtual void s59(); virtual void s60(); virtual void s61(); virtual void s62();
	virtual bool isLeaving();		// +0xFC

	void rva0025E75F();

	unsigned char m_pad04[0x0C - 0x04];
	ConnectionManager *m_conMgr;		// +0x0C
	int m_localStatus;			// +0x10
};

static inline void deleteMessage(GameMessage *msg)
{
	::delete msg;
}

void Rva0025E4CD::rva0025E75F()
{
	GameMessage *msg = TheCommandList->getFirstMessage();
	while (msg != 0)
	{
		GameMessage *next = msg->next();
		int type = msg->getType();
		if (type > 1000 && type < 1999)
		{
			if (m_localStatus == 1 && m_conMgr != 0)
			{
				if (!((BFMEConnectionManager *)m_conMgr)->isPacketRouter() || !isLeaving())
					m_conMgr->sendLocalGameMessage(msg);
			}
			TheCommandList->removeMessage(msg);
			deleteMessage(msg);
		}
		else if (type == 0x1D)
		{
			Rva0025E75FLogic *logic = (Rva0025E75FLogic *)TheGameLogic;
			if (!logic->m_71 && m_localStatus == 1
				&& (logic->m_114 == 3 || (msg->getArgumentCount() == 1 && *(const int *)msg->getArgument(0) == 2)))
			{
				m_conMgr->rva004D0A0A();
				TheCommandList->removeMessage(msg);
				deleteMessage(msg);
			}
		}
		msg = next;
	}

	bool leaving = false;
	if (m_conMgr != 0 && m_conMgr->getNumPlayers() <= 1 && TheGameInfo != 0 && TheGameInfo->isMultiPlayer()
		&& ((Rva00210C66CmpBoolField *)TheGameLogic)->get() && TheLivingWorldLogic != 0
		&& ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
	{
		Rva00073116 keys;
		TheLivingWorldLogic->rva002B693F(&keys);
		if (keys.size() <= 1)
			leaving = true;
	}

	if (m_conMgr != 0 && m_localStatus == 1 && (m_conMgr->rva004CF3E1() || leaving))
	{
		if (m_conMgr != 0)
			m_conMgr->processPlayerLeave((unsigned char)getLocalPlayerID());
		if ((((BFMEConnectionManager *)m_conMgr)->*reinterpret_cast<bool (BFMEConnectionManager::*)(int)>(&BFMEConnectionManager::isPlayerSlotActive))(getLocalPlayerID())
			&& ((Rva004CF0FB *)m_conMgr)->rva004CF0FB(getLocalPlayerID()) == 0)
		{
			Rva004D57AE *cmd = new Rva004D57AE;
			cmd->m_0C = getLocalPlayerID();
			cmd->setPlayerIndex(getLocalPlayerID());
			((NetworkInterface *)this)->ProcessDestroyPlayerCommand((NetWrapperCommandMsg *)cmd);
			cmd->detach();
		}
		m_localStatus = 2;
	}
}
