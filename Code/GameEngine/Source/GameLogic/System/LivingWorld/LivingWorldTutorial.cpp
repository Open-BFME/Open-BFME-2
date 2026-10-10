// cl: /EHs /EHc- /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// LivingWorldTutorial.cpp -- tutorial session-task members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and getRegionParam (0x003F83FE, rowed under a placeholder name);
// retail supplies the bytes. The battle comes from the living-world logic's
// region manager (+0xB0) through 0x0020E57F (unnamed).

class LivingWorldLogic {public:void *rva002B4948(void *,void *,void *);};
extern LivingWorldLogic *TheLivingWorldLogic;
typedef int Int;

// Native getBattleParam forwards the region result as one raw 32-bit key.
// The existing real lookup owns 20E57F and compares that word with entry+24;
// the meaning of the key and its original C++ parameter type stay unproven.
class LivingWorldPendingBattle;
class LivingWorldRegionManager
{
public:
	LivingWorldPendingBattle *rva0020E57F(unsigned int regionKey);	// 0x0020E57F
};

class Rva002BA8F1Logic
{
public:
	unsigned char m_pad00[0xb0];
	LivingWorldRegionManager *m_regionManager;	// +0xB0
};

	// TheLivingWorldLogic

class Rva003F802B
{
public:
	bool rva003F802B();
private:
	unsigned char m_pad00[8];
	void *m_08;
	int m_0C;
};

#include <vector>
#include "ascii_string.h"
struct TargetRef00217D4C;

class Rva0056AC26;

class Rva0056AC26Owner
{


public:

 void rva003F87FF(Rva0056AC26 *);

 void rva003F8814(Rva0056AC26 *);

 void rva003F8829(Rva0056AC26 *);

 void rva003F883E(Rva0056AC26 *);

 void rva003F8853(Rva0056AC26 *);

 void rva003F8868(Rva0056AC26 *);

 void rva003F887D(Rva0056AC26 *);

 void rva003F8892(Rva0056AC26 *);

}
;

class Rva002BED91
{
 
public:
void set(TargetRef00217D4C *);
 
private:
TargetRef00217D4C *m_ref;
 }
;

class Rva0056AC26A
{

public:
virtual ~Rva0056AC26A();

private:
int m_04;
}
;

class Rva0056AC26B
{

public:
virtual ~Rva0056AC26B();

private:
int m_04,m_08;
}
;

class Rva0056AC26:public Rva0056AC26A,public Rva0056AC26B
{

public:
virtual ~Rva0056AC26();
}
;

struct Parent0056B126;
 struct Parent0056B218;
 struct Parent0056B0BF;
 struct Parent0056B2DD;
struct Rva0056B188Owner;

class Rva0056B126:public Rva0056AC26
{

public:
Rva0056B126(Rva0056AC26Owner *,Parent0056B126 *,int);

private:
char storage14[16];
}
;

class Rva0056B188:public Rva0056AC26
{

public:
Rva0056B188(Rva0056AC26Owner *,int,Rva0056B188Owner *);

private:
char storage14[16];
}
;

class Rva0056B218:public Rva0056AC26
{

public:
Rva0056B218(Rva0056AC26Owner *,Parent0056B218 *,Parent0056B218 *);

private:
char storage14[16];
}
;

class Rva0056B2DD:public Rva0056AC26
{

public:
Rva0056B2DD(Rva0056AC26Owner *,Parent0056B2DD *,int);

private:
char storage14[12];
}
;

class Rva0056B0BF:public Rva0056AC26
{

public:
Rva0056B0BF(Rva0056AC26Owner *,Parent0056B0BF *);

private:
char storage14[12];
}
;

class LivingWorldPendingBattle;

class Rva0056ACC5:public Rva0056AC26
{

public:
Rva0056ACC5(Rva0056AC26Owner *,LivingWorldPendingBattle *);

private:
char storage14[8];
}
;

class Rva0056AF4B:public Rva0056AC26
{

public:
Rva0056AF4B(void *,int,int);

private:
char storage14[8];
}
;

class Rva0056AF94:public Rva0056AC26
{

public:
Rva0056AF94(void *);
}
;

class Rva0056AC82:public Rva0056AC26
{

public:
Rva0056AC82(Rva0056AC26Owner *,void *,void *);
}
;

class Rva0056ADF1:public Rva0056AC26
{

public:
Rva0056ADF1(void *,int);

private:
int storage14;
}
;

class Rva0056AD19:public Rva0056AC26
{

public:
Rva0056AD19(Rva0056AC26Owner *);

private:
int storage14;
}
;

struct Rva002E1948Entry;

class Rva003F83D9
{

public:
double rva003F83D9(int);
}
;

class Rva004E0625
{

public:
int rva004E0625() const;
}
;

class ModuleData;

class Rva003F287F
{

public:
void rva003F2818(int,_STL::vector<const ModuleData *> &);
}
;

class TutorialWorldLookup
{

public:
char prefix[0x98];
void *player98;
__forceinline void *player()const{
return player98;
}}
;


class LivingWorldTutorial
{
public:
	class SessionTask
	{
	public:
		void *getBattleParam(Int index);
		void *getRegionParam(Int index);	// 0x003F83FE
		void create(); // 0x003F88BC; WB names the complete retail switch.
        Rva002E1948Entry *getArmyParam(int);
    private:
        int m_word00;Rva0056AC26Owner *m_owner;int m_kind;
        _STL::vector<AsciiString> m_params;AsciiString m_label;Rva002BED91 m_task;
	};

	// A phase session holds the task it creates once its audio is done
	// (+0x14) and a created flag (+0x18).
	class PhaseSession
		: public Rva003F802B
	{
	public:
		void createTaskAfterAudio();
		void rva003F8F94();

	private:
		unsigned char m_pad10[4];
		SessionTask *m_task;			// +0x14
		bool m_taskCreated;			// +0x18
	};
};

