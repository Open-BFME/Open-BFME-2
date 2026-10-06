// cl: /MD /GX-
//
// Node teardown at 0x003B448C (15B): restores the 0x00BBB554 base
// vtable word at +0x04, then tail-jumps the rowed clear at 0x003B4071
// for the +0x08 member. Called as the node destructor from the
// ScriptList-subrecord element drain at 0x003B675B (the 47B twin of
// 0x003B578E, whose node destructor is the pinned 0x003B3F5E).
// Address-derived name; the +0x00 link and +0x08 member meanings follow
// the drain's 0x14 element layout.

extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

class Rva003B4071
{
public:
	void clear();
};

class Rva003B448C
{
public:
	~Rva003B448C();

private:
	void *m_next;					// +0x00
	void *m_vtable;					// +0x04
	Rva003B4071 m_mem;				// +0x08
};

// ??1Rva003B448C@@QAE@XZ
Rva003B448C::~Rva003B448C()
{
	m_vtable = (void *)((unsigned int)vtbl_00BBB554);
	m_mem.clear();
}
