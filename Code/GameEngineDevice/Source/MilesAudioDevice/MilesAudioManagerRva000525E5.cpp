// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1Rva000525E5@@QAE@XZ, retail 0x000525E5, 125 bytes. Scalar dtor for 0x48-byte Miles audio element.
// Evidence: vector deleting dtor at 0x0005277C uses size 0x48 and dtor 0x4525E5 via ??_M; body calls pin 0x51038 then row 0x50FE3 then delete[] at +0x18 then three 0xA8A37 handles at +0x28/+0x24/+0x20 then Release_Ref at +0x88 of +0xC pointee like Rva00A86CE precedent.
class Rva0005F279Elem
{
public:
	bool rva00051038() throw();
};

class Rva00050FE3
{
public:
	void rva00050FE3() throw();
};

void __cdecl operator delete[](void *) throw();

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();
private:
	void *m_target;
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva000525E5Owner
{
	char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class Rva000525E5Holder
{
public:
	~Rva000525E5Holder()
	{
		if (m_owner)
			m_owner->m_ref.Release_Ref();
	}
	Rva000525E5Owner *m_owner;
};

class Rva000525E5
{
public:
	~Rva000525E5();
private:
	char m_sample[0xC];
	Rva000525E5Holder m_holder0C;
	char m_pad10[8];
	void *m_array18;
	char m_pad1C[4];
	Rva00690FF0Handle m_h20;
	Rva00690FF0Handle m_h24;
	Rva00690FF0Handle m_h28;
	char m_tail2C[0x48 - 0x2C];
};

Rva000525E5::~Rva000525E5()
{
	if (!((Rva0005F279Elem *)this)->rva00051038())
		((Rva00050FE3 *)this)->rva00050FE3();
	if (m_array18) {
		::operator delete[](m_array18);
		m_array18 = 0;
	}
}
