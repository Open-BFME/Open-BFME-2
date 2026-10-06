// cl: /DNDEBUG /MD
// ?rva004031F3@Rva004031F3@@QAEXPAUObj@@PAUInfo@@@Z @0x004031F3 64B
// Four-step virtual fetch: call slot 31 with this, if info byte at +1 >= 3
// call slot 27 with &m1, then slot 30 with &m2 and &m3. Evidence: vtable
// offsets 0x7c/0x6c/0x78/0x78 in the disassembly; two callers in 0x0040426D;
// neighbours are AttributeModifierPoolUpdate/Rva0040327B units. Owner and
// peer identities unknown so honest Rva names are used; slots are fixed by
// declaring 32 virtuals in order.
struct Rva004031F3;

struct Obj
{
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
	virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
	virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24(); virtual void f25(); virtual void f26();
	virtual void f27(int *out);
	virtual void f28(); virtual void f29();
	virtual void f30(int *out);
	virtual void f31(Rva004031F3 *ctx);
};

struct Info
{
	char m00;
	unsigned char m01;
};

struct Rva004031F3
{
public:
	void rva004031F3(Obj *obj, Info *info);

private:
	int m00;
	int m01;
	int m02;
	int m03;
};

void Rva004031F3::rva004031F3(Obj *obj, Info *info)
{
	obj->f31(this);
	if (info->m01 >= 3)
		obj->f27(&m01);
	obj->f30(&m02);
	obj->f30(&m03);
}
