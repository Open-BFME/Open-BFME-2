// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ??1Sub005CD540Outer@@QAE@XZ
// retail 0x001FA95A, 23 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BigChainBaseDtors.cpp (reference/open-bfme-1 @
// 6d943426). Compiled /Os the donor body is byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// and the base classes it needs are defined here; the donor's other 23
// definitions are omitted.
//
// The donor's whole argument applies: destroying a SECOND BASE at +4 emits the
// NULL-checked pointer adjustment (`ecx = this ? this + 4 : 0`) that destroying
// a member cannot, so the object at +4 is a base, not a member.

class BigChainVictim
{
public:
	virtual ~BigChainVictim();
};

class BigChainHold
{
public:
	BigChainVictim *m_p;
	~BigChainHold() { if ( m_p ) delete m_p; }
};

#define BFME_CHAIN_SECOND_BASE( ADDR )                                    \
	class Rva##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		~Rva##ADDR();                                                     \
	};

#define BFME_CHAIN_DTOR( NAME, SECOND )                                   \
	class NAME : public BigChainHold, public SECOND                       \
	{                                                                     \
	public:                                                               \
		__declspec(noinline) ~NAME();                                     \
	};

BFME_CHAIN_SECOND_BASE( 005C67C0 )

BFME_CHAIN_DTOR( Rva005C9D30, Rva005C67C0 )

class BigChainPad
{
	int m_pad;
};

#define BFME_CHAIN_NESTED_SECOND_BASE( ADDR, TERMINAL )                   \
	class Sub##ADDR##Inner : public BigChainPad, public TERMINAL {};       \
	class Sub##ADDR##Outer : public BigChainPad, public Sub##ADDR##Inner   \
	{                                                                     \
	public:                                                               \
		__declspec(noinline) ~Sub##ADDR##Outer();                         \
	};                                                                    \
	Sub##ADDR##Outer::~Sub##ADDR##Outer() {}                              \
	class Sub##ADDR : public BigChainHold, public Sub##ADDR##Outer         \
	{                                                                     \
	public:                                                               \
		__declspec(noinline) ~Sub##ADDR();                                \
	};                                                                    \
	Sub##ADDR::~Sub##ADDR() {}

BFME_CHAIN_NESTED_SECOND_BASE( 005CD540, Rva005C9D30 )