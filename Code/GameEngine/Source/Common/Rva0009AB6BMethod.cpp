// cl: /O1 /MD
// ?rva0009AB6B@Rva0009AB6B@@QAEXXZ @0x0009AB6B 26B
// Chain method: rowed Reset 0x002BFD6F then virtuals at +0x1C and +0x28 with 0.
// Evidence: calls 0x002BFD6F which just landed; callees rowed/pinned; prev/next neighbours.
class Rva002BFD6F
{
public:
	void rva002BFD6F();
};

class Rva0009AB6B
{
public:
	void rva0009AB6B();
	virtual void _0();
	virtual void _1();
	virtual void _2();
	virtual void _3();
	virtual void _4();
	virtual void _5();
	virtual void _6();
	virtual void f_1C();
	virtual void _8();
	virtual void _9();
	virtual void f_28(int v);
};

void Rva0009AB6B::rva0009AB6B()
{
	((Rva002BFD6F *)this)->rva002BFD6F();
	f_1C();
	f_28(0);
}
