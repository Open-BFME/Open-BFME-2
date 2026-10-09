// ?rva005CCF47@Impl@Checklist@StrategicInGameUI@@QAE?AUChecklistItemRef@3@PAVChecklistItem@3@@Z
// partial score=0.97 date=2026-10-09
// ?rva005CCF47@Impl@Checklist@StrategicInGameUI@@QAE?AUChecklistItemRef@3@PAVChecklistItem@3@@Z
// partial score=0.97 date=2026-10-09 (home unit at fc76501ed4 plus this body)
// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::Checklist (WorldBuilder StrategicInGameUIChecklist.cpp).
// Target facts for AddItem 0x005CD0C2 (thiscall, ret 4): hands the new
// item's counted reference and the item's own implementation (+0x08) to
// the checklist's implementation (+0x04), Impl::AddItem 0x005CD049
// (WorldBuilder name, pinned). The reference type is viewed by layout.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class RefCountClass
{
public:
	void Release_Ref();
};

// Native 5CCC74 copies a counted reference and an implementation pointer.
// WB inlines the equivalent pair construction; its original pair type is
// unknown, so this view keeps the retail constructor's address.
class Rva005CCC74Record;
class Rva005CD018Obj;
namespace _STL {
template<class T> class allocator;
template<class T> struct _Nonconst_traits;
template<class T, class Traits> struct _List_iterator {
	void *m_node;
	explicit _List_iterator(void *node) : m_node(node) {}
	_List_iterator(const _List_iterator &other) : m_node(other.m_node) {}
};
template<class T, class A> class list {
public:
	void push_back(const T &);
	void pop_back();
	_List_iterator<T, _Nonconst_traits<T> > erase(_List_iterator<T, _Nonconst_traits<T> >);
};
}
typedef _STL::list<Rva005CD018Obj *,
	_STL::allocator<Rva005CD018Obj *> > Rva005CD018ListView;

class ChecklistInlineCountedView {
public:
 virtual void destroy();
 int references;
};
class ChecklistTempRef {
public:
 ChecklistInlineCountedView *ptr;
 __forceinline ~ChecklistTempRef() { if(ptr) { ChecklistInlineCountedView *obj=ptr; if(--obj->references==0) obj->destroy(); } }
};
class Rva005D1A87Ref
{
public:
	RefCountClass *m_ptr;
 Rva005D1A87Ref(ChecklistInlineCountedView *ptr) : m_ptr(reinterpret_cast<RefCountClass*>(ptr)) {
  if(ptr) ++ptr->references;
 }
 ~Rva005D1A87Ref() { if (m_ptr) m_ptr->Release_Ref(); }
};
class Rva005D1A87UI
{
public:
	virtual ChecklistTempRef createNativeItem();
 Rva005D1A87Ref rva005D1A87();
};

class ChecklistUIFactory {
public:
 virtual void unused0();
 virtual Rva005D1A87UI *getChecklistUI();
};
class Rva005CB26A { public: int rva005CB26A(); };
class Rva005CCCD0 { public: void rva005CCCFC(); };
class ChecklistUIItemNative {
public:
 // Native binding calls folded vcall thunks at slots 1/3/5/7/9. Taking
 // these virtual member pointers emits their existing compiler thunk names.
 // WB15B3410 proves the listener/text/importance/check/age operations.
 virtual void destroy(); virtual void bindListener(void*); virtual void unused2();
 virtual void setText(void*); virtual void unused4(); virtual void setImportance(int);
 virtual void unused6(); virtual void setCheck(bool); virtual void unused8(); virtual void age(); virtual bool selected();
};
class Rva005CC9F8 { public: void rva005CC9F8(); ChecklistUIItemNative *get() const { return m_ptr; } ChecklistUIItemNative *m_ptr; };
class Rva005CC9CB { public: Rva005CC9CB *rva005CC9CB(Rva005CC9CB*); };
namespace StrategicInGameUI
{
class ChecklistItem
{
public:
	class Impl;

