// cl: /DNDEBUG /MD /GX-
// ?Rva004384F2Free@@YGXPAVObject@@H@Z @0x004384F2 (58B): Object flag 0x20 at +0x115 gates virtual f68 at +0x250+0x110 taking code struct 1 plus rva0029130C int setup. Evidence: prev 0x004383EB same flags; rowed rva0029130C 0x0029130C; precedent Rva003743CFBehavior f68 code struct 1 shape; ret 8 two stack args; caller 0x00438E89.
struct Rva003743CFParam
{
	int m_00;
	bool m_04;
};
class Rva003743CF250
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
	virtual void f50();
	virtual void f51();
	virtual void f52();
	virtual void f53();
	virtual void f54();
	virtual void f55();
	virtual void f56();
	virtual void f57();
	virtual void f58();
	virtual void f59();
	virtual void f60();
	virtual void f61();
	virtual void f62();
	virtual void f63();
	virtual void f64();
	virtual void f65();
	virtual void f66();
	virtual void f67();
	virtual void f68(int a, Rva003743CFParam *b, int c);
};
class Object
{
public:
	void rva0029130C(int val);
private:
	unsigned char m_pad00[4];
	const void *m_04;
	unsigned char m_pad08[0x250 - 0x08];
	Rva003743CF250 *m_250;
};

// Retail 0x00438166, 16 bytes. The matched parent passes this callback
// through f68 with &val. Retail loads *param and calls the already-rowed
// Object method, with a plain ret establishing __cdecl.
void __cdecl Rva00438166Callback(Object *obj, const int *param)
{
	obj->rva0029130C(*param);
}

void __stdcall Rva004384F2Free(Object *obj, int val)
{
	obj->rva0029130C(val);
	const void *flagObj = *(const void *const *)((const char *)obj + 4);
	if (((*(const unsigned char *)((const char *)flagObj + 0x115)) & 0x20) == 0) {
		return;
	}
	Rva003743CF250 *target = *(Rva003743CF250 **)((char *)obj + 0x250);
	Rva003743CFParam *param = (Rva003743CFParam *)&val;
	target->f68(reinterpret_cast<int>(&Rva00438166Callback), param, 1);
}
