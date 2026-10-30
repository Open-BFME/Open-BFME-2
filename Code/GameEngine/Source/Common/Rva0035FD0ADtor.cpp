// cl: /MD /EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii /Ireference/open-bfme-1/inputs/reference/shims/asciistringsetoutofline /Ireference/open-bfme-1/inputs/reference/shims/fullfade /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??1Rva0035FD0A@@UAE@XZ @0x0035FD0A (105B): virtual dtor storing vtable 0x008166BC.
// Zeroes +0xC, frees DisplayString at +0x34 via TheDisplayStringManager slot 0x3C,
// zeroes +0x34, destroys wide StringBase at +0x30/+0x2C via rowed releaseBuffer
// 0x00036E70, then base dtor via pinned 0x001DBAC3. Caller at 0x0035FF59 is
// deleting dtor. Prev tail dtors in FamilyTailDtors1DBAC3.cpp.
class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString(DisplayString *s) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;

#include "unicode_string.h"

class GameWindow;
class Rva001DBAA4
{
public:
	Rva001DBAA4();
	virtual ~Rva001DBAA4();
	int m_frameLength; // +0x04 +0x04
	bool m_isFinished; // +0x08 +0x08
	bool m_isForward; // +0x09 +0x09
	bool m_isReversed; // +0x0A +0x0a
	char m_pad0B[0x1];
	GameWindow *m_win; // +0x0C +0x0c
};

class Rva0035FD0A : public Rva001DBAA4
{
public:
	Rva0035FD0A();
	virtual ~Rva0035FD0A();
	int m_startFrame;
	int m_endFrame;
	char m_pad18[0x10];
	int m_drawState;
	UnicodeString m_2C;
	UnicodeString m_30;
	DisplayString *m_34;
};

// Native [0x0035FCD6,0x0035FD0A), 52 bytes. The two zeroed words at
// +0x2C/+0x30 are the independently rowed destructor's wide-string
// subobjects, whose inline default construction precedes the body stores.
// The 0x38-byte factory at 0x0035FD73 and its StartFrame/EndFrame table
// prove the prefix fields; vtable slot 2 points to rowed TextType update.
// Original class name remains conservatively address-derived here.
Rva0035FD0A::Rva0035FD0A()
{
	m_drawState = -1;
	m_endFrame = 30;
	m_frameLength = 30;
	m_startFrame = 0;
	m_win = 0;
	m_isForward = true;
	m_34 = 0;
}

Rva0035FD0A::~Rva0035FD0A()
{
	m_win = 0;
	if (m_34 != 0)
		TheDisplayStringManager->freeDisplayString(m_34);
	m_34 = 0;
}

// Native [0x0035FD73,0x0035FDCA), 87 bytes. Both this factory and the
// CountUp factory reference the same complete 48-byte StartFrame/EndFrame
// field table at VA 0x00C166DC, defined in CountUpTransitionDestructorThunk.cpp.
typedef char Rva0035FD0ARetailSize[(sizeof(Rva0035FD0A) == 0x38) ? 1 : -1];

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

extern const FieldParse CountUpTransitionFields[];

class Rva0035FF76;
class Rva003600D6Holder
{
public:
	void set(Rva0035FF76 *obj);
};

// Reuse the established opaque pointer-setter binding: full ten-byte
// 0x005F69CE stores only the pointer at holder+0x10, with no pointee access.
void __cdecl Rva0035FD73Parse(INI *ini, Rva003600D6Holder *holder)
{
	Rva0035FD0A *obj = new Rva0035FD0A;
	ini->initFromINI(obj, CountUpTransitionFields);
	obj->m_frameLength = obj->m_endFrame;
	holder->set((Rva0035FF76 *)obj);
}
