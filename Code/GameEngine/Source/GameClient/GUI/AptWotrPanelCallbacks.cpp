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

// The scroll bar's enable forwarder to its Impl (0x005D49CD, pinned by
// address), as Rva005D498BVisible.cpp views the scroll bar.
class AptScrollBar
{
public:
	void rva005D49CD(bool enabled);
};

// The empty update folded onto the shared empty body 0x000B3FD0.
class Rva000B3FD0Nop
{
public:
	void noop();
};

// The checklist's items: an STLport list of pointers (sentinel node at
// +0x30, data at node +8), each item updating its +8 member through the
// unrowed 0x005D4769 (pinned by address).
class Rva005D4769
{
public:
	void rva005D4769();
};

struct Rva0057B499Item
{
	unsigned char m_pad00[0x08];
	Rva005D4769 m_08;
};

struct Rva0057B499Node
{
	Rva0057B499Node *m_next;
	Rva0057B499Node *m_prev;
	Rva0057B499Item *m_item;
};

// The Apt window manager's virtual at +0x40 answers a scale pair, as its
// +0x3C one does for Rva0057A24AFlt.cpp.
struct Rva00222A8BScale
{
	float x;
	float y;
};

class Rva00222A8BTarget
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual Rva00222A8BScale *slot3C();
	virtual Rva00222A8BScale *slot40();
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

static __forceinline const char *Rva0057AC8FGetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

// The checklist's three vftables, stored by its constructor 0x0057B5AA:
// 0x00C6F118 at +0, 0x00C6F0FC at +4 and, at +8, the scroll bar listener's
// 0x00C6F0F4 (base 0x00C6EE20: the empty one-argument 0x0047A69C and the
// (int, float) position slot the bar's listener walk 0x005D4A66 calls).
class Rva0057AF2EBase
{
public:
	virtual void slot00();
};

class Rva0057A83CBase
{
public:
	virtual void slot00();
};

class Rva0057AC8FScrollListener
{
public:
	virtual void slot00(int);
	virtual void rva0057AC8F(int unused, float position);

	void listenTo(Rva005D4DA9 *scrollBar)
	{
		scrollBar->m_listeners.append((Rva002BA8F1Listener *)this);
	}
};

// One-word, nontrivially copied iterator ABI witnessed at native57AD4D.
// It is a node pointer, not the integer index the older declaration used.
struct ChecklistSelectNode;
struct ChecklistIteratorView {
 ChecklistSelectNode *node;
 ChecklistIteratorView(const ChecklistIteratorView& other):node(other.node){}
};

namespace StrategicHUD {
class ChecklistUIImpl;
}

class StrategicHUD::ChecklistUIImpl : public Rva0057AF2EBase, public Rva0057A83CBase, public Rva0057AC8FScrollListener
{
public:
 void SetCurrentItem(ChecklistIteratorView);
	void OnClosed(const char *unused);
	void OnOpen(const char *unused);
	void OnScrollBarUnloaded(const char *unused);
	void OnExpandButtonClicked(const char *unused);
	void OnScrollBarLoaded(const char *name);
	void rva0057B499();

	// Unrowed 0x0057B16D (170 bytes) and 0x0057B217, pinned by address.
	void rva0057B16D();
	void rva0057B217();
	// Rowed in Rva0057A961Apt.cpp.
	void SetExpandButtonEnabled(bool enabled);
	// The item list's height (unrowed 0x0057ABD0, pinned by address).
	float rva0057ABD0() const;
	virtual void rva0057AC8F(int unused, float position);

private:
	void *m_level; // +0x0C, the movie's Apt level
	AsciiString m_path; // +0x10, the movie's path
	int m_state; // +0x14
	unsigned char m_pad18[0x26 - 0x18];
	bool m_26; // +0x26: expand once closed
	unsigned char m_pad27;
	Rva000AD6F4 m_scrollBar; // +0x28
	unsigned char m_pad2c[0x30 - 0x2C];
	Rva0057B499Node *m_items; // +0x30
	unsigned char m_pad34[0x38 - 0x34];
	bool m_38; // +0x38: rva0057B217 pending
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
		listenTo((Rva005D4DA9 *)scrollBar->m_ptr);
		rva0057B16D();
	}
}

