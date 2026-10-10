// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
//
// Native 0x005B8116..0x005B87ED, RET8, including the 24-entry jump table.
// WB01582480, callers and the matched Rva005C1BDEView::call establish the
// six-side statistics-table builder; original method name remains unknown.
// Field/map offsets, word/float payloads and 37-row switch come from target
// bytes. Lookup5B8053 is a fully owned leaf with no call or throw path, so its
// nothrow contract is target-backed; exposing it closes all eleven stack-home
// differences without duplicating that provider. Static word/float helpers
// use the native ESI/XMM0 internal ABI in this actual consuming TU.
// Prior reconstruction retained from the bank; canonical ASCII/Wide headers.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva005B8053
{
	void *m_header;
public:
	__declspec(nothrow) void *rva005B8053(unsigned char const *key);
};

static int rva005B808D(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0;
	return *(unsigned short *)((char *)node + 0x12);
}

static float rva005B80D0(unsigned char key, Rva005B8053 *self)
{
	((unsigned char *)&key)[3] = key;
	void *node = self->rva005B8053((unsigned char const *)((char *)&key + 3));
	if (node == *(void **)self)
		return 0.0f;
	return *(float *)((char *)node + 0x14);
}

static __forceinline float rva005B80F2Inline(int side, float def, Rva005B8053 *self)
{
	unsigned char key = (unsigned char)side;
	void *node = self->rva005B8053(&key);
	if (node == *(void **)self)
		return def;
	return *(float *)((char *)node + 0x14);
}

struct BfmeStringRecord005DDD40 { UnicodeString text; unsigned int word; };
class Rva005DD822 : public BfmeStringRecord005DDD40 { public: Rva005DD822(unsigned int); };
class Rva005DD8E0 : public BfmeStringRecord005DDD40 { public: Rva005DD8E0(float, float); };
class Rva005DDE01 { public: void rva005DDE01(unsigned int, unsigned int, const BfmeStringRecord005DDD40 &, bool); };

struct Rva005B8116Map { Rva005B8053 m_tree; int m_pad[2]; };

struct Rva005B8116Stats
{
	int m_pad00;
	Rva005B8053 m_04; int m_pad08[2];
	Rva005B8053 m_10; int m_pad14[2];
	Rva005B8053 m_1C; int m_pad20[2];
	Rva005B8053 m_28; int m_pad2C[2];
	Rva005B8053 m_34; int m_pad38[2];
	Rva005B8053 m_40; int m_pad44[2];
	char m_pad4C[0xDC - 0x4C];
	Rva005B8053 m_DC; int m_padE0[2];
	Rva005B8053 m_E8; int m_padEC[2];
	Rva005B8053 m_F4; int m_padF8[2];
	Rva005B8053 m_100; int m_pad104[2];
	Rva005B8053 m_10C; int m_pad110[2];
	Rva005B8053 m_118; int m_pad11C[2];
	Rva005B8053 m_124; int m_pad128[2];
	Rva005B8053 m_130; int m_pad134[2];
	char m_pad13C[0x146 - 0x13C];
	unsigned short m_146;
	unsigned short m_148;
	unsigned short m_14A;
	unsigned short m_14C;
};

class Rva005B8116
{
public:
	void rva005B8116(Rva005B8116Stats *stats, int *total);

private:
	char m_pad00[0x60];
	Rva005DDE01 m_table; // +0x60
};

