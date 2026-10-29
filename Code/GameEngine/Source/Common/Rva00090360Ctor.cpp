// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /MD
// ??0W3DDisplayStringManager@@QAE@XZ 33B @0x00090360: ctor calling rowed base 0x00262002 then storing vtable 0x007C7E20 then zeroing +0x14 (10 dwords) and +0x3C. Size 0x40 per caller alloc at 0x0004C55E. Evidence: rowed base callee plus vtable plus caller.
#include <new>
#include "ascii_string.h"

typedef bool Bool;
#include "subsystem_interface.h"
typedef int Int;

class DisplayString;

enum { MAX_GROUPS = 10 };

// DisplayStringManager: its ctor 0x00262002 and dtor 0x0026201C are still
// ledgered as Rva0026201C (unLink 0x00262045 as Rva00262045), link 0x00262027
// as DisplayStringManager::link; this unit views the class through both names.
// Retail W3DDisplayStringManager vtable 0x007C7E20 (18 slots): the fourteen
// SubsystemInterface slots (init 0x000B3FD0 empty, postProcessLoad 3, reset 9,
// update 10 overridden), then newDisplayString 0x000905F0, freeDisplayString
// 0x00090381, getGroupNumeralString 0x00090417 and the formation letter getter
// (folded into 0x005C4AF1, a +0x3C dword read).
class Rva0026201C : public SubsystemInterface
{
public:
	Rva0026201C();
	virtual ~Rva0026201C();
	virtual void init( void ) {}
	virtual DisplayString *newDisplayString( void ) = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;
	virtual DisplayString *getGroupNumeralString( Int numeral ) = 0;
	virtual DisplayString *getFormationLetterString( void ) = 0;
protected:
	DisplayString *m_stringList;												///< 0x0C
	DisplayString *m_currentCheckpoint;									///< 0x10
};

class W3DDisplayStringManager : public Rva0026201C
{
public:
	W3DDisplayStringManager( void );
	virtual ~W3DDisplayStringManager( void );
	virtual void postProcessLoad( void );
	virtual void update( void );
	virtual void reset( void );
	virtual DisplayString *newDisplayString( void );
	virtual void freeDisplayString( DisplayString *string );
	virtual DisplayString *getGroupNumeralString( Int numeral );
	virtual DisplayString *getFormationLetterString( void ) { return m_formationLetterDisplayString; }
protected:
	DisplayString *m_groupNumeralStrings[ MAX_GROUPS ];		///< 0x14
	DisplayString *m_formationLetterDisplayString;				///< 0x3C
};

struct Rva90381Node
{
	virtual void *rva(int x);
	char m_pad04[8];
	Rva90381Node *m_next;
	Rva90381Node *m_prev;
};

struct Node00262045;
class Rva00262045
{
public:
	void unLink(struct Node00262045 *n);
};


// ?freeDisplayString@W3DDisplayStringManager@@UAEXPAVDisplayString@@@Z @0x00090381 47B
// Slot 15 offset 0x3C of vtable 0x007C7E20. Unlinks n via rowed 0x00262045,
// clears head at +0x10 if it equals n, releases via slot0 plus rowed delete 0x0002FD60.
// Callers in dtor 0x0009045E.
void W3DDisplayStringManager::freeDisplayString(DisplayString *string)
{
	if (string != 0) {
		((Rva00262045 *)this)->unLink((struct Node00262045 *)string);
		if (m_currentCheckpoint == string)
			m_currentCheckpoint = 0;
		operator delete(((Rva90381Node *)string)->rva(0));
	}
}

W3DDisplayStringManager::W3DDisplayStringManager()
{
	for (int i = 0; i < 10; ++i)
		m_groupNumeralStrings[i] = 0;
	m_formationLetterDisplayString = 0;
}
