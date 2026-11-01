// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?Rva0030F04AApply@@YAXHPAURva0030F04AOut@@@Z @0x0030F04A 79B: flag-gated bit sets plus InGameUI slot48 check. Evidence: packet disasm with rowed TheInGameUI; caller 0x0030F0E2 pushes prove __cdecl (int, ptr) with ret; virtual at 0xC0 is slot48.
struct Slot48Ret
{
	char m_pad[0x14];
	int m_0014;
};

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

struct Rva0030F04AOut
{
	unsigned int m_00;
	unsigned char m_04;
	unsigned char m_05;
	unsigned char m_06;
	unsigned char m_07;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned char m_10;
	unsigned char m_11;
};

// The exact mask helper is owned by Rva0030F04AApply.cpp.
void Rva0030F04AApply(int flags, Rva0030F04AOut *out);

#include <string.h>
unsigned int Rva0030F099(bool alternate);
class Rva0024C7B3Member {
public:
 Rva0024C7B3Member();
 void setBit(int bit) { reinterpret_cast<unsigned int *>(m_data)[bit >> 5] |= 1u << (bit & 31); }
 unsigned char m_data[0x1C];
};
// Native constructor 0x0030F0E2..0x0030F14C. Two independently rowed
// 28-byte members at +8 and +24, sentinel +40 and mode bytes +4/+5.
// The mode is copied from InGameUI +8B8, then the owned mask helpers
// initialize the first member. Original owner and mode names are unknown.
class Rva0030F0E2 {
public:
 Rva0030F0E2();
private:
 int tag;
 bool alternate;
 bool flag5;
 char pad6[2];
 Rva0024C7B3Member include;
 Rva0024C7B3Member exclude;
 int sentinel;
};
Rva0030F0E2::Rva0030F0E2() : tag(0), flag5(false), sentinel(-1) {
 tag=0;
 alternate=false;
 memset(include.m_data,0,0x1C);
 memset(exclude.m_data,0,0x1C);
 alternate=*reinterpret_cast<const bool *>(reinterpret_cast<const char *>(TheInGameUI)+0x8B8);
 const unsigned int flags=Rva0030F099(alternate);
 Rva0030F04AApply(flags,reinterpret_cast<Rva0030F04AOut *>(include.m_data));
 if (!alternate) include.setBit(58);
}
