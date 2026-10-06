// cl: /MD
// ??1Rva00367F8D@@UAE@XZ @0x00367F8D 11B
// Empty virtual dtor storing vtable 0x00817768 then tail-jmp to rowed base
// ??1Rva00542C19@@UAE@XZ @0x00542C19 (itself child of pinned Rva004D759C).
// Evidence: retail mov [ecx],0x00817768 plus jmp to 0x542C19; deleting dtor
// 0x00368B35 calls here then conditional delete (28B ??_G shape) unlocking on landing.
// Owner unproven so honest address class name used.
class Rva00542C19
{
public:
	virtual ~Rva00542C19();
};
class Rva00367F8D : public Rva00542C19
{
public:
	virtual ~Rva00367F8D();
};
Rva00367F8D::~Rva00367F8D()
{
}
