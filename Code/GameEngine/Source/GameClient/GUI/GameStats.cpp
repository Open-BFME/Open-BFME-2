// cl: /G7 /Ireference/shims/bfme2_ascii /O1 /Ob2 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// GameStats::Row::Init, retail 0x005DE8CD (89B), from the WorldBuilder lead
// (GameStats.cpp): size the row's cell vector (+4; the one-argument resize
// 0x005DE84E that default-constructs the fill cell) and, given a label, set
// the row title (+0) to its localized text (TheGameText->fetch, the
// const char * overload at vtable slot 0x3C as in
// gametext_list_add_from_ascii_00433C75.cpp's view).
//
// Target facts: the cell vector keeps the ledger's address-derived spelling.

// stlport
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

struct Rva005DE7D1Record {UnicodeString text;float word;Rva005DE7D1Record();};
class Rva005DE7D1Vector {public:
 unsigned size()const{return finish-start;} Rva005DE7D1Record*begin(){return start;} Rva005DE7D1Record*end(){return finish;}
 void resize(unsigned);
 void resize(unsigned,Rva005DE7D1Record);
private:
 Rva005DE7D1Record*start;Rva005DE7D1Record*finish;Rva005DE7D1Record*limit;
 Rva005DE7D1Record*erase(Rva005DE7D1Record*,Rva005DE7D1Record*);
 void fill(Rva005DE7D1Record*,unsigned,const Rva005DE7D1Record&);
};

class GameStats
{
public:
	class Row
	{
	public:
		void Init(const char *label, int numCells);
		bool isDirty() const { return m_dirty != 0; }

	private:
		UnicodeString m_label;
		Rva005DE7D1Vector m_cells;
		// The lifecycle and refresh bodies prove the rest of this 24-byte row.
		float m_maximum;
		unsigned char m_dirty;
	};
	class Persistent;
};

void GameStats::Row::Init(const char *label, int numCells)
{
	m_cells.resize(numCells);
	if (label)
		m_label = TheGameText->fetch(label);
}

class GameWindow;
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
class Rva005DD88A : public UnicodeString {
public:
    float value;
    int rva005DD88A(GameWindow*,int,int,float);
};
inline int RowRefreshWhiteColor() { return -1; }
class Rva005DDBAB {
public:
    void rva005DDBAB(int window,int focus);
private:
    UnicodeString m_label;
    _STL::vector<Rva005DD88A> m_cells;
    float m_maximum;
    unsigned char m_dirty;
};
// Native 5DDBAB..5DDC6B, 192 bytes; WB 15D7710 is unnamed.
// The existing 24-byte owner ctor/copy/dtor and updater independently prove
// label0, 8-byte cells at4, float10 and dirty14. Retain an address-derived
// spelling until the owner's names and private class views are reconciled.
// The established two-int ABI carries Window* and vector<int>* addresses.
// WB packs four 255 channels for the local static white color; ordinary
// C++ initialization reproduces its guard and storage without address pins.
void Rva005DDBAB::rva005DDBAB(int window,int focus) {
    static int color=RowRefreshWhiteColor();
    if(m_dirty) {
        GameWindow *win=(GameWindow*)window;
        const _STL::vector<int> *indices=(const _STL::vector<int>*)focus;
        int row=GadgetListBoxAddEntryText(win,m_label,color,-1,0,true);
        int column=1;
        for(const int *it=indices->begin();it!=indices->end();++column,++it) {
            unsigned index=*it;
            if(index<m_cells.size())
                m_cells[index].rva005DD88A(win,row,column,m_maximum);
        }
        GadgetListBoxAddEntryText(win,UnicodeString(L" "),color,-1,0,true);
    }
}

// Native constructor 5DD772..5DD7C3: the eight-byte fill record owns
// UnicodeString at0 and float at4; caller5DE85C constructs it in-place.
// This composition constructor is a full byte-and-relocation twin of
// the existing display-record constructor; original record name remains open.
Rva005DE7D1Record::Rva005DE7D1Record()
    : text(AsciiString("-")), word(0.0f) {}

// Native5DE84E..5DE870, RET4: construct the default8B fill record
// in the outgoing by-value argument and call the already-matched resize.
void Rva005DE7D1Vector::resize(unsigned count)
{
    resize(count, Rva005DE7D1Record());
}

