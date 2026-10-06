// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00578AC1@Rva00578AC1@@QAEXPAX@Z, retail 0x00578AC1, 24 bytes.
// Clears byte at +0x54 then broadcasts callback 0x005CB265 with arg this+4 over list at +8 via forEach 0x00578A60.
// Evidence: packet disassembly, prev forEach row, slot-3 update dispatch thunk, sibling 0x00578B4C pattern, caller 0x00578B7F.
//
// The class is a War of the Ring in-game UI whose constructor (unrowed
// 0x00578D22, vftable 0x00C6EB08) binds its Apt callbacks as member pointers
// under "<movie>_On..." names: the movie name it is given plus a fixed
// suffix. The bodies below carry the suffix as their method name; the
// options and objectives buttons are the +0x04/+0x18 subobjects whose
// listener lists sit at +0x08/+0x1C. The class name is unknown.
#include "ascii_string.h"

class Rva00578A60Listener
{
public:
	virtual void notify(void *);
};

class Rva00578A60List
{
public:
	void forEach(void (Rva00578A60Listener::*notify)(void *), void *arg);
private:
	Rva00578A60Listener **m_begin;
	Rva00578A60Listener **m_end;
	Rva00578A60Listener **m_capacity;
	unsigned int m_index;
};

class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual ~ProcessAnimateWindowSlideFromBottomTimed();
	virtual void initAnimateWindow(AnimateWindow *);
	virtual void initReverseAnimateWindow(AnimateWindow *, unsigned int);
	virtual bool updateAnimateWindow(AnimateWindow *);
	virtual bool reverseAnimateWindow(AnimateWindow *);
};

// The Apt window manager's +0x318 mode (0: open, 2: close).
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva00578A7EAptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

// BfmePathLeafAfterMarker.cpp's path helpers.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// The four sub-movie objects, each built from the loaded movie's level and
// path by an unrowed constructor pinned by address. Sizes come from the
// operator new calls.
class Rva005D25F2
{
public:
	Rva005D25F2(int level, const AsciiString &path);

	unsigned char m_pad[0xC4];
};

class Rva005D32D4
{
public:
	Rva005D32D4(int level, const AsciiString &path);

	unsigned char m_pad[0x4];
};

class Rva005D3731
{
public:
	Rva005D3731(int level, const AsciiString &path);

	unsigned char m_pad[0x20];
};

class Rva005D3C2B
{
public:
	Rva005D3C2B(int level, const AsciiString &path);
	// Unrowed 0x005D3CA6 (hands it the selection), pinned by address.
	void rva005D3CA6(void *selection);

	unsigned char m_pad[0x34];
};

// The owning pointers at +0x44..+0x50, viewed through their rowed resets
// and clears.
class Rva0057866D
{
public:
	void rva0057866D(Rva005D25F2 *p);

	Rva005D25F2 *m_ptr;
};

class Rva00578690
{
public:
	void rva00578690();
};

class Rva005786AA
{
public:
	void rva005786AA(Rva005D32D4 *p);

	Rva005D32D4 *m_ptr;
};

class Rva005786CD
{
public:
	void clear();
};

class Rva00578701
{
public:
	void reset(Rva005D3731 *p);

	Rva005D3731 *m_ptr;
};

class Rva005786E7
{
public:
	void rva005786E7();
};

class Rva0057873E
{
public:
	void rva0057873E(Rva005D3C2B *p);

	Rva005D3C2B *m_ptr;
};

class Rva00578724
{
public:
	void clear();
};

class Rva00578AC1
{
public:
	void rva00578AC1(void *arg);
	void rva00578B4C(void *arg);

	void OnCommandUILoaded(const char *name);
	void OnCommandUIUnloaded(const char *name);
	void OnRegionStatsTrayLoaded(const char *name);
	void OnRegionStatsTrayUnloaded(const char *name);
	void OnRegionUILoaded(const char *name);
	void OnRegionUIUnloaded(const char *name);
	void OnSelectionUILoaded(const char *name);
	void OnSelectionUIUnloaded(const char *name);
	void OnOptionsButtonClicked(const char *unused);
	void OnOptionsButtonRollOver(const char *unused);
	void OnObjectivesButtonClicked(const char *unused);
	void OnObjectivesButtonRollOut(const char *unused);

	void rva005785A2(void *selection);

private:
	int m_00;
	int m_04;
	Rva00578A60List m_list08;
	int m_18;
	Rva00578A60List m_list1C;
	char m_pad2C[0x40 - 0x2C];
	void *m_selection; // +0x40
	Rva0057866D m_commandUI; // +0x44
	Rva005786AA m_regionStatsTray; // +0x48
	Rva00578701 m_regionUI; // +0x4C
	Rva0057873E m_selectionUI; // +0x50
	bool m_flag54;
	char m_pad55;
	bool m_flag56;
};

void Rva00578AC1::rva00578AC1(void *unused)
{
	(void)unused;
	m_flag54 = false;
	m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), &m_04);
}

// ?rva00578B4C@Rva00578AC1@@QAEXPAX@Z, retail 0x00578B4C, 24 bytes.
// Sets byte at +0x56 then broadcasts callback 0x005CB26A with arg this+0x18 over list at +0x1C via forEach 0x00578A60.
// Evidence: packet disassembly, sibling 0x00578AC1 pattern, target slot-4 dispatch thunk, caller 0x00578BD4.
void Rva00578AC1::rva00578B4C(void *unused)
{
	(void)unused;
	m_flag56 = true;
	m_list1C.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), &m_18);
}

