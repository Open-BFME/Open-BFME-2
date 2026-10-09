// cl: /O1 /G7 /EHsc /MD
//
// ??1Rva0007BAD6@@QAE@XZ @ 0x0007C0F5 (153B). Destructor of the class whose release-all clear
// is rowed at 0x0007BAD6 (Rva0007BAD6Clear.cpp; member layout +0x14/+0x18 texture refs,
// +0x1C interface, +0x20/+0x24 holders is target fact there). Retail runs that clear first
// (SEH state 5, all six counted members live), then destroys the members in reverse order:
// +0x24 and +0x20 holders and the +0x04/+0x00 holders as inline `if (p && --p->count == 0)
// p->slot0()` (refcount at +4, vtable slot 0 thiscall), and +0x18/+0x14 as direct
// Release_Ref 0x0061ED10 behind a null test. SEH states 4..0 follow the members.
// Evidence for the holder shape is the retail inline; owner of the class remains unproven so the
// address name stays.

class TextureClass
{
public:
	void Release_Ref();
};

class HolderTarget
{
public:
	virtual void destroy();
	int m_count;
};

struct DtorHolder
{
	HolderTarget *m_ptr;
	__forceinline ~DtorHolder()
	{
		HolderTarget *ptr = m_ptr;
		if (ptr && --ptr->m_count == 0)
			ptr->destroy();
	}
};

struct DtorTextureRef
{
	TextureClass *m_ptr;
	__forceinline ~DtorTextureRef()
	{
		TextureClass *ptr = m_ptr;
		if (ptr)
			ptr->Release_Ref();
	}
};

class Rva0007BAD6
{
public:
	~Rva0007BAD6();
	void rva0007BAD6();

private:
	DtorHolder m_00;
	DtorHolder m_04;
	int m_pad08[3];
	DtorTextureRef m_14;
	DtorTextureRef m_18;
	void *m_1c;
	DtorHolder m_20;
	DtorHolder m_24;
};

Rva0007BAD6::~Rva0007BAD6()
{
	rva0007BAD6();
}
