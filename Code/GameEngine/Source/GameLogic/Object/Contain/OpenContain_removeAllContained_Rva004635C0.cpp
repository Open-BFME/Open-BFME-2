// cl: /MD /DNDEBUG
//
// ?removeAllContained@OpenContain@@UAEX_N@Z
// retail 0x004635C0, 44 bytes (Ghidra FUN_008635c0).
//
// Target evidence: the address sits in seven .rdata vtables (the contain
// interface tables of OpenContain's subclasses) and is pinned from the
// base-class call in 0x00478231. MSVC compiles an override of a secondary
// base's virtual with `this` at that base: retail steps back 0x20 to the
// OpenContain object for the inner call and reads the contain list's
// header node at +0x34 from the interface (+0x54 in OpenContain).
//
// Donor: GeneralsMD OpenContain.cpp removeAllContained - loop while the
// list is not empty, removing its first rider. BFME 2's inner call takes the
// rider itself and is not virtual (0x00462FB3 is in no vtable), so it is kept
// under its address rather than Zero Hour's removeFromContainViaIterator.

class Object;

struct ContainListNode
{
	ContainListNode *m_next;
	ContainListNode *m_prev;
	Object *m_rider;
};

class OpenContainModuleBase
{
public:
	virtual ~OpenContainModuleBase();
private:
	char m_pad04[0x20 - 0x04];
};

class ContainModuleInterface
{
public:
	virtual void removeAllContained(bool exposeStealthUnits) = 0;
};

class OpenContain : public OpenContainModuleBase, public ContainModuleInterface
{
public:
	virtual void removeAllContained(bool exposeStealthUnits);
	void rva00462FB3(Object *rider, bool exposeStealthUnits);
private:
	char m_pad24[0x54 - 0x24];
	ContainListNode *m_containList;
};

void OpenContain::removeAllContained(bool exposeStealthUnits)
{
	ContainListNode *it;
	while ((it = m_containList->m_next) != m_containList)
		rva00462FB3(it->m_rider, exposeStealthUnits);
}
