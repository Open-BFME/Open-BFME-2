// cl: /GX /DNDEBUG /MD
//
// ??1Rva0010F7EE@@UAE@XZ, retail 0x0010F7EE, 52 bytes.
// Virtual dtor releasing the +0x08 holder through the rowed Release_Ref at
// 0x00050ED3 when non-null, then restoring base vtable 0x00BC5128. Holder
// dtor is inline and throwing (EH-tracked state 0, EH prolog); remaining
// members are trivial pads. Shape follows AIUpdateModuleDataDtor 52B
// (TU-local base with inline vtable-restoring dtor, novtable suppresses
// the derived vtable store retail lacks, empty derived body).
// Evidence: vtable 0x00BC5128 stored at end; caller ??_GRva0010F7EE@@UAEPAXI@Z
// at 0x0010F7D2; gap between two rows of OpaqueScalarDeletingDtorsB01.cpp.

extern "C" const void *const vtbl_00BC5128[];  // ??_7Rva001DA2D5Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC5128=??_7Rva001DA2D5Base@@6B@")

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva0010F7EEHolder
{
	~Rva0010F7EEHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class Rva0010F7EEBase
{
public:
	virtual ~Rva0010F7EEBase()
	{
		*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BC5128));
	}
};

class __declspec(novtable) Rva0010F7EE : public Rva0010F7EEBase
{
public:
	virtual ~Rva0010F7EE();

private:
	int m_unused04; // +0x04
	Rva0010F7EEHolder m_holder08; // +0x08
};

Rva0010F7EE::~Rva0010F7EE()
{
}
