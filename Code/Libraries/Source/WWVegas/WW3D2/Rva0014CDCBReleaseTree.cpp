// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva0014CDCB_ReleaseTree@Rva0014CD63_Prototype@@QAEXXZ @ 0x0014CDCB
// (25 bytes). Counted-tree release installed as virtual slot 6 in two
// prototype vtables (0x00BD37EC slot 6 and 0x00BD4F90 slot 6, sharing slots
// 0/4/8 with the same ret-stub pattern): when the +0x14 holder is set, drop
// its +4 count and dispatch its slot 0 when the count reaches zero, then
// null the holder. No direct calls (slot 0 goes indirect), so no pins.
// Retail names for the class, the holder type and slot 0 are unrecovered;
// the TU-local view below keeps the observed offsets with documented holes.

class PrototypeTreeRef
{
public:
	virtual void DeleteThis(); // slot 0, destroys on final release
	int m_refCount; // +0x04
};

class Rva0014CD63_Prototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	void Rva0014CDCB_ReleaseTree();

	char m_pad04[0x10]; // +0x04..+0x13, untouched by this body
	PrototypeTreeRef *m_tree; // +0x14
};

// ?Rva0014CDCB_ReleaseTree@Rva0014CD63_Prototype@@QAEXXZ
void Rva0014CD63_Prototype::Rva0014CDCB_ReleaseTree()
{
	PrototypeTreeRef *tree = m_tree;
	if (tree != 0)
	{
		if (--tree->m_refCount == 0)
			tree->DeleteThis();
		m_tree = 0;
	}
}
