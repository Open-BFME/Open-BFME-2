// cl: /MD
// ?Rva0040707EUpdate@@YAXPAX00PAVRva00406FBF@@@Z @0x0040707E 27B: free cdecl 4-arg helper calling virtual slot 0x78 on arg1 with arg2 then Rva00406FBF::rva00406FBF(arg2) with this=arg4 arg3 unused. Evidence: chain via 0x00406FBF now ready; caller 0x00407279 pushes 4 args add esp 16; retail mov ecx/push/call [eax+0x78] then push/mov ecx/call 0x406FBF.
class Rva00406FBF
{
public:
	void rva00406FBF(unsigned char *data);
};
class Rva0040707EObj
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
};
void __cdecl Rva0040707EUpdate(void *a1, void *a2, void *a3_unused, Rva00406FBF *a4)
{
	((Rva0040707EObj *)a1)->vf30(a2);
	(void)a3_unused;
	a4->rva00406FBF((unsigned char *)a2);
}
