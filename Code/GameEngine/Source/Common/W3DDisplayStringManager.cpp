// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /MD /EHsc
// ??1W3DDisplayStringManager@@UAE@XZ 108B @0x0009045E: dtor storing vtable 0x007C7E20 then releasing 10 nodes at +0x14 plus node at +0x3C via rowed 0x00090381 then rowed base 0x0026201C. Evidence: vtable plus rowed callees plus caller 0x000905D4.
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

W3DDisplayStringManager::~W3DDisplayStringManager()
{
	for (int i = 0; i < 10; ++i) {
		if (m_groupNumeralStrings[i] != 0)
			freeDisplayString(m_groupNumeralStrings[i]);
		m_groupNumeralStrings[i] = 0;
	}
	if (m_formationLetterDisplayString != 0)
		freeDisplayString(m_formationLetterDisplayString);
	m_formationLetterDisplayString = 0;
}
