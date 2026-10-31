// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva004FDB57@Rva004FDB57@@QAEXVAsciiString@@@Z, retail 0x004FDB57, 83 bytes.
// Assigns the by-value AsciiString arg into the member at +0x1000 via the
// pinned AsciiString::operator= at 0x000366F0, resolves an int through the
// GameSpy global at 0x00A02320 slot 0x120 (same object as the rowed
// getLocalProfileID slot 0x7C caller), stores it at +0x1004, then releases
// the by-value arg via the rowed StringBase releaseBuffer at 0x00036410.
// Evidence: EH-prolog + state 0/-1 shape; caller 0x005AF5BF; AsciiString is
// 4 bytes here (single-word StringBase) so the arg fits ret 4.
#include "ascii_string.h"
#include <map>


template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class VSlots<0>
{
};

template <class B, int N> class VPad : public VPad<B, N - 1>
{
public:
	virtual void pad(B *, char (*)[N]) = 0;
};

template <class B> class VPad<B, 0> : public B
{
};


class GameSpyStagingRoom;

class PlayerInfo
{
public:
	AsciiString m_name;
	AsciiString m_locale;
	AsciiString m_clan;
	int m_wins;
	int m_losses;
	int m_profileID;
	int m_flags;
	int m_rankPoints;
	int m_side;
	int m_unk24;
	int m_dc;
	int m_desync;
	int m_preorder;
};

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};

typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

class GameSpyInfoSlot22 : public VSlots<21>
{
public:
	virtual PlayerInfoMap *getPlayerInfoMap(void) = 0;		// slot 21 (+0x54)
	virtual PlayerInfo *rva00382CCE(const char *key) = 0;		// slot 22 (+0x58)
};

class GameSpyInfoSlot29 : public VPad<GameSpyInfoSlot22, 6>
{
public:
	virtual AsciiString getLocalName(void) = 0; // slot 29 (+0x74)
};

class GameSpyInfoSlot31 : public VPad<GameSpyInfoSlot29, 1>
{
public:
	virtual int getLocalProfileID(void) = 0;			// slot 31 (+0x7C)
};

class GameSpyInfoSlot47 : public VPad<GameSpyInfoSlot31, 15>
{
public:
	virtual void leaveStagingRoom(void) = 0;			// slot 47 (+0xBC)
};

class GameSpyInfoSlot53 : public VPad<GameSpyInfoSlot47, 5>
{
public:
	virtual GameSpyStagingRoom *getCurrentStagingRoom(void) = 0;	// slot 53 (+0xD4)
};

class GameSpyInfoSlot72 : public VPad<GameSpyInfoSlot53, 18>
{
public:
	virtual int _M_slot_120(const AsciiString &name); // slot 72 (+0x120)
};

class GameSpyInfoInterface : public VPad<GameSpyInfoSlot72, 17>
{
public:
	virtual bool didPlayerPreorder(int profileID) const = 0;	// slot 90 (+0x168)
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva004FDB57 {
	char m_pad[0x1000];
	AsciiString m_name1000;
	int m_id1004;
public:
	void rva004FDB57(AsciiString arg);
};

void Rva004FDB57::rva004FDB57(AsciiString arg)
{
	AsciiString &slot = m_name1000;
	slot = arg;
	m_id1004 = TheGameSpyInfo->_M_slot_120(arg);
}

class Rva004FDB04 {
	char m_pad[0x1B8];
	AsciiString m_name1B8;
	int m_id1BC;
public:
	void rva004FDB04(AsciiString arg);
};

void Rva004FDB04::rva004FDB04(AsciiString arg)
{
	AsciiString &slot = m_name1B8;
	slot = arg;
	m_id1BC = TheGameSpyInfo->_M_slot_120(arg);
}
