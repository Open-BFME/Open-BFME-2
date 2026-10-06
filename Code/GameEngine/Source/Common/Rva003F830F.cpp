// cl: /O1 /DNDEBUG /MD /EHsc /Oi
// ?rva003F830F@Rva003F81FDProxy@@QAEXPAX@Z @0x003F830F 61B
// Evidence: unlock lane; calls pinned ?rva003F81B0@Rva003F81FDProxy (0x003F81B0)
//   to get Rva003F7D86Inner, then builds 8B callback with vtable 0x00C37310
//   (Rva003F82E2 ctor row) and calls pinned ?rva0020E7BD@Rva0020E7BD (0x0020E7BD);
//   caller at 0x0020EBDC; ret 4 one-pointer thiscall on Rva003F81FDProxy.
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);
class Rva003F7D86Inner;
class Rva0020E7BD
{
public:
	void rva0020E7BD(void *p);
};
extern const void *const g_00C37310[];
class Rva003F81FDProxy
{
public:
	Rva003F7D86Inner *rva003F81B0();
	void rva003F830F(void *p);
};
struct EmptyBase003F830F
{
	EmptyBase003F830F() {}
	~EmptyBase003F830F() { _ReadWriteBarrier(); }
};
struct Tmp003F830F : EmptyBase003F830F
{
	const void *v;
	void *o;
	Tmp003F830F(void *oo) : v(g_00C37310), o(oo) {}
	~Tmp003F830F() {}
};
void Rva003F81FDProxy::rva003F830F(void *p)
{
	Rva003F7D86Inner *inner = rva003F81B0();
	if (inner) {
		Tmp003F830F tmp(inner);
		((Rva0020E7BD *)p)->rva0020E7BD(&tmp);
	}
}
