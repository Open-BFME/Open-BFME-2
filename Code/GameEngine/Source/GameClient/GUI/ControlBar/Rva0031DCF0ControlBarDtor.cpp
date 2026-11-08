// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??1Rva0031DCF0@@UAE@XZ retail 0x0031DCF0..0x0031DF89 665 B.
// Destructor called by the scalar deleting destructor 0x0031EB7A (vtable
// 0x00C0CC88 slot 0; slot 9 of that table is the matched ControlBar::reset
// 0x0031E09E so this is ControlBar's destructor; the opaque pinned class
// name is kept). The member layout is the ControlBar one the matched
// ControlBar::reset 0x0031E09E reads (+0x2C command list with next at +0x18
// / +0x30 window-video map walked with 0x00427195 and 0x00411084 / +0x44
// ControlBarSchemeManager / +0xDC 32-window array / +0x2A4 holder cleared
// by 0x000AD6F4 / +0x26C / +0x298): global-delete the four owned objects
// at +0xC..+0x18 and the scheme manager / every map value / the command
// list / the +0xD4 layout after its slot 8 / destroy the window array (each
// slot is cleared before winDestroy reads it) and +0x68 / global-delete the
// +0x2A0 object and both pointer vectors' entries then clear them; leave
// TheSubsystemList then the members (map dtor 0x0031C79D) and the
// SubsystemInterface base. WorldBuilder twin 0x00C299B0 has the same body.
// Offsets and callee names are target evidence; class names stay opaque.
typedef bool Bool;
// C++-linkage free (0x00030830) as LargeGroupAudio.cpp uses for vector storage.
namespace _STL { void __cdecl free(void *); }
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releasePointerStorage(void *storage)
{
	_STL::free(storage);
}
#include <cstdlib>
#include <vector>
namespace _STL {
template<> inline void allocator<void *>::deallocate(void **__p, size_type) const
{
	if (__p != 0) releasePointerStorage((void *)__p);
}
}
#include "ascii_string.h"
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../Include/Common/SubsystemInterfaceList.h"
extern SubsystemInterfaceList *TheSubsystemList;

#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
// bfme link decl-only end

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}

class GameWindow;
class GadgetCreateView;
class WindowLayout;
typedef int Int;
#include "../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;


struct Rva0031DCF0Owned
{
	virtual ~Rva0031DCF0Owned();
};

struct Rva0031DCF0Command
{
	virtual ~Rva0031DCF0Command();
	char pad04[0x18 - 4];
	Rva0031DCF0Command *m_next;
};

struct Rva0031DCF0Layout
{
	virtual void v00();
	virtual ~Rva0031DCF0Layout();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void destroyWindows();	// +0x20
};

// class-gate: allow ControlBarSchemeManager retail calls the out-of-line dtor 0x003204D9; ControlBarSchemeManagerView.h declares none so its implicit dtor inlines the list teardown (proved by bytes)
class ControlBarSchemeManager
{
public:
	~ControlBarSchemeManager();
};

#include "../../../../Include/GameClient/Rva000411084.h"
struct Rva0031DCF0Iterator { char *m_current; void *m_owner; };

#include <utility>
struct NoCaseTreeValue4;
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> Bef1Pair;
struct VideoPair;
class Rva000411084;
#include "../../../../Include/GameLogic/Rva000427195.h"

#include <hash_map>
class Rva00409FFA;
namespace rts
{
template <class T> struct hash
{
    unsigned int operator()(T value) const;
};
}
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > Rva0031E7F0Map;
class Rva0031C79DMap : public Rva0031E7F0Map
{
public:
    ~Rva0031C79DMap();
};

#include "../../../../Include/Common/Rva000AD6F4.h"

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

Rva0031DCF0::~Rva0031DCF0()
{
	m_26C = 0;
	if (m_0C)
		::delete m_0C;
	m_0C = 0;
	if (m_14)
		::delete m_14;
	m_14 = 0;
	if (m_10)
		::delete m_10;
	m_10 = 0;
	if (m_18)
		::delete m_18;
	m_18 = 0;
	if (m_schemeManager)
		delete m_schemeManager;
	m_schemeManager = 0;

	{
		Rva0031DCF0Iterator it;
		for (reinterpret_cast<Rva000427195 *>(&m_videoMap)->first((Rva000411084 *)&it);
			it.m_current != 0; ((Rva000411084 *)&it)->next())
			::delete *(Rva0031DCF0Owned **)(it.m_current + 8);
	}

	while (m_commands) {
		Rva0031DCF0Command *next = m_commands->m_next;
		::delete m_commands;
		m_commands = next;
	}

	if (m_layout) {
		m_layout->destroyWindows();
		::delete m_layout;
		m_layout = 0;
	}

	for (int i = 0; i < 32; ++i) {
		m_windows[i] = 0;
		TheWindowManager->winDestroy(m_windows[i]);
		m_windows[i] = 0;
	}
	TheWindowManager->winDestroy(m_68);
	m_68 = 0;
	m_298 = 0;
	::delete m_2A0;
	m_2A0 = 0;

	unsigned int elementIndex;
	for (elementIndex = 0; elementIndex < m_230.size(); ++elementIndex)
		::delete (Rva0031DCF0Owned *)m_230[elementIndex];
	for (elementIndex = 0; elementIndex < m_23C.size(); ++elementIndex)
		::delete (Rva0031DCF0Owned *)m_23C[elementIndex];
	m_230.clear();
	m_23C.clear();

	if (TheSubsystemList)
		TheSubsystemList->removeSubsystem(this);
}
