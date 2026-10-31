// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva003AC9AF@Rva003AC9AFTemplate@@UAEPAVRva003AC9AFModule@@I@Z, retail
// 0x003AC9AF (89 bytes, RET 4): the module factory slot of an FX particle
// module template, reached through the template's +0x14 interface. It
// allocates the 0x38-byte module, runs the rowed module constructor
// 0x0055F840 with the argument and the template, and installs the derived
// module's three vtables (0x00C1C9A0 at +0, 0x00C1BF80 at +8, 0x00C1C990 at
// +0x0C). The derived constructor is inline, so its vtable stores are
// written as explicit members with TU-local stand-ins (as in
// DeployStyleAIUpdateCtor.cpp); nothing here emits a vtable.
//
// The same factory for three sibling templates:
// ?CreateModule@Rva003AC93ETemplate@@UAEPAVRva003AC93EModule@@I@Z, retail
// 0x003AC93E (92 bytes): 0xB0-byte module over the rowed 0x0055BCF1
// (template passed by pointer), vtables 0x00C1C954/0x00C1C950/0x00C1C940.
// ?rva003ACA24@Rva003ACA24Template@@UAEPAVRva003ACA24Module@@I@Z, retail
// 0x003ACA24 (89 bytes): 0x20-byte module over the rowed 0x0056413D,
// vtables at +0/+8/+0x10.
// ?rva003AD03B@Rva003AD03BTemplate@@UAEPAVRva003AD03BModule@@I@Z, retail
// 0x003AD03B (89 bytes): 0x14-byte module over the rowed 0x003A59C3
// (Rva003A59C3Ctor.cpp), vtables 0x00C1CED8/0x00C1BFB4/0x00C1CEC8.
struct Src0055F840;

static int s_vtable00;
static int s_vtable08;
static int s_vtable0C;

class Rva003ADFB2
{
public:
	Rva003ADFB2(unsigned int arg, Src0055F840 &src);
protected:
	const void *m_vtable00;		// +0x00
	unsigned char m_pad04[4];
	const void *m_vtable08;		// +0x08
	const void *m_vtable0C;		// +0x0C
	unsigned char m_pad10[0x38 - 0x10];
};

class Rva003AC9AFModule : public Rva003ADFB2
{
public:
	__forceinline Rva003AC9AFModule(unsigned int arg, Src0055F840 &src)
		: Rva003ADFB2(arg, src)
	{
		m_vtable00 = &s_vtable00;
		m_vtable08 = &s_vtable08;
		m_vtable0C = &s_vtable0C;
	}
};

class Rva003AC9AFPrimary
{
public:
	virtual void p00();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva003AC9AFFactory
{
public:
	virtual Rva003AC9AFModule *rva003AC9AF(unsigned int arg) = 0;
};

class Rva003AC9AFTemplate : public Rva003AC9AFPrimary, public Rva003AC9AFFactory
{
public:
	virtual Rva003AC9AFModule *rva003AC9AF(unsigned int arg);
};

Rva003AC9AFModule *Rva003AC9AFTemplate::rva003AC9AF(unsigned int arg)
{
	return new Rva003AC9AFModule(arg, *(Src0055F840 *)this);
}

struct ColorModuleTemplate;
struct LifeInput413D;
struct Rva003A59C3Src;

static int s_vt93E_00, s_vt93E_08, s_vt93E_0C;
static int s_vtA24_00, s_vtA24_08, s_vtA24_10;
static int s_vtD03B_00, s_vtD03B_08, s_vtD03B_0C;

class Rva0055BCF1
{
public:
	Rva0055BCF1(unsigned int arg, const ColorModuleTemplate *src);
protected:
	const void *m_vtable00;
	unsigned char m_pad04[4];
	const void *m_vtable08;
	const void *m_vtable0C;
	unsigned char m_pad10[0xB0 - 0x10];
};
class Rva003AC93EModule : public Rva0055BCF1
{
public:
	__forceinline Rva003AC93EModule(unsigned int arg, const ColorModuleTemplate *src)
		: Rva0055BCF1(arg, src)
	{
		m_vtable00 = &s_vt93E_00;
		m_vtable08 = &s_vt93E_08;
		m_vtable0C = &s_vt93E_0C;
	}
};
class Rva003AC93EFactory
{
public:
	virtual Rva003AC93EModule *CreateModule(unsigned int arg) = 0;
};
class Rva003AC93ETemplate : public Rva003AC9AFPrimary, public Rva003AC93EFactory
{
public:
	virtual Rva003AC93EModule *CreateModule(unsigned int arg);
};
Rva003AC93EModule *Rva003AC93ETemplate::CreateModule(unsigned int arg)
{
	return new Rva003AC93EModule(arg, (const ColorModuleTemplate *)this);
}

class Rva003AE0D5
{
public:
	Rva003AE0D5(unsigned int arg, LifeInput413D &src);
protected:
	const void *m_vtable00;
	unsigned char m_pad04[4];
	const void *m_vtable08;
	unsigned char m_pad0C[4];
	const void *m_vtable10;
	unsigned char m_pad14[0x20 - 0x14];
};
class Rva003ACA24Module : public Rva003AE0D5
{
public:
	__forceinline Rva003ACA24Module(unsigned int arg, LifeInput413D &src)
		: Rva003AE0D5(arg, src)
	{
		m_vtable00 = &s_vtA24_00;
		m_vtable08 = &s_vtA24_08;
		m_vtable10 = &s_vtA24_10;
	}
};
class Rva003ACA24Factory
{
public:
	virtual Rva003ACA24Module *rva003ACA24(unsigned int arg) = 0;
};
class Rva003ACA24Template : public Rva003AC9AFPrimary, public Rva003ACA24Factory
{
public:
	virtual Rva003ACA24Module *rva003ACA24(unsigned int arg);
};
Rva003ACA24Module *Rva003ACA24Template::rva003ACA24(unsigned int arg)
{
	return new Rva003ACA24Module(arg, *(LifeInput413D *)this);
}

class Rva003A59C3
{
public:
	Rva003A59C3(unsigned int arg, Rva003A59C3Src &src);
protected:
	const void *m_vtable00;
	unsigned char m_pad04[4];
	const void *m_vtable08;
	const void *m_vtable0C;
	unsigned char m_pad10[0x14 - 0x10];
};
class Rva003AD03BModule : public Rva003A59C3
{
public:
	__forceinline Rva003AD03BModule(unsigned int arg, Rva003A59C3Src &src)
		: Rva003A59C3(arg, src)
	{
		m_vtable00 = &s_vtD03B_00;
		m_vtable08 = &s_vtD03B_08;
		m_vtable0C = &s_vtD03B_0C;
	}
};
class Rva003AD03BFactory
{
public:
	virtual Rva003AD03BModule *rva003AD03B(unsigned int arg) = 0;
};
class Rva003AD03BTemplate : public Rva003AC9AFPrimary, public Rva003AD03BFactory
{
public:
	virtual Rva003AD03BModule *rva003AD03B(unsigned int arg);
};
Rva003AD03BModule *Rva003AD03BTemplate::rva003AD03B(unsigned int arg)
{
	return new Rva003AD03BModule(arg, *(Rva003A59C3Src *)this);
}

class DefaultModuleSecondBase { public: virtual Rva003AC9AFModule *rva003AC9AF(unsigned int); };
Rva003AC9AFModule *DefaultModuleSecondBase::rva003AC9AF(unsigned int arg) {
 return new Rva003AC9AFModule(arg, *reinterpret_cast<Src0055F840 *>((char *)this-0x14));
}
