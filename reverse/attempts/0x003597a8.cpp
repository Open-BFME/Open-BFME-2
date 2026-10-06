// ?rva003597A8@Rva003597A8@@QAEXHH@Z
// partial score=0.89 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva003597A8@Rva003597A8@@QAEXHH@Z @0x003597A8 26B.
// Void this-plus-0x24 forwarder (thiscall, int plus int): adjusts this by
// 0x24, routes (id, &flag) through the pinned 0x596AD factory returning an
// opaque taker, then invokes the pinned 0-arg 0x2174A4 on it. Frameless;
// both callees ride address-derived pins (0x2174A4 shares its address with
// a rowed assignment operator).
class Rva002174A4Taker
{
public:
	void rva002174A4();
};

class Rva003596AD
{
public:
	void *rva003596AD(int a1, int *a2);
};

class Rva003597A8
{
public:
	void rva003597A8(int a1, int a2);
};

void Rva003597A8::rva003597A8(int a1, int a2)
{
	void *t = ((Rva003596AD *)((char *)this + 0x24))->rva003596AD(a1, &a2);
	((Rva002174A4Taker *)t)->rva002174A4();
}
