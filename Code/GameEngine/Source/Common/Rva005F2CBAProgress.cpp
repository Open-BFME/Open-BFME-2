// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva005F2CBA@Rva005F2FEF@@QAEXM@Z @0x005F2CBA 135B
// Evidence: Apt rank progress float at +0x50 flag 4 at +0x58 via rowed Fire 0x00527925 AptCall 0x005FB5E6 strings SetMemberRankProgress SetMemberRankProgressBarState _show globals 0x009FE4CC 0x007BAC1C caller 0x005F2F49.
#include <math.h>
#include "ascii_string.h"
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);
int __cdecl Rva0052519DFire(void *target, void *level, const char *prefix, const char *function, int *val);
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

struct Rva005F2FEFTeam
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD {
class ArmyDetailsMovieClip
{
public:
	class Impl;
};
}

// The Apt scroll bar's owner-side setters (rowed under address names:
// SetPageSize 0x005D4BAE, SetLineSize 0x005D4BC1, SetEnabled 0x005D49CD,
// SetVisible 0x005D49D5), all called on the clip's scroll bar at +0x1C.
class Rva005D4BAE
{
public:
	void rva005D4BAE(float v);
};
class Rva005D4BC1
{
public:
	void rva005D4BC1(float v);
};
class Rva005D49CD
{
public:
	void rva005D49CD(bool v);
	void rva005D49D5(bool v);
};

// STLport rotate, rowed as its int* instantiation, and the icon slot list's
// erase, rowed as vector<void*>'s (pointer elements fold with both).
namespace _STL {
template <class _ForwardIter>
_ForwardIter rotate(_ForwardIter __first, _ForwardIter __middle, _ForwardIter __last);
template <class _Tp>
class allocator;
template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	_Tp *erase(_Tp *__position);
	_Tp *begin() { return _M_start; }
	_Tp &operator[](unsigned int __n) { return *(begin() + __n); }
	bool empty() const { return _M_start == _M_finish; }

	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};
}

// BfmePathLeafAfterMarker.cpp's path helpers.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// The scroll bar, built from the loaded movie's level and path by the
// constructor 0x005D4DA9 (pinned by address); observers join its +4 list
// through the rowed append 0x005A0B4C, and its holder sets it through the
// rowed 0x00575674 (the views AptWotrPanelCallbacks.cpp uses).
struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
	unsigned char m_pad[0x14];
};
class Rva005D4DA9
{
public:
	Rva005D4DA9(int level, const AsciiString &path);
	void *m_0;
	Rva005A0B4CList m_listeners; // +0x04
};
class Object;
class Rva00575674
{
public:
	void rva00575674(Object *scrollBar);
};
struct Rva005F2CBAScrollBarHolder
{
	void *m_ptr;
};

// The icon slot's member clip, built from the loaded movie's level and path
// (rowed ctor 0x005C31D5, 0x10 bytes) into the slot's holder at +0x20; and
// the rowed address-named body 0x005F2792 that removes the slot's
// "_OnUnitIconSlotLoaded" command map (WorldBuilder
// IconSlot::RemoveOnLoadedCommandMap).
class Rva005C31FB
{
public:
	Rva005C31FB(int level, const AsciiString &path);
	unsigned char m_pad[0x10];
};
class Rva005F2792
{
public:
	void rva005F2792();
};

// The Apt command-map registration (AptCallbackAdders.cpp's view): a
// counted reference built from an (object, method) delegate by the rowed
// 0x00579E47 and handed to the Apt player's pinned AddCommandMap 0x002243E3;
// the reference releases through the rowed 0x0007DEEF.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
class AptCommandTarget
{
};
struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};
class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};
template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};
class AptPlayer
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map); // 0x002243E3
};
__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
{
	((AptPlayer *)g_bfmeAptWindowManager)->AddCommandMap(name, &desc);
}

// The owning holder of the icon slot's clip: its destructor is the rowed
// clear 0x000AD6F4 (pinned destructor view).
class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void *m_ptr;
};

