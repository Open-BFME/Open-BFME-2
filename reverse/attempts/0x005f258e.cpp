// ?updateScrollBar@Rva005F38F5@@QAEXXZ
// partial score=0.72 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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

// The scroll bar built from the loaded movie's level and path by the
// unrowed constructor 0x005D4DA9 (pinned by address); listeners join its
// +4 list through the rowed append 0x005A0B4C. The holder sets it through
// its rowed 0x00575674.
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

namespace StrategicHUD {
class ChecklistUIImpl;
}

class StrategicHUD::ChecklistUIImpl
{
public:
	void OnClosed(const char *unused);
	void OnOpen(const char *unused);
	void OnScrollBarUnloaded(const char *unused);
	void OnExpandButtonClicked(const char *unused);
	void OnScrollBarLoaded(const char *name);

	// Unrowed 0x0057B16D (170 bytes), pinned by address.
	void rva0057B16D();

private:
	unsigned char m_pad00[0x08];
	int m_listener; // +0x08, the scroll bar listener
	unsigned char m_pad0c[0x14 - 0x0C];
	int m_state; // +0x14
	unsigned char m_pad18[0x28 - 0x18];
	Rva000AD6F4 m_scrollBar; // +0x28
};

// Retail 0x0057A3D7, 13 bytes: bound as "<movie>_OnClosed" (0x0057B7E5).
void StrategicHUD::ChecklistUIImpl::OnClosed(const char *unused)
{
	if (m_state == 3)
		m_state = 0;
}

// Retail 0x0057A3E4, 16 bytes: bound as "<movie>_OnOpen" (0x0057B774).
void StrategicHUD::ChecklistUIImpl::OnOpen(const char *unused)
{
	if (m_state == 1)
		m_state = 2;
}

// Retail 0x0057A4DC, 11 bytes: bound as "<movie>_OnScrollBarUnloaded"
// (0x0057B703).
void StrategicHUD::ChecklistUIImpl::OnScrollBarUnloaded(const char *unused)
{
	m_scrollBar.clear();
}

