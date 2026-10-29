// cl: /MD /EHsc
// ??1W3DDisplayStringManager@@UAE@XZ 108B @0x0009045E: dtor storing vtable 0x007C7E20 then releasing 10 nodes at +0x14 plus node at +0x3C via rowed 0x00090381 then rowed base 0x0026201C. Evidence: vtable plus rowed callees plus caller 0x000905D4.
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

W3DDisplayStringManager::~W3DDisplayStringManager()
{
	for (int i = 0; i < 10; ++i) {
		if (m_groupNumeralStrings[i] != 0)
			freeDisplayString((Rva90381Node *)m_groupNumeralStrings[i]);
		m_groupNumeralStrings[i] = 0;
	}
	if (m_formationLetterDisplayString != 0)
		freeDisplayString((Rva90381Node *)m_formationLetterDisplayString);
	m_formationLetterDisplayString = 0;
}
