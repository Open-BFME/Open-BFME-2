// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
    GameStats::Row *m_rows;
    GameStats::Row *m_finish;
    GameStats::Row *m_capacity;
    int m_10;
};
class GameStats::Persistent : public Rva005DE9E3 {
public:
    Persistent(int numCells);
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
