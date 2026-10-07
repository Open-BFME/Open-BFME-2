// cl: /DNDEBUG /MD /EHsc
// readable body of ??1CountUpTransition@@UAE@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// Open-BFME5: CountUpTransition dtor.
// Early derived vtbl, zero +0x0c, dual Buffer @+0x2c/+0x30, base dtor.

class CountUpBuffer
{
public:
	~CountUpBuffer();
private:
	unsigned char m_pad[4];
};

class CountUpTransitionBase
{
public:
	virtual ~CountUpTransitionBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class CountUpTransition : public CountUpTransitionBase
{
public:
	CountUpTransition();
	virtual ~CountUpTransition();
	int m_frameLength; // +0x04
	unsigned char m_gap[4]; // +0x08 .. +0x0b
	unsigned int m_zero; // +0x0c
	int m_startFrame; // +0x10
	int m_endFrame; // +0x14
	unsigned char m_gap2[0x14]; // +0x18 .. +0x2b
	CountUpBuffer m_fullText; // +0x2c
	CountUpBuffer m_b; // +0x30
	unsigned char m_tail[0x0c]; // +0x34 .. +0x3f
};

// ??1CountUpTransition@@UAE@XZ
CountUpTransition::~CountUpTransition()
{
	m_zero = 0;
}

// Native factory [0x0035F6E2,0x0035F739), 87 bytes. The allocation is
// 0x40 bytes; its full 74-byte constructor at 0x0035F64A installs the
// CountUp vtable (VA 0x00C1667C) whose deleting destructor is rowed here.
// Retail's field table at VA 0x00C166DC names StartFrame (+0x10) and
// EndFrame (+0x14). After parsing, +0x14 is copied to frameLength (+4).
// ZH CountUpTransition supplies purpose/names; the target constructor,
// field table and factory independently supply this layout and ABI.
typedef char CountUpTransitionRetailSize[(sizeof(CountUpTransition) == 0x40) ? 1 : -1];

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

extern const FieldParse CountUpTransitionFields[] = {
	{ "StartFrame", &INI::parseInt, 0, 0x10 },
	{ "EndFrame", &INI::parseInt, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

class Rva0035FF76;
class Rva003600D6Holder
{
public:
	void set(Rva0035FF76 *obj);
};

// The existing opaque holder binding is a verified ten-byte ICF setter:
// it stores its pointer argument at receiver+0x10 (0x005F69CE). It does
// not consume the pointed-to type; the pointee cast reuses that ABI binding.
void __cdecl Rva0035F6E2Parse(INI *ini, Rva003600D6Holder *holder)
{
	CountUpTransition *obj = new CountUpTransition;
	ini->initFromINI(obj, CountUpTransitionFields);
	obj->m_frameLength = obj->m_endFrame;
	holder->set((Rva0035FF76 *)obj);
}
