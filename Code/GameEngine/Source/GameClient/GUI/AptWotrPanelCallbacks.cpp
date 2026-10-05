// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Apt callbacks of two War of the Ring in-game panels, bound as member
// pointers under "<movie>_On..." names (the movie name each constructor is
// given plus a fixed suffix) by their unrowed constructors 0x0057B5AA and
// 0x0057BD79; that binding is their only reference. The methods carry the
// suffix as their name; the class names are unknown, so each class keeps
// its constructor's address. Both keep an open state (1 opening, 2 open,
// 3 closing, 0 closed) and call their rowed open and close bodies, which
// the ledger names after their own addresses.
#include "ascii_string.h"

// BfmePathLeafAfterMarker.cpp's path helpers.
const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

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

class Rva0057BC45Listener
{
public:
	virtual void notify(void *);
};

class Rva0057BC45List
{
public:
	void forEach(void (Rva0057BC45Listener::*notify)(void *), void *arg);

private:
	Rva0057BC45Listener **m_begin;
	Rva0057BC45Listener **m_end;
	Rva0057BC45Listener **m_capacity;
	unsigned int m_index;
};

// ---- the panel built by 0x0057B5AA

// The scroll bar holder at +0x28 (Rva000AD6F4's clear).
class Rva000AD6F4
{
public:
	void clear();

	void *m_ptr;
};

// The rowed expand and collapse bodies.
class Rva0057A8F9
{
public:
	void rva0057A8F9();
};

class Rva0057A92D
{
public:
	void rva0057A92D();
};

class Rva0057B5AA
{
public:
	void OnClosed(const char *unused);
	void OnOpen(const char *unused);
	void OnScrollBarUnloaded(const char *unused);
	void OnExpandButtonClicked(const char *unused);

private:
	unsigned char m_pad00[0x14];
	int m_state; // +0x14
	unsigned char m_pad18[0x28 - 0x18];
	Rva000AD6F4 m_scrollBar; // +0x28
};

// Retail 0x0057A3D7, 13 bytes: bound as "<movie>_OnClosed" (0x0057B7E5).
void Rva0057B5AA::OnClosed(const char *unused)
{
	if (m_state == 3)
		m_state = 0;
}

// Retail 0x0057A3E4, 16 bytes: bound as "<movie>_OnOpen" (0x0057B774).
void Rva0057B5AA::OnOpen(const char *unused)
{
	if (m_state == 1)
		m_state = 2;
}

// Retail 0x0057A4DC, 11 bytes: bound as "<movie>_OnScrollBarUnloaded"
// (0x0057B703).
void Rva0057B5AA::OnScrollBarUnloaded(const char *unused)
{
	m_scrollBar.clear();
}

// Retail 0x0057AC0C, 27 bytes: bound as "<movie>_OnExpandButtonClicked"
// (0x0057B859): collapses an open panel, expands a closed one.
void Rva0057B5AA::OnExpandButtonClicked(const char *unused)
{
	int state = m_state;
	if (state == 2)
		((Rva0057A8F9 *)this)->rva0057A8F9();
	else if (state == 0)
		((Rva0057A92D *)this)->rva0057A92D();
}

// ---- the panel built by 0x0057BD79

// The panel frame movie, built from the loaded movie's level and path by
// the unrowed constructor 0x005D4FBA (pinned by address); the owning
// pointer at +0x34 is viewed through its rowed reset and clear.
class Rva005D4FFC
{
public:
	Rva005D4FFC(int level, const AsciiString &path);

	unsigned char m_pad[0x4];
};

class Rva0057B993
{
public:
	void reset(Rva005D4FFC *p);

	Rva005D4FFC *m_ptr;
};

class Rva0057B9B6
{
public:
	void clear();
};

// The rowed open and close bodies.
class Rva0057BA90
{
public:
	void rva0057BA90();
};

class Rva0057BAC4
{
public:
	void rva0057BAC4();
};

class Rva0057BD79
{
public:
	void OnPanelFrameLoaded(const char *name);
	void OnPanelFrameUnloaded(const char *name);
	void OnToggleButtonClicked(const char *unused);
	void OnClosed(const char *unused);
	void OnOpened(const char *unused);

private:
	unsigned char m_pad00[0x04];
	Rva0057BC45List m_listeners; // +0x04
	unsigned char m_pad14[0x28 - 0x14];
	int m_state; // +0x28
	unsigned char m_pad2c[0x34 - 0x2C];
	Rva0057B993 m_panelFrame; // +0x34
};

// Retail 0x0057B9F1, 148 bytes: bound as "<movie>_OnPanelFrameLoaded"
// (0x0057BEE4).
void Rva0057BD79::OnPanelFrameLoaded(const char *name)
{
	if (m_panelFrame.m_ptr == 0)
		m_panelFrame.reset(new Rva005D4FFC(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0057BA85, 11 bytes: bound as "<movie>_OnPanelFrameUnloaded"
// (0x0057BF3A).
void Rva0057BD79::OnPanelFrameUnloaded(const char *name)
{
	((Rva0057B9B6 *)&m_panelFrame)->clear();
}

// Retail 0x0057BC2A, 27 bytes: bound as "<movie>_OnToggleButtonClicked"
// (0x0057BFC9): opens a closed panel, closes an open one.
void Rva0057BD79::OnToggleButtonClicked(const char *unused)
{
	int state = m_state;
	if (state == 0)
		((Rva0057BA90 *)this)->rva0057BA90();
	else if (state == 2)
		((Rva0057BAC4 *)this)->rva0057BAC4();
}

// Retail 0x0057BC9E, 27 bytes: bound as "<movie>_OnClosed" (0x0057BE19);
// finishes closing and tells the listeners (animation slot 2).
void Rva0057BD79::OnClosed(const char *unused)
{
	if (m_state == 3)
	{
		m_state = 0;
		m_listeners.forEach(reinterpret_cast<void (Rva0057BC45Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this);
	}
}

// Retail 0x0057BCB9, 30 bytes: bound as "<movie>_OnOpened" (0x0057BE5B);
// finishes opening and tells the listeners (animation slot 1).
void Rva0057BD79::OnOpened(const char *unused)
{
	if (m_state == 1)
	{
		m_state = 2;
		m_listeners.forEach(reinterpret_cast<void (Rva0057BC45Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), this);
	}
}
