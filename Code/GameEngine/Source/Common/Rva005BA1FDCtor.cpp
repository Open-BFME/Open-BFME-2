// cl: -GR- -EHsc-
// ??0AptOnlineOpenPlay@@QAE@H@Z @0x005BA1FD 55B: composing constructor. Builds
// the base with (arg, 0) through the AptOnlineCustomMatch ctor, installs the
// three polymorphic tables, publishes this to the 0xE06544 global when clear,
// and returns this. Both constructors bind the verified destructor emitters'
// compiler tables; complete class identities and table slots remain unrecovered.
#include "../../Include/GameClient/AptOnlineCustomMatch.h"


// Retail table at VA 0x00C73D34: Rva005BA23A's compiler table (Rva005BA2CBDtor.cpp emits it).
extern "C" const void *const __identifier("??_7Rva005BA23A@@6BRva005A0009@@@")[];

// Retail table at VA 0x00C73CD8: Rva005BA23A's compiler table (Rva005BA2CBDtor.cpp emits it).
extern "C" const void *const __identifier("??_7Rva005BA23A@@6BRva005BA23ABase60@@@")[];

// Retail table at VA 0x00C73CCC: Rva005BA23A's compiler table (Rva005BA2CBDtor.cpp emits it).
extern "C" const void *const __identifier("??_7Rva005BA23A@@6BRva005BA23ABase6C@@@")[];




// Native table binding proved by the verified 0x005BA2CB destructor.
extern "C" const void *const __identifier("??_7Rva005BA2CB@@6BRva005A0009@@@")[1];

// Native table binding proved by the verified 0x005BA2CB destructor.
extern "C" const void *const __identifier("??_7Rva005BA2CB@@6BRva005BA2CBBase60@@@")[1];

// Native table binding proved by the verified 0x005BA2CB destructor.
extern "C" const void *const __identifier("??_7Rva005BA2CB@@6BRva005BA2CBBase6C@@@")[1];

class AptOnlineOpenPlay;
// g_rva005BA1FDInst is only an alias of the owned global g_Va00E06544 (ledger names column); this unit reads through it.
extern int g_Va00E06544;
#define g_rva005BA1FDInst (*(AptOnlineOpenPlay * *)&g_Va00E06544)

class AptOnlineOpenPlay : public AptOnlineCustomMatch
{
public:
	AptOnlineOpenPlay(int arg);

private:
	const void *const *m_table00;
	char m_pad04[0x60 - 4];
	const void *const *m_table60;
	char m_pad64[8];
	const void *const *m_table6C;
};

AptOnlineOpenPlay::AptOnlineOpenPlay(int arg)
	: AptOnlineCustomMatch(arg, 0)
{
	m_table00 = __identifier("??_7Rva005BA23A@@6BRva005A0009@@@");
	m_table60 = __identifier("??_7Rva005BA23A@@6BRva005BA23ABase60@@@");
	m_table6C = __identifier("??_7Rva005BA23A@@6BRva005BA23ABase6C@@@");
	if (g_rva005BA1FDInst == 0)
		g_rva005BA1FDInst = this;
}

// ??0Rva005BA28E@@QAE@H@Z @0x005BA28E 55B: sibling composing constructor,
// same skeleton as AptOnlineOpenPlay above. Builds the shared base with
// (arg, 1), installs its three tables and publishes this to the 0xE06548
// screen-instance global that the rowed destructor 0x005BA2CB clears.
// Original class name unknown.
class Rva005BA28E;
extern int g_Va00E06548;
#define g_rva005BA28EInst (*(Rva005BA28E * *)&g_Va00E06548)

class Rva005BA28E : public AptOnlineCustomMatch
{
public:
	Rva005BA28E(int arg);

private:
	const void *const *m_table00;
	char m_pad04[0x60 - 4];
	const void *const *m_table60;
	char m_pad64[8];
	const void *const *m_table6C;
};

Rva005BA28E::Rva005BA28E(int arg)
	: AptOnlineCustomMatch(arg, 1)
{
	m_table00 = __identifier("??_7Rva005BA2CB@@6BRva005A0009@@@");
	m_table60 = __identifier("??_7Rva005BA2CB@@6BRva005BA2CBBase60@@@");
	m_table6C = __identifier("??_7Rva005BA2CB@@6BRva005BA2CBBase6C@@@");
	if (g_rva005BA28EInst == 0)
		g_rva005BA28EInst = this;
}
