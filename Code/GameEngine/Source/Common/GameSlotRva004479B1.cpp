// cl: /Ireference/shims/bfme2_ascii /MD /Oi-
//
// ?rva004479B1@GameSlot@@QAEPAXXZ @0x004479B1 76B.
// If GameSlot::isHuman, copy connectInfo +0x38/+0x3C to +0x1C0/+0x1C4, copy
// +0x1CC to +0x1B8, set UnicodeString at +0x1AC from name at +0x30 via pinned
// set 0x00037150, zero +0x1BC, return &m_1AC else NULL. Evidence: unlock lane;
// callee isHuman rowed 0x003FF0F1; callers in 0x00449258; neighbours share flags.
typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

#include "ascii_string.h"


#include "unicode_string.h"

struct GameSlotConnectInfo
{
	unsigned int m_nat;
	unsigned int m_port;
};

class GameSlot
{
public:
	virtual void _v0();
	virtual void _v4();
	virtual void _v8();
	virtual void _vC();
	virtual void reset();
	Bool isHuman() const;
	void *rva004479B1();

private:
	Int m_state;                    // +0x04
	Bool m_isAccepted;              // +0x08
	Bool m_hasMap;                  // +0x09
	Bool m_isMuted;                 // +0x0A
	char m_pad0B;                   // +0x0B
	Int m_color;                    // +0x0C
	Int m_startPos;                 // +0x10
	Int m_bfme14;                   // +0x14
	Int m_playerTemplate;           // +0x18
	Int m_teamNumber;               // +0x1C
	Int m_bfme20;                   // +0x20
	Int m_origColor;                // +0x24
	Int m_origStartPos;             // +0x28
	Int m_origPlayerTemplate;       // +0x2C
	UnicodeString m_name;           // +0x30
	AsciiString m_ip;               // +0x34
	GameSlotConnectInfo m_connectInfo; // +0x38
	char m_pad040[0x16C];           // +0x40..+0x1AB
	UnicodeString m_1AC;            // +0x1AC
	char m_pad1B0[8];               // +0x1B0..+0x1B7
	Int m_1B8;                      // +0x1B8
	Int m_1BC;                      // +0x1BC
	Int m_1C0;                      // +0x1C0
	Int m_1C4;                      // +0x1C4
	Int m_1C8;                      // +0x1C8
	Int m_1CC;                      // +0x1CC
};

void *GameSlot::rva004479B1()
{
	if (isHuman()) {
		m_1C0 = (Int)m_connectInfo.m_nat;
		m_1C4 = (Int)m_connectInfo.m_port;
		m_1B8 = m_1CC;
		m_1AC = m_name;
		m_1BC = 0;
		return &m_1AC;
	}
	return 0;
}
