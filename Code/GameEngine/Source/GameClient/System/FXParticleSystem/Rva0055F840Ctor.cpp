// Target55F840..55F98A RET8; BFME1 default-update family is the reference lead.
// C1D31C slot0=3AE270 and C1D348 slot0=3A5A48 bind this to existing
// Rva003ADFB2 destructor41 and deleting lifetime28/8. Native parent12 includes
// interface+8; info44 at+C and parameter/random-variable offsets are target facts.
// Primary/secondary decomposition is a local structural view, not an original name.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/moduledata
// Native cleanup states: parent+0 ->24B3A583E; info+C ->7B49B47C;
// owned12B handle temporary ->11B2115C5. All three providers are measured folds.
// BFME1 f98983a7d game/GameEngine/Source/GameClient/System/FXParticleSystem/
// DefaultModule2CtorThunk.cpp supplies the related default-update source-record
// lead; target sampling calls/layout and the existing376B sibling supply the
// reconstruction evidence. No original target class name is asserted.
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

class __declspec(novtable) Rva003ADFDBPrimary {public:virtual ~Rva003ADFDBPrimary();private:unsigned argument4;};
class __declspec(novtable) Iface00C1C780 {public:virtual void slot00()=0;};
class __declspec(novtable) Rva003ADFDB:public Rva003ADFDBPrimary,public Iface00C1C780 {public:Rva003ADFDB(unsigned);virtual ~Rva003ADFDB();};

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
class Rva003ADFB2:public Rva003ADFDB,public Rva0055F72C {public:Rva003ADFB2(unsigned,Src0055F840&);virtual~Rva003ADFB2();virtual void slot00()=0;};
Rva003ADFB2::Rva003ADFB2(unsigned a,Src0055F840&src):Rva003ADFDB(a){
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