// LivingWorldTutorial::SessionTask::getBattleParam, retail 0x003F841D.
void *LivingWorldTutorial::SessionTask::getBattleParam(Int index)
{
	void *region = getRegionParam(index);
	if (region)
	{
		LivingWorldRegionManager *manager = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_regionManager;
		return manager->rva0020E57F(reinterpret_cast<unsigned int>(region));
	}
	return 0;
}

// LivingWorldTutorial::PhaseSession::createTaskAfterAudio, retail 0x003F8DAB
// (21 bytes): WB names it (asserts !isAudioPlaying() at
// LivingWorldTutorial.cpp:1006, compiled out of retail) and its callee
// SessionTask::create.
void LivingWorldTutorial::PhaseSession::createTaskAfterAudio()
{
	if (m_task)
		m_task->create();
	m_taskCreated = true;
}

void LivingWorldTutorial::PhaseSession::rva003F8F94()
{
	if (rva003F802B())
		return;
	if (!m_taskCreated)
	{
		createTaskAfterAudio();
		m_taskCreated = true;
	}
}

// WB 0x01051CB0 supplies the SessionTask::create identity and task-kind algorithm.
// Retail 0x003F88BC supplies all offsets, allocation footprints and actual task
// constructor contracts. The address-owned task names retain their original-name
// uncertainty; declarations below do not emit additional task bodies or vtables.
// The duration multiplier is the existing sole float owner at RVA 0x009BA4F4,
// initialized to 5.0f by Rva0040C985Init.cpp. Widening the duration before the
// compound multiplication preserves retail's x87 precision and _ftol2 truncation
// without promoting the measured float operand to a double literal.
extern float g_00DBA4F4;
static __forceinline double scaledTutorialDuration(float duration) {
	double product=duration;
	product*=g_00DBA4F4;
	return product;
}
void LivingWorldTutorial::SessionTask::create()
{
	Rva0056AC26 *task = 0;
	switch(m_kind) {
		case 0:case 1:break;
		case 2:{
			if(m_params.size()!=1) break;
			void *region=getRegionParam(0);
			if(!region)break;
			task=new Rva0056B126(m_owner,(Parent0056B126 *)region,4);
			m_owner->rva003F8814(task);
			break;
		}
		case 3:{
			if(m_params.size()!=1) break;
			void *region=getRegionParam(0);
			if(!region)break;
			_STL::vector<const ModuleData *> buildings;
			((Rva003F287F *)region)->rva003F2818(4,buildings);
			if(buildings.size()==0)break;
			const ModuleData *building=buildings[0];
			int nugget=((const Rva004E0625 *)building)->rva004E0625();
			if(!nugget)break;
			task=new Rva0056B188(m_owner,(int)((char *)building+0x48),(Rva0056B188Owner *)nugget);
			m_owner->rva003F8829(task);
			break;
		}
		case 4:{
			if(m_params.size()!=2)break;
			void *region=getRegionParam(0);
			if(!region)break;
			void *garrison=TheLivingWorldLogic->rva002B4948(((TutorialWorldLookup *)TheLivingWorldLogic)->player(),region,0);
			if(!garrison)break;
			Rva002E1948Entry *target=getArmyParam(1);
			if(!target)break;
			task=new Rva0056B218(m_owner,(Parent0056B218 *)garrison,(Parent0056B218 *)target);
			m_owner->rva003F883E(task);
			break;
		}
		case 5:{
			if(m_params.size()!=2)break;
			Rva002E1948Entry *army=getArmyParam(0);
			if(!army)break;
			void *region=getRegionParam(1);
			if(!region)break;
			task=new Rva0056B2DD(m_owner,(Parent0056B2DD *)army,(int)region);
			m_owner->rva003F8853(task);
			break;
		}
		case 6:{
			if(m_params.size()!=1)break;
			void *region=getRegionParam(0);
			if(!region)break;
			void *army=TheLivingWorldLogic->rva002B4948(((TutorialWorldLookup *)TheLivingWorldLogic)->player(),region,0);
			if(!army)break;
			task=new Rva0056B0BF(m_owner,(Parent0056B0BF *)army);
			m_owner->rva003F8892(task);
			break;
		}
		case 7:{
			if(m_params.size()!=1)break;
			void *battle=getBattleParam(0);
			if(!battle)break;
			task=new Rva0056ACC5(m_owner,(LivingWorldPendingBattle *)battle);
			m_owner->rva003F8868(task);
			break;
		}
		case 8:{
			if(m_params.size()!=1)break;
			void *battle=getBattleParam(0);
			if(!battle)break;
			task=new Rva0056AF4B(m_owner,(int)battle,2);
			break;
		}
		case 9:{
			task=new Rva0056AF94(m_owner);
			m_owner->rva003F887D(task);
			break;
		}
		case 10:{
			if(m_params.size()!=2)break;
			Rva002E1948Entry *army=getArmyParam(0);
			if(!army)break;
			void *region=getRegionParam(1);
			if(!region)break;
			task=new Rva0056AC82(m_owner,army,region);
			break;
		}
		case 11:{
			if(m_params.size()!=1)break;
			float duration=(float)((Rva003F83D9 *)this)->rva003F83D9(0);
			if(duration<0.0f)break;
			task=new Rva0056ADF1(m_owner,(int)scaledTutorialDuration(duration));
			break;
		}
		case 12:{
			task=new Rva0056AD19(m_owner);
			break;
		}
	}
	if(task){
		m_task.set((TargetRef00217D4C *)task);
		m_owner->rva003F87FF(task);
	}
}
