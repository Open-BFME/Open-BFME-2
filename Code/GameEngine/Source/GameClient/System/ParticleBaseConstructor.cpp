// Native1F4B63..1F4C67: complete260B base particle constructor.
// BF1 ParticleConstructor.cpp at donor874e38488c7d supplies the semantic
// field-order guide. Retail and matched Rva001F4C67 destructor separately
// establish the intrusive handles at3C and78 (the old bank called78 Vec12).
// The existing vtable/dtor owner provides this honest address-derived class
// name. The complete original Particle identity is not asserted here.
// cl: /O1 /MD /arch:SSE /EHsc
// ??0Rva001F4C67@@QAE@ABVRvaSmartPtr12@@ABVRva001F376E@@@Z, RVA 0x001F4B63, 260B.
// Chain lane: calls 0x001F376E just landed. Base Rva001F376E at +0x0, SmartPtr at +0x3C,
// floats/ints copied from second arg, GameClient slot 0x7c to +0x58, manager insert,
// ParticleSystem slot 0x7c and helper slot 0x14. Evidence: vtable 0x007E173C,
// TheGameClient/TheParticleSystemManager globals, Make pin, Rva001F416C row.
struct Vec12
{
	float x;
	float y;
	float z;
};
class Rva001F376E
{
public:
	Rva001F376E();
	virtual ~Rva001F376E();
	float m_04;
	float m_08;
	float m_0c;
	Vec12 m_10;
	Vec12 m_1c;
	Vec12 m_28;
	int m_34;
	unsigned char m_38;
	char m_pad39[3];
};
class BfmeParticleSystemHandle {public:~BfmeParticleSystemHandle()throw();};
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12
{
public:
  ParticleSystem *operator->()const{return m_ptr?(ParticleSystem*)m_ptr:Make001FCBD7();}
 RvaSmartPtr12() { m_ptr = 0; m_pad04 = 0; m_pad08 = 0; }
  RvaSmartPtr12(const RvaSmartPtr12 &that);
  RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
 ~RvaSmartPtr12() throw() {if(m_ptr)((BfmeParticleSystemHandle*)this)->BfmeParticleSystemHandle::~BfmeParticleSystemHandle();}
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class ClientFrameSubsystem
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual int s31();
};
extern ClientFrameSubsystem *TheGameClient;
class ParticleSystem;
class Rva001F4C67;
class HelperA4
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5(Rva001F4C67 *p);
};
class ParticleSystem
{
public:
	char m_pad00[0x7c];
	int m_7c;
	char m_pad80[0x24];
	HelperA4 *m_a4;
};
extern ParticleSystem *Make001FCBD7();
class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;
struct Node001F416C
{
	char m_pad[0x6c];
	Node001F416C *m_prev;
	Node001F416C *m_next;
	char m_gap;
	unsigned char m_flag;
};
class Rva001F416C
{
public:
	void rva001F416C(Node001F416C *node, int slot);
	char m_pad0[0x10];
	Node001F416C *m_arr1[7];
	Node001F416C *m_arr2[9];
	int m_count;
};
class Rva001F4C67 : public Rva001F376E
{
public:
	Rva001F4C67(const RvaSmartPtr12 &a, const Rva001F376E &b);
	RvaSmartPtr12 m_smart;
	Vec12 m_48;
	int m_54;
	int m_58;
	int m_5c;
	unsigned char m_60;
	char m_pad61[3];
	int m_64;
	int m_68;
	void *m_6c;
	void *m_70;
	unsigned char m_74;
	unsigned char m_75;
	char m_pad76[2];
	RvaSmartPtr12 m_78;
	int m_84;
};
// ??0Rva001F4C67@@QAE@ABVRvaSmartPtr12@@ABVRva001F376E@@@Z
Rva001F4C67::Rva001F4C67(const RvaSmartPtr12 &a, const Rva001F376E &b)
	: m_5c(1)
{
	m_84 = 0;
	m_smart = a;
	m_60 = 0;
	m_10 = b.m_10;
	m_1c = b.m_1c;
	m_48.x = 0.0f;
	m_48.y = 0.0f;
	m_48.z = 0.0f;
	m_38 = b.m_38;
	m_28 = b.m_28;
	m_34 = b.m_34;
	m_54 = b.m_34;
	m_58 = TheGameClient->s31();
	m_75 = 0;
	m_74 = 0;
	m_6c = 0;
	m_70 = 0;
	m_64 = 0;
	m_68 = 0;
	ParticleSystem *ps = (ParticleSystem *)a.m_ptr;
	if (ps == 0)
		ps = Make001FCBD7();
	((Rva001F416C *)TheParticleSystemManager)->rva001F416C((Node001F416C *)this, ps->m_7c);
	m_smart->m_a4->f5(this);
}
