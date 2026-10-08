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
