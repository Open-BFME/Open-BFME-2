// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
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
#include <list>
#include "unicode_string.h"
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline void *&_STL::vector<void*>::operator[](size_t __n) { return *(this->_M_start + __n); }
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return this->_M_finish; }
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Imported inline: still inlined, never emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
}

// g_Va00E01D0C: VA 0x00E01D0C (.bss); retail initial byte 00.
static bool g_Va00E01D0C;

// WB 0x00C2D900 retains the receiver at entry; INICommandButton's native
// 0x001DAFEA loads TheControlBar before its call. The original method name
// remains unknown, but its thiscall ABI is established independently of the
// eight-byte optimized body, which does not need to read the receiver.
class INI;
class CommandSet;
typedef bool Bool;
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "ControlBarMemberTypes.h"
enum CommandButtonMappedBorderType
{
    COMMAND_BUTTON_BORDER_NONE,
    COMMAND_BUTTON_BORDER_BUILD,
    COMMAND_BUTTON_BORDER_UPGRADE,
    COMMAND_BUTTON_BORDER_ACTION,
    COMMAND_BUTTON_BORDER_SYSTEM,
    COMMAND_BUTTON_BORDER_BFME5
};
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};
class CommandButton;
class GameWindow;
class Image;
class Player;
class Object;
struct Coord3D;
class PlayerTemplate;
class WindowVideoManager;
class AnimateWindowManager;
struct ICoord2D;
struct Rva0031DBFCElement;
class ControlBarSchemeManager;
class Drawable;
class WindowLayout;
struct PlayerAITypeEntry;
class Rva000AD6F4;
#include "../../../../Include/GameClient/ControlBar.h"

void ControlBar::rva0031AB77SetFlag()
{
	g_Va00E01D0C = 1;
}

class Drawable;
class UnicodeString;
typedef std::list<Drawable *> DrawableList;
class InGameUI
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void __cdecl message(UnicodeString format, ...);	// +0x40
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void notify();	// +0x110
	virtual void v69();
	virtual int getSelectCount();	// +0x118
	virtual void v71();
	virtual void v72();
	virtual const DrawableList *getAllSelectedDrawables() const;	// +0x124
	virtual void v74();
	virtual void v75();
	virtual int getSoloNexusSelectedDrawableID();	// +0x130
	bool areSelectedObjectsControllable() const;	// 0x0029C752
	char m_pad04[0x11];
	unsigned char m_15;
	unsigned char m_16;
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

// Retail's bucket index 0x00223149 passes the key's address to the hash at
// 0x00055041 (ret 4, no AsciiString copy), so the hasher takes the key by
// reference; the by-value spelling copies the key and keeps the two-argument
// bucket index out of line, which is not retail's chain under 0x00411084.
unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name);
namespace rts
{
template <class T> struct hash;
template <> struct hash<AsciiString>
{
	__declspec(dllimport) __forceinline
	unsigned int operator()(const AsciiString &value) const { return Rva00055041AsciiHash(&value); }
};
}

// The map's values: each gets refreshIfStale (0x00409FCC). The INI field
// table and button parser further down belong to the same class.
struct FieldParse;
class Overridable
{
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const;
    Overridable *deleteOverrides();
    bool isOverride() const { return m_isOverride; }
    void markAsOverride() { m_isOverride = true; }
    void setNextOverride(Overridable *next) { m_nextOverride = next; }
    void clearStale() { m0C = 0; }
private:
    Overridable *m_nextOverride;
    bool m_isOverride;
    int m0C;
};
class CommandSet : public Overridable
{
public:
    CommandSet(const AsciiString &, int);
    virtual ~CommandSet();
    const AsciiString &getName() const { return m_name; }
    const class CommandButton *getCommandButton(int) const;
    void refreshIfStale();
    static const FieldParse m_commandSetFieldParseTable[];
    static void parseCommandButton(class INI *, void *, const class CommandButton **, int);
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};

// Value view for the map below. Its iterator increment (0x00411084) and begin
// (0x00427195) are ICF-folded bodies whose addresses already carry other real
// names, so their pins keep this address-named value spelling; each value is
// a CommandSet, reached through this empty derived view at offset 0.
class Rva00409FFA : public CommandSet {};

// AsciiString-keyed: retail advances it with the iterator increment 0x00411084
// that the rts::hash<AsciiString> maps share (ICF); begin is the shared
// 0x00427195. The pointer value sits at node +8. The equality functor is not
// evidenced by these bytes.
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva0031E7F0Map;
typedef _STL::hashtable<_STL::pair<const AsciiString, Rva00409FFA *>,
	AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<_STL::pair<const AsciiString, Rva00409FFA *> >,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00409FFA *> > > Rva0031E7F0Table;

