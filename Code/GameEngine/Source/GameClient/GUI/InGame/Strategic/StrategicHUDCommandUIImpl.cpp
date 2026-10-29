// The complete native parents and associative EH code/data graphs prove
// platformsdk
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::CommandUIImpl (WorldBuilder StrategicHUDCommandUIImpl.cpp
// names OnSubMenuLoaded and OnToggleFlashLoaded). Target facts: the Apt
// callbacks 0x005D27E5 and 0x005D2920 (ret 4) read the button slot index
// (rowed 0x005D2505, 0..5) and the "name" parameter (pinned 0x004128F0)
// from the Apt path; when that slot (stride 0x1C from +0x1C) has no
// sub-menu (+0x04) / toggle flash (+0x08) yet they build one (0x10 bytes,
// ctor 0x005D2405, WorldBuilder ButtonSubMenu::ButtonSubMenu / 8 bytes,
// ctor 0x005C3932) from the name's level (0x004128BB) and leaf (0x00412845)
// and hand it to the slot's owning holder, whose reset is the folded
// 0x00575674 / 0x00528FE6 (address-named views here).
#include "ascii_string.h"
#define inline static inline
#include <math.h>
#undef inline
#include <windows.h>

class Rva005D2462
{
public:
	Rva005D2462(int level, const AsciiString &name, int a, int b);
private:
	char m_pad[0x18];
};
struct TargetRef00217D4C {virtual void*destroy(unsigned);virtual void slot1();int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {TargetRef00217D4C*m_ptr;TreeHintRef00217D4C(const TreeHintRef00217D4C&);TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}};
class Rva005C39C4 {public:TreeHintRef00217D4C rva005C39C4(int);};
class Rva002BED91 {public:void clear();TargetRef00217D4C*ptr;};

class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
AsciiString __cdecl Rva00222834Get(int val);

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

static __forceinline const char *GetStr(const AsciiString &asciiString)
{
	char *stringData = *(char **)(void *)&asciiString;
	return stringData ? stringData + 8 : "";
}

inline __declspec(noinline) int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 2, GetStr(Rva00222834Get(*a5)), a6, 0, 0, 0);
}



namespace StrategicHUD { bool __cdecl ParseButtonSlotIndex(const char *params, int *out); }
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }

// The slot's owning holders: reset(new object) deletes the old one (rowed
// address-named setters; their parameter types are those views').
class Object;
struct CameraMarker;
class Rva00575674
{
public:
	void rva00575674(Object *object);
	void *get() const { return m_ptr; }

private:
	void *m_ptr;
};
class Rva00528FE6
{
public:
	void rva00528FE6(CameraMarker *marker);

private:
	void *m_ptr;
};

// The Apt clip base the sub-menu derives from (vtable at +0x00, its
// impl at +0x04; rowed under address names, ctor 0x005C40E7 with an untyped
// two-argument view: here the clip's level and name). Its empty hook, which
// the sub-menu's shown/hidden handlers call first (WorldBuilder 0x1559FA0 /
// 0x1559FB0), is folded in retail into the shared empty body at 0x000B3FD0
// and is called here through that address's opaque pin.
class Rva005C3F02
{
public:
	Rva005C3F02(void *level, void *name);
	virtual ~Rva005C3F02();
	void rva005C3E81();

private:
	void *m_impl; // +0x04
};

// The folded empty body (pinned opaque name).
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

// The per-slot sub-menu clip's activation (rowed 0x005C39AA, address-named).
class Rva005C39AA
{
public:
	void rva005C39AA();
};

namespace StrategicHUD {
class CommandUIImpl
{
public:
	virtual int rva005D24E5(int);
	virtual void rva005D264D(int, const struct TreeHintRef00217D4C &);
	virtual void rva005D2664(int);
	virtual void rva005D269B();
	virtual void DoFlashButton(int slot, float duration);

	// Target facts: ctor 0x005D2405 (WorldBuilder name, callgraph) installs
	// vtable 0x008757D8 = { scalar deleting dtor 0x005D2495, 0x005D24B1,
	// 0x005D2449 }; the dtor 0x005D242F reinstalls it. WorldBuilder's
	// ButtonSubMenu vtable names slot 1 OnShown; slot 2 is unnamed there.
	class ButtonSubMenu : public Rva005C3F02
	{
	public:
		ButtonSubMenu(CommandUIImpl *owner, int slot, int level, const AsciiString &name);
		virtual ~ButtonSubMenu();
		virtual void OnShown();
		virtual void OnHidden();

	private:
		CommandUIImpl *m_owner; // +0x08
		int m_slot; // +0x0C
	};

	void Update();
	void OnButtonFrameLoaded(const char *path);
	void OnSubMenuLoaded(const char *path);
	void OnToggleFlashLoaded(const char *path);

private:
	struct ButtonSlot
	{
		Rva00575674 m_frame; // +0x00
		Rva00575674 m_subMenu; // +0x04
		Rva00528FE6 m_toggleFlash; // +0x08
		Rva002BED91 queued;
		TreeHintRef00217D4C active;
		unsigned startTime,timeout;
	};

	void *level;
	AsciiString name;
	char m_pad0C[0x18 - 0x0C];
	int m_currentSubMenu; // +0x18: slot whose sub-menu is shown, or -1
	ButtonSlot m_slots[6]; // +0x1C
};
}

StrategicHUD::CommandUIImpl::ButtonSubMenu::ButtonSubMenu(CommandUIImpl *owner, int slot, int level, const AsciiString &name)
	: Rva005C3F02((void *)level, (void *)&name), m_owner(owner), m_slot(slot)
{
}

