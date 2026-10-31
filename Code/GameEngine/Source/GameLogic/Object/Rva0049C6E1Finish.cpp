// ?rva0049C6E1@Rva0049C6E1@@QAE_NPAVObject@@@Z
// partial score=0.96 date=2026-10-04
// cl: /DNDEBUG /MD
//
// ?rva0049C6E1@Rva0049C6E1@@QAE_NPAVObject@@@Z @0x0049C6E1 89B. Upgrade check via
// TheUpgradeCenter plus rowed find 0x0026F0F0 with mask at this+8 plus 0x284
// then provider path via rowed 0x0049C5F4 plus virtual slot 43 plus pin
// Object::affectedByUpgrade else path. Evidence: push esi plus TheUpgradeCenter plus
// 0x284 plus find plus provider plus 0xAC plus pin plus al 1/0; callers
// 0x0041CE8B 0x0049C9AE 0x0049CA77; honest address name.
class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *mask);
};

class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0049C73A_2 = 2,
	OS_3 = 3,
	OS_42 = 0x42,
	OBJECT_STATUS_RVA0049C73A_66 = 0x42
};

class UpgradeTemplate;

class Player;
struct Coord3D;
class ThingTemplate;
class Provider31;
class AIUpdate;
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Object *rva002931F5(bool flag);
	Player *getControllingPlayer() const; // 0x0028AFA9
	bool testStatus(ObjectStatusTypes bit) const; // 0x0004E536
	const Coord3D *getPosition() const { return &m_pos; }
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	char m_pad00[0x4];
	const ThingTemplate *m_template; // +0x04 +0x04
	char m_pad08[0x30];
	Coord3D m_pos; // +0x38 +0x38
	char m_pad44[0x34];
	ObjectID m_78; // +0x78 +0x78
	char m_pad7C[0x1D4];
	Provider31 *m_prov250; // +0x250
	char m_pad254[0x4];
	AIUpdate *m_ai; // +0x258
	char m_pad25C[0x18];
	int m_int274; // +0x274
	char m_pad278[0xC];
	unsigned m_284[32]; // +0x284 +0x284 the upgrade mask
	char m_pad304[0x134];
	unsigned char m_b438; // +0x438
	char m_pad439[0x3];
};

class Rva0049C5F4
{
public:
	void *rva0049C5F4(Object *arg);
};

class Rva0049C6E1Prov
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42();
	virtual bool slot43(void *upgrade);
};

class Rva0049C6E1
{
public:
	bool rva0049C6E1(Object *object);
	char m_pad00[0x8];
private:
	void *m_ptr08; // +0x08
};

// ?rva0049C6E1@Rva0049C6E1@@QAE_NPAVObject@@@Z
// Retail lays the value test out with the TRUE return inline and the FALSE
// return as the out-of-line branch target (test al,al / je FALSE / mov al,1),
// which only the positive-nested form produces: every failing guard falls out
// to a single shared `return false` and the success path returns true early.
bool Rva0049C6E1::rva0049C6E1(Object *object)
{
	void *upgrade = ((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0((const void *)((char *)m_ptr08 + 0x284));
	if (upgrade != 0)
	{
		unsigned char ok;
		if (object->m_int274 != 0)
		{
			void *prov = ((Rva0049C5F4 *)this)->rva0049C5F4(object);
			if (prov != 0)
			{
				ok = ((Rva0049C6E1Prov *)prov)->slot43(upgrade);
				if (ok != 0)
					return true;
			}
		}
		else
		{
			ok = object->affectedByUpgrade((const UpgradeTemplate *)upgrade);
			if (ok != 0)
				return true;
		}
	}
	return false;
}
