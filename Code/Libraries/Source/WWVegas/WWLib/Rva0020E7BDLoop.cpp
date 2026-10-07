// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0020E7BD@Rva0020E7BD@@QAEXPAX@Z @0x0020E7BD 43B
// Pointer scan at +0x14/+0x18 calling virtual slot 0 on arg with each
// element breaking on false. Same 43B shape as Rva0020E7E8Loop at +0x20.
// Evidence: callers at 0x0020EC85 0x003F8339 0x0056AF19 0x00576787;
// caller TU Rva003F830F.cpp shows void* callback with vtable g_00C37310;
// neighbours 0x0020E794/0x0020E7E8; Ghidra start proven by direct calls.

class Rva0020E7BDCallback
{
public:
	virtual bool invoke(void *p) = 0;
};

class Rva0020E7BD
{
public:
	void rva0020E7BD(void *cb);

private:
	unsigned char m_pad[0x14];
	void **m_begin;
	void **m_end;
};

void Rva0020E7BD::rva0020E7BD(void *cb)
{
	void **begin = m_begin;
	void **end = m_end;
	for (; begin != end; ++begin) {
		void *elem = *begin;
		if (!((Rva0020E7BDCallback *)cb)->invoke(elem))
			break;
	}
}
