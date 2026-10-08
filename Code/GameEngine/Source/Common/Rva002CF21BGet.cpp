// cl: /MD
// ?rva002CF21B@Rva002CF21B@@QAEHPAXHH@Z @0x002CF21B 99B.
// Manager dispatch: null arg returns 0, else virtual slot 0x70 on the global
// at 0x009FE77C with 3 args, then walk the pointer array at result+0x154;
// per element Sleep(0) if byte at 0x009FF004 set, virtual slot 0x40 then
// slot 0, ret 12. Callers pass global 0x009FF000 in ecx with 3 stack args.
// Unblocks 9 free functions, none ready yet.
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long ms);
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

// g_00DFF004: VA 0x00dff004 (.data/bss); retail zero-filled.
unsigned char g_00DFF004;

struct Obj
{
	virtual void v00();
};

struct Elem
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual Obj *v16();
};

struct Result
{
	unsigned char m_pad[0x154];
	Elem **m_array;
};

struct Mgr
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual Result *v28(int a1, int a2, int a3);
};

struct Rva002CF21B
{
	void *rva002CF21B(void *a1, int a2, int a3);
};

void *Rva002CF21B::rva002CF21B(void *a1, int a2, int a3)
{
	if (a1 == 0)
		return 0;
	Result *r;
	{
		Mgr *mgr = (Mgr *)((ClientFrameSubsystem *)TheGameClient);
		r = mgr->v28((int)a1, a2, a3);
	}
	Elem **p = r->m_array;
	if (p == 0)
		return r;
	while (*p != 0) {
		if (g_00DFF004)
			Sleep(0);
		Obj *o = (*p)->v16();
		if (o != 0)
			o->v00();
		++p;
	}
	return r;
}
