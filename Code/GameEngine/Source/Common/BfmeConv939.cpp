// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv939.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGo939E 0x002E7D28 (23B), BfmeThing939G::bfmeGo939G
// 0x0044BDC1 (23B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.
// Open-BFME5 conversions.

class BfmeGlob939A
{
public:
	virtual void bfmeSlot939A00();
	virtual void bfmeSlot939A01();
	virtual void bfmeSlot939A02();
	virtual void bfmeSlot939A03();
	virtual void bfmeTail939A();
};

// Retail's global at 0x012F64BC is ParticleSystemManager *TheParticleSystemManager;
// only the global's spelling matters to the link, so the pointee keeps this
// TU's own vtable view (BfmeGlob939A) and is cast at the use.
class ParticleSystemManager;

extern ParticleSystemManager *TheParticleSystemManager;
void bfmeCall939A(void);


class Object;
class DelayedLuaEventList;

struct BfmeElem939B
{
	int m_bfmeA;
	int m_bfmeB;
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B(int i, Object *object, DelayedLuaEventList *events);
	void bfmeTail939B(BfmeElem939B *e, Object *object, DelayedLuaEventList *events);
	char m_bfmePad[0x10];
	BfmeElem939B m_bfmeArr[1];
};


class BfmeGlob939C
{
public:
	virtual void bfmeSlot939C00();
	virtual void bfmeSlot939C01();
	virtual void bfmeSlot939C02();
	virtual void bfmeSlot939C03();
	virtual void bfmeSlot939C04();
	virtual void bfmeSlot939C05();
	virtual void bfmeSlot939C06();
	virtual void bfmeSlot939C07();
	virtual void bfmeSlot939C08();
	virtual void bfmeSlot939C09();
	virtual void bfmeSlot939C10();
	virtual void bfmeSlot939C11();
	virtual void bfmeSlot939C12();
	virtual void bfmeSlot939C13();
	virtual void bfmeSlot939C14();
	virtual void bfmeSlot939C15();
	virtual void bfmeSlot939C16();
	virtual void bfmeSlot939C17();
	virtual void bfmeSlot939C18();
	virtual void bfmeSlot939C19();
	virtual void bfmeSlot939C20();
	virtual void bfmeSlot939C21();
	virtual void bfmeSlot939C22();
	virtual void bfmeSlot939C23();
	virtual void bfmeSlot939C24();
	virtual void bfmeSlot939C25();
	virtual void bfmeSlot939C26();
	virtual void bfmeSlot939C27();
	virtual void bfmeSlot939C28();
	virtual void bfmeSlot939C29();
	virtual void bfmeSlot939C30();
	virtual int bfmeVirt939C(int f);
};

// Retail's global at 0x012ED668 is `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp. Only the name has to be canonical for the link;
// this TU keeps its own TU-local view of the pointee and casts at the use.
class AudioManager;

extern AudioManager *TheAudio;


// Retail global at 0x012F0898 is GameLogic *TheGameLogic (defined once in
// game_logic.cpp). This TU calls through a local view type, so keep the view
// and cast at the use; the global itself uses the canonical spelling.
class BfmeGlob939D
{
public:
	char bfmeCall939D();
};

class GameLogic;
extern GameLogic *TheGameLogic;


// bfmeGo939E is the "Pathfinder" block parser PathfinderConstructor.cpp
// registers. Its callee (pinned bfmeCall939E, 0x0002DE78) is the rowed
// INI::initFromINI, and the table it passes is retail .data VA 0xDBD2F8:
// {"SlopeLimits", 0x004B3FD0, NULL, 0} plus the null terminator (read from the
// image). The field's parser is the shared empty RET at 0x000B3FD0, an ICF
// fold whose own name is unknown; the table reaches it through the rowed empty
// pathfinder debug hook folded there (PathfinderReleaseDebug.cpp).
class INI;
typedef void (*FieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};
struct Coord3D;
struct PathfinderDebugColor;
void Rva000B3FD0PathDebug(const Coord3D *, float, int, PathfinderDebugColor);

FieldParse g_bfmePathfinderFieldParse[2] = {
	{ "SlopeLimits", (FieldParseProc)&Rva000B3FD0PathDebug, 0, 0 },
	{ 0, 0, 0, 0 }
};

class BfmeSub939E;

void parsePathfinderDefinition(BfmeSub939E *ini)
{
	int tmp;
	reinterpret_cast<INI *>(ini)->initFromINI(&tmp, g_bfmePathfinderFieldParse);
}

// The pinned bfmeCall939G (0x0044BD79) is the rowed BfmeA1042N::bfmeGo1042D
// there; in BFME 1 the pin's ILT thunk 0x00011900 jumps to that same body
// (0x004C5F20).
class BfmeA1042N
{
public:
	void bfmeGo1042D();
};

class BfmeSub939G
{
public:
	void *m_bfmeP;
};

class BfmeThing939G
{
public:
	void bfmeGo939G(void *a);
	char m_bfmePad[8];
	BfmeSub939G m_callback;
};

void BfmeThing939G::bfmeGo939G(void *a)
{
	BfmeSub939G *callback = &m_callback;
	if (!a && callback->m_bfmeP)
		reinterpret_cast<BfmeA1042N *>(callback)->bfmeGo1042D();
}
