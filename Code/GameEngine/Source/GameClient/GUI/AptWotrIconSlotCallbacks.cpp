// cl: /DNDEBUG /MD
//
// Apt callbacks of the War of the Ring icon slot widgets, bound as member
// pointers under "<movie>_On..." names (a movie name plus a fixed suffix)
// by their unrowed registrations; that binding is their only reference.
// The methods carry the suffix as their name; the class names are unknown,
// so each class view is named for the function that binds it:
//
//   0x005EF669  _OnIconSlotClicked / RollOut / RollOver
//   0x005EF92D  _OnRollOverCommandPoints / _OnRollOutCommandPoints,
//               _PlayerColor (an Apt query)
//   0x005F0CC9  _OnIconSlot* (with the Type variants), the turns-remaining
//               roll-over flag, _RenderProgress (a render callback)
//   0x005F141D  _OnRegionFortressRollOver, and 0x005F057A bound as its
//               _OnRegionFortressTypeRollOver and as "_OnRollOut" by
//               0x005FCB47 and 0x005FF675 (folded, so an address name)
//
// A click goes to the slot's listener's vslot 1 or 2 by the Apt window
// manager's +0x318 mode; roll-outs and roll-overs go to the following
// slots. The listener types are unknown and viewed by slot.

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005EEE74AptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

// A render callback's position and size: two floats each (the type is
// inferred from use).
#include "../../../../Libraries/Include/Lib/Coord2D.h"

// TheDisplay, through Rva000A4826Call.cpp's view.
class Display;
extern Display *TheDisplay;

class Rva000A4826
{
public:
	void rva000A4875(float a, float b, float c, float d, float e, int f);
};

class Rva005EEE74Listener
{
public:
	virtual void v00();
	virtual void v01(void *slot);
	virtual void v02(void *slot);
	virtual void v03(void *slot);
	virtual void v04(void *slot);
	virtual void v05(void *slot);
	virtual void v06(void *slot);
};

class Rva005F0570Target
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
};

// ---- bound by 0x005EF669

class Rva005EF669
{
public:
	void OnIconSlotClicked(const char *unused);
	void OnIconSlotRollOut(const char *unused);
	void OnIconSlotRollOver(const char *unused);

private:
	unsigned char m_pad00[0x2C];
	bool m_rolledOver; // +0x2C
	unsigned char m_pad2d[0x30 - 0x2D];
	Rva005EEE74Listener *m_listener; // +0x30
};

// Retail 0x005EEE74, 52 bytes: bound as "<movie>_OnIconSlotClicked"
// (0x005EF725).
void Rva005EF669::OnIconSlotClicked(const char *unused)
{
	if (m_listener)
	{
		int mode = ((Rva005EEE74AptMode *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->m_mode;
		if (mode == 0)
			m_listener->v01(this);
		else if (mode == 2)
			m_listener->v02(this);
	}
}

// Retail 0x005EEEA8, 22 bytes: bound as "<movie>_OnIconSlotRollOut"
// (0x005EF82D).
void Rva005EF669::OnIconSlotRollOut(const char *unused)
{
	m_rolledOver = false;
	if (m_listener)
		m_listener->v03(this);
}

// Retail 0x005EEEBE, 22 bytes: bound as "<movie>_OnIconSlotRollOver"
// (0x005EF7A8).
void Rva005EF669::OnIconSlotRollOver(const char *unused)
{
	m_rolledOver = true;
	if (m_listener)
		m_listener->v04(this);
}

// ---- bound by 0x005EF92D

class Rva005EF92D
{
public:
	void OnRollOverCommandPoints(const char *unused);
	void OnRollOutCommandPoints(const char *unused);
	void PlayerColor(int query, char *result, bool skip);

private:
	unsigned char m_pad00[0x08];
	unsigned int m_color; // +0x08
	unsigned char m_pad0c[0x3E - 0x0C];
	bool m_commandPointsRolledOver; // +0x3E
};

// Retail 0x005EEED4, 7 bytes: bound as "<movie>_OnRollOverCommandPoints"
// (0x005EF9D5).
void Rva005EF92D::OnRollOverCommandPoints(const char *unused)
{
	m_commandPointsRolledOver = true;
}

// Retail 0x005EEEDB, 7 bytes: bound as "<movie>_OnRollOutCommandPoints"
// (0x005EFA34).
void Rva005EF92D::OnRollOutCommandPoints(const char *unused)
{
	m_commandPointsRolledOver = false;
}

// Retail 0x005EEEE2, 29 bytes: bound as "<movie>_PlayerColor" (0x005EFA93),
// an Apt query answering +0x08.
void Rva005EF92D::PlayerColor(int query, char *result, bool skip)
{
	_snprintf(result, 0xFF, "%u", m_color);
}

// ---- bound by 0x005F0CC9


struct Rva005F0505Owner
{
	unsigned char m_pad00[0x04];
	void *m_level; // +0x04
	char *m_name; // +0x08: the movie name's AsciiString buffer
	int m_0c; // +0x0C

	const char *name() const { return m_name ? m_name + 8 : ""; }
};

// The icon slot state names (0x00878D64) and the Apt calls taking them.
extern const char *g_00C78D64[];
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const int &a, const char *const &b);
int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);

