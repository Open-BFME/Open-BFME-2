// cl: /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// The "needs restart" byte at VA 0x00E01D0C and the bodies that touch it:
//
//   0x0031AB77  sets it (8 bytes).
//   0x0031E7F0  slot 4 of vftable 0x00C0CC88 (the class whose deleting
//               destructor is 0x0031EB7A), the INI reload notice: clear the
//               byte, and when the class's own slot 2 reports a reload put
//               "RIF: ControlBar ... reloaded" on screen through TheInGameUI (its
//               slot 16, cdecl), call 0x00409FCC on every value of the
//               AsciiString-keyed hash map at +0x30, walk the +0x2C
//               list (0x0031AC39), latch +0x28 and answer true; a byte set
//               meanwhile is passed out through the argument and cleared.
//
// Target evidence: the reload notice's codegen loads the vptr before it
// stores the byte, which MSVC 7.1 only does when the byte is a file-static
// it can prove `this` does not alias (an extern byte keeps the store first),
// so the byte is file-static here and its setter, which sits beside
// 0x0031AC39 in the same address range, lives in this unit too. The classes
// keep their address-derived names; the message and map meanings are
// inferred from the callees.

#include "ascii_string.h"
#include "unicode_string.h"
#include <hash_map>

// g_Va00E01D0C: VA 0x00E01D0C (.bss); retail initial byte 00.
static bool g_Va00E01D0C;

// WB 0x00C2D900 retains the receiver at entry; INICommandButton's native
// 0x001DAFEA loads TheControlBar before its call. The original method name
// remains unknown, but its thiscall ABI is established independently of the
// eight-byte optimized body, which does not need to read the receiver.
class INI;
class Rva00409FFA;
class ControlBar
{
public:
	void rva0031AB77SetFlag();
    void forgetStaleCommandSet(const AsciiString &);
    Rva00409FFA *rva0031E8D5(const AsciiString &,int);
    Rva00409FFA *rva0031B05B(Rva00409FFA *);
    static void parseCommandSetDefinition(INI *);
};

void ControlBar::rva0031AB77SetFlag()
{
	g_Va00E01D0C = 1;
}

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void __cdecl message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

namespace rts
{
template <class T> struct hash
{
	unsigned int operator()(T value) const;
};
}

class Rva001E3624 {
public:
    virtual ~Rva001E3624();
    bool isOverride() const { return m_override; }
    void markAsOverride() { m_override=true; }
    void clearStale() { m_stale=0; }
private:
    Rva001E3624 *m_next;
    bool m_override;
    int m_stale;
};

// The map's values: each gets 0x00409FCC (rowed under this address name).
class Rva00409FFA : public Rva001E3624
{
public:
	void rva00409FCC();
};

// AsciiString-keyed: retail advances it with the iterator increment 0x00411084
// that the rts::hash<AsciiString> maps share (ICF); begin is the shared
// 0x00427195. The pointer value sits at node +8. The equality functor is not
// evidenced by these bytes.
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva0031E7F0Map;

// View of the object 0x0031AC39 walks; polymorphic here so the derived
// class below shares its address.
class Rva0031AC39
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool v02();	// 0x0031B53D in vftable 0x00C0CC88
	void rva0031AC39();
};

class Rva0031DCF0 : public Rva0031AC39
{
public:
	bool rva0031E7F0(bool *needsRestart);
private:
	char m_unmodelled04[0x28 - 0x04];
	bool m_reloaded28;
	void *m_list2C;
	Rva0031E7F0Map m_map30;
};

bool Rva0031DCF0::rva0031E7F0(bool *needsRestart)
{
	bool result = false;
	g_Va00E01D0C = result;
	if (v02())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ControlBar (CommandSet/CommandButton) reloaded. Changes effective immediately."));
		for (Rva0031E7F0Map::iterator it = m_map30.begin(); it != m_map30.end(); ++it)
		{
			(*it).second->rva00409FCC();
		}
		rva0031AC39();
		m_reloaded28 = true;
		result = true;
	}
	if (g_Va00E01D0C)
	{
		*needsRestart = true;
		g_Va00E01D0C = false;
	}
	return result;
}

