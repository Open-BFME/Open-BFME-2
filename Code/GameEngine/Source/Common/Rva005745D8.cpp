// cl: /O1 /DNDEBUG /MD
// ?Rva005745D8Get@@YIXPAX@Z 187B @0x005745D8: free fastcall void (void*) chaining get plus globals plus 0x2E0C68 plus 0x2E0CD4 plus virtuals plus floor scale.
// Evidence: chain lane calls 0x002E0C68 just landed rowed; caller 0x0057506A mov ecx [esi+0x20] call no pushes ret0 so fastcall void* ret void; callees all rowed/pinned per packet incl 0x42D714 (row says int but body derefs as pointer so cast with note for central retype) 0x2E0C68 0x2E0CD4 0x2E0C2B 0x2E063B plus IAT floor plus BfmeZeroRange style floats at 0xBCF628 0xBBB8D8; prev Rva00574499Dtor next Rva005746AFCtor share /O1 /DNDEBUG /MD.
class Rva0042D714PtrChaseField
{
public:
	int get() const;
};
struct BfmeWorldRV;
extern BfmeWorldRV *g_bfmeWorldRV;
extern void *g_009FEF10;
class Rva002BA8F1Logic;
class Rva002E0C68
{
public:
	int rva002E0C68();
};
class Rva002E0CD4
{
public:
	int get() const;
};
class Rva002E0C2B
{
public:
	int rva002E0C2B();
};
class Rva002E063B
{
public:
	int get() const;
};
extern "C" __declspec(dllimport) double __cdecl floor(double v);
extern float g_Va00BCF628;
extern float g_Va00BBB8D8;
struct Virt04
{
	virtual void v00();
	virtual void v01(int a, int b);
};
struct Virt0C
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03(int a, int b);
};
struct Virt14
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05(float f);
};
struct Virt1C
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07(int a);
};
void __fastcall Rva005745D8Get(void *a)
{
	int first = ((Rva0042D714PtrChaseField *)a)->get();
	void *esi_obj = (void *)first;
	if (esi_obj == 0)
		return;
	void *g = g_009FEF10;
	if (g == 0)
		return;
	void *edi_obj = *(void **)((char *)g + 0x98);
	if (edi_obj == 0)
		return;
	int saved298 = *(int *)((char *)edi_obj + 0x298);
	int sum = ((Rva002E0C68 *)edi_obj)->rva002E0C68() + saved298;
	int second = ((Rva002E0CD4 *)edi_obj)->get();
	((Virt04 *)esi_obj)->v01(sum, second);
	((Virt0C *)esi_obj)->v03(0, *(int *)((char *)edi_obj + 0x268));
	((Virt0C *)esi_obj)->v03(1, *(int *)((char *)edi_obj + 0x26C));
	((Virt0C *)esi_obj)->v03(2, *(int *)((char *)edi_obj + 0x270));
	int third = ((Rva002E0C2B *)edi_obj)->rva002E0C2B();
	float g1 = (float)third * g_Va00BCF628 + g_Va00BBB8D8;
	((Virt14 *)esi_obj)->v05(g1);
	int fourth = ((Rva002E063B *)edi_obj)->get();
	((Virt1C *)esi_obj)->v07(fourth);
}
