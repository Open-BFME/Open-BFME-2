// cl: /DNDEBUG /MD /EHs
// ??0Rva0056224F@@QAE@XZ @0x0056224F 87B: frameless ctor storing vtable
// 0x81D358, 1.0f at +0x4/+0x8/+0xC via 0x7BB8D8, 0.0f at +0x10..+0x30,
// 1 at +0x34. Called once from 0x562389. The unwind map of that caller names
// this class: its state 1 destroys the +0xC subobject through
// ??1BoxEmissionVolumeInfo@FXParticleSystem@@UAE@XZ, so this is the
// BoxEmissionVolumeInfo default ctor under its placeholder name.
//
// ??0Rva00562366@@QAE@IAAUSrc00562366@@@Z @0x00562366 376B, caller
// 0x003ACAC1 (twin of 0x005646BC): the emitter built from a Src00562366
// template block. Target evidence (unwind map at 0x00B99C46): state 0
// destroys the +0 parent through the24B Rva003AE13C cleanup fold; the
// parent Rva003ADFDB includes interface+8 and has uint ctor0x0055F821.
// The two neutral class names need not denote the same class. State1 destroys the
// +0xC base through the BoxEmissionVolumeInfo dtor, state 2 destroys the
// 12-byte RvaSmartPtr12 temporary at [ebp-0x1C] through the rowed 0x002115C5,
// whose body is `cmp [ecx],0 / je / jmp 0x0004CBC0`: the handle dtor is the
// inline `if (m_ptr) rva0004CBC0()` and 0x0004CBC0 (rowed as
// ??1BfmeParticleSystemHandle, the same handle under its other placeholder)
// is its non-null tail, pinned here under this class. The three vtables the
// ctor installs (0x00C1D31C at +0, 0x00C1C780 at +8, 0x00C1D348 at +0xC) are
// this class's tables for its three bases; the +8 base is an interface with
// no data (novtable, so only the derived ctor writes it); the twelve floats
// and the int at +0x10..+0x40 are the +0xC base's members. Structural
// inference: the getter and the handle dtor are throw() -- with them nothrow
// cl drops the state-1 store (nothing can throw before state 2) and the
// state restore before the final release, exactly as retail; the twelve
// GameClientRandomVariable fields of the source block are read in retail
// order and the ParticleSystem values come from the handle's pointee or the
// fallback Make001FCBD7.
class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

class ParticleSystem;

class __declspec(novtable) Rva003ADFDBPrimary {public:virtual ~Rva003ADFDBPrimary();private:unsigned argument4;};
class __declspec(novtable) Iface00C1C780 {public:virtual void slot00()=0;};
class __declspec(novtable) Rva003ADFDB:public Rva003ADFDBPrimary,public Iface00C1C780 {public:Rva003ADFDB(unsigned);virtual ~Rva003ADFDB();};

class Rva0056224F
{
public:
	Rva0056224F();
	virtual ~Rva0056224F();

protected:
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	int m_34;
};

Rva0056224F::Rva0056224F()
{
	m_04 = 1.0f;
	m_08 = 1.0f;
	m_0C = 1.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_30 = 0.0f;
	m_34 = 1;
}

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle() throw();
	void *m_system;
	void *m_prev;
	void *m_next;
};

class RvaSmartPtr12
{
public:
	~RvaSmartPtr12() throw()
	{
		BfmeParticleSystemHandle *p = (BfmeParticleSystemHandle *)this;
		if (p->m_system != 0)
			p->~BfmeParticleSystemHandle();
	}
	ParticleSystem *m_ptr;
	int m_04;
	int m_08;
};

class Rva0055DDB6SmartField
{
public:
	RvaSmartPtr12 get() const throw();
};

ParticleSystem *Make001FCBD7();

struct Src00562366
{
	char m_00[0x20];
	GameClientRandomVariable m_20;
	GameClientRandomVariable m_2C;
	GameClientRandomVariable m_38;
	GameClientRandomVariable m_44;
	GameClientRandomVariable m_50;
	GameClientRandomVariable m_5C;
	GameClientRandomVariable m_68;
	GameClientRandomVariable m_74;
	GameClientRandomVariable m_80;
	GameClientRandomVariable m_8C;
	GameClientRandomVariable m_98;
	GameClientRandomVariable m_A4;
	int m_B0;
};

// ParticleSystem fields read: +0x180 and +0x184 (floats).
struct ParticleSystemView
{
	char m_000[0x180];
	float m_180;
	float m_184;
};

class Rva00562366 : public Rva003ADFDB, public Rva0056224F
{
public:
	Rva00562366(unsigned int a, Src00562366 &src);
	virtual ~Rva00562366();
	virtual void slot00();
};

// The twelve floats and the int the ctor fills (+0x10..+0x40) are the
// BoxEmissionVolumeInfo base's own members (+4..+0x34 of the +0xC subobject),
// first set by its ctor and then overwritten from the template block.
Rva00562366::Rva00562366(unsigned int a, Src00562366 &src)
	: Rva003ADFDB(a)
{
	RvaSmartPtr12 smart = ((Rva0055DDB6SmartField *)&src)->get();
	float v20 = src.m_20.getValue();
	m_04 = v20;
	ParticleSystem *ps = smart.m_ptr;
	if (!ps)
		ps = Make001FCBD7();
	float mul = ((ParticleSystemView *)ps)->m_184;
	float v2C = src.m_2C.getValue();
	m_08 = v2C * mul;
	m_0C = src.m_38.getValue();
	m_10 = src.m_44.getValue();
	m_14 = src.m_50.getValue();
	m_18 = src.m_5C.getValue();
	m_1C = src.m_68.getValue();
	m_20 = src.m_74.getValue();
	m_24 = src.m_80.getValue();
	ParticleSystem *pa = smart.m_ptr;
	if (!pa)
		pa = Make001FCBD7();
	float add0 = ((ParticleSystemView *)pa)->m_180;
	m_04 += add0;
	ParticleSystem *pb = smart.m_ptr;
	if (!pb)
		pb = Make001FCBD7();
	float add1 = ((ParticleSystemView *)pb)->m_180;
	m_08 += add1;
	ParticleSystem *pc = smart.m_ptr;
	if (!pc)
		pc = Make001FCBD7();
	float add2 = ((ParticleSystemView *)pc)->m_180;
	m_0C += add2;
	m_28 = src.m_8C.getValue();
	m_2C = src.m_98.getValue();
	m_30 = src.m_A4.getValue();
	m_34 = src.m_B0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot00@Rva00562366@@UAEXXZ=__purecall")
