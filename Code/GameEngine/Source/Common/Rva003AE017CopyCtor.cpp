// cl: /DNDEBUG /MD /EHsc
// ??0Rva003AE017@@QAE@ABV0@@Z, retail 0x003AE017, 38 bytes.
// Derived V3-inline copy: calls rowed base ??0Rva003AE03D@@QAE@ABV0@@Z at
// 0x003AE03D then installs its own three vftables (+0 0x00C1CED8,
// +8 0x00C1BFB4, +0x0C 0x00C1CEC8). Caller is 0x003AE00C. Same 38B shape as
// rowed 0x003AE1A7. Vtable dwords are DIR32 sites the gate takes from target.

class Rva003AE03D
{
public:
	Rva003AE03D(const Rva003AE03D &other);
};

// Rva003AE017_v0: matched references place it at VA 0xc1ced8 (retail .rdata value 112).
extern "C" char Rva003AE017_v0 = 112;
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@");
// Rva003AE017_v0C: matched references place it at VA 0xc1cec8 (retail .rdata value 72).
extern "C" char Rva003AE017_v0C = 72;

// The class the constructor 0x003A59C3 builds (tables 0x00C1B5E0, 0x00C1C780,
// 0x00C1B5D0). This class's primary table 0x00C1CED8 is that class's with
// slot 2, pure there, filled by the clone 0x003ADFFA, so it is the base;
// its copy constructor is the rowed 0x003AE03D.
class Rva003A59C3
{
private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
	void *m_v0C;
};

class Rva003AE017 : public Rva003A59C3
{
public:
	__declspec(noinline) Rva003AE017(const Rva003AE017 &other);
};

Rva003AE017::Rva003AE017(const Rva003AE017 &that)
{
	const void *src = &that;
	((Rva003AE03D *)this)->Rva003AE03D::Rva003AE03D(*(const Rva003AE03D *)src);
	*(void **)this = &Rva003AE017_v0;
	*(void **)((char *)this + 8) = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@");
	*(void **)((char *)this + 0x0C) = &Rva003AE017_v0C;
}
