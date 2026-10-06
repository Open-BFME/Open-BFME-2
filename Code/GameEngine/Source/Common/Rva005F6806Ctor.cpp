// cl: /EHsc /MD /DNDEBUG
// ??0Rva005F6806@@QAE@PAXPAXPAX@Z @0x005F6806 100B
// Constructor: base at +0 built by pinned 0x005F3E93 from (a1, a2, 1, a3),
// own vtable 0x00C796D0, pointer member at +8 allocated via rowed operator
// new 0x0002FDA0 (0x38 bytes) and constructed by pinned 0x005F654C when the
// allocation is non-null. Evidence: same new-plus-conditional-init EH shape
// as 0x005E1627; base ret 0x10 (4 args) and heap ret 0xC (3 args) with ghidra
// extents 80B/698B; states 0/1 and __EH_prolog from the init-list new under
// /EHsc.
class Rva005F6806Base
{
public:
	Rva005F6806Base(void *a1, void *a2, int a3, void *a4);
	virtual ~Rva005F6806Base();
private:
	void *m_04;
};

class Rva005F6806Heap
{
public:
	Rva005F6806Heap(void *s, void *a1, void *a2);
	virtual ~Rva005F6806Heap();
private:
	char m_pad[0x38 - 4];
};

class Rva005F6806 : public Rva005F6806Base
{
public:
	Rva005F6806(void *a1, void *a2, void *a3);
	virtual ~Rva005F6806();
private:
	Rva005F6806Heap *m_08;
};

Rva005F6806::Rva005F6806(void *a1, void *a2, void *a3)
	: Rva005F6806Base(a1, a2, 1, a3)
	, m_08(new Rva005F6806Heap(this, a1, a2))
{
}