StrategicHUD::CommandUIImpl::ButtonSubMenu::~ButtonSubMenu()
{
	if (m_owner->m_currentSubMenu == m_slot)
		m_owner->m_currentSubMenu = -1;
}

void StrategicHUD::CommandUIImpl::ButtonSubMenu::OnShown()
{
	((Rva000B3FD0 *)this)->rva000B3FD0();
	if (m_owner->m_currentSubMenu != m_slot)
	{
		if (m_owner->m_currentSubMenu >= 0)
			((Rva005C39AA *)m_owner->m_slots[m_owner->m_currentSubMenu].m_subMenu.get())->rva005C39AA();
		m_owner->m_currentSubMenu = m_slot;
	}
}

void StrategicHUD::CommandUIImpl::ButtonSubMenu::OnHidden()
{
	((Rva000B3FD0 *)this)->rva000B3FD0();
	if (m_owner->m_currentSubMenu == m_slot)
		m_owner->m_currentSubMenu = -1;
}

// The toggle flash clip built per slot (8 bytes; ctor 0x005C3932, pinned;
// name unknown).
class Rva005C3932
{
public:
	Rva005C3932(int level, const AsciiString &name);

private:
	int m_level; // Native constructor writes +0 before copy construction at +4.
	AsciiString m_name;
};

// Both rowed callers allocate8 bytes and construct this two-field object.
Rva005C3932::Rva005C3932(int level, const AsciiString &name)
	: m_level(level), m_name(name)
{}

void StrategicHUD::CommandUIImpl::OnSubMenuLoaded(const char *path)
{
	AsciiString name;
	int slot;
	if (!StrategicHUD::ParseButtonSlotIndex(path, &slot) || !Rva004128F0GetParam(path, "name", name))
		return;
	ButtonSlot &button = m_slots[slot];
	if (*(void **)&button.m_subMenu)
		return;
	button.m_subMenu.rva00575674((Object *)new ButtonSubMenu(this, slot, AptUtils::LevelIndexFromTarget(name.str()), AsciiString(AptUtils::SkipLevelN(name.str()))));
}

void StrategicHUD::CommandUIImpl::OnToggleFlashLoaded(const char *path)
{
	AsciiString name;
	ButtonSlot *button;
	{
		int slot;
		if (!StrategicHUD::ParseButtonSlotIndex(path, &slot))
			return;
		if (!Rva004128F0GetParam(path, "name", name))
			return;
		button = &m_slots[slot];
	}
	if (*(void **)&button->m_toggleFlash)
		return;
	button->m_toggleFlash.rva00528FE6((CameraMarker *)new Rva005C3932(AptUtils::LevelIndexFromTarget(name.str()), AsciiString(AptUtils::SkipLevelN(name.str()))));
}

// WB15AD7B0: per-slot help/submenu updates and flash expiry. The visible
// Apt forwarder above restores retail's owner stack home without volatile.
void StrategicHUD::CommandUIImpl::Update()
{
    CommandUIImpl *self = this;
    for (int i = 0; i < 6; ++i)
    {
        ButtonSlot *slot = &self->m_slots[i];
        if (slot->m_frame.get())
        {
            if (slot->queued.ptr)
            {
                slot->active = ((Rva005C39C4 *)slot->queued.ptr)->rva005C39C4((int)slot->m_frame.get());
                slot->queued.clear();
            }
            if (slot->active.m_ptr)
                slot->active.m_ptr->slot1();
        }
        if (slot->m_subMenu.get())
            ((Rva005C3F02 *)slot->m_subMenu.get())->rva005C3E81();
        if (slot->timeout && timeGetTime() - slot->startTime >= slot->timeout)
        {
            CommandUIImpl *owner = self;
            Rva00525338Fire(g_bfmeAptWindowManager, owner->level,
                owner->name.str(), "SetFlashEffectState", &i, (void *)"_hide");
            slot->timeout = 0;
        }
    }
}

void StrategicHUD::CommandUIImpl::OnButtonFrameLoaded(const char *params)
{
	AsciiString name;
	ButtonSlot *button;
	{
		int idx;
		if (!StrategicHUD::ParseButtonSlotIndex(params, &idx) || !Rva004128F0GetParam(params, "name", name))
			return;
		button = &m_slots[idx];
		if (*(void **)&button->m_frame)
			return;
	}
	button->m_frame.rva00575674((Object *)new Rva005D2462(
		AptUtils::LevelIndexFromTarget(name.str()),
		AsciiString(AptUtils::SkipLevelN(name.str())),
		(int)&button->m_subMenu,
		(int)&button->m_toggleFlash));
}

void StrategicHUD::CommandUIImpl::DoFlashButton(int slot, float duration)
{
	ButtonSlot *btn = &m_slots[slot];
	int old = btn->timeout;
	unsigned long currentTime = timeGetTime();
	float s = duration * 1000.0f;
	btn->startTime = currentTime;
	s = s + 0.5f;
	float roundedDurationMilliseconds = floorf(s);
	int ni;
	__asm {
		fld [roundedDurationMilliseconds]
		fistp [ni]
	}
	btn->timeout = ni;
	if (old == 0) {
		if (ni == 0)
			return;
		Rva00525338Fire(g_bfmeAptWindowManager, level, name.str(), "SetFlashEffectState", &slot, (void *)"_show");
	} else {
		if (ni != 0)
			return;
		Rva00525338Fire(g_bfmeAptWindowManager, level, name.str(), "SetFlashEffectState", &slot, (void *)"_hide");
	}
}
