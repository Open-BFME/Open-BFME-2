// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2
// stlport
// Target 0x0031E94C..0x0031EB7A, RET, 558 bytes.
// Ownership guide: BFME1 575ba2b047 ControlBarConstructor.cpp uses WeakPointer
// and OwnedPointer for its corresponding tail fields. Target stores establish
// +2A0/+2A4. +2A0 is a plain pointer cleared in member order: ControlBar::init hands it to
// winSetUserData, and a weak holder adds no cleanup. +2A4 is the holder
// ControlBar::reset and ControlBar::update release through clear (0x000AD6F4);
// the ctor nulls its pointer in member order (an inline default ctor). Its
// pointee type is unknown; the EH map stays exact (no member-dtor state).
// ??0ControlBar@@QAE@XZ @ 0x0031E94C 558B: ControlBar constructor.
// Evidence: pinned name; callers ?init@InGameUI@@UAEXXZ 0x0029E5D0 and
// ?recreateControlBar@InGameUI@@UAEXXZ 0x0029F890; vtable data 0x0080CC88;
// donor Zero Hour ControlBar::ControlBar plus BFME1 ControlBarConstructor.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <vector>
#include "ascii_string.h"

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$vector@UPlayerAITypeEntry@@V?$allocator@UPlayerAITypeEntry@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct PlayerAITypeEntry;
namespace _STL { template <> vector<PlayerAITypeEntry,allocator<PlayerAITypeEntry> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@UPlayerAITypeEntry@@V?$allocator@UPlayerAITypeEntry@@@_STL@@@_STL@@QAE@X:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct PlayerAITypeEntry;
namespace _STL { template <> _Vector_base<PlayerAITypeEntry,allocator<PlayerAITypeEntry> >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UPlayerAITypeEntry@@@_STL@@QBEXPAUPlayerAITypeEntry@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct PlayerAITypeEntry;
namespace _STL { template <> void allocator<PlayerAITypeEntry>::deallocate(PlayerAITypeEntry *,unsigned int) const; }

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

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

typedef unsigned int UnsignedInt;
inline UnsignedInt GameMakeColor(int r, int g, int b, int a) { return (a << 24) | (r << 16) | (g << 8) | b; }

class GameWindow;

#include "ControlBarMemberTypes.h"  // the +0x30 map and the +0x2A4 holder

// The hash-map provider owns these helpers; its element view has eight bytes.
namespace _STL {
typedef hashtable<pair<const int, Rva0031DBFCElement>, int, hash<int>,
    _Select1st<pair<const int, Rva0031DBFCElement> >, equal_to<int>,
    allocator<pair<const int, Rva0031DBFCElement> > > ControlBarTable;
template <> void ControlBarTable::_M_initialize_buckets(size_t);
template <> void ControlBarTable::clear();
}

struct PlayerAITypeEntry
{
	AsciiString m_name;
	char m_unknown[12];
};

typedef bool Bool;
#include "subsystem_interface.h"

class WindowVideoManager : public SubsystemInterface { public: WindowVideoManager(); virtual void init(); virtual void reset(); virtual void update(); private: char m_opaque[0x24 - 0x0C]; };

class AnimateWindowManager : public SubsystemInterface { public: AnimateWindowManager(); virtual void init(); virtual void reset(); virtual void update(); private: char m_opaque[0x38 - 0x0C]; };

#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

class ControlBarSchemeManager;
class Image;

class Rva0053B914
{
public:
	void rva0053B914();
};

class Rva0053ED1A
{
public:
	Rva0053ED1A();
private:
	char m_pad[0x5C];
};

class Rva0053ED1A_InitView
{
public:
	virtual void v00();
	virtual void v01();
};

class ControlBar : public SubsystemInterface
{
public:
	ControlBar();
	virtual void init(void);
	virtual void update(void);
	void rva0031AD14(int a, int b, int c, int d, int e);

private:
	WindowVideoManager *m_videoManager;
	AnimateWindowManager *m_animateWindowManager;
	AnimateWindowManager *m_animateWindowManagerForGenShortcuts;
	AnimateWindowManager *m_generalsScreenAnimate;
	ICoord2D m_defaultControlBarPosition;
	int m_0024;
	bool m_UIDirty;
	char m_pad29[3];
	void *m_002C;
	_STL::hash_map<int, Rva0031DBFCElement> m_0030;
	ControlBarSchemeManager *m_controlBarSchemeManager;
	// Nine slots: the constructor clears +0x48..+0x6C with one rep stosd.
	GameWindow *m_contextParent[9];
	void *m_006C;
	int m_0070;
	int m_0074;
	float m_0078;
	int m_007C;
	int m_0080;
	GameWindow *m_rightHUDWindow;
	GameWindow *m_rightHUDCameoWindow;
	char m_pad8C[0xA0 - 0x8C];
	GameWindow *m_rightHUDUnitSelectParent;
	GameWindow *m_communicatorButton;
	GameWindow *m_specialPowerShortcutButtons[5];
	GameWindow *m_specialPowerShortcutButtonParents[5];
	char m_padD0[4];
	void *m_00D4;
	void *m_00D8;
	GameWindow *m_commandWindows[32];
	void *m_015C[32];
	bool m_sideSelectAnimateDown;
	char m_pad1DD[3];
	int m_01E0;
	int m_01E4;
	int m_01E8;
	int m_01EC;
	int m_01F0;
	int m_01F4;
	int m_01F8;
	int m_01FC;
	void *m_0200;
	int m_0204;
	UnsignedInt m_0208;
	bool m_020C;
	char m_pad20D[3];
	void *m_0210;
	bool m_showBuildToolTipLayout;
	char m_pad215[3];
	int m_commandButtonBorderBuildColor;
	int m_commandButtonBorderActionColor;
	int m_commandButtonBorderUpgradeColor;
	int m_commandButtonBorderSystemColor;
	int m_commandButtonBorderBfme5Color;
	UnsignedInt m_022C;
	_STL::vector<PlayerAITypeEntry> m_0230;
	_STL::vector<PlayerAITypeEntry> m_023C;
	const Image *m_genStarOn;
	const Image *m_genStarOff;
	void *m_0250;
	void *m_0254;
	void *m_0258;
	void *m_025C;
	void *m_0260;
	void *m_0264;
	char m_pad268[4];
	void *m_026C;
	void *m_0270;
	void *m_0274;
	bool m_genStarFlash;
	char m_pad279[0x290 - 0x279];
	bool m_0290;
	char m_pad291[3];
	int m_0294;
	GameWindow *m_radarAttackGlowWindow;
	int m_rva0031C83D29C;
	void *m_commandWindowUserData;
	Rva000AD6F4 m_buildToolTipLayout;
	_STL::vector<PlayerAITypeEntry> m_02A8;
};

ControlBar::ControlBar() : m_showBuildToolTipLayout(false), m_commandWindowUserData(0)
{
	m_002C = 0;
	m_controlBarSchemeManager = 0;
	m_020C = false;
	m_0210 = 0;
	m_01F4 = 0;
	m_01F0 = 0;
	m_01E4 = 0;
	m_01E0 = 0;
	m_01FC = 0;
	m_01F8 = 0;
	m_01EC = 0;
	m_01E8 = 0;
	m_0200 = 0;
	m_0204 = 0;
	for (int i = 0; i < 32; ++i)
		m_015C[i] = 0;
	UnsignedInt clock = GameMakeColor(0, 0, 0, 100);
	m_0208 = clock;
	m_022C = clock;
	m_0070 = 0;
	m_defaultControlBarPosition.y = 0;
	m_defaultControlBarPosition.x = 0;
	m_genStarFlash = false;
	m_genStarOff = 0;
	m_genStarOn = 0;
	m_UIDirty = false;
	for (int i = 0; i < 9; ++i)
		m_contextParent[i] = 0;
	for (int i = 0; i < 32; ++i)
		m_commandWindows[i] = 0;
	for (int i = 0; i < 5; ++i)
	{
		m_specialPowerShortcutButtons[i] = 0;
		m_specialPowerShortcutButtonParents[i] = 0;
	}
	m_00D8 = 0;
	m_00D4 = 0;
	m_rightHUDWindow = 0;
	m_rightHUDCameoWindow = 0;
	m_rightHUDUnitSelectParent = 0;
	m_communicatorButton = 0;
	m_006C = 0;
	m_0070 = 0;
	m_0074 = 0;
	m_0078 = -1.0f;
	m_007C = 0;
	((Rva0053B914 *)this)->rva0053B914();
	int white = (int)GameMakeColor(255, 255, 255, 0);
	m_0080 = 0;
	m_videoManager = 0;
	m_animateWindowManager = 0;
	m_generalsScreenAnimate = 0;
	m_animateWindowManagerForGenShortcuts = 0;
	m_0250 = 0;
	m_0254 = 0;
	m_0258 = 0;
	m_025C = 0;
	m_0260 = 0;
	m_0264 = 0;
	m_0270 = 0;
	m_0274 = 0;
	m_026C = 0;
	m_sideSelectAnimateDown = false;
	rva0031AD14(white, white, white, white, white);
	m_0290 = false;
	m_0294 = 0;
	m_radarAttackGlowWindow = 0;
	m_rva0031C83D29C = 0;
	Rva0053ED1A *overlay = new Rva0053ED1A;
	m_commandWindowUserData = overlay;
	((Rva0053ED1A_InitView *)overlay)->v01();
	if (TheSubsystemList != 0)
		TheSubsystemList->rva001B5018(this);
}
