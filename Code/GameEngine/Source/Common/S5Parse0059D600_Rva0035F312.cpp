// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Parse the BfmeB1140 definition, then register the populated record.
// The vtable at 0x0110C814 matches BfmeB1140 and the sibling constructor at
// 0x0059D570.  Volatile fields preserve the retail store order around m_14.

struct FieldParse;

class INI
{
public:
	void initFromINI( void *what, const FieldParse *table );
};

struct Gen_00489270
{
	void m( int value );
};

class GameWindow;
class Rva001DBAA4
{
public:
	Rva001DBAA4();
	virtual ~Rva001DBAA4();
	int m_frameLength; // +0x04 +0x04 +0x04
	bool m_isFinished; // +0x08 +0x08 +0x08
	bool m_isForward; // +0x09 +0x09 +0x09
	bool m_isReversed; // +0x0A +0x0A +0x0a
	char m_pad0B[0x1];
	GameWindow *m_win; // +0x0C +0x0C +0x0c
};
class Rva00489210
{
public:
	// Construction is the rowed ??0Rva001DBAA4, reached by a qualified call.
	__declspec(dllimport) __forceinline Rva00489210() { ((Rva001DBAA4 *)this)->Rva001DBAA4::Rva001DBAA4(); }
	volatile int *volatile m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

// The vtable address the record is stamped with is the one
// dir32_addresses.csv records for
// ??_7Rva0059D400MultiTailDtor@@6BRva0001AA9BMultiBase@@@; that vftable is
// compiler-emitted, so it is spelled here by its decorated name.
extern "C" int __identifier("??_7Rva0059D400MultiTailDtor@@6BRva0001AA9BMultiBase@@@");
// The parse table at 0x008166DC is the one CountUpTransitionDestructorThunk.cpp
// owns as CountUpTransitionFields (data ledger alias s5Table0059D600).
extern const FieldParse CountUpTransitionFields[];

// The record's constructor (0x0035F2B3) is the rowed FullFadeTransition
// constructor (GameWindowTransitionsStyles.cpp); the record is that class.
struct FullFadeTransition : public Rva00489210
{
	volatile int m_10;
	volatile int m_14;
	volatile int m_18;
	volatile int m_1C;
	volatile int m_20;
	volatile int m_24;
	int m_28;
	int m_2C;

	FullFadeTransition();
};

void s5parse0059D600( INI *ini, Gen_00489270 *sink )
{
	FullFadeTransition *record = new FullFadeTransition;
	ini->initFromINI( record, CountUpTransitionFields );
	record->m_04 = record->m_14;
	sink->m( (int)record );
}