// Retail 0x0057B499, 96 bytes. Name unknown. The checklist's per-frame
// update, reached from the HUD's (0x0042D577) on its +0x30 slot: enables the
// expand button, runs the pending 0x0057B217, enables and updates the scroll
// bar, expands a closed panel that asked to, and updates every item.
void StrategicHUD::ChecklistUIImpl::rva0057B499()
{
	SetExpandButtonEnabled(true);
	if (m_38)
		rva0057B217();
	if (m_scrollBar.m_ptr != 0)
	{
		((AptScrollBar *)m_scrollBar.m_ptr)->rva005D49CD(true);
		((Rva000B3FD0Nop *)m_scrollBar.m_ptr)->noop();
	}
	if (m_26 && m_state == 0)
	{
		((Rva0057A92D *)this)->rva0057A92D();
		m_26 = false;
	}
	Rva0057B499Node *end = m_items;
	for (Rva0057B499Node *node = end->m_next; node != end; node = node->m_next)
		node->m_item->m_08.rva005D4769();
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

// Retail 0x0057AC8F, 92 bytes: the scroll bar listener's position slot
// (+8 vftable 0x00C6F0F4 slot 1): scrolls the item list to the position's
// share of its height (0x0057ABD0), scaled by the window manager's +0x40
// pair, through the movie's "SetItemListY".
void StrategicHUD::ChecklistUIImpl::rva0057AC8F(int unused, float position)
{
	float height = rva0057ABD0();
	position = (0.0f - height * position) * TheRva00222A8BTarget->slot40()->y;
	Rva00527925Fire(TheRva00222A8BTarget, m_level, Rva0057AC8FGetStr(m_path), "SetItemListY", &position);
}

// ---- the panel built by 0x0057BD79

// The panel frame movie, built from the loaded movie's level and path by
// the unrowed constructor 0x005D4FBA (pinned by address); the owning
// pointer at +0x34 is viewed through its rowed reset and clear.
// The pending hint at +0x30: a reference to the shared hint object, cleared
// through the rowed 0x002BED91.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C() : m_ptr(0) {}
	// ??1TreeHintRef00217D4C@@QAE@XZ present-unmatched
	__forceinline ~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

	void *m_ptr;
};

class Rva002BED91
{
public:
	void clear();
};

class Rva005D4FFC
{
public:
	Rva005D4FFC(int level, const AsciiString &path);
	// Unrowed 0x005D508E (hands its Impl the hint), pinned by address.
	void rva005D508E(const TreeHintRef00217D4C &hint);

	unsigned char m_pad[0x4];
};

// The panel frame's rowed per-frame update.
class Rva005D4E84
{
public:
	void rva005D4E84();
};

class Rva0057B9B6
{
public:
	void clear();
};

class Rva0057B993
{
public:
	Rva0057B993() { m_ptr = 0; }
	void reset(Rva005D4FFC *p);
	// ??1Rva0057B993@@QAE@XZ present-unmatched
	__forceinline ~Rva0057B993() { ((Rva0057B9B6 *)this)->clear(); }

	Rva005D4FFC *m_ptr;
};

// Command-map binding (the shape 0x0057BC63's rowed holder takes): the
// target, an unused word, then the member pointer in its two-word
// (multiple-inheritance) form.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	template <class T> FunctorBinding(T *target, void (T::*method)(const char *))
		: m_target(reinterpret_cast<FunctorTarget *>(target)), m_method(reinterpret_cast<FunctorMethod>(method)) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding); // 0x0057BC63

	void *m_ptr;
};

class AptCommandMap;

// The reference-counted command map AptCommandMapAdder::AddCommandMap
// takes by value, built in the argument slot from a binding.
template <class T> class AptRef
{
public:
	AptRef(const FunctorBinding &binding) : m_holder(binding) {}
	AptRef(const AptRef &that);
	~AptRef()
	{
		if (m_holder.m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_holder.m_ptr);
	}

private:
	Rva0057BC63FunctorHolder m_holder;
};

// The 12-byte command-map name list at +0x1C: ctor 0x001F81BF (ICF fold,
// pinned), AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapBinding(const AsciiString &name, FunctorBinding binding)
	{
		AddCommandMap(name, binding);
	}

private:
	char m_pad[0xC];
};

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

// The listener-list interface (vtable 0x00C6F248, nine pure slots and no
// destructor slot), then the listener list at +4 as a second base: the
// callbacks are bound as two-word (multiple-inheritance) member pointers.
// The ledger rows its constructor (0x0057BCD7, which installs that vtable)
// and its destructor (0x0057BCEC, which frees the list storage) under two
// address names; the destructor is reached through a cast, as elsewhere in
// this unit.
class Rva0057BCEC
{
public:
	~Rva0057BCEC();
};

class __declspec(novtable) Rva0057BCD7Base0
{
public:
	virtual void slot00() = 0;
};

class __declspec(novtable) Rva0057BCD7 : public Rva0057BCD7Base0, public Rva0057BC45List
{
public:
	Rva0057BCD7();
	__forceinline ~Rva0057BCD7() { ((Rva0057BCEC *)this)->~Rva0057BCEC(); }
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
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

class StrategicHUD::SelectionDetailsUIImpl : public Rva0057BCD7
{
public:
	SelectionDetailsUIImpl(int level, const AsciiString &name);
	~SelectionDetailsUIImpl();
	void OnPanelFrameLoaded(const char *name);
	void OnPanelFrameUnloaded(const char *name);
	void OnToggleButtonClicked(const char *unused);
	void OnClosed(const char *unused);
	void OnOpened(const char *unused);
	void rva0057BBBB();

