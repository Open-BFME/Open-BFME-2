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

extern "C" char __identifier("??_7Rva003ADEFB@@6BV3Vt01111D90@@@");
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
extern "C" char __identifier("??_7Rva003ADEFB@@6B@");

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
		m_vtable00 = &__identifier("??_7Rva003ADEFB@@6BV3Vt01111D90@@@");
		m_vtable08 = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$01@1@@");
		m_vtable0C = &__identifier("??_7Rva003ADEFB@@6B@");
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

// Retail tables 0x00C1C954 (6 slots, +0) and 0x00C1C940 (4 slots, +0x0C), stored by
// the inline Rva003AC93EModule constructor below. Own the complete initialized
// tables instead of zero-int stand-ins (Rva004DF324Dtor.cpp s_10 precedent): each
// slot names a matched row at retail's slot target, taken by address and never
// called through these erased signatures. 0x00C1C940's first word reads as the
// string "HZz"; it is the +0x0C table (slot 0 the -0x0C deleting adjustor).
extern "C" {
void __identifier("??_GRva003ADFB2@@UAEPAXI@Z")();
void __identifier("?rva0055BA3D@Rva0055B9BDView@@QAEXXZ")();
void __identifier("?make@U4Maker005EA530@@QAEPAVU4Made005EA530@@XZ")();
void __identifier("?rva0055BB5C@Rva0055BB5C@@UAEXPAVXfer@@@Z")();
void __identifier("?rva0055BBAE@Rva003ADFB2@@QAE_NH@Z")();
void __identifier("?get@Rva003AC99ALeaGetter@@QBEPAXXZ")();
void __identifier("??_ERva003ADFB2@@WM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003AC9A1Get@@YAHXZ")();
void __identifier("?rva0055BB5C@Rva0055BB5C@@WM@AEXPAVXfer@@@Z")();
}
static const void *const s_vt93E_00[6] = {
	(const void *)&__identifier("??_GRva003ADFB2@@UAEPAXI@Z"), //  0 0x003AE270
	(const void *)&__identifier("?rva0055BA3D@Rva0055B9BDView@@QAEXXZ"), //  1 0x0055BA3D
	(const void *)&__identifier("?make@U4Maker005EA530@@QAEPAVU4Made005EA530@@XZ"), //  2 0x003ADCEB
	(const void *)&__identifier("?rva0055BB5C@Rva0055BB5C@@UAEXPAVXfer@@@Z"), //  3 0x0055BB5C
	(const void *)&__identifier("?rva0055BBAE@Rva003ADFB2@@QAE_NH@Z"), //  4 0x0055BBAE
	(const void *)&__identifier("?get@Rva003AC99ALeaGetter@@QBEPAXXZ")  //  5 0x003AC99A
};
static const void *const s_vt93E_0C[4] = {
	(const void *)&__identifier("??_ERva003ADFB2@@WM@AEPAXI@Z"), //  0 0x003A5A48
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003AC9A1Get@@YAHXZ"), //  2 0x003AC9A1
	(const void *)&__identifier("?rva0055BB5C@Rva0055BB5C@@WM@AEXPAVXfer@@@Z")  //  3 0x003AC9A7
};
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$0A@@1@@");
// Retail 0x00C1CA04/0x00C1C9F0 and 0x00C1CED8/0x00C1CEC8 are the tables the rowed
// copy constructors 0x003AE0AF and 0x003AE017 store and own complete (their
// units, Rva003AE0AFCopyCtor.cpp and Rva003AE017CopyCtor.cpp): store those.
extern "C" const void *const Rva003AE0AF_v0[4];
extern "C" const void *const Rva003AE0AF_v10[4];
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$07@1@@");
extern "C" const void *const Rva003AE017_v0[4];
extern "C" const void *const Rva003AE017_v0C[4];
extern "C" char __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$06@1@@");

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
		m_vtable00 = s_vt93E_00;
		m_vtable08 = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$0A@@1@@");
		m_vtable0C = s_vt93E_0C;
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
		m_vtable00 = Rva003AE0AF_v0;
		m_vtable08 = &__identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$07@1@@");
		m_vtable10 = Rva003AE0AF_v10;
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
		m_vtable00 = Rva003AE017_v0;
		m_vtable08 = &__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$06@1@@");
		m_vtable0C = Rva003AE017_v0C;
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
