// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005EC135Delete@@YAXPAPAX@Z @ 0x005EC135 (33B): safe delete via vector deleting dtor.
// Evidence: free function ret no N cdecl 1 arg pp; ecx=*pp test je; virtual slot0 push 0 call [eax];
// eax result or 0 pushed to operator delete 0x0002FD60; and [esi],0 clears; callers 0x005D07E1 0x005D1210.
void __cdecl operator delete(void *p);

class DelBase005EC135
{
public:
	virtual void *vecDel(unsigned int);
};

void __cdecl Rva005EC135Delete(void **pp)
{
	DelBase005EC135 *q = *(DelBase005EC135 **)pp;
	void *p;
	if (q != 0)
		p = q->vecDel(0);
	else
		p = 0;
	operator delete(p);
	*pp = 0;
}
