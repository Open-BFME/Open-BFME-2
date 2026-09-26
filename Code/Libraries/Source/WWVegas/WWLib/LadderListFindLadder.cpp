// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?findLadder@LadderList@@QAEPBVLadderInfo@@ABVAsciiString@@G@Z, retail 0x0054D74B, 151 bytes.
// Gap between two rows of stlport_list_asciistring_insert.cpp; flags copied
// from that TU. Searches the three ladder lists (special at +4, standard at
// +8, local at +0) for AsciiString at +0x28 plus port at +0x2C via rowed
// StringBase<char>::compare 0x000069D6. Donor is BFME1
// Code/GameEngine/Source/GameNetwork/GameSpy/LadderList_findLadder_Thunk.cpp
// (readable body of same mangled) plus upstream ZH LadderDefs.h layout
// (three LadderInfoList, LadderInfo with address/port tail). Identity is the
// GUI:JoinFailedUnknownLadder caller at 0x005A59CE plus TheLadderList global
// at 0x00A05FB0; class name is the real donor name.

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &other) const;
private:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString();
	~AsciiString();
};

struct LadderListNode
{
	LadderListNode *next;
	LadderListNode *prev;
	void *value;
};

class LadderInfo
{
public:
	char m_pad[0x28];
	AsciiString address;
	unsigned short port;
};

class LadderList
{
public:
	const LadderInfo *findLadder(const AsciiString &addr, unsigned short port);

private:
	LadderListNode *m_localLadders;
	LadderListNode *m_specialLadders;
	LadderListNode *m_standardLadders;
};

const LadderInfo *LadderList::findLadder(const AsciiString &addr, unsigned short port)
{
	for (LadderListNode *n = m_specialLadders->next; n != m_specialLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *n = m_standardLadders->next; n != m_standardLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *n = m_localLadders->next; n != m_localLadders; n = n->next)
	{
		LadderInfo *li = (LadderInfo *)n->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	return 0;
}
