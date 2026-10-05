// cl: /O1 /MD
//
// ?rva00330BDB@Rva00330BDB@@QBEMXZ retail 0x00330BDB 8B this-adjusting
// forwarder: this-0x34 then tail-jmp to rowed Rva0030B719Shape::rva0030B706
// 0x0030B706 float at +0x1C. Callers tail-jmp here; same adjustor family as
// the 0x00330C22 this-0x3C center forwarder. Honest address names.

typedef float Real;

class Rva0030B719Shape
{
public:
	Real rva0030B706() const;
};

class Rva00330BDB
{
public:
	Real rva00330BDB() const;
};

Real Rva00330BDB::rva00330BDB() const
{
	const Rva0030B719Shape *shape = (const Rva0030B719Shape *)((const char *)this - 0x34);
	return shape->rva0030B706();
}
