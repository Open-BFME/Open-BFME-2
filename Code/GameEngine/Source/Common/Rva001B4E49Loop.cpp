// cl: /MD
//
// ?rva001B4E49@Rva001B4E49@@QAEXXZ @0x001B4E49 26B. Loop over an 8-byte-entry
// array ([this+0]=begin, [this+4]=end): calls virtual slot 3 (call
// [eax+0xc]) on each entry's +0 object, stepping 8 bytes.
// Evidence: ret with no N proves __thiscall with no stack args; ecx read
// before write proves thiscall; stride 8 matches Rva001B4F8B entry shape;
// neighbours share // cl: /O1 /MD.

struct Rva001B4E49Target
{
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
};

struct Rva001B4E49Entry
{
	void *m_obj; // +0 dereferenced for the virtual call
	int m_pad; // +4 keeps the 8-byte stride retail steps
};

class Rva001B4E49
{
public:
	void rva001B4E49();

private:
	Rva001B4E49Entry *m_begin; // +0
	Rva001B4E49Entry *m_end; // +4
};

void Rva001B4E49::rva001B4E49()
{
	for (Rva001B4E49Entry *p = m_begin; p != m_end; ++p) {
		((Rva001B4E49Target *)p->m_obj)->vf3();
	}
}
