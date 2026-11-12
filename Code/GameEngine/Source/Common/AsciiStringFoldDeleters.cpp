// cl: /Ireference/shims/bfme2_ascii /O1 /MD /DBFME_STRINGBASE_PUBLIC_DTOR
//
// Opaque single-member destructors that tail-call the folded AsciiString
// member destructor at 0x0036410, the same shape as Bucket::~Bucket (vtable
// store, this-adjust, tail jump). Each class below is a distinct retail
// vtable whose owner identity is unproven; the member offset is retail
// measured per body. One ledger row per destructor, landed one commit at
// a time. The member view uses the existing shared AsciiString header;
// every destructor keeps its verified cleanup call to the 0x36410 worker.

#include "ascii_string.h"
#include "Rva004FA830.h"

// GameFont: FontLibrary::rva0021857E (0x0021857E) news this 0x20-byte font,
// installs vtable 0x00BE5AAC (slot 0 the deleting dtor 0x00217545) and
// deletes it through that slot; the class name is the ZH GameFont that
// getFont allocates (donor fact). Was the opaque Rva00217537.
class GameFont
{
public:
	GameFont();
	virtual ~GameFont();

private:
	char m_pad04[4];
	AsciiString m_member08;
};

GameFont::~GameFont()
{
}

class Rva0030714F
{
public:
	Rva0030714F();
	virtual ~Rva0030714F();

private:
	char m_pad04[4];
	AsciiString m_member08;
};

Rva0030714F::~Rva0030714F()
{
}

class Rva004E156B
{
public:
	Rva004E156B();
	virtual ~Rva004E156B();

private:
	AsciiString m_member04;
};

Rva004E156B::~Rva004E156B()
{
}

class Rva004E194E
{
public:
	virtual ~Rva004E194E();

private:
	char m_pad04[8];
	AsciiString m_member0C;
};

__declspec(noinline) inline Rva004E194E::~Rva004E194E()
{
}

inline Rva004FA830::~Rva004FA830()
{
}

// These destructors are header inlines in their callers; the anchor is not retail code.
#pragma inline_depth(0)
// ?<_bfmeRva004FA830DtorInlineAnchor> absent-from-retail
void _bfmeRva004FA830DtorInlineAnchor(Rva004FA830 *first, Rva004E194E *second)
{
	first->Rva004FA830::~Rva004FA830();
	second->Rva004E194E::~Rva004E194E();
}
#pragma inline_depth()

class Rva00538C5F
{
public:
	virtual ~Rva00538C5F();

private:
	AsciiString m_member04;
};

Rva00538C5F::~Rva00538C5F()
{
}


#include "../../Include/Common/Rva005C31FB.h"

// ??0Rva005C31FB@@QAE@HABVAsciiString@@@Z @0x005C31D5 38B: vtable 0x008743F8, level at +4, name copy at +8 via 0x365F0, flag 0 at +0xC.
// Callers at 0x005284F4 0x00528B11 0x005F2856 pass level from GetLevel 0x4128BB plus StringBase temp; new 0x10.
// Sibling dtor at 0x005C31FB plus deleting dtor at 0x005C327F in this TU (/O1 /MD).
Rva005C31FB::Rva005C31FB(int level, const AsciiString &name) : m_level(level), m_name(name), m_flag0C(false)
{
}

Rva005C31FB::~Rva005C31FB()
{
}

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

// ?DeleteContentMovieClip@Rva005C31FB@@QAEXXZ @0x005C3209 55B: guarded DeleteContent AptCall.
// If flag +0xC is clear return; else pass level +4 and name text +8 (or
// g_Rva0107301CEmptyString when null) with literal "DeleteContent" to rowed
// 0x00524EF4, then clear flag. Evidence: retail cmp/je flag, mov/test/add-8
// string select, pushes to 0x00524EF4, neighbours Rva005C31FB ctor in this TU,
// precedent Rva005C394DGo.cpp, callers 0x005C7954 0x005E0DC0.
void Rva005C31FB::DeleteContentMovieClip()
{
	if (!m_flag0C)
		return;
	char *buffer = *(char **)(void *)&m_name;
	const char *text = buffer ? buffer + 8 : "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level, text, "DeleteContent");
	m_flag0C = false;
}

// Native4E155E..4E156B is a complete ctor between INT3 and the existing
// Rva004E156B dtor. Both store vtableC61A20; the ctor zeros the member at4
// whose dtor reaches the verified AsciiString cleanup at36410. This target
// evidence establishes the existing address-owned class and its empty string
// state; BF1 9cb Rva003AA980VectorCopy only supplies the default-ctor pattern.
// Original semantic class name and complete class bounds remain unresolved.
// ??0Rva004E156B@@QAE@XZ
Rva004E156B::Rva004E156B() {}

// Native 0x002175BA..0x002175C7 (13B) is the ctor of GameFont above:
// it stores vtable 0x00BE5AAC (slot 0 the rowed ??_G 0x00217545)
// and empties the string at +8, leaving +4 untouched. Same
// default-ctor shape as Rva004E156B above. getFont inlines the same
// constructor, so it is an inline (select-any) body: FontLibraryFindRecord.cpp
// emits the identical COMDAT copy. The anchor below keeps this one emitted.
// ??0GameFont@@QAE@XZ
__declspec(noinline) inline GameFont::GameFont() {}
// ?bfmeAnchorGameFont absent-from-retail
void bfmeAnchorGameFont(GameFont *gameFont) { gameFont->GameFont::GameFont(); }
// Rva0030714F's identical mapping-constructor shape at 0x00307126 is
// owned by System/DataChunk.cpp, which already emits its exact 13B body.

// Natives 0x0025558E (13B) and 0x0025559B (17B): constructors that store a
// module-data vtable and empty one or two strings, leaving +4 untouched. The
// stored vtables are the ones the ledger's FadeAndDieOrnamentUpdateModuleData
// (0x00BF3740, deleting dtor 0x002561A3) and SpawnUnitBehaviorModuleData
// (0x00BF36C0, deleting dtor 0x0025629F) constructors install, but both of
// those constructors are rowed elsewhere (0x002555AC, 0x0025598C), so these
// are ICF-shared tables of same-layout classes whose names are not
// recovered; address-owned like Rva004E156B above.
class Rva0025558E
{
public:
	Rva0025558E();
	virtual ~Rva0025558E() {}
private:
	char m_pad04[4];
	AsciiString m_member08;
};
// ??0Rva0025558E@@QAE@XZ
Rva0025558E::Rva0025558E() {}

class Rva0025559B
{
public:
	Rva0025559B();
	virtual ~Rva0025559B() {}
private:
	char m_pad04[4];
	AsciiString m_member08;
	AsciiString m_member0C;
};
// ??0Rva0025559B@@QAE@XZ
Rva0025559B::Rva0025559B() {}

// Native 0x002223E8 (22B, cdecl): formats "/_level%d" with the integer
// argument into the string argument through the rowed AsciiString::format
// 0x00038150 (an Apt level-path builder; caller and owner unresolved).
void buildLevelPath(AsciiString &path, int level)
{
	path.format("/_level%d", level);
}
