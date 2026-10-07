// cl: /DNDEBUG /MD /EHsc /O1 /G7
//
// Target facts: the 74-byte destructor at 0x001164F5 stores vtable 0xBCFB38
// then calls 0x0010F70A on the pointer at +8 with this as one stack argument.
// It next releases the still-non-null +8 reference through 0x00050ED3 and
// restores base vtable 0xBC5128. Constructor 0x001164D3 confirms the +4 word
// and copied +8 object. The base and member names below are address-derived
// structural views; identity is unproven.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0010F70A
{
public:
	void rva0010F70A(void *owner);
};

extern "C" const void *const vtbl_00BC5128[];
#pragma comment(linker, "/alternatename:_vtbl_00BC5128=??_7Rva001DA2D5Base@@6B@")

class Rva001164F5Base
{
public:
	virtual void v00() {}
	virtual void v04() {}
	virtual void v08() {}
	virtual void v0C() {}
	virtual void v10() {}

	__forceinline ~Rva001164F5Base()
	{
		*(const void **)this = vtbl_00BC5128;
	}

private:
	int m_04;
};

class Rva0036CA00Str
{
public:
	void *m_item;

	__forceinline ~Rva0036CA00Str()
	{
		if (m_item != 0) {
			((OpaqueRefCounted *)m_item)->Release_Ref();
		}
	}
};

class Rva001164F5 : public Rva001164F5Base
{
public:
	__declspec(noinline) virtual ~Rva001164F5();

private:
	Rva0036CA00Str m_str08;
};

Rva001164F5::~Rva001164F5()
{
	((Rva0010F70A *)m_str08.m_item)->rva0010F70A(this);
}

void Rva001164F5_ScalarDeletingDtor(Rva001164F5 *p)
{
	delete p;
}
