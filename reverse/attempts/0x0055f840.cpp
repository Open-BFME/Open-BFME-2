// ??0Rva0055F840@@QAE@IAAUSrc0055F840@@@Z
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/moduledata
// ??0Rva0055F72C@@QAE@XZ @0x0056224F 87B: frameless ctor storing vtable
// 0x81D358, 1.0f at +0x4/+0x8/+0xC via 0x7BB8D8, 0.0f at +0x10..+0x30,
// 1 at +0x34. Called once from 0x562389. The unwind map of that caller names
// this class: its state 1 destroys the +0xC subobject through
// ??1BoxEmissionVolumeInfo@FXParticleSystem@@UAE@XZ, so this is the
// BoxEmissionVolumeInfo default ctor under its placeholder name.
//
// ??0Rva00562366@@QAE@IAAUSrc00562366@@@Z @0x00562366 376B, caller
// 0x003ACAC1 (twin of 0x005646BC): the emitter built from a Src00562366
// template block. Target evidence (unwind map at 0x00B99C46): state 0
// destroys the +0 base (??1Rva003AE13C, the Rva003ADFDB class under another
// placeholder; its uint ctor is the rowed 0x0055F821), state 1 destroys the
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
#include "Common/Snapshot.h"
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

class __declspec(novtable) Rva003AE13C {public:virtual ~Rva003AE13C();private:unsigned word4;};
class __declspec(novtable) Rva003ADFDB:public Rva003AE13C {public:Rva003ADFDB(unsigned);virtual __forceinline ~Rva003ADFDB() {}};

class __declspec(novtable) Iface00C1C780
{
public:
	virtual void slot00() = 0;
};

class Rva0055F72C:public Snapshot
{
public:
	Rva0055F72C();
	virtual ~Rva0055F72C() {}

protected:
 float m_04,m_08,m_0C,m_10,m_14,m_18;int m_1C;float m_20,m_24,m_28;
};

Rva0055F72C::Rva0055F72C():m_04(0),m_08(0),m_0C(0),m_10(0),m_14(0),m_18(0),m_1C(1),m_20(0),m_24(0),m_28(0){}
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

struct Src0055F840 {char prefix[0x20];GameClientRandomVariable var20,var2C,var38,var44,var50;int kind5C;GameClientRandomVariable var60,var6C,var78;};
struct ParticleView330 {char pad[0x28];GameClientRandomVariable initial;char tail[0x17C-0x34];float multiplier,offset;};
class GlobalData {public:char prefix[0x9EC];float particleScale;};extern GlobalData*TheWritableGlobalData;
class Rva0055F840:public Rva003ADFDB,public Iface00C1C780,public Rva0055F72C {public:Rva0055F840(unsigned,Src0055F840&);virtual~Rva0055F840();virtual void slot00()=0;};
Rva0055F840::Rva0055F840(unsigned a,Src0055F840&src):Rva003ADFDB(a){
 RvaSmartPtr12 smart=((Rva0055DDB6SmartField*)&src)->get();
 ParticleSystem*ps=smart.m_ptr;if(!ps)ps=Make001FCBD7();
 ParticleSystem*pf=smart.m_ptr;if(!pf)pf=Make001FCBD7();
 float multiplier=((ParticleView330*)pf)->multiplier;
 m_04=((ParticleView330*)ps)->initial.getValue()*TheWritableGlobalData->particleScale*multiplier;
 ParticleSystem*py=smart.m_ptr;if(!py)py=Make001FCBD7();
 multiplier=((ParticleView330*)py)->multiplier;
 m_08=src.var20.getValue()*TheWritableGlobalData->particleScale*multiplier;
 m_0C=src.var2C.getValue();
 ParticleSystem*pa=smart.m_ptr;if(!pa)pa=Make001FCBD7();m_04+=((ParticleView330*)pa)->offset;
 m_10=src.var38.getValue();m_14=src.var44.getValue();m_18=src.var50.getValue();m_1C=src.kind5C;m_20=src.var60.getValue();m_24=src.var6C.getValue();m_28=src.var78.getValue();
}
