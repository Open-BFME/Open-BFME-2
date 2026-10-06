// ?Rva0038190FSendChat@@YA_NABVUnicodeString@@ABV?$vector@IV?$allocator@I@_STL@@@_STL@@@Z
// partial score=0.8415 date=2026-10-05
// ?Rva0038190FSendChat@@YA_NABVUnicodeString@@ABV?$vector@IV?$allocator@I@_STL@@@_STL@@@Z
// partial score=0.90 date=2026-09-30
// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0038190FSendChat@@YA_NABVUnicodeString@@ABV?$vector@IV?$allocator@I@_STL@@@_STL@@@Z @0x0038190F (440B)
// Chat send via TheNetwork: builds recipient mask from slot list, formats via TheGameText fetch.
// Evidence: chain from 0x002AA231 bfmeAskRV; strings APT:ObserverChat APT:GlobalChat APT:PrivateChat;
// callees rowed vector copy 0x2CFAB9 push_back 0x4DFCB0 getSlot 0x3FF29F isHuman 0x3FF0F1
// nameToKey 0x9FA65 findPlayer 0x2A7A41 format 0x6CB660 StringBase copy 0x37050 release 0x36E70 free 0x30830.
#include <vector>

typedef int Int;
typedef bool Bool;
typedef unsigned short Wide;
typedef unsigned short WideChar;

class AsciiString;
class UnicodeString;

template <class T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
	StringBase(const T *s);
	StringBase(const StringBase<T> &that);
	void releaseBuffer();
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &o) : StringBase<char>(o) {}
	~AsciiString() {}
};

class UnicodeString : public StringBase<Wide>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &o) : StringBase<Wide>(o) {}
	~UnicodeString() {}
	void __cdecl format(const UnicodeString *fmt, ...);
	void __cdecl format(const Wide *fmt, ...);
	const WideChar *str() const
	{
		static const WideChar TheNullChr = 0;
		return m_data ? &m_data->data[0] : &TheNullChr;
	}
};

class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

class Player
{
public:
	int dummy;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(int key);
private:
	char m_pad00[0x10];
public:
	BfmeMemberRV *m_local10;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};

class GameSlot
{
public:
	bool isHuman() const;
private:
	void *m_vtable;
	int m_state;
	char m_pad08[0x34 - 0x08];
public:
	AsciiString m_name34;
};

class GameInfo
{
public:
	GameSlot *getSlot(int i);
};

class GameLogic
{
public:
	char m_pad[0x110];
	int m_110;
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual const UnicodeString &slot44(const char *label, bool *exists = 0) = 0;
};

class NetworkInterface
{
public:
	virtual ~NetworkInterface() {}
	virtual void n00() = 0;
	virtual void n01() = 0;
	virtual void n02() = 0;
	virtual void n03() = 0;
	virtual void n04() = 0;
	virtual void n05() = 0;
	virtual void n06() = 0;
	virtual void n07() = 0;
	virtual void n08() = 0;
	virtual void n09() = 0;
	virtual void n10() = 0;
	virtual void n11() = 0;
	virtual void n12() = 0;
	virtual void n13() = 0;
	virtual void n14() = 0;
	virtual void n15() = 0;
	virtual void n16() = 0;
	virtual void n17() = 0;
	virtual void n18() = 0;
	virtual void n19() = 0;
	virtual void n20() = 0;
	virtual void n21() = 0;
	virtual void n22() = 0;
	virtual void n23() = 0;
	virtual void n24() = 0;
	virtual void sendChat(UnicodeString text, int mask) = 0;
};

extern NetworkInterface *TheNetwork;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameTextInterface *TheGameText;

class ModuleData
{
public:
	int dummy;
};

bool Rva0038190FSendChat(const UnicodeString &msg, const _STL::vector<unsigned int> &selected)
{
	if (TheNetwork == 0)
		return false;
	if (TheGameLogic->m_110 == 3)
		return false;
	BfmeMemberRV *local = ThePlayerList->m_local10;
	if (local == 0)
		return false;
	bool notRV = !local->bfmeAskRV();
	unsigned int mask = 0;
	_STL::vector<unsigned int> list(selected);
	if (list.begin() == list.end())
	{
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = TheGameInfo->getSlot(i);
			if (slot == 0)
				continue;
			if (!slot->isHuman())
				continue;
			((_STL::vector<const ModuleData *> *)&list)->push_back(*(const ModuleData *const *)&i);
		}
	}
	for (_STL::vector<unsigned int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		unsigned int idx = *it;
		GameSlot *slot = TheGameInfo->getSlot(idx);
		if (slot == 0)
			continue;
		NameKeyType key = TheNameKeyGenerator->nameToKey(slot->m_name34);
		Player *player = ThePlayerList->findPlayerWithNameKey(key);
		if (player == 0)
			continue;
		if (notRV)
		{
			if (((BfmeMemberRV *)player)->bfmeAskRV())
				continue;
		}
		mask |= 1u << idx;
	}
	UnicodeString chatText;
	if (notRV)
	{
		chatText.format(&TheGameText->slot44("APT:ObserverChat", 0), msg.str());
	}
	else
	{
		if (selected.begin() == selected.end())
		{
			chatText.format(&TheGameText->slot44("APT:GlobalChat", 0), msg.str());
		}
		else
		{
			chatText.format(&TheGameText->slot44("APT:PrivateChat", 0), msg.str());
		}
	}
	TheNetwork->sendChat(chatText, mask);
	return true;
}