// Retail 0x0057B4F9, 177 bytes: bound as "<movie>_OnScrollBarLoaded"
// (0x0057B6A3): builds the scroll bar once, listens to it and refreshes.
void StrategicHUD::ChecklistUIImpl::OnScrollBarLoaded(const char *name)
{
	Rva000AD6F4 *scrollBar = &m_scrollBar;
	if (scrollBar->m_ptr == 0)
	{
		((Rva00575674 *)scrollBar)->rva00575674((Object *)new Rva005D4DA9(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		((Rva005D4DA9 *)scrollBar->m_ptr)->m_listeners.append((Rva002BA8F1Listener *)&m_listener);
		rva0057B16D();
	}
}

// Retail 0x0057AC0C, 27 bytes: bound as "<movie>_OnExpandButtonClicked"
// (0x0057B859): collapses an open panel, expands a closed one.
void StrategicHUD::ChecklistUIImpl::OnExpandButtonClicked(const char *unused)
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

namespace StrategicHUD {
class SelectionDetailsUIImpl;
}

class StrategicHUD::SelectionDetailsUIImpl
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
void StrategicHUD::SelectionDetailsUIImpl::OnPanelFrameLoaded(const char *name)
{
	if (m_panelFrame.m_ptr == 0)
		m_panelFrame.reset(new Rva005D4FFC(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
}

// Retail 0x0057BA85, 11 bytes: bound as "<movie>_OnPanelFrameUnloaded"
// (0x0057BF3A).
void StrategicHUD::SelectionDetailsUIImpl::OnPanelFrameUnloaded(const char *name)
{
	((Rva0057B9B6 *)&m_panelFrame)->clear();
}

// Retail 0x0057BC2A, 27 bytes: bound as "<movie>_OnToggleButtonClicked"
// (0x0057BFC9): opens a closed panel, closes an open one.
void StrategicHUD::SelectionDetailsUIImpl::OnToggleButtonClicked(const char *unused)
{
	int state = m_state;
	if (state == 0)
		((Rva0057BA90 *)this)->rva0057BA90();
	else if (state == 2)
		((Rva0057BAC4 *)this)->rva0057BAC4();
}

// Retail 0x0057BC9E, 27 bytes: bound as "<movie>_OnClosed" (0x0057BE19);
// finishes closing and tells the listeners (animation slot 2).
void StrategicHUD::SelectionDetailsUIImpl::OnClosed(const char *unused)
{
	if (m_state == 3)
	{
		m_state = 0;
		m_listeners.forEach(reinterpret_cast<void (Rva0057BC45Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this);
	}
}

// Retail 0x0057BCB9, 30 bytes: bound as "<movie>_OnOpened" (0x0057BE5B);
// finishes opening and tells the listeners (animation slot 1).
void StrategicHUD::SelectionDetailsUIImpl::OnOpened(const char *unused)
{
	if (m_state == 1)
	{
		m_state = 2;
		m_listeners.forEach(reinterpret_cast<void (Rva0057BC45Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), this);
	}
}

// The owner class is still unidentified. Both functions use the same
// +0x1C scroll-bar holder; the handler name is proven by its callback binding.
class AptScrollBar
{
public:
	class Impl;
};

class Rva005D49CD
{
public:
	void SetEnabled(bool enabled);
};

class Rva005D49D5
{
public:
	void SetVisible(bool visible);

private:
	unsigned char m_pad00[0x14];
	AptScrollBar::Impl *m_impl14;
};

class Rva005D4BAE
{
public:
	void rva005D4BAE(float pageSize);
};

class Rva005D4BC1
{
public:
	void rva005D4BC1(float lineSize);
};

extern const float BfmeZeroRange;
extern "C" __declspec(dllimport) double __cdecl floor(double);

class Rva005F38F5
{
public:
	void updateScrollBar();
	void OnScrollBarLoaded(const char *name);

private:
	unsigned char m_pad00[0x1C];
	Rva000AD6F4 m_scrollBar; // +0x1C
	unsigned char m_pad20[4];
	char *m_rangeBegin24;
	char *m_rangeEnd28;
	unsigned char m_pad2C[4];
	float m_extent30;
	float m_extent34;
	unsigned char m_pad38[4];
	float m_viewSize3C;
	float m_lineSize40;
};

// 0x005F258E [0x005F258E,0x005F267E), 240 bytes. The retail body sizes
// the scroll bar from the byte range at +0x24..+0x28 and the float fields
// at +0x30, +0x34, +0x3C and +0x40. The containing class name is address-
// derived; the routine's scroll-bar update role follows its rowed callees.
void Rva005F38F5::updateScrollBar()
{
	float effectiveExtent;
	if (m_rangeBegin24 != m_rangeEnd28)
	{
		float pageCountValue = (float)floor((double)m_extent30 / (double)m_viewSize3C);
		int pageCount;
		__asm {
			fld pageCountValue
			fistp pageCount
		}
		int elementCountSigned = (int)(m_rangeEnd28 - m_rangeBegin24) >> 2;
		unsigned int itemsPerPageUnsigned = ((unsigned int)elementCountSigned + (unsigned int)pageCount - 1) / (unsigned int)pageCount;
		int itemsPerPage = (int)itemsPerPageUnsigned;
		float requiredExtent = (float)itemsPerPage * m_lineSize40;
		effectiveExtent = requiredExtent;
		if (m_extent34 > effectiveExtent)
			effectiveExtent = m_extent34;
		float scale = 1.0f / effectiveExtent;
		((Rva005D4BAE *)m_scrollBar.m_ptr)->rva005D4BAE(scale * m_extent34);
		((Rva005D4BC1 *)m_scrollBar.m_ptr)->rva005D4BC1(scale * m_lineSize40);
		((Rva005D49CD *)m_scrollBar.m_ptr)->SetEnabled(true);
		((Rva005D49D5 *)m_scrollBar.m_ptr)->SetVisible(effectiveExtent > m_extent34);
	}
	else
	{
		((Rva005D4BAE *)m_scrollBar.m_ptr)->rva005D4BAE(0.0f);
		((Rva005D4BC1 *)m_scrollBar.m_ptr)->rva005D4BC1(0.0f);
		((Rva005D49CD *)m_scrollBar.m_ptr)->SetEnabled(false);
		((Rva005D49D5 *)m_scrollBar.m_ptr)->SetVisible(false);
	}
}

// Retail [0x005F38F5,0x005F39BA), 197 bytes; the function address is
// registered beside the `_OnScrollBarLoaded` string at VA 0x00C6F21C.
void Rva005F38F5::OnScrollBarLoaded(const char *name)
{
	Rva000AD6F4 *scrollBar = &m_scrollBar;
	if (scrollBar->m_ptr == 0)
	{
		((Rva00575674 *)scrollBar)->rva00575674((Object *)new Rva005D4DA9(Rva004128BBGetLevel(name), AsciiString(Rva00412845AfterLevel(name))));
		((Rva005D49D5 *)scrollBar->m_ptr)->SetVisible(false);
		if (m_viewSize3C > BfmeZeroRange)
			updateScrollBar();
		((Rva005D4DA9 *)scrollBar->m_ptr)->m_listeners.append((Rva002BA8F1Listener *)this);
	}
}
