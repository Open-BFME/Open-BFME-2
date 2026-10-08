// ??0Rva0030F0E2@@QAE@XZ
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?Rva0030F04AApply@@YAXHPAURva0030F04AOut@@@Z @0x0030F04A 79B: flag-gated bit sets plus InGameUI slot48 check. Evidence: packet disasm with rowed TheInGameUI; caller 0x0030F0E2 pushes prove __cdecl (int, ptr) with ret; virtual at 0xC0 is slot48.
struct Slot48Ret
{
	char m_pad[0x14];
	int m_0014;
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual Slot48Ret *slot48();
};

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

void Rva0030F04AApply(int flags, Rva0030F04AOut *out)
{
	if (flags & 4) {
		out->m_00 |= 2;
		Slot48Ret *p = TheInGameUI->slot48();
		if (p && p->m_0014 == 0x18)
			out->m_07 |= 0x10;
	}
	if (flags & 8)
		out->m_00 |= 0x40;
	if (flags & 0x200) {
		out->m_0C |= 2;
		out->m_11 |= 1;
	}
	if (flags & 0x20)
		out->m_08 |= 0x10;
}

extern "C" void *memset(void *, int, unsigned int);
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
