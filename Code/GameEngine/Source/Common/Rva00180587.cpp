// cl: /MD
//
// ?rva00180587@Rva001805E0@@QAEPAVParticleEmitterClass@@XZ retail 0x00180587
// 39 bytes. Vslot 15 of Rva001805E0 calling slots 0x28 bool and 0x2C void
// on this then creating via rowed ParticleEmitterClass Create_From_Definition
// from Def at +0x14 or null. Evidence is vtable 0x7D4FD0 plus member layout
// plus rowed callee.

class ParticleEmitterDefClass;
class ParticleEmitterClass
{
public:
	static ParticleEmitterClass *Create_From_Definition(const ParticleEmitterDefClass &def);
};

class Rva0061ED80
{
public:
	virtual ~Rva0061ED80();
};

class Rva001805E0 : public Rva0061ED80
{
public:
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual bool IsReady();
	virtual void Prime();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual ParticleEmitterClass *rva00180587();

private:
	char m_pad04[0x10];
	ParticleEmitterDefClass *m_14;
};

ParticleEmitterClass *Rva001805E0::rva00180587()
{
	if (!IsReady())
		Prime();
	ParticleEmitterDefClass *def = m_14;
	if (def == 0)
		return 0;
	return ParticleEmitterClass::Create_From_Definition(*def);
}