// Retail 0x005785A2, 25 bytes. Name unknown. Keeps the selection and hands
// it to the selection UI.
void Rva00578AC1::rva005785A2(void *selection)
{
	if (selection != m_selection)
	{
		m_selection = selection;
		if (m_selectionUI.m_ptr)
			m_selectionUI.m_ptr->rva005D3CA6(selection);
	}
}

// Retail 0x00578761, 151 bytes: bound as "<movie>_OnCommandUILoaded".
void Rva00578AC1::OnCommandUILoaded(const char *name)
{
	if (m_commandUI.m_ptr == 0)
		m_commandUI.rva0057866D(new Rva005D25F2(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x005787F8, 11 bytes: bound as "<movie>_OnCommandUIUnloaded".
void Rva00578AC1::OnCommandUIUnloaded(const char *name)
{
	((Rva00578690 *)&m_commandUI)->rva00578690();
}

// Retail 0x00578803, 148 bytes: bound as "<movie>_OnRegionStatsTrayLoaded".
void Rva00578AC1::OnRegionStatsTrayLoaded(const char *name)
{
	if (m_regionStatsTray.m_ptr == 0)
		m_regionStatsTray.rva005786AA(new Rva005D32D4(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x00578897, 11 bytes: bound as
// "<movie>_OnRegionStatsTrayUnloaded".
void Rva00578AC1::OnRegionStatsTrayUnloaded(const char *name)
{
	((Rva005786CD *)&m_regionStatsTray)->clear();
}

// Retail 0x005788A2, 148 bytes: bound as "<movie>_OnRegionUILoaded".
void Rva00578AC1::OnRegionUILoaded(const char *name)
{
	if (m_regionUI.m_ptr == 0)
		m_regionUI.reset(new Rva005D3731(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x00578936, 11 bytes: bound as "<movie>_OnRegionUIUnloaded".
void Rva00578AC1::OnRegionUIUnloaded(const char *name)
{
	((Rva005786E7 *)&m_regionUI)->rva005786E7();
}

// Retail 0x00578941, 167 bytes: bound as "<movie>_OnSelectionUILoaded";
// also hands the new selection UI the current selection.
void Rva00578AC1::OnSelectionUILoaded(const char *name)
{
	if (m_selectionUI.m_ptr == 0)
	{
		m_selectionUI.rva0057873E(new Rva005D3C2B(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		if (m_selection)
			m_selectionUI.m_ptr->rva005D3CA6(m_selection);
	}
}

// Retail 0x005789E8, 11 bytes: bound as "<movie>_OnSelectionUIUnloaded".
void Rva00578AC1::OnSelectionUIUnloaded(const char *name)
{
	((Rva00578724 *)&m_selectionUI)->clear();
}

// Retail 0x00578A7E, 67 bytes: bound as "<movie>_OnOptionsButtonClicked";
// starts the options button's open (mode 0) or close (mode 2) animation.
void Rva00578AC1::OnOptionsButtonClicked(const char *unused)
{
	int mode = ((Rva00578A7EAptMode *)TheRva00222A8BTarget)->m_mode;
	if (mode == 0)
		m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), this ? &m_04 : 0);
	else if (mode == 2)
		m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this ? &m_04 : 0);
}

// Retail 0x00578AD9, 24 bytes: bound as "<movie>_OnOptionsButtonRollOver"
// (rva00578AC1 is its "_OnOptionsButtonRollOut").
void Rva00578AC1::OnOptionsButtonRollOver(const char *unused)
{
	m_flag54 = true;
	m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), &m_04);
}

// Retail 0x00578AF1, 67 bytes: bound as "<movie>_OnObjectivesButtonClicked".
void Rva00578AC1::OnObjectivesButtonClicked(const char *unused)
{
	int mode = ((Rva00578A7EAptMode *)TheRva00222A8BTarget)->m_mode;
	if (mode == 0)
		m_list1C.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), this ? &m_18 : 0);
	else if (mode == 2)
		m_list1C.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this ? &m_18 : 0);
}

// Retail 0x00578B34, 24 bytes: bound as "<movie>_OnObjectivesButtonRollOut"
// (rva00578B4C is its "_OnObjectivesButtonRollOver").
void Rva00578AC1::OnObjectivesButtonRollOut(const char *unused)
{
	m_flag56 = false;
	m_list1C.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), &m_18);
}

// RVA 0x005CB265 is the 5-byte slot-3 dispatch (jmp [vptr+0x0C]);
// taking updateAnimateWindow emits ??_9@$BM@AE rather than slot-0 BA.
// The interface order comes from the reference ProcessAnimateWindow.h and
// the target BottomTimed ctor-installed table at VA 0x00C7481C.
// The adjacent RVA 0x005CB26A dispatches slot 4 (jmp [vptr+0x10]);
// taking reverseAnimateWindow emits its real compiler thunk as well,
// replacing the undefined free-function placeholder and union bit-pun.
// 0x005CB260 and 0x005CC208 are the slot-1 and slot-2 dispatches the
// Clicked handlers take.