void Rva005B8116::rva005B8116(Rva005B8116Stats *stats, int *total)
{
	for (int side = 0; side < 6; ++side)
	{
		unsigned int a = rva005B808D(side, &stats->m_04);
		unsigned int b = rva005B808D(side, &stats->m_10);
		unsigned int c = (unsigned int)rva005B80D0(side, &stats->m_F4);
		unsigned int d = (unsigned int)rva005B80D0(side, &stats->m_E8);
		unsigned int e = (unsigned int)rva005B80D0(side, &stats->m_DC);
		unsigned int f = (unsigned int)rva005B80D0(side, &stats->m_100);
		unsigned int g = (unsigned int)rva005B80D0(side, &stats->m_124);
		int h = (int)rva005B80F2Inline(side, -1.0f, &stats->m_130);
		if (h == -1)
			h = g;
		*total += h;
		for (int row = 0; row < 37; ++row)
		{
			switch (row)
			{
			case 0: m_table.rva005DDE01(0, side, Rva005DD822(rva005B808D(side, &stats->m_1C)), true); break;
			case 1: m_table.rva005DDE01(1, side, Rva005DD822(rva005B808D(side, &stats->m_28)), true); break;
			case 2: m_table.rva005DDE01(2, side, Rva005DD822(rva005B808D(side, &stats->m_40)), true); break;
			case 3: m_table.rva005DDE01(3, side, Rva005DD822(rva005B808D(side, &stats->m_34)), true); break;
			case 4: m_table.rva005DDE01(4, side, Rva005DD822(a), true); break;
			case 5: m_table.rva005DDE01(5, side, Rva005DD822(b), true); break;
			case 6: m_table.rva005DDE01(6, side, Rva005DD8E0((float)a, (float)b), true); break;
			case 7: m_table.rva005DDE01(7, side, Rva005DD822(a + b), true); break;
			case 14: m_table.rva005DDE01(14, side, Rva005DD822((unsigned int)rva005B80D0(side, &stats->m_118)), true); break;
			case 15: m_table.rva005DDE01(15, side, Rva005DD822((unsigned int)rva005B80D0(side, &stats->m_10C)), true); break;
			case 16: m_table.rva005DDE01(16, side, Rva005DD822(f), true); break;
			case 17: m_table.rva005DDE01(17, side, Rva005DD822(c), true); break;
			case 18: m_table.rva005DDE01(18, side, Rva005DD822(d), true); break;
			case 19: m_table.rva005DDE01(19, side, Rva005DD8E0((float)e, (float)d), true); break;
			case 20: m_table.rva005DDE01(20, side, Rva005DD822(e), true); break;
			case 21: m_table.rva005DDE01(21, side, Rva005DD822(g), true); break;
			case 22: m_table.rva005DDE01(22, side, Rva005DD8E0((float)((f + e) * 100), (float)h), true); break;
			case 23: m_table.rva005DDE01(23, side, Rva005DD8E0((float)c, (float)d), true); break;
			}
		}
	}
	m_table.rva005DDE01(0, 6, Rva005DD822(stats->m_146), false);
	m_table.rva005DDE01(1, 6, Rva005DD822(stats->m_14A), false);
	m_table.rva005DDE01(2, 6, Rva005DD822(stats->m_148), false);
	m_table.rva005DDE01(3, 6, Rva005DD822(stats->m_14C), false);
}

// Native 005B87ED..005B899F RET8; WB1582F60 has the same six-side 37-row
// extension builder. Tree offsets/payloads here are target observations.
class Rva005DDED5 : public BfmeStringRecord005DDD40 {public:Rva005DDED5(unsigned);};
struct Rva005B8EBB
{
	char pad[0x58];
	void *m_58;
	char pad2[0x60 - 0x58 - 4];
	char m_60[0x8C - 0x60];
	int m_8C;

	void rva00517F31();
	void rva005B8D1C();
	void rva005B89A1();
	void rva005B8A40();
	void rva005DD48C();

	void rva005B87ED(void *, unsigned *);
	void Run();
};


static __forceinline int extraInt(unsigned char key,Rva005B8053*self){void*node=self->rva005B8053(&key);if(node==*(void**)self)return 0;return *(int*)((char*)node+0x14);}
void Rva005B8EBB::rva005B87ED(void *opaque,unsigned *total){
 ((Rva005B8116*)this)->rva005B8116((Rva005B8116Stats*)opaque,(int*)total);
 for(int side=0;side<6;++side){
  for(int row=0;row<37;++row){
   switch(row){
   case 11:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(11,side,Rva005DDED5(extraInt(side,(Rva005B8053*)((char*)opaque+0x154))),true);break;
   case 9: ((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(9,side,Rva005DDED5(rva005B808D(side,(Rva005B8053*)((char*)opaque+0x160))),true);break;
   case 10:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(10,side,Rva005DDED5(rva005B808D(side,(Rva005B8053*)((char*)opaque+0x16c))),true);break;
   case 24:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(24,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)opaque+0x178))),true);break;
   case 25:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(25,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)opaque+0x184))),true);break;
   }
  }
 }
}

// ABI-only returned-record views. Sizes independently proved in the
// PersistentStorageThread provider; names retained from its owned types.
class Rva003844D7 { unsigned storage[0x190/4]; public: Rva003844D7(const Rva003844D7 &); ~Rva003844D7(); };
class Rva00385333 { unsigned storage[0x1A8/4]; public: Rva00385333(const Rva00385333 &); ~Rva00385333(); };
class Rva0038454E {unsigned storage[0x208/4];public:Rva0038454E(const Rva0038454E&);~Rva0038454E();};
class PSPlayerAllStats { unsigned storage[0x548/4]; public:
    PSPlayerAllStats(const PSPlayerAllStats &);
    ~PSPlayerAllStats();
    Rva003844D7 rva00389DF1() const;
    Rva00385333 rva00556508() const;
    Rva0038454E rva00389E0F() const;
};
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
struct Rva005B89A1InfoView {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
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

