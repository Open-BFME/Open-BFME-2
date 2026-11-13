// EA FESL client SDK ("jabba") small members: state setter with transition
// trace (0x008022A0) and embedded array-clear plus trailing zeroing
// (0x00801830). Ported from Open-BFME-1
// Code/GameEngine/Source/GameNetwork/Y2FeslBrowserSmallMembers.cpp.
// Trimmed to the two placed bodies; reset (0x00802290) and the 0x00802BB0
// clear are declared-only here. Callees reuse ledger names: Rva007EB810Get
// (pinned) and Rva00801570::clear (rowed). Zero new pins.

// ---------------------------------------------------------- the reporter
#include "../../Include/GameNetwork/Rva007EB810Diag.h"

extern Rva007EB810Diag *Rva007EB810Get();

// ------------------------------------- the already-landed array clear
class Rva00801570Elem
{
public:
	virtual void step( int flags );
	char m_pad[ 48 - 4 ];
};

class Rva00801570
{
public:
	void clear();

	Rva00801570Elem *m_array;
	int m_count;
};

class Rva00802A10Elem
{
public:
	virtual void step( int flags );
	char m_pad[ 128 - 4 ];
};

#include "../../Include/GameNetwork/Rva00802A10.h"

// ------------------------------------------------------------------ rows
class Rva00802290Owner
{
public:
	void reset();               // 0x00802290

	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
};

void Rva00802290Owner::reset()
{
	m_field4 = 0;
	m_fieldC = 0;
	m_field8 = 0;
}

class Rva008022A0Owner
{
public:
	void setHpState( int state );   // 0x008022A0

	int m_field0;
	int m_field4;
	int m_field8;
	int m_hpState;
};

// ?setHpState@Rva008022A0Owner@@QAEXH@Z
void Rva008022A0Owner::setHpState( int state )
{
	Rva007EB810Get()->log( 0, "hpstate: %d -> %d\n", m_hpState, state );
	m_hpState = state;
}

class Rva00801830Owner
{
public:
	void clear();               // 0x00801830

	char        m_pad000[ 0x3C ];
	Rva00801570 m_entries;      // +0x3C
	int         m_field44;
	int         m_field48;
};

// ?clear@Rva00801830Owner@@QAEXXZ
void Rva00801830Owner::clear()
{
	m_entries.clear();
	m_field44 = 0;
	m_field48 = 0;
}

class Rva00802BB0Owner
{
public:
	void clear();               // 0x00802BB0

	char        m_pad000[ 0x1C ];
	Rva00802A10 m_entries;      // +0x1C
	int         m_field24;
	int         m_field28;
};

// ?clear@Rva00802BB0Owner@@QAEXXZ
void Rva00802BB0Owner::clear()
{
	m_entries.clear();
	m_field24 = 0;
	m_field28 = 0;
}
