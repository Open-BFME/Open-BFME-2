// cl: /MD
//
// ?rva002B22AF@Rva002B22AF@@QAEXPAVRva002B22AFArg@@@Z @0x002B22AF 68B
// __thiscall virtual forwarder: passes this+0x00/+0x08/+0x0C/+0x10/+0x14 to
// five virtuals (slots 0x50/0x7C/0x6C/0x6C/0x90) on its single pointer arg.
// Evidence: all calls are indirect so no rows needed; caller 0x002BB63D passes
// an array element as this and edi as arg; neighbours are default-flags
// Disp getters/setters.
class Rva002B22AFArg
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void v20(void *p);
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void v27a(void *p);
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void v31(void *p);
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void v36(void *p);
};

class Rva002B22AF
{
public:
	void rva002B22AF(Rva002B22AFArg *arg);

private:
	char m_data[0x18];
};

void Rva002B22AF::rva002B22AF(Rva002B22AFArg *arg)
{
	arg->v20(this);
	arg->v31((void *)((char *)this + 8));
	arg->v27a((void *)((char *)this + 0x0C));
	arg->v27a((void *)((char *)this + 0x10));
	arg->v36((void *)((char *)this + 0x14));
}
