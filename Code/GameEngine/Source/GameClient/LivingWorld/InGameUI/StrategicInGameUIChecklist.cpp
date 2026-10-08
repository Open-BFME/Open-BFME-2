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

class Rva005D1A87Ref
{
public:
	RefCountClass *m_ptr;
	~Rva005D1A87Ref() { if (m_ptr) m_ptr->Release_Ref(); }
};
class Rva005D1A87UI
{
public:
	Rva005D1A87Ref rva005D1A87();
};

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
private:
	void *m_vtbl;
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
