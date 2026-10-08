// cl: /O1 /DNDEBUG /MD /EHsc
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
template<class T, class A> class list {
public:
	void push_back(const T &);
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
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void updateNative();
};

struct ChecklistItemRef
{
	ChecklistItem *m_ptr;
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
