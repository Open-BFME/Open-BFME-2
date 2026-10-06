// cl: /MD
// ?Rva004070B6Update@@YAXPAX00PAVRva00406FBF@@@Z @0x004070B6 30B: free cdecl 4-arg helper calling virtual slot 0x90 on arg1 with arg2 then Rva00406FBF::rva00406FDC(arg2) with this=arg4 arg3 unused. Evidence: chain via 0x00406FDC now ready; same family as 0x0040707E slot 0x78; retail mov ecx/push/call [eax+0x90] then push/mov ecx/call 0x406FDC.
class Rva00406FBF
{
public:
	void rva00406FDC(unsigned char *data);
};
class Rva004070B6Obj
{
public:
	virtual void vf00(void *p);
	virtual void vf01(void *p);
	virtual void vf02(void *p);
	virtual void vf03(void *p);
	virtual void vf04(void *p);
	virtual void vf05(void *p);
	virtual void vf06(void *p);
	virtual void vf07(void *p);
	virtual void vf08(void *p);
	virtual void vf09(void *p);
	virtual void vf10(void *p);
	virtual void vf11(void *p);
	virtual void vf12(void *p);
	virtual void vf13(void *p);
	virtual void vf14(void *p);
	virtual void vf15(void *p);
	virtual void vf16(void *p);
	virtual void vf17(void *p);
	virtual void vf18(void *p);
	virtual void vf19(void *p);
	virtual void vf20(void *p);
	virtual void vf21(void *p);
	virtual void vf22(void *p);
	virtual void vf23(void *p);
	virtual void vf24(void *p);
	virtual void vf25(void *p);
	virtual void vf26(void *p);
	virtual void vf27(void *p);
	virtual void vf28(void *p);
	virtual void vf29(void *p);
	virtual void vf30(void *p);
	virtual void vf31(void *p);
	virtual void vf32(void *p);
	virtual void vf33(void *p);
	virtual void vf34(void *p);
	virtual void vf35(void *p);
	virtual void vf36(void *p);
};
void __cdecl Rva004070B6Update(void *a1, void *a2, void *a3_unused, Rva00406FBF *a4)
{
	((Rva004070B6Obj *)a1)->vf36(a2);
	(void)a3_unused;
	a4->rva00406FDC((unsigned char *)a2);
}
