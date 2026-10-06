// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// GameStats::Row::Init, retail 0x005DE8CD (89B), from the WorldBuilder lead
// (GameStats.cpp): size the row's cell vector (+4; the one-argument resize
// 0x005DE84E that default-constructs the fill cell) and, given a label, set
// the row title (+0) to its localized text (TheGameText->fetch, the
// const char * overload at vtable slot 0x3C as in
// gametext_list_add_from_ascii_00433C75.cpp's view).
//
// Target facts: the cell vector keeps the ledger's address-derived spelling.

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

class Rva005DE7D1Vector
{
public:
	void resize(unsigned int count);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
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
	};
};

void GameStats::Row::Init(const char *label, int numCells)
{
	m_cells.resize(numCells);
	if (label)
		m_label = TheGameText->fetch(label);
}