// The icon slot's base: an interface whose out-of-line destructor only
// restores its vtable (folded 0x005277B3, read from the ctor's unwind map);
// it zeroes the word at +0x04.
class Rva005F3444Base
{
public:
	Rva005F3444Base() : m_04(0) {}
	~Rva005F3444Base();
	virtual void Dispose() = 0;
	virtual int GetPosition() const = 0;
	virtual void DoMoveTo(int newPosition) = 0;

protected:
	void *m_04;
};

// The icon slot's owning pointer (rowed opaque dtor 0x005F329E: deletes the
// slot through its pinned dtor 0x005F2B22).
class Rva005F2B22;
class Rva005F329E
{
public:
	~Rva005F329E();
	Rva005F2B22 *m_elem;
};

// STLport's max and min (reference-returning).
namespace _STL {
template <class _Tp>
inline const _Tp &(max)(const _Tp &__a, const _Tp &__b) { return __a < __b ? __b : __a; }
template <class _Tp>
inline const _Tp &(min)(const _Tp &__a, const _Tp &__b) { return __b < __a ? __b : __a; }
}

// The plain fld/fistp x87 round (BaseType.h's fast_float2long_round), here
// applied to the CRT floor() of the slots-per-row quotient.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class StrategicHUD::ArmyDetailsMovieClip::Impl
{
public:
	// Retail vtable 0x00C78618 = { Dispose 0x005F3544, 0x005DB09D,
	// DoMoveTo 0x005F3606 } (WorldBuilder names); the slot's owner at +0x08
	// and its position in the owner's list at +0x10.
	class IconSlot : public Rva005F3444Base
	{
	public:
		IconSlot(Impl *owner, int aptIndex, int pos);
		virtual void Dispose();
		virtual int GetPosition() const { return m_pos; } // folded 0x001DB09D
		virtual void DoMoveTo(int newPosition);
		void OnLoaded(const char *path);

	private:
		Impl *m_owner; // +0x08
		int m_aptIndex; // +0x0C, the slot's Apt index
		int m_pos; // +0x10
		float m_x; // +0x14, the position last sent to Apt
		float m_y; // +0x18
		bool m_visible; // +0x1C, the visibility last sent to Apt
		Rva000AD6F4 m_clip; // +0x20, the slot's movie clip
		friend class Impl;
	};

	void ShowMemberRankProgress(float progress);
	void UpdateIconSlotPositions();
	void SetupScrollBar();
	void OnScrollBarLoaded(const char *name);
	void rva005F2E85();
private:
	char m_pad00[8];
	void *m_level08;
	Rva005F2FEFTeam *m_team0C;
	char m_pad10[0x1C - 0x10];
	void *m_scrollBar; // +0x1C, held through Rva005F2CBAScrollBarHolder
	int m_20; // +0x20, cleared when the last icon slot goes
	_STL::vector<void *> m_iconSlots; // +0x24
	float m_iconStageWidth; // +0x30
	float m_iconStageHeight; // +0x34
	float m_iconStageY; // +0x38, the Apt stage's current scroll offset
	float m_slotWidth; // +0x3C
	float m_slotHeight; // +0x40
	int m_scrollRow; // +0x44, the first visible row
	char m_pad48[0x50 - 0x48];
	float m_progress50;
	char m_pad54[4];
	unsigned char m_flags58;
};

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowMemberRankProgress(float progress)
{
	if (progress != m_progress50) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetMemberRankProgress", &progress);
		m_progress50 = progress;
	}
	if (!(m_flags58 & 4)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetMemberRankProgressBarState", "_show");
		m_flags58 |= 4;
	}
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::SetupScrollBar (WorldBuilder name,
// StrategicHUDArmyDetailsMovieClip.cpp lines 705..707 assert m_scrollBar,
// m_iconStageHeight, m_slotWidth/m_slotHeight): retail 0x005F258E 240B. The
// scroll bar's page and line sizes are the stage and slot heights over the
// content height (rows of slots per stage width, at least the stage height).
void StrategicHUD::ArmyDetailsMovieClip::Impl::SetupScrollBar()
{
	if (m_iconSlots._M_start != m_iconSlots._M_finish)
	{
		int slotsPerRow = fast_float2long_round(floor(m_iconStageWidth / m_slotWidth));
		int rows = ((unsigned)(m_iconSlots._M_finish - m_iconSlots._M_start) + slotsPerRow - 1) / slotsPerRow;
		float contentHeight = rows * m_slotHeight;
		if (contentHeight < m_iconStageHeight)
			contentHeight = m_iconStageHeight;
		((Rva005D4BAE *)m_scrollBar)->rva005D4BAE(m_iconStageHeight / contentHeight);
		((Rva005D4BC1 *)m_scrollBar)->rva005D4BC1(m_slotHeight / contentHeight);
		((Rva005D49CD *)m_scrollBar)->rva005D49CD(true);
		((Rva005D49CD *)m_scrollBar)->rva005D49D5(contentHeight > m_iconStageHeight);
	}
	else
	{
		((Rva005D4BAE *)m_scrollBar)->rva005D4BAE(0.0f);
		((Rva005D4BC1 *)m_scrollBar)->rva005D4BC1(0.0f);
		((Rva005D49CD *)m_scrollBar)->rva005D49CD(false);
		((Rva005D49CD *)m_scrollBar)->rva005D49D5(false);
	}
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::UpdateIconSlotPositions
// (WorldBuilder name; it calls SetupScrollBar): retail 0x005F2A07 43B.
void StrategicHUD::ArmyDetailsMovieClip::Impl::UpdateIconSlotPositions()
{
	int count = m_iconSlots._M_finish - m_iconSlots._M_start;
	for (int i = 0; i < count; ++i)
		((IconSlot *)m_iconSlots._M_start[i])->m_pos = i;
	if (m_scrollBar)
		SetupScrollBar();
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::DoMoveTo (WorldBuilder
// name, asserts lines 294..295 on newPosition and m_owner.m_iconSlots[m_pos]):
// retail 0x005F3606 76B, vtable slot 2.
void StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::DoMoveTo(int newPosition)
{
	if (newPosition == m_pos)
		return;
	int **slots = (int **)m_owner->m_iconSlots._M_start;
	if (newPosition < m_pos)
		_STL::rotate((int *)(slots + newPosition), (int *)(slots + m_pos), (int *)(slots + m_pos + 1));
	else
		_STL::rotate((int *)(slots + m_pos), (int *)(slots + m_pos + 1), (int *)(slots + newPosition + 1));
	m_owner->UpdateIconSlotPositions();
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::Dispose (WorldBuilder
// name; retail string DeleteUnitIconSlot): retail 0x005F3544 143B, vtable
// slot 0. Leaves the owner's list (rowed vector<void*>::erase 0x001FF51F),
// clears the owner's +0x20 when the list empties, deletes the Apt slot,
// renumbers the rest and deletes itself on the way out.
void StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::Dispose()
{
	Rva005F329E self = { (Rva005F2B22 *)this };
	m_owner->m_iconSlots.erase(m_owner->m_iconSlots.begin() + m_pos);
	if (m_owner->m_iconSlots.empty())
		m_owner->m_20 = 0;
	if (g_bfmeAptWindowManager)
	{
		const char *team = m_owner->m_team0C ? m_owner->m_team0C->m_name : "";
		Rva0052519DFire(g_bfmeAptWindowManager, m_owner->m_level08, team, "DeleteUnitIconSlot", &m_aptIndex);
	}
	m_owner->UpdateIconSlotPositions();
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::OnScrollBarLoaded (WorldBuilder
// name, callgraph): retail 0x005F38F5 197B, ret 4. Builds the scroll bar once,
// hides it, sizes it when the slot width is known and observes it; the
// checklist's OnScrollBarLoaded 0x0057B4F9 is the same shape.
void StrategicHUD::ArmyDetailsMovieClip::Impl::OnScrollBarLoaded(const char *name)
{
	Rva005F2CBAScrollBarHolder *scrollBar = (Rva005F2CBAScrollBarHolder *)&m_scrollBar;
	if (scrollBar->m_ptr == 0)
	{
		((Rva00575674 *)scrollBar)->rva00575674((Object *)new Rva005D4DA9(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		((Rva005D49CD *)scrollBar->m_ptr)->rva005D49D5(false);
		if (m_slotWidth > 0.0f)
			SetupScrollBar();
		((Rva005D4DA9 *)scrollBar->m_ptr)->m_listeners.append((Rva002BA8F1Listener *)this);
	}
}

// Retail 0x005F2E85 188B (unnamed in WorldBuilder; retail string
// SetUnitIconStageY; called first by Update 0x005F30AE): eases the icon
// stage's Y offset a fifth of the way toward the scroll row's offset, by at
// least a fifth of a slot, and tells Apt.
void StrategicHUD::ArmyDetailsMovieClip::Impl::rva005F2E85()
{
	float targetY = m_scrollRow * -m_slotHeight;
	if (targetY != m_iconStageY)
	{
		float newY = (targetY - m_iconStageY) * 0.2f + m_iconStageY;
		if (targetY < m_iconStageY)
			newY = (_STL::max)(newY - m_slotHeight * 0.2f, targetY);
		else
			newY = (_STL::min)(m_slotHeight * 0.2f + newY, targetY);
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level08, team, "SetUnitIconStageY", &newY);
		m_iconStageY = newY;
	}
}


// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::OnLoaded (WorldBuilder
// name; it calls IconSlot::RemoveOnLoadedCommandMap): retail 0x005F27F8 159B,
// ret 4. Builds the slot's clip once from the loaded path, then drops the
// load callback; the same shape as OnScrollBarLoaded above.
// ?StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::OnLoaded present-unmatched
void StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::OnLoaded(const char *path)
{
	Rva005F2CBAScrollBarHolder *clip = (Rva005F2CBAScrollBarHolder *)&m_clip;
	if (clip->m_ptr == 0)
	{
		((Rva00575674 *)clip)->rva00575674((Object *)new Rva005C31FB(Rva004128BBGetLevel(path), AsciiString(Rva00412845AfterLevel(path))));
		((Rva005F2792 *)this)->rva005F2792();
	}
}

// StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::IconSlot (WorldBuilder
// name, asserts lines 244..247 on m_owner.m_iconSlots[m_pos] and TheAptPlayer;
// retail strings CreateUnitIconSlot and "_level%u.%s_OnUnitIconSlotLoaded%d"):
// retail 0x005F3444 256B, ret 0xC. Takes its place in the owner's list,
// creates the Apt slot and binds its OnLoaded callback (0x005F27F8).
StrategicHUD::ArmyDetailsMovieClip::Impl::IconSlot::IconSlot(Impl *owner, int aptIndex, int pos)
	: m_owner(owner), m_aptIndex(aptIndex), m_pos(pos), m_x(0.0f), m_y(0.0f), m_visible(true)
{
	m_owner->m_iconSlots[m_pos] = this;
	const char *team = m_owner->m_team0C ? m_owner->m_team0C->m_name : "";
	Rva0052519DFire(g_bfmeAptWindowManager, m_owner->m_level08, team, "CreateUnitIconSlot", &m_aptIndex);
	AsciiString name;
	team = m_owner->m_team0C ? m_owner->m_team0C->m_name : "";
	name.format("_level%u.%s_OnUnitIconSlotLoaded%d", m_owner->m_level08, team, m_aptIndex);
	AddCommandMapDelegate(name, DelegateDesc(this, &IconSlot::OnLoaded));
}
