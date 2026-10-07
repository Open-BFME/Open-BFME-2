// cl: /DNDEBUG /MD /EHsc
// readable body of ??1CountUpTransition@@UAE@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// Open-BFME5: CountUpTransition dtor.
// Early derived vtbl, zero +0x0c, dual Buffer @+0x2c/+0x30, base dtor.

class CountUpBuffer
{
public:
	CountUpBuffer() : m_word(0) {}
	~CountUpBuffer();
private:
	unsigned int m_word;
};

class Rva001DBAA4
{
public:
	Rva001DBAA4();
	virtual ~Rva001DBAA4();
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	unsigned int m_zero;
};

struct CountUpIntPair
{
	CountUpIntPair() : x(0), y(0) {}
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class CountUpTransition : public Rva001DBAA4
{
public:
	CountUpTransition();
	virtual ~CountUpTransition();
	int m_startFrame; // +0x10
	int m_endFrame; // +0x14
	CountUpIntPair m_pos; // +0x18
	CountUpIntPair m_size; // +0x20
	int m_drawState; // +0x28
	CountUpBuffer m_fullText; // +0x2c
	CountUpBuffer m_b; // +0x30
	int m_intValue; // +0x34
	int m_currentValue; // +0x38
	int m_countState; // +0x3c
};

CountUpTransition::CountUpTransition()
	: m_startFrame(0), m_endFrame(30), m_drawState(-1),
	  m_intValue(0), m_currentValue(0), m_countState(0)
{
	m_frameLength = m_endFrame;
	m_zero = 0;
	m_isForward = true;
}

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
