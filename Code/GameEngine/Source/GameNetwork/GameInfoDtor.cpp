// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ??1Rva00382FA7@@UAE@XZ @0x00400A7F 121B: GameInfo virtual dtor (Rva name keeps
// pinned caller 0x003830CE and LINK GameSpyStagingRoomCopy); installs vtable
// 0x008193C8 then destroys owned TreeHint ptr at +0xC8 via delete plus null,
// Version at +0x90 via rowed 0x00002152, AsciiString at +0x40 via narrow
// 0x00036410, UnicodeString at +0x04 via wide 0x00036E70, then inline Snapshot
// base restoring 0x00BBB554. Layout from rowed copy 0x00382FA7 and ctor
// 0x00400A07 plus GameInfoReset reset 0x003FFF8F; EH states 3-0.
#include "ascii_string.h"
#include "unicode_string.h"

class Version
{
public:
	~Version();
private:
	char m_pad[0x30];
};

class TreeHintOpaque0043671B
{
public:
	~TreeHintOpaque0043671B();
};

class Xfer;
#include "Common/Snapshot.h"

class Rva00382FA7 : public Snapshot
{
public:
	virtual ~Rva00382FA7();
private:
	UnicodeString m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	unsigned char m_12;
	char m_pad13;
	int m_14;
	int m_18[8];
	int m_38;
	int m_3C;
	AsciiString m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60[10];
	int m_88;
	unsigned char m_8C;
	char m_pad8D[3];
	Version m_90;
	int m_C0;
	int m_C4;
	TreeHintOpaque0043671B *m_C8;
	int m_CC[4];
};

Rva00382FA7::~Rva00382FA7()
{
	if (m_C8 != 0)
	{
		delete m_C8;
		m_C8 = 0;
	}
}
