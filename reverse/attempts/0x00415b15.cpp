// ?wrap@Rva00415B15Host@@QAEHXZ
// partial score=0.88 date=2026-10-06
// cl: /O1 /MD
// ?wrap@Rva00415B15Host@@QAEHXZ @0x00415B15 25B: wrapper calling rowed
// init 0x004152BC with two pointers to one stack byte. Returns this.
class Rva004152BCHost
{
public:
	int init(int a, int b);
};
class Rva00415B15Host
{
public:
	int wrap();
};
int Rva00415B15Host::wrap()
{
	union { char a; char b; } u;
	Rva004152BCHost *self = (Rva004152BCHost *)this;
	self->init((int)&u.a, (int)&u.b);
	return (int)this;
}
