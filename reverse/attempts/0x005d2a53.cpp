// ?Update@CommandUIImpl@StrategicHUD@@QAEXXZ
// partial score=0.9 date=2026-10-06
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

bool __cdecl Rva005D2505Get(const char *params, int *out); // StrategicHUD::ParseButtonSlotIndex in WorldBuilder
bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

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
	void rva005C3E81(); // per-frame forward to its element (rowed)

private:
	void *m_impl; // +0x04
};

// The folded empty body (pinned opaque name).
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

// The slot's counted help handle (assignment 0x002174A4 and release
// 0x0007DEEF rowed elsewhere); the help object's vtable slot 1 runs per frame.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	virtual void vslot1();
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);

	TargetRef00217D4C *m_ptr;
};

// The slot's pending button settings: a holder whose clear (0x002BED91)
// releases it, and whose object's vtable slot 2 (forwarder 0x005C39C4,
// rowed) builds the button's help handle.
struct Rva002BED91
{
	void *m_ptr;
	void clear();
};
class Rva005C39C4
{
public:
	TreeHintRef00217D4C rva005C39C4(int button);
};

int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

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
		virtual void rva005D2449();

	private:
		CommandUIImpl *m_owner; // +0x08
		int m_slot; // +0x0C
	};

	void Update();
	void OnSubMenuLoaded(const char *path);
	void OnToggleFlashLoaded(const char *path);

private:
	struct ButtonSlot
	{
		void *m_button; // +0x00
		Rva00575674 m_subMenu; // +0x04
		Rva00528FE6 m_toggleFlash; // +0x08
		Rva002BED91 m_settings; // +0x0C
		TreeHintRef00217D4C m_help; // +0x10
		unsigned long m_flashStart; // +0x14
		unsigned long m_flashDuration; // +0x18

	};

	char m_pad00[4];
	void *m_movie; // +0x04
	AsciiString m_name; // +0x08
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

void StrategicHUD::CommandUIImpl::ButtonSubMenu::rva005D2449()
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
	char m_data[8];
};

void StrategicHUD::CommandUIImpl::Update()
{
	for (int i = 0; i < 6; ++i)
	{
		ButtonSlot &slot = m_slots[i];
		if (slot.m_button)
		{
			if (slot.m_settings.m_ptr)
			{
				slot.m_help = ((Rva005C39C4 *)slot.m_settings.m_ptr)->rva005C39C4((int)slot.m_button);
				slot.m_settings.clear();
			}
			if (slot.m_help.m_ptr)
				slot.m_help.m_ptr->vslot1();
		}
		if (slot.m_subMenu.get())
			((ButtonSubMenu *)slot.m_subMenu.get())->rva005C3E81();
		if (slot.m_flashDuration && timeGetTime() - slot.m_flashStart >= slot.m_flashDuration)
		{
			Rva00525338Fire(g_bfmeAptWindowManager, m_movie, m_name.str(), "SetFlashEffectState", &i, (void *)"_hide");
			slot.m_flashDuration = 0;
		}
	}
}

void StrategicHUD::CommandUIImpl::OnSubMenuLoaded(const char *path)
{
	AsciiString name;
	int slot;
	if (!Rva005D2505Get(path, &slot) || !Rva004128F0GetParam(path, "name", name))
		return;
	ButtonSlot &button = m_slots[slot];
	if (*(void **)&button.m_subMenu)
		return;
	button.m_subMenu.rva00575674((Object *)new ButtonSubMenu(this, slot, Rva004128BBGetLevel(name.str()), AsciiString(Rva00412845AfterLevel(name.str()))));
}

void StrategicHUD::CommandUIImpl::OnToggleFlashLoaded(const char *path)
{
	AsciiString name;
	ButtonSlot *button;
	{
		int slot;
		if (!Rva005D2505Get(path, &slot))
			return;
		if (!Rva004128F0GetParam(path, "name", name))
			return;
		button = &m_slots[slot];
	}
	if (*(void **)&button->m_toggleFlash)
		return;
	button->m_toggleFlash.rva00528FE6((CameraMarker *)new Rva005C3932(Rva004128BBGetLevel(name.str()), AsciiString(Rva00412845AfterLevel(name.str()))));
}