// WB 0x015D5700 names GameStats::Persistent::Persistent; its 37 labels
// and assertion GameStats.cpp:220 agree with complete retail5DEE37..5DF144.
// The existing31B base constructor owns a20B object with rows at4; its
// row lifecycle providers and every Init receiver prove a24B row stride.
// Retail adds a word at14 initialized to numCells-1; its original name is open.
// All three named table constructors store C76DD4. Existing StrategicEndGame
// destructor/scalar owners retain the folded address; no new aliases or pins.
class Rva005DE9E3 {
public:
    Rva005DE9E3(unsigned int);
    virtual ~Rva005DE9E3();
protected:
    _STL::vector<GameStats::Row> m_rows;
    int m_10;
};
class GameStats::Persistent : public Rva005DE9E3 {
public:
    Persistent(int numCells);
    void CalculateTotalColumn(float total);
private:
    int m_14;
};
typedef char GameStatsRowSize[(sizeof(GameStats::Row) == 24) ? 1 : -1];
typedef char GameStatsPersistentSize[(sizeof(GameStats::Persistent) == 24) ? 1 : -1];
GameStats::Persistent::Persistent(int numCells)
    : Rva005DE9E3(37), m_14(numCells - 1)
{
    m_rows[0].Init("STAT:PERSIST_CURRENT_WIN_STREAK", numCells);
    m_rows[1].Init("STAT:PERSIST_CURRENT_LOSS_STREAK", numCells);
    m_rows[2].Init("STAT:PERSIST_LONGEST_WIN_STREAK", numCells);
    m_rows[3].Init("STAT:PERSIST_WORST_LOSS_STREAK", numCells);
    m_rows[4].Init("STAT:PERSIST_CAREER_WINS", numCells);
    m_rows[5].Init("STAT:PERSIST_CAREER_LOSSES", numCells);
    m_rows[6].Init("STAT:PERSIST_WIN_LOSS_RATIO", numCells);
    m_rows[7].Init("STAT:PERSIST_TOTAL_GAMES_PLAYED", numCells);
    m_rows[8].Init("STAT:PERSIST_AVERAGE_GAME_LENGTH", numCells);
    m_rows[9].Init("STAT:PERSIST_LONGEST_GAME_LENGTH", numCells);
    m_rows[10].Init("STAT:PERSIST_SHORTEST_GAME_LENGTH", numCells);
    m_rows[11].Init("STAT:PERSIST_TOTAL_TIME_PLAYED", numCells);
    m_rows[12].Init("STAT:PERSIST_FACTION_MOST_SUCCESSFUL_AGAINST", numCells);
    m_rows[13].Init("STAT:PERSIST_FACTION_LEAST_SUCCESSFUL_AGAINST", numCells);
    m_rows[14].Init("STAT:PERSIST_STRUCTURES_CREATED", numCells);
    m_rows[15].Init("STAT:PERSIST_STRUCTURES_LOST", numCells);
    m_rows[16].Init("STAT:PERSIST_STRUCTURES_DESTROYED", numCells);
    m_rows[17].Init("STAT:PERSIST_UNITS_CREATED", numCells);
    m_rows[18].Init("STAT:PERSIST_UNITS_LOST", numCells);
    m_rows[19].Init("STAT:PERSIST_UNIT_KILL_DEATH_RATIO", numCells);
    m_rows[20].Init("STAT:PERSIST_UNITS_KILLED", numCells);
    m_rows[21].Init("STAT:PERSIST_TOTAL_RESOURCES_GATHERED", numCells);
    m_rows[22].Init("STAT:PERSIST_STRATEGIC_SKILL", numCells);
    m_rows[23].Init("STAT:PERSIST_TACTICAL_SKILL", numCells);
    m_rows[24].Init("STAT:PERSIST_HEROES_BUILT", numCells);
    m_rows[25].Init("STAT:PERSIST_HEROES_LOST", numCells);
    m_rows[26].Init("STAT:PERSIST_STRATEGIC_TURNS_PLAYED", numCells);
    m_rows[27].Init("STAT:PERSIST_STRATEGIC_MOST_TURNS_PLAYED", numCells);
    m_rows[28].Init("STAT:PERSIST_STRATEGIC_TACTICAL_BATTLES_WON", numCells);
    m_rows[29].Init("STAT:PERSIST_STRATEGIC_TACTICAL_BATTLES_LOST", numCells);
    m_rows[30].Init("STAT:PERSIST_STRATEGIC_AUTO_RESOLVE_BATTLES_WON", numCells);
    m_rows[31].Init("STAT:PERSIST_STRATEGIC_AUTO_RESOLVE_BATTLES_LOST", numCells);
    m_rows[32].Init("STAT:PERSIST_STRATEGIC_AUTO_RESOLVE_BATTLES_PLAYED", numCells);
    m_rows[33].Init("STAT:PERSIST_STRATEGIC_REGIONS_WON", numCells);
    m_rows[34].Init("STAT:PERSIST_STRATEGIC_REGIONS_LOST", numCells);
    m_rows[35].Init("STAT:PERSIST_STRATEGIC_TERRITORIES_WON", numCells);
    m_rows[36].Init("STAT:PERSIST_STRATEGIC_TERRITORIES_LOST", numCells);
}

