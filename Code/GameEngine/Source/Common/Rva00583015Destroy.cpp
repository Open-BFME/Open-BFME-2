// cl: /DNDEBUG /MD /EHsc
// ?Rva00583015Destroy@@YAXXZ @0x00583015 31B
// Singleton destroy for global 0x00A06398 (created by 0x005836B5 via 0x00583359).
// Evidence: mov ecx [0x00A06398] test je mov eax [ecx] push 0 call [eax] push eax
// call operator delete 0x0002FD60 and [0x00A06398] 0 pop ecx ret; caller 0x0044D279;
// same virtual-slot-0 plus delete shape as Rva0023C420Delete 20B.

void __cdecl operator delete(void *p);

class Rva00583015Obj
{
public:
	virtual void *s0(int x);
};

extern Rva00583015Obj *g_Va00A06398;

void __cdecl Rva00583015Destroy(void)
{
	Rva00583015Obj *p = g_Va00A06398;
	if (p != 0)
	{
		void *q = p->s0(0);
		::operator delete(q);
		g_Va00A06398 = 0;
	}
}
// ?g_Va00A06398@@3PAVRva00583015Obj@@A: the global at VA 0xe06398 is ?g_Va00E06398@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00A06398@@3PAVRva00583015Obj@@A=?g_Va00E06398@@3HA")
