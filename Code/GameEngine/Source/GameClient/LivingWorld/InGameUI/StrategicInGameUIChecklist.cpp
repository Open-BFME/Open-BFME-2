// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::Checklist (WorldBuilder StrategicInGameUIChecklist.cpp).
// Target facts for AddItem 0x005CD0C2 (thiscall, ret 4): hands the new
// item's counted reference and the item's own implementation (+0x08) to
// the checklist's implementation (+0x04), Impl::AddItem 0x005CD049
// (WorldBuilder name, pinned). The reference type is viewed by layout.
namespace StrategicInGameUI
{
class ChecklistItem
{
public:
	class Impl;

	char m_pad00[0x08];
	Impl *m_impl; // +0x08
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
};
}

void StrategicInGameUI::Checklist::AddItem(const ChecklistItemRef &newItem)
{
	m_impl->AddItem(newItem, newItem.m_ptr->m_impl);
}
