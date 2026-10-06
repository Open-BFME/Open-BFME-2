// cl: /MD
// ?Rva0047FDFEGet@@YAHPAX@Z @ 0x0047FDFE 39B
// Leaf: iterate null-terminated ptr array at +0x244 calling virtual slot 0xA4
// on embedded obj at elem+0xC returning first nonzero. Evidence: gap abuts
// prev 0x0047FDF7 and next 0x0047FE25; frameless esp+4 ret (cdecl 1 arg);
// indirect call FF50A4 needs no pin; caller 0x00294D2E pushes one ptr.
class Target0047FDFE
{
public:
	virtual int f00();
	virtual int f01();
	virtual int f02();
	virtual int f03();
	virtual int f04();
	virtual int f05();
	virtual int f06();
	virtual int f07();
	virtual int f08();
	virtual int f09();
	virtual int f10();
	virtual int f11();
	virtual int f12();
	virtual int f13();
	virtual int f14();
	virtual int f15();
	virtual int f16();
	virtual int f17();
	virtual int f18();
	virtual int f19();
	virtual int f20();
	virtual int f21();
	virtual int f22();
	virtual int f23();
	virtual int f24();
	virtual int f25();
	virtual int f26();
	virtual int f27();
	virtual int f28();
	virtual int f29();
	virtual int f30();
	virtual int f31();
	virtual int f32();
	virtual int f33();
	virtual int f34();
	virtual int f35();
	virtual int f36();
	virtual int f37();
	virtual int f38();
	virtual int f39();
	virtual int f40();
	virtual int check();
};

struct Elem0047FDFE
{
	unsigned char pad[0xC];
	Target0047FDFE obj;
};

struct Arg0047FDFE
{
	unsigned char pad[0x244];
	Elem0047FDFE **list;
};

int __cdecl Rva0047FDFEGet(void *argIn)
{
	Arg0047FDFE *arg = (Arg0047FDFE *)argIn;
	Elem0047FDFE **p = arg->list;
	while (*p != 0)
	{
		Target0047FDFE *o = &(*p)->obj;
		int r = o->check();
		if (r != 0)
			return r;
		++p;
	}
	return 0;
}