	// Rowed in Rva0057BAF8Toggle.cpp.
	void SetToggleButtonEnabled(bool enabled);

private:
	int m_level; // +0x14
	AsciiString m_name; // +0x18
	AptCommandMapAdder m_commandMaps; // +0x1C
	int m_state; // +0x28
	bool m_2C; // +0x2C: the toggle button may be used
	bool m_2D;
	unsigned char m_pad2e[0x30 - 0x2E];
	TreeHintRef00217D4C m_hint; // +0x30
	Rva0057B993 m_panelFrame; // +0x34
};

// Retail 0x0057BD79, 706 bytes: the constructor (the HUD's
// OnSelectionDetailsLoaded news it). After the rowed interface ctor it
// stores the level and copies the name, zeroes the state, flags, hint and
// panel frame, and binds five <_level%u.><name>_On... callbacks (retail
// strings) to the handlers below through AptCommandMapAdder::AddCommandMap,
// each reference built in place by the rowed functor holder 0x0057BC63.
StrategicHUD::SelectionDetailsUIImpl::SelectionDetailsUIImpl(int level, const AsciiString &name)
	: m_level(level), m_name(name), m_state(0), m_2C(false), m_2D(false)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnClosed", FunctorBinding(this, &SelectionDetailsUIImpl::OnClosed));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnOpened", FunctorBinding(this, &SelectionDetailsUIImpl::OnOpened));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnPanelFrameLoaded", FunctorBinding(this, &SelectionDetailsUIImpl::OnPanelFrameLoaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnPanelFrameUnloaded", FunctorBinding(this, &SelectionDetailsUIImpl::OnPanelFrameUnloaded));
	m_commandMaps.AddCommandMapBinding(prefix + m_name + "_OnToggleButtonClicked", FunctorBinding(this, &SelectionDetailsUIImpl::OnToggleButtonClicked));
}

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
		forEach(reinterpret_cast<void (Rva0057BC45Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initReverseAnimateWindow), this);
	}
}

// Retail 0x0057BCB9, 30 bytes: bound as "<movie>_OnOpened" (0x0057BE5B);
// finishes opening and tells the listeners (animation slot 1).
void StrategicHUD::SelectionDetailsUIImpl::OnOpened(const char *unused)
{
	if (m_state == 1)
	{
		m_state = 2;
		forEach(reinterpret_cast<void (Rva0057BC45Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::initAnimateWindow), this);
	}
}

// Retail 0x0057BBBB, 101 bytes. Name unknown. The selection details'
// per-frame update, reached from the HUD's (0x0042D577) on its +0x34 slot:
// without +0x2C it closes an open panel and disables the toggle button;
// it hands the panel frame the pending hint and updates the frame; then it
// enables the toggle button only when allowed and open or closed.
void StrategicHUD::SelectionDetailsUIImpl::rva0057BBBB()
{
	if (!m_2C)
	{
		if (m_state == 2)
			((Rva0057BAC4 *)this)->rva0057BAC4();
		SetToggleButtonEnabled(false);
	}
	if (m_panelFrame.m_ptr != 0)
	{
		if (m_hint.m_ptr != 0)
		{
			m_panelFrame.m_ptr->rva005D508E(m_hint);
			((Rva002BED91 *)&m_hint)->clear();
		}
		((Rva005D4E84 *)m_panelFrame.m_ptr)->rva005D4E84();
	}
	SetToggleButtonEnabled(m_2C && (m_state == 2 || m_state == 0));
}

// Retail 0x0057BD01, 120 bytes: the destructor (vtable 0x00C6F26C), run by
// the HUD's owning-pointer reset 0x0042D87D. It tells the listeners first
// (slot 0, through the shared forwarder 0x001FF3A9).
StrategicHUD::SelectionDetailsUIImpl::~SelectionDetailsUIImpl()
{
	forEach((void (Rva0057BC45Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
}

// Native57AD26..57AD6E and WB14BB520 identify Item::DoSelect.
// Keep the witnessed second owner-current load; the first snapshot supplies
// the old item while the second decides whether it is the end iterator.
struct ChecklistSelectionOwnerView {char prefix[0x30];ChecklistIteratorView end,current;};
class Rva0057AD26;
struct ChecklistSelectObserver {virtual void deselect(Rva0057AD26*);virtual void slot04();virtual void slot08();virtual void slot0c();virtual void select(Rva0057AD26*);};
struct ChecklistSelectNode {void *next,*prev;Rva0057AD26* item;};
class Rva0057AD26 {public: void rva0057AD26(); char prefix[0x48]; StrategicHUD::ChecklistUIImpl *owner;ChecklistIteratorView position;int pad50;ChecklistSelectObserver *observer;};
void Rva0057AD26::rva0057AD26()
{
 ChecklistSelectionOwnerView *state=reinterpret_cast<ChecklistSelectionOwnerView*>(owner);
 ChecklistIteratorView current=state->current;
 if(current.node==position.node) return;
 if(*reinterpret_cast<ChecklistSelectNode*volatile*>(&state->current.node)!=state->end.node) {
  Rva0057AD26 *item=reinterpret_cast<ChecklistSelectNode*>(current.node)->item;
  if(item->observer) item->observer->deselect(item);
 }
 owner->SetCurrentItem(position);
 if(observer) observer->select(this);
}