// WB15D5ED0 names CalculateTotalColumn. Retail code5DE100..5DE3EC
// plus ten DWORD targets and31 compressed switch bytes ends5DE433.
// Existing table wrappers preserve independently witnessed identities;
// Casts below carry their common table receiver, rows24B and total column14.
// Retail excludes row32 from aggregation. The vector view is also required
// for its native addressing shape; known range-sum definitions before this
// caller preserve the target x87 stack across calls.
struct BfmeStringRecord005DDD40 { UnicodeString text; unsigned int word; };
class Rva005DD822:public BfmeStringRecord005DDD40 {public:Rva005DD822(unsigned int);};
class Rva005DD8E0:public BfmeStringRecord005DDD40 {public:Rva005DD8E0(float,float);};
class Rva005DDED5:public BfmeStringRecord005DDD40 {public:Rva005DDED5(unsigned int);};
class Rva005DDE01 {public:void rva005DDE01(unsigned int,unsigned int,const BfmeStringRecord005DDD40&,bool);};

// ?rva005DDC6B@Rva005DDC6B@@QAEMII@Z, RVA 0x005DDC6B, 58B. Unlock lane: float
// range-sum method over 8-byte elements; base pointer at +4 has a 4-byte
// header, elements hold the summed float at +0. Unsigned lo/hi give the jae
// early-out; do-while with dec/jne; x87 fld return. One caller at 0x005DDE60
// in 0x005DDE33. Owner unknown so honest address-derived method name. Flags
// copy the prev neighbour Rva005DD772Ctor.cpp for the SSE float idioms.
// ?rva005DDCA5@Rva005DDC6B@@QAEMII@Z @0x005DDCA5 64B. Float range-max with
// init from 0x00BBB8DC, comiss/jbe keep-largest, same stride. Caller 0x005DDE96.
// ?rva005DDCE5@Rva005DDC6B@@QAEMII@Z @0x005DDCE5 91B. Float range-min over
// the non-zero entries (FLT_MAX from 0x00BBB8E0 as the empty marker, 0 when
// nothing qualified or the range is empty), same stride. Caller 0x005DDECC.
// Structural inference: both zero results reach one shared store, which
// retail gets by hoisting xorps before the range test; written as a goto to
// that store.

class Rva005DDC6B
{
public:
	__declspec(noinline) float rva005DDC6B(unsigned lo, unsigned hi);
	__declspec(noinline) float rva005DDCA5(unsigned lo, unsigned hi);
	__declspec(noinline) float rva005DDCE5(unsigned lo, unsigned hi);
private:
	int m_00;
	char *m_04;
};

float Rva005DDC6B::rva005DDC6B(unsigned lo, unsigned hi)
{
	float sum = 0.0f;
	if (lo < hi) {
		float *p = (float *)(m_04 + lo * 8 + 4);
		unsigned n = hi - lo;
		do {
			sum += *p;
			p = (float *)((char *)p + 8);
		} while (--n != 0);
	}
	return sum;
}

float Rva005DDC6B::rva005DDCA5(unsigned lo, unsigned hi)
{
	float cur = (-3.4028235e+38f);
	if (lo < hi) {
		float *p = (float *)(m_04 + lo * 8 + 4);
		unsigned n = hi - lo;
		do {
			float v = *p;
			if (v > cur)
				cur = v;
			p = (float *)((char *)p + 8);
		} while (--n != 0);
	}
	return cur;
}

