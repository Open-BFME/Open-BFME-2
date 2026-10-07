// ?Rva00152C47Create@@YA?AVRva00087A93@@PBD0HH@Z
// partial score=0.98 date=2026-10-07
// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva00152C47Create@@YA?AVRva00087A93@@PBD0HH@Z present-unmatched
// Address-derived factory view at 0x00152C47, Ghidra extent 147B. Target code
// locks the DX8 device, allocates a 0x34-byte object, calls the matched
// 0x001525FB constructor, tests the bool result from 0x0015288F, constructs a
// one-pointer return holder, and balances its reference count through the
// matched Rva00087A93 holder destructor at 0x0007B724. The first stack argument
// is the hidden return buffer; the unwind map confirms return-holder cleanup
// after the local holder and device lock. The original type names remain
// unknown; the local views preserve only the target-proven layout/ABI.
#include <new>

void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);

class Rva001525FB
{
public:
	__declspec(nothrow) Rva001525FB();
private:
	char m_object[0x34];
};
typedef char Rva001525FBSizeCheck[sizeof(Rva001525FB) == 0x34 ? 1 : -1];

class Rva0015288F
{
public:
	bool rva0015288F(int a1, int a2, int a3, int a4);
};

class Rva00087A93
{
	public:
	struct Data
	{
		virtual void slot();
		int ref;
	};
	Data *m_data;
	Rva00087A93() {}
	__forceinline Rva00087A93(bool succeeded, Rva001525FB *object)
	{
		if (!succeeded)
		{
			m_data = 0;
		}
		else
		{
			m_data = (Data *)object;
			if (object)
				++*(int *)((char *)object + 4);
		}
	}
	~Rva00087A93()
	{
		Data *d = m_data;
		if (d && --d->ref == 0)
			d->slot();
	}
};

class Rva00152C47DeviceLock
{
public:
	Rva00152C47DeviceLock() { BFME_DX8_Thread_Lock(); }
	~Rva00152C47DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// ?Rva00152C47Create@@YA?AVRva00087A93@@PBD0HH@Z
Rva00087A93 __cdecl Rva00152C47Create(const char *first,
	const char *second, int mode, int value)
{
	Rva00152C47DeviceLock guard;
	Rva001525FB *object = new Rva001525FB;
	Rva00087A93 holder;
	holder.m_data = (Rva00087A93::Data *)object;
	bool succeeded = ((Rva0015288F *)object)->rva0015288F(
		(int)first, (int)second, mode, value);
	return Rva00087A93(succeeded, object);
}
