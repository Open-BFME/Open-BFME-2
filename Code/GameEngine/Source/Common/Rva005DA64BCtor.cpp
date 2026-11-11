// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva005DA64B@@QAE@PAX@Z, retail 0x005DA64B, 24 bytes.
// Derived holder: forwards void* to rowed base Rva005DAA36 ctor at 0x005DAA36
// then stores vtable 0x008765A0. Evidence: call plus vtable store;
// caller 0x0059726E. Base declared only here so the call stays out-of-line
// and `this` is kept in esi, as retail.

class Rva005DAA36
{
public:
	Rva005DAA36(void *held);
	// Same base view as V3PolyCopyCtors.cpp: retail base vftable 0x00C70B80
	// is __purecall then the deleting dtor (inline vptr-reset dtor).
	virtual int f0(int) = 0;
	virtual ~Rva005DAA36() {}

	void *m_field04;
};

class Rva005DA64B : public Rva005DAA36
{
public:
	Rva005DA64B(void *held);
	// Inline like the base: retail's deleting dtor (0x005DA663) only resets
	// the vptrs before delete; no out-of-line ~Rva005DA64B exists.
	virtual int f0(int) { return 0; }
	virtual ~Rva005DA64B() {}
};

Rva005DA64B::Rva005DA64B(void *held)
	: Rva005DAA36(held)
{
}