	char m_pad00[0x08];
	Impl *m_impl; // +0x08
};

class ChecklistItem::Impl
{
public:
	void rva005CCA0B(const Rva005D1A87Ref &);
 void rva005CCA57();
 virtual void slot0(ChecklistUIItemNative*); virtual void slot1(); virtual void slot2(); virtual void slot3(ChecklistUIItemNative*);
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void updateNative();
 ChecklistUIItemNative *uiItem;
 char text[4]; int importance; char unknown10[0x11]; bool checked; bool noAge; bool notifyDetach;
};

struct ChecklistItemRef
{
	ChecklistItem *m_ptr;
	ChecklistItemRef() : m_ptr(0) {}
	explicit ChecklistItemRef(ChecklistItem *p) : m_ptr(p)
	{ if (m_ptr) ++reinterpret_cast<int *>(m_ptr)[1]; }
	ChecklistItemRef(const ChecklistItemRef &other) : m_ptr(other.m_ptr)
	{ if (m_ptr) ++reinterpret_cast<int *>(m_ptr)[1]; }
	~ChecklistItemRef()
	{ if (m_ptr) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_ptr)); }
};

class Checklist
{
public:
	class Impl;

	void AddItem(const ChecklistItemRef &newItem);

private:
	void *m_vtbl;
	Impl *m_impl; // +0x04
};

class Checklist::Impl
{
public:
	void AddItem(const ChecklistItemRef &newItem, ChecklistItem::Impl *itemImpl);
 void Update();
 void rva005CCFD1();
 ChecklistItemRef rva005CCF47(ChecklistItem *item);
private:
	ChecklistUIFactory *m_factory;
	Rva005D1A87UI *m_ui; // native +4
	char m_records[4]; // native +8; viewed only through the rowed list ABI
};
}

class Rva005CCC74Record
{
public:
	Rva005CCC74Record(const StrategicInGameUI::ChecklistItemRef &,
		StrategicInGameUI::ChecklistItem::Impl *);
	~Rva005CCC74Record()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_ptr));
	}
	StrategicInGameUI::ChecklistItem *m_ptr;
	StrategicInGameUI::ChecklistItem::Impl *m_impl;
};

void StrategicInGameUI::Checklist::AddItem(const ChecklistItemRef &newItem)
{
	m_impl->AddItem(newItem, newItem.m_ptr->m_impl);
}

// Native 5CD049..5CD0C2 (121B): add a temporary counted record to +8,
// then, if +4 is bound, create and attach its UI reference. The independent
// WB15B43D0 sequence agrees; native fixes the offsets and both release calls.
void StrategicInGameUI::Checklist::Impl::AddItem(
	const ChecklistItemRef &newItem, ChecklistItem::Impl *itemImpl)
{
	reinterpret_cast<Rva005CD018ListView *>(m_records)->push_back(
		*reinterpret_cast<Rva005CD018Obj *const *>(
			&Rva005CCC74Record(newItem, itemImpl)));
	if (m_ui)
		itemImpl->rva005CCA0B(m_ui->rva005D1A87());
}

struct ChecklistNode {
 ChecklistNode *next, *prev;
 StrategicInGameUI::ChecklistItem *item;
 StrategicInGameUI::ChecklistItem::Impl *impl;
};
// Native5CCE1B..5CCEB6 and WB15B4B80: bind UI refs then select/update items.
void StrategicInGameUI::Checklist::Impl::Update()
{
 if( !m_ui ) {
  m_ui=m_factory->getChecklistUI();
  if( m_ui ) {
   ChecklistNode *end=*reinterpret_cast<ChecklistNode**>(m_records);
   for( ChecklistNode *it=end->next; it!=end; it=it->next )
    it->impl->rva005CCA0B(m_ui->rva005D1A87());
  }
 }
 if( m_ui && !reinterpret_cast<Rva005CB26A*>(m_ui)->rva005CB26A() )
  reinterpret_cast<Rva005CCCD0*>(this)->rva005CCCFC();
 ChecklistNode *end=*reinterpret_cast<ChecklistNode**>(m_records);
 ChecklistNode *it=end->next;
 while( it!=end ) {
  ChecklistNode *next=it->next;
  it->impl->updateNative();
  it=next;
 }
}


// Native5CCC74..5CCC8F ends in ret8; the following nine bytes form a separate getter.
// Counted reference acquisition precedes the implementation store, matching AddItem ownership.
struct CountedChecklistItemView { void *vtable; int references; };
Rva005CCC74Record::Rva005CCC74Record(
 const StrategicInGameUI::ChecklistItemRef &item,
 StrategicInGameUI::ChecklistItem::Impl *impl)
 : m_ptr(item.m_ptr)
{
 if(m_ptr) ++reinterpret_cast<CountedChecklistItemView*>(m_ptr)->references;
 m_impl=impl;
}

// Native5CCEB6..5CCEBE: forwards the implementation pointer at+4 to the
// independently identified checklist update. The outer receiver/name has no
// independent identity proof, so retain a complete address-derived view.
class Rva005CCEB6
{
public:
 void rva005CCEB6();
 void *unknown00;
 StrategicInGameUI::Checklist::Impl *implementation;
};
void Rva005CCEB6::rva005CCEB6()
{
 implementation->Update();
}

