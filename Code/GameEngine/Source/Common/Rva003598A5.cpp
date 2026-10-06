// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003598A5@@YGXHHHPAX@Z 0x003598A5 38B loop virtual slot0 over int range
// Evidence: retail for low to high calls [esi] slot0 with loopvar and arg3; callers 0x003599C7 0x003599E0 push 4 args stdcall; LINK via 0x0035997F
struct Rva003598A5Obj
{
	virtual void f(int a, int b);
};

void __stdcall Rva003598A5(int low, int high, int x, void *obj)
{
	Rva003598A5Obj *o = (Rva003598A5Obj *)obj;
	for (int i = low; i <= high; ++i)
		o->f(i, x);
}
