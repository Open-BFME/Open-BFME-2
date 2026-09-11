// ?bfmeInitDGF@BfmeThingDGF@@QAEPAV1@PAX@Z
// partial score=0.85 date=2026-09-10
// cl: /O1 /MD
//
// BfmeThingDGF::bfmeInitDGF, retail 0x00664DB0, 95 bytes. Dedicated TU
// so BfmeConv692.cpp keeps its matched allocator wrapper.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeDGFSub10
{
	void Init();
	void *vtbl;
	int a;
	int b;
	int c;
};

struct BfmeDGFArg
{
	void Init(void *sub4);
};

class BfmeThingDGF
{
public:
	BfmeThingDGF *bfmeInitDGF(void *arg);

private:
	void *_vtbl;
	void *_sub4;
	int _a;
	int _b;
	BfmeDGFSub10 _sub10;
	int _e;
	char _f;
	int _g;
	int _h;
};

BfmeThingDGF *BfmeThingDGF::bfmeInitDGF(void *arg)
{
	void **p4 = &_sub4;
	BfmeDGFSub10 *p10 = &_sub10;
	*p4 = (void *)0x00C1C780;
	_ReadWriteBarrier();
	_vtbl = (void *)0x00CE30B8;
	*p4 = (void *)0x00CE30B4;
	p10->Init();
	p10->vtbl = (void *)0x00CE0F20;
	p10->a = 0;
	p10->b = 0;
	p10->c = 0;
	_a = 0;
	_b = 0;
	_e = 0;
	_f = 0;
	_g = 0;
	_h = 0;
	((BfmeDGFArg *)arg)->Init(p4);
	return this;
}
