// cl: /MD /EHsc
// ?rva000F0972@Rva000F0912@@QAEXXZ @0x000F0972 111B: release two globals plus buffer manager then clear 160-slot list under DX8 lock. Evidence: chain callee 0x000F0912 row plus LINK BONUS via 0x000F09E1 plus callers 0x0009A3E8 0x000F09FD.
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
class Rva000F0972Releasable
{
public:
	virtual void f0();
	virtual void f1();
	virtual void __stdcall f2();
};
extern Rva000F0972Releasable *g_00DEBCE0;
extern Rva000F0972Releasable *g_00DEBCDC;
class W3DBufferManager
{
public:
	void rva00115FF1();
};
extern class W3DBufferManager *TheW3DBufferManager;
class Rva000F0912
{
public:
	void rva000F0912();
	void rva000F0972();
};
struct Rva000F0972LockGuard
{
	Rva000F0972LockGuard() { BFME_DX8_Thread_Lock(); }
	~Rva000F0972LockGuard() { BFME_DX8_Thread_Assert(); }
};
void Rva000F0912::rva000F0972()
{
	Rva000F0972LockGuard guard;
	if (g_00DEBCE0 != 0)
		g_00DEBCE0->f2();
	if (g_00DEBCDC != 0)
		g_00DEBCDC->f2();
	W3DBufferManager *mgr = TheW3DBufferManager;
	g_00DEBCE0 = 0;
	g_00DEBCDC = 0;
	if (mgr != 0)
	{
		mgr->rva00115FF1();
		rva000F0912();
	}
}