    virtual PSPlayerAllStats stats();
};
namespace GameStats { class Persistent { public: void CalculateTotalColumn(float); }; }
// Native 005B8D1C..005B8DBB RET0; WB1583220 and the owned
// PSPlayerAllStats getter/dtor prove548 snapshot and1A8 tournament block.
void Rva005B8EBB::rva005B8D1C() {
    PSPlayerAllStats all=((Rva005B89A1InfoView *)TheGameSpyInfo)->stats();
    Rva00385333 stats=all.rva00556508();
    unsigned total=0;
    rva005B87ED(&stats,&total);
    ((GameStats::Persistent *)m_60)->CalculateTotalColumn((float)total);
}

// Native 005B8A40..005B8D1C RET0; WB15833A0 callgraph and owned
// strategic getter/dtor establish purpose and208-byte returned block.
// Eight row/map offsets and float-versus-word payloads below are target facts.
void Rva005B8EBB::rva005B8A40(){
 PSPlayerAllStats all=((Rva005B89A1InfoView*)TheGameSpyInfo)->stats();
 Rva0038454E stats=all.rva00389E0F();unsigned total=0;
 ((Rva005B8116*)this)->rva005B8116((Rva005B8116Stats*)&stats,(int*)&total);
 for(int side=0;side<6;++side){for(int row=0;row<37;++row){switch(row){
case 26:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(26,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x154))),true);break;
case 27:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(27,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x160))),true);break;
case 28:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(28,side,Rva005DD822(rva005B808D(side,(Rva005B8053*)((char*)&stats+0x1b4))),true);break;
case 32:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(32,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x1cc))),true);break;
case 33:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(33,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x1d8))),true);break;
case 34:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(34,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x1e4))),true);break;
case 35:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(35,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x1f0))),true);break;
case 36:((Rva005DDE01*)((char*)this+0x60))->rva005DDE01(36,side,Rva005DD822((unsigned)rva005B80D0(side,(Rva005B8053*)((char*)&stats+0x1fc))),true);break;
}}}((GameStats::Persistent*)m_60)->CalculateTotalColumn((float)total);}

class Rva00553E47StatsCore;
class Rva00559D0CRankWeights{
 char opaque[0x34];
public:int rva00559DA0(const Rva00553E47StatsCore*,unsigned char)const;
};
extern Rva00559D0CRankWeights g_00E05FCC,g_00E06000;
class Rva005B8DBB{public:unsigned rva005B8DBB(unsigned);};
// Native 005B8DBB..005B8EBB RET4; WB1583940 callgraph gives three
// owned snapshot/getter branches. Mode2C and both rank-table receivers are
// target facts; globals reuse existing PeerThreadPushStatsBfme declarations.
// The leaf rank helper stays external so the target EH states are retained.
unsigned Rva005B8DBB::rva005B8DBB(unsigned key){
 PSPlayerAllStats all=((Rva005B89A1InfoView*)TheGameSpyInfo)->stats();
 switch(*(int*)((char*)this+0x2c)){
 case 0:{Rva00385333 stats=all.rva00556508();return g_00E06000.rva00559DA0((const Rva00553E47StatsCore*)&stats,(unsigned char)key);}
 default:{Rva003844D7 stats=all.rva00389DF1();return g_00E06000.rva00559DA0((const Rva00553E47StatsCore*)&stats,(unsigned char)key);}
 case 2:{Rva0038454E stats=all.rva00389E0F();return g_00E05FCC.rva00559DA0((const Rva00553E47StatsCore*)&stats,(unsigned char)key);}
 }
}

// Native005B89A1..005B8A40 and WB15832D0; 190B open snapshot provider,
// six-side extension and total column contracts established by owned siblings.
void Rva005B8EBB::rva005B89A1(){
 PSPlayerAllStats all=((Rva005B89A1InfoView*)TheGameSpyInfo)->stats();
 Rva003844D7 stats=all.rva00389DF1();
 unsigned total=0;
 rva005B87ED(&stats,&total);
 ((GameStats::Persistent*)m_60)->CalculateTotalColumn((float)total);
}
