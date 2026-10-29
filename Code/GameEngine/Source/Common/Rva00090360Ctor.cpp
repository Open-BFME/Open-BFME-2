// cl: /MD
// ??0W3DDisplayStringManager@@QAE@XZ 33B @0x00090360: ctor calling rowed base 0x00262002 then storing vtable 0x007C7E20 then zeroing +0x14 (10 dwords) and +0x3C. Size 0x40 per caller alloc at 0x0004C55E. Evidence: rowed base callee plus vtable plus caller.
typedef int Int;

class DisplayString;

enum { MAX_GROUPS = 10 };

// DisplayStringManager: its ctor 0x00262002 and dtor 0x0026201C are still
// ledgered as Rva0026201C (unLink 0x00262045 as Rva00262045), link 0x00262027
// as DisplayStringManager::link; this unit views the class through both names.
class Rva0026201C
{
public:
	Rva0026201C();
	virtual ~Rva0026201C();
	virtual void init( void );
	virtual void postProcessLoad( void );
	virtual void reset( void );
	virtual void update( void );
	virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10();
	virtual void vslot11(); virtual void vslot12(); virtual void vslot13();
	virtual DisplayString *newDisplayString( void ) = 0;
protected:
	char m_opaque04[ 8 ];
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
	void freeDisplayString( struct Rva90381Node *string );
	virtual DisplayString *getGroupNumeralString( Int numeral );
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

#include <new>

// ?freeDisplayString@W3DDisplayStringManager@@QAEXPAURva90381Node@@@Z @0x00090381 47B
// Slot 15 offset 0x3C of vtable 0x007C7E20. Unlinks n via rowed 0x00262045,
// clears head at +0x10 if it equals n, releases via slot0 plus rowed delete 0x0002FD60.
// Callers in dtor 0x0009045E.
void W3DDisplayStringManager::freeDisplayString(struct Rva90381Node *string)
{
	if (string != 0) {
		((Rva00262045 *)this)->unLink((struct Node00262045 *)string);
		if (m_currentCheckpoint == (DisplayString *)string)
			m_currentCheckpoint = 0;
		operator delete(string->rva(0));
	}
}

W3DDisplayStringManager::W3DDisplayStringManager()
{
	for (int i = 0; i < 10; ++i)
		m_groupNumeralStrings[i] = 0;
	m_formationLetterDisplayString = 0;
}
