// cl: /DNDEBUG /MD /EHsc
// ??1Rva00109610@@UAE@XZ @0x00109610 51B
// Derived dtor sets derived vtable 0x007CFA00 calls rowed base
// W3DProjectedShadow::rva00108951 on same this then restores base vtable
// 0x007CEFA0; caller is ??_G at 0x0010BA83; chain from 0x00108951.
class W3DProjectedShadow
{
public:
	virtual ~W3DProjectedShadow() {}
	void rva00108951();
};
class Rva00109610 : public W3DProjectedShadow
{
public:
	virtual ~Rva00109610();
};
Rva00109610::~Rva00109610()
{
	rva00108951();
}