// WB 0x00C2D2B0 names ControlBar::parseCommandSetDefinition at ControlBar.cpp
// line 1525; native block registration 0x007AD120 binds CommandSet to this
// complete 0x0031EC03..0x0031ED00 body. BFME1 ba7ddda7 INICommandSet.cpp guides
// the find/create/override/duplicate behavior; native adds reload type 5.
// Keep the inline restart-byte store in the unit owning that file-static byte.
// The complete proposed TU retains exact 8B setter and 137B reload-notice bodies;
// the new parser is exact through its complete 253B retail boundary.
#include "Common/INIException.h"
class INI;
typedef void (*INIFieldParseProc)(INI *,void *,void *,const void *);
struct FieldParse {
    const char *token;
    INIFieldParseProc parse;
    const void *userData;
    int offset;
};
class INI {
public:
    const char *getNextToken(const char *separators=0);
    void initFromINI(void *,const FieldParse *);
    static void parseInt(INI *,void *,void *,const void *);
    char m_unknown00[8];
    int m_loadType;
};
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class CommandSet { public: static const FieldParse m_commandSetFieldParseTable[]; };
extern ControlBar *TheControlBar;
void ControlBar::parseCommandSetDefinition(INI *ini)
{
    AsciiString name;
    name=ini->getNextToken();
    Rva00409FFA *set=(Rva00409FFA *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&name);
    if(!set) {
        set=TheControlBar->rva0031E8D5(name,0);
        if(ini->m_loadType==2) set->markAsOverride();
    } else if(ini->m_loadType==2) {
        set=TheControlBar->rva0031B05B(set);
    } else if(ini->m_loadType==5) {
        if(set->isOverride()) g_Va00E01D0C=1;
        TheControlBar->forgetStaleCommandSet(name);
        set=TheControlBar->rva0031E8D5(name,0);
        set->clearStale();
    } else {
        throw INIException(3,"Duplicate commandset %s found!",name.str());
    }
    ini->initFromINI(set,CommandSet::m_commandSetFieldParseTable);
}

// Complete retail table at RVA 0x00838DD0: 32 command slots at object+0x14,
// followed by InitialVisible at +0x94 and the four-zero terminator. Callback
// 0x0040A092 already owns its address-derived name in the function ledger.
class CommandButton;
void Rva0040A092Parse(INI *,void *,const CommandButton **,int);
const FieldParse CommandSet::m_commandSetFieldParseTable[] =
{
    {"1",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)0,0x14},
    {"2",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)1,0x14},
    {"3",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)2,0x14},
    {"4",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)3,0x14},
    {"5",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)4,0x14},
    {"6",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)5,0x14},
    {"7",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)6,0x14},
    {"8",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)7,0x14},
    {"9",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)8,0x14},
    {"10",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)9,0x14},
    {"11",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)10,0x14},
    {"12",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)11,0x14},
    {"13",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)12,0x14},
    {"14",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)13,0x14},
    {"15",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)14,0x14},
    {"16",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)15,0x14},
    {"17",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)16,0x14},
    {"18",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)17,0x14},
    {"19",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)18,0x14},
    {"20",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)19,0x14},
    {"21",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)20,0x14},
    {"22",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)21,0x14},
    {"23",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)22,0x14},
    {"24",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)23,0x14},
    {"25",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)24,0x14},
    {"26",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)25,0x14},
    {"27",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)26,0x14},
    {"28",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)27,0x14},
    {"29",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)28,0x14},
    {"30",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)29,0x14},
    {"31",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)30,0x14},
    {"32",reinterpret_cast<INIFieldParseProc>(Rva0040A092Parse),(const void *)31,0x14},
    {"InitialVisible",INI::parseInt,0,0x94},
    {0,0,0,0}
};