float Rva005DDC6B::rva005DDCE5(unsigned lo, unsigned hi)
{
	float best = 3.4028235e+38f;
	float ret;
	if (lo < hi) {
		float *p = (float *)(m_04 + lo * 8 + 4);
		unsigned n = hi - lo;
		do {
			float v = *p;
			if (v != 0.0f) {
				if (v < best)
					best = v;
			}
			p = (float *)((char *)p + 8);
		} while (--n != 0);
		ret = best;
		if (ret != 3.4028235e+38f)
			goto done;
	}
	ret = 0.0f;
done:
	return ret;
}


// ?rva005DDE33@Rva005DDE33@@QAEMIII@Z, RVA 0x005DDE33, 54B. Chain lane:
// bounds-checked delegate; count is the byte range at +4/+8 divided by 0x18
// via push/pop idiv, out of range returns pooled 0.0f BfmeZeroRange, else calls
// the rowed float range-sum 0x005DDC6B on the indexed 0x18 element head with
// (lo,hi). 12 callers in 0x005DE100. Owner unknown so honest address-derived
// method name; element head overlaps the callee layout at +4 by construction.
// Flags copy the prev neighbour allocate_copy TU (frameless-friendly, no EH).
// The body mirrors landed sibling Rva005DDE69 (0x005DDE69): count hoisted
// before the barrier, pointer-cast element access. That form is what schedules
// the hi push ahead of the imul, which retail 0x005DDE33 also does; the
// start/finish-local form emits the imul first and is one byte short of exact.
extern const float BfmeZeroRange;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005DDE33
{
public:
	__declspec(noinline) float rva005DDE33(unsigned idx, unsigned lo, unsigned hi);
private:
	int m_00;
	char *m_04;
	char *m_08;
};

float Rva005DDE33::rva005DDE33(unsigned idx, unsigned lo, unsigned hi)
{
	int count = (m_08 - m_04) / 0x18;
	_ReadWriteBarrier();
	if (idx >= (unsigned)count)
		return BfmeZeroRange;
	return ((Rva005DDC6B *)(m_04 + idx * 0x18))->rva005DDC6B(lo, hi);
}


class Rva005DDE69 {public:float rva005DDE69(unsigned int,unsigned int,unsigned int);float rva005DDE9F(unsigned int,unsigned int,unsigned int);};
void GameStats::Persistent::CalculateTotalColumn(float total) {
 for(int row=0;row<37;++row) {
  if(!m_rows[row].isDirty())continue;
  switch(row) {
  case 11: ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DDED5((unsigned int)((Rva005DDE33*)this)->rva005DDE33(row,0,m_14)),false); break;
  case 4:case 5:case 7:case 14:case 15:case 16:case 17:case 18:case 20:case 21:case 24:case 25:case 26:case 28:case 29:case 30:case 31:case 33:case 34:
   ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DD822((unsigned int)((Rva005DDE33*)this)->rva005DDE33(row,0,m_14)),false); break;
  case 9: ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DDED5((unsigned int)((Rva005DDE69*)this)->rva005DDE69(row,0,m_14)),false);break;
  case 10: ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DDED5((unsigned int)((Rva005DDE69*)this)->rva005DDE9F(row,0,m_14)),false);break;
  case 6: {
   float wins=(int)((Rva005DDE33*)this)->rva005DDE33(4,0,m_14);
   float losses=(int)((Rva005DDE33*)this)->rva005DDE33(5,0,m_14);
   ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DD8E0((float)wins,(float)losses),false);break;
  }
  case 8: {
   float time=((Rva005DDE33*)this)->rva005DDE33(11,0,m_14);
   float games=((Rva005DDE33*)this)->rva005DDE33(7,0,m_14);
   ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DDED5((unsigned int)(games!=0?time/games:0)),false);break;
  }
  case 19: {float killed=((Rva005DDE33*)this)->rva005DDE33(20,0,m_14);float lost=((Rva005DDE33*)this)->rva005DDE33(18,0,m_14);((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DD8E0(killed,lost),false);break;}
  case 22: {float numerator=(((Rva005DDE33*)this)->rva005DDE33(16,0,m_14)+((Rva005DDE33*)this)->rva005DDE33(20,0,m_14));((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DD8E0(numerator*100.0f,total),false);break;}
  case 23: {
   float lost=((Rva005DDE33*)this)->rva005DDE33(18,0,m_14);
   float built=((Rva005DDE33*)this)->rva005DDE33(17,0,m_14);
   ((Rva005DDE01*)this)->rva005DDE01(row,m_14,Rva005DD8E0((float)built,(float)lost),false);break;
  }
  }
 }
}