class Rva005F0CC9
{
public:
	virtual void DoSetState(int state);
	void DoHideProgress();
	void OnIconSlotClicked(const char *unused);
	void OnIconSlotRollOut(const char *unused);
	void OnIconSlotRollOver(const char *unused);
	void OnIconSlotTypeRollOut(const char *unused);
	void OnIconSlotTypeRollOver(const char *unused);
	void OnRollOutTurnsRemaining(const char *unused);
	void OnRollOverTurnsRemaining(const char *unused);
	void RenderProgress(const Coord2D *position, const Coord2D *size, void *unused3, void *unused4);

private:
	unsigned char m_pad04[0x0C - 0x04];
	Rva005F0505Owner *m_owner; // +0x0C
	int m_index; // +0x10
	Rva005EEE74Listener *m_listener; // +0x14
	int m_state; // +0x18
	unsigned char m_pad1C[0x24 - 0x1C];
	int m_total; // +0x24
	int m_remaining; // +0x28
	bool m_showProgress; // +0x2C
	bool m_turnsRolledOver; // +0x2D
};

// Retail 0x005F0473, 52 bytes: bound as "<movie>_OnIconSlotClicked"
// (0x005F0D7A).
void Rva005F0CC9::OnIconSlotClicked(const char *unused)
{
	if (m_listener)
	{
		int mode = ((Rva005EEE74AptMode *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->m_mode;
		if (mode == 0)
			m_listener->v01(this);
		else if (mode == 2)
			m_listener->v02(this);
	}
}

// Retail 0x005F04A7, 20 bytes: bound as "<movie>_OnIconSlotRollOut"
// (0x005F0E8B).
void Rva005F0CC9::OnIconSlotRollOut(const char *unused)
{
	if (m_listener)
		m_listener->v03(this);
}

// Retail 0x005F04BB, 20 bytes: bound as "<movie>_OnIconSlotRollOver"
// (0x005F0E03).
void Rva005F0CC9::OnIconSlotRollOver(const char *unused)
{
	if (m_listener)
		m_listener->v04(this);
}

// Retail 0x005F04CF, 20 bytes: bound as "<movie>_OnIconSlotTypeRollOut"
// (0x005F0F7D).
void Rva005F0CC9::OnIconSlotTypeRollOut(const char *unused)
{
	if (m_listener)
		m_listener->v05(this);
}

// Retail 0x005F04E3, 20 bytes: bound as "<movie>_OnIconSlotTypeRollOver"
// (0x005F0F16).
void Rva005F0CC9::OnIconSlotTypeRollOver(const char *unused)
{
	if (m_listener)
		m_listener->v06(this);
}

// Retail 0x005F04F7, 7 bytes: bound as "<movie>_OnRollOutTurnsRemaining"
// (0x005F10B4).
void Rva005F0CC9::OnRollOutTurnsRemaining(const char *unused)
{
	m_turnsRolledOver = false;
}

// Retail 0x005F04FE, 7 bytes: bound as "<movie>_OnRollOverTurnsRemaining"
// (0x005F1029).
void Rva005F0CC9::OnRollOverTurnsRemaining(const char *unused)
{
	m_turnsRolledOver = true;
}

// Retail 0x005F0505, 107 bytes: bound as "<movie>_RenderProgress"
// (0x005F1139); draws the elapsed share (in percent) over the slot's
// rectangle through TheDisplay.
void Rva005F0CC9::RenderProgress(const Coord2D *position, const Coord2D *size, void *unused3, void *unused4)
{
	if (!m_showProgress)
		return;
	float progress;
	if (m_total)
		progress = (float)(m_total - m_remaining) / (float)m_total;
	else
		progress = 0.0f;
	((Rva000A4826 *)TheDisplay)->rva000A4875(position->x, position->y, size->x, size->y, progress * 100.0f, m_owner->m_0c);
}

// ---- bound by 0x005F141D

class Rva005F141D
{
public:
	void OnRegionFortressRollOver(const char *unused);
	// Also bound as "_OnRollOut" by 0x005FCB47 and 0x005FF675, so it
	// keeps its address.
	void rva005F057A(const char *unused);

private:
	Rva005F0570Target *m_target; // +0x00
};

// Retail 0x005F0570, 10 bytes: bound as "<movie>_OnRegionFortressRollOver"
// (0x005F158C).
void Rva005F141D::OnRegionFortressRollOver(const char *unused)
{
	m_target->v01();
}

// Retail 0x005F057A, 10 bytes: bound as
// "<movie>_OnRegionFortressTypeRollOver" (0x005F1648) and as "_OnRollOut"
// (0x005FCD2E, 0x005FF7DD).
void Rva005F141D::rva005F057A(const char *unused)
{
	m_target->v03();
}

// Retail 0x005F0A50 (WorldBuilder RegionDetailsStructuresMovieClip::Impl::
// IconSlot::DoSetState, vtable match): "SetIconSlotState" with the slot index
// and the state's name.
void Rva005F0CC9::DoSetState(int state)
{
	if (state == m_state)
		return;
	Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_owner->m_level, m_owner->name(), "SetIconSlotState", m_index, g_00C78D64[state]);
	m_state = state;
}

// Retail 0x005F0BF2 (WorldBuilder IconSlot::DoHideProgress): hides the
// progress overlay once shown.
void Rva005F0CC9::DoHideProgress()
{
	if (!m_showProgress)
		return;
	Rva00525338Fire(g_bfmeAptWindowManager, m_owner->m_level, m_owner->name(), "SetIconSlotProgressState", &m_index, (void *)"_hide");
	m_showProgress = false;
	m_turnsRolledOver = false;
}
