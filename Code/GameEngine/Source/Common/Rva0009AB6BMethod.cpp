// cl: /MD
// ?rva0009AB6B@Rva0009AB6B@@QAEXXZ @0x0009AB6B 26B
// Chain method: rowed Reset 0x002BFD6F then virtuals at +0x1C and +0x28 with 0.
// Evidence: calls 0x002BFD6F which just landed; callees rowed/pinned; prev/next neighbours.
class Rva002BFD6F
{
public:
	void rva002BFD6F();
};

// Native9AB85..9AC04 is a complete127-byte no-argument member.
// Target facts only: rendererC4 vslot0C detaches holdersD4/188; each
// holderD4/188/1CC then releases reference word4 and invokes slot0 at zero.
// Original class/type names and unused virtual slots remain unknown.
class Rva0009AB85Ref {public:virtual void dispose();int references04;};
struct Rva0009AB85Holder {
    Rva0009AB85Ref *ptr;
    __forceinline void clear() {
        Rva0009AB85Ref *p=ptr;
        if(p) {if(--p->references04==0)p->dispose();ptr=0;}
    }
};
class Rva0009AB85Renderer {
public:
    virtual void slot0();virtual void slot1();virtual void slot2();
    virtual void remove(Rva0009AB85Ref *);
};

class Rva0009AB6B
{
public:
	void rva0009AB6B();
	void rva0009AB85();
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
private:
    char pad04[0xC4-4];
    Rva0009AB85Renderer *rendererC4;
    char padC8[0xD4-0xC8];
    Rva0009AB85Holder firstD4;
    char padD8[0x188-0xD8];
    Rva0009AB85Holder second188;
    char pad18C[0x1CC-0x18C];
    Rva0009AB85Holder third1CC;
};

void Rva0009AB6B::rva0009AB6B()
{
	((Rva002BFD6F *)this)->rva002BFD6F();
	f_1C();
	f_28(0);
}

// ?rva0009AB85@Rva0009AB6B@@QAEXXZ
void Rva0009AB6B::rva0009AB85()
{
    if(Rva0009AB85Renderer *r=rendererC4) {
        if(firstD4.ptr)r->remove(firstD4.ptr);
        if(second188.ptr)rendererC4->remove(second188.ptr);
    }
    firstD4.clear();second188.clear();third1CC.clear();
}