// Native5D1A87..5D1ADE and WB15A87B0 ChecklistUI CreateNewItem: slot0 returns
// a temporary counted reference; acquire output ownership then release the temporary.
Rva005D1A87Ref Rva005D1A87UI::rva005D1A87()
{
 ChecklistTempRef result=createNativeItem();
 return Rva005D1A87Ref(result.ptr);
}

// Native5CCA0B..5CCA57: bind the counted UI item at+4 then initialize its
// listener and presentation state. G7 preserves native's MOV AL boolean ABI.
void StrategicInGameUI::ChecklistItem::Impl::rva005CCA0B(const Rva005D1A87Ref &item)
{
 reinterpret_cast<Rva005CC9CB*>(&uiItem)->rva005CC9CB(reinterpret_cast<Rva005CC9CB*>(const_cast<Rva005D1A87Ref*>(&item)));
 (uiItem->*&ChecklistUIItemNative::bindListener)(this);
 (uiItem->*&ChecklistUIItemNative::setText)(text);
 (uiItem->*&ChecklistUIItemNative::setImportance)(importance);
 (uiItem->*&ChecklistUIItemNative::setCheck)(checked);
 if(!noAge) (uiItem->*&ChecklistUIItemNative::age)();
}

// Native5CCA57..5CCA98 RET: when the counted UI item at+4 is bound,
// optionally notify slot3 (flag+23), notify slot0 when the item's slot10
// query holds, unbind its listener (slot1 thunk) and release the reference
// through rowed 5CC9F8. Taking the reference holder's inline accessor keeps
// native's EDI receiver / ESI holder registers; a direct member read swaps them.
void StrategicInGameUI::ChecklistItem::Impl::rva005CCA57()
{
 Rva005CC9F8 &ref=*reinterpret_cast<Rva005CC9F8*>(&uiItem);
 if(ref.get()) {
  if(notifyDetach) slot3(ref.get());
  if((ref.get()->*&ChecklistUIItemNative::selected)()) slot0(ref.get());
  (ref.get()->*&ChecklistUIItemNative::bindListener)(0);
  ref.rva005CC9F8();
 }
}

// Native5CCFD1..5CCFF3 RET: drain the record list at+8 from the back,
// detaching each record's item implementation (+0xC) before the rowed
// pop_back 5CCEBE (an ICF-shared list body, hence its element name).
// Native rereads the list head in the body; a head view taken per pass
// (not one hoisted reference) keeps that reload.
struct Rva005F8F96;
typedef _STL::list<Rva005F8F96, _STL::allocator<Rva005F8F96> > Rva005CCFD1ListView;
struct Rva005CCFD1ListHead { ChecklistNode *node; bool empty() const { return node->next==node; } ChecklistNode *back() const { return node->prev; } };
void StrategicInGameUI::Checklist::Impl::rva005CCFD1()
{
 while( !reinterpret_cast<Rva005CCFD1ListHead*>(m_records)->empty() ) {
  Rva005CCFD1ListHead &list=*reinterpret_cast<Rva005CCFD1ListHead*>(m_records);
  list.back()->impl->rva005CCA57();
  reinterpret_cast<Rva005CCFD1ListView*>(&list)->pop_back();
 }
}

// Native5CD010..5CD018 forwards the implementation pointer at+4 to the
// list drain above; caller 576D43. Address-derived receiver, as 5CCEB6.
class Rva005CD010
{
public:
 void rva005CD010();
 void *unknown00;
 StrategicInGameUI::Checklist::Impl *implementation;
};
void Rva005CD010::rva005CD010()
{
 implementation->rva005CCFD1();
}

StrategicInGameUI::ChecklistItemRef
StrategicInGameUI::Checklist::Impl::rva005CCF47(ChecklistItem *item)
{
	ChecklistNode *end = *reinterpret_cast<ChecklistNode **>(m_records);
	for (ChecklistNode *node = end->next; node != end; node = node->next) {
		if (node->item == item) {
			ChecklistItemRef result(node->item);
			node->impl->rva005CCA57();
			typedef _STL::_List_iterator<Rva005F8F96,
				_STL::_Nonconst_traits<Rva005F8F96> > Iterator;
			reinterpret_cast<Rva005CCFD1ListView *>(m_records)->erase(Iterator(node));
			return result;
		}
	}
	return ChecklistItemRef();
}
