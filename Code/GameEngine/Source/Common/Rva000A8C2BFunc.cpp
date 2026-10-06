// cl: /MD
// ?Rva000A8C2BInit@@YGXPAVRva000A8C2BObj@@PAH@Z retail 0x000A8C2B 67B
// Free __stdcall with 2 args (ret 8): obj in esi from [ebp+8] with 32-slot vtable; int* ptr in edi from [ebp+0xC].
// Evidence: 4 virtual calls slot10 0x28 with 2-byte {1 1} local at [ebp-4] then slot28 0x70 with ptr+8 then slot31 0x7C with ptr then ptr+1 via add edi 4; single caller at 0x0005B351 in 0x0005B256; neighbours share Common dir.
// Honest Rva free name; slot offsets prove vtable width.
struct TwoBytes
{
	unsigned char a;
	unsigned char b;
};

class Rva000A8C2BObj
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10(TwoBytes *t);
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28(int *p);
	virtual void s29();
	virtual void s30();
	virtual void s31(int *p);
};

void __stdcall Rva000A8C2BInit(Rva000A8C2BObj *obj, int *ptr)
{
	TwoBytes t;
	t.a = 1;
	t.b = 1;
	obj->s10(&t);
	obj->s28(ptr + 2);
	obj->s31(ptr);
	obj->s31(++ptr);
}