// 0x00223149 hashes before it reads the bucket count (the AptScreenClose.cpp
// spelling of the same shared bucket index).
namespace _STL {
template <> inline unsigned int Rva0031E7F0Table::_M_bkt_num_key(const AsciiString &key) const
{
	unsigned int hash = _M_hash(key);
	return hash % _M_buckets.size();
}
// 0x003F7925 reads the table pointer once, before the bucket index call.
typedef _Hashtable_iterator<pair<const AsciiString, Rva00409FFA *>, AsciiString,
	rts::hash<AsciiString>, _Select1st<pair<const AsciiString, Rva00409FFA *> >,
	equal_to<AsciiString>, allocator<pair<const AsciiString, Rva00409FFA *> > > Rva0031E7F0IteratorCore;
template <> _Hashtable_node<pair<const AsciiString, Rva00409FFA *> > *Rva0031E7F0IteratorCore::_M_skip_to_next()
{
	const Rva0031E7F0Table *table = _M_ht;
	size_t bucket = table->_M_bkt_num(_M_cur->_M_val);
	size_t count = table->bucket_count();
	_Node *node = 0;
	while (node == 0 && ++bucket < count)
		node = (_Node *)table->_M_buckets[bucket];
	return node;
}
}


struct Rva0031DCF0Owned;
struct Rva0031DCF0Command;
struct Rva0031DCF0Layout;
class Rva0031C79DMap : public Rva0031E7F0Map
{
public:
    ~Rva0031C79DMap();
};
// ControlBar view (vftable 0x00C0CC88) has its SubsystemInterface base at +0.
class Rva0031DCF0 : public SubsystemInterface
{
public:
	virtual ~Rva0031DCF0();
	bool rva0031E7F0(bool *needsRestart);

	Rva0031DCF0Owned *m_0C;
	Rva0031DCF0Owned *m_10;
	Rva0031DCF0Owned *m_14;
	Rva0031DCF0Owned *m_18;
	char pad1C[0x28 - 0x1c];
	bool m_reloaded28;
	char m_pad29[3];
	Rva0031DCF0Command *m_commands;		// +0x2C
	Rva0031C79DMap m_videoMap;		// +0x30
	ControlBarSchemeManager *m_schemeManager;	// +0x44
	char pad48[0x68 - 0x48];
	GameWindow *m_68;
	char pad6C[0xd4 - 0x6c];
	Rva0031DCF0Layout *m_layout;		// +0xD4
	char padD8[4];
	GameWindow *m_windows[32];		// +0xDC
	char pad15C[0x230 - 0x15c];
	_STL::vector<void *> m_230;
	_STL::vector<void *> m_23C;
	char pad248[0x26c - 0x248];
	int m_26C;
	char pad270[0x298 - 0x270];
	int m_298;
	char pad29C[4];
	Rva0031DCF0Owned *m_2A0;
	Rva000AD6F4 m_2A4;
	_STL::vector<void *> m_2A8;
};

bool Rva0031DCF0::rva0031E7F0(bool *needsRestart)
{
	bool result = false;
	g_Va00E01D0C = result;
	if (loadIniFilesFromLegend()) // 0x0031B53D in vftable 0x00C0CC88
	{
		TheInGameUI->message(UnicodeString(L"RIF: ControlBar (CommandSet/CommandButton) reloaded. Changes effective immediately."));
		for (Rva0031E7F0Map::iterator it = m_videoMap.begin(); it != m_videoMap.end(); ++it)
		{
			(*it).second->refreshIfStale();
		}
		((ControlBar *)this)->postProcessCommands();
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
#include "../../../../Include/Common/INI/FieldParse.h"
class INI;
class Xfer;
enum INILoadType { INI_LOAD_OVERWRITE = 1 };
#include "../../../../Include/Common/INI/INI.h"
struct Rva0041534BIter;
#include "../../../../Include/GameClient/Rva00056F61.h"
#include "../../../../Include/Common/Rva0031D5F8.h"
extern ControlBar *TheControlBar;
void ControlBar::parseCommandSetDefinition(INI *ini)
{
    AsciiString name;
    name=ini->getNextToken();
    CommandSet *set=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&name);
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

const FieldParse CommandSet::m_commandSetFieldParseTable[] =
{
    {"1",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)0,0x14},
    {"2",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)1,0x14},
    {"3",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)2,0x14},
    {"4",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)3,0x14},
    {"5",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)4,0x14},
    {"6",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)5,0x14},
    {"7",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)6,0x14},
    {"8",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)7,0x14},
    {"9",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)8,0x14},
    {"10",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)9,0x14},
    {"11",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)10,0x14},
    {"12",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)11,0x14},
    {"13",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)12,0x14},
    {"14",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)13,0x14},
    {"15",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)14,0x14},
    {"16",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)15,0x14},
    {"17",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)16,0x14},
    {"18",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)17,0x14},
    {"19",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)18,0x14},
    {"20",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)19,0x14},
    {"21",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)20,0x14},
    {"22",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)21,0x14},
    {"23",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)22,0x14},
    {"24",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)23,0x14},
    {"25",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)24,0x14},
    {"26",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)25,0x14},
    {"27",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)26,0x14},
    {"28",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)27,0x14},
    {"29",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)28,0x14},
    {"30",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)29,0x14},
    {"31",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)30,0x14},
    {"32",reinterpret_cast<INIFieldParseProc>(CommandSet::parseCommandButton),(const void *)31,0x14},
    {"InitialVisible",INI::parseInt,0,0x94},
    {0,0,0,0}
};
