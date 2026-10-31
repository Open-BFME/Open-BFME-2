// ?rva00496B48@Rva00496B48@@QAE_NXZ
// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// ?rva00496B48@Rva00496B48@@QAE_NXZ, retail 0x00496B48 138B. Unlock: landing
// makes 0x00496BD2 ready. Walks +0x274 chain from this+8, checks [[+4]+0x116]
// &0x40, cached AllowBannerSpawnUpgrade key via static, findModule, virtual
// at module+0x10 slot0 bool. False only if module vetoes, else true.
// Evidence: callees __EH_prolog 0x00629188 nameToKey 0x00148E1A findModule
// 0x0028B6D6, string AllowBannerSpawnUpgrade, caller 0x00496C29.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleInner
{
public:
	virtual bool allow();
};

#include "../../../../Include/Common/Module.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

// Partial storage view: native 496BB8 adjusts the receiver by +0x10.
// The original derived/interface identities remain unrecovered.
class Rva00496B48ModuleView : public Module
{
public:
    char m_pad08[0x10 - 0x08];
    ModuleInner m_10;
};


struct ObjectInner04
{
	char m_pad00[0x116];
	unsigned char m_116;
};

enum KindOfType { KINDOF_DUMMY=0 };

enum ObjectStatusTypes { STATUS_DUMMY=0 };

class UpgradeTemplate;

class Player;

class Gen_0028EF10;

class BannerContain;

class AIUpdateInterface;

class Object { public:
 bool isKindOf(KindOfType) const;
 bool testStatus(ObjectStatusTypes) const; // 0x0004E536
 bool hasUpgrade(const UpgradeTemplate *) const;
 Object *rva002931F5(bool);
 int rva0028AF76() const;
 Player *getControllingPlayer() const; // 0x0028AFA9
 void *rva0028C197() const; // 0x0028C197
 void rva0028CFB2(const int *clearFlags, const int *setFlags);
 void updateShroudNow(); // 0x0028C11A
 const Coord3D *getPosition() const { return &m_position; }
 AIUpdateInterface *getAI() const { return m_ai; }
 char pad00[4]; ObjectInner04 *m_04; // +0x04
 char matrix[0x30]; // +0x08
 Coord3D m_position; // +0x38
 char pad44[0x24C-0x44]; Gen_0028EF10 *m_stats; BannerContain *m_contain; // +0x24C, +0x250
 char pad254[4]; AIUpdateInterface *m_ai; // +0x258
 char pad25C[0x274-0x25C]; Object *m_containedBy; // +0x274
protected:
 Module *findModule(NameKeyType key) const;
};

struct ObjectHack : public Object
{
	static Module *find(const Object *object, NameKeyType k) { return ((ObjectHack *)object)->findModule(k); }
};

class Rva00496B48
{
public:
	bool rva00496B48();
	char m_pad00[0x8];
private:
	Object *m_obj08; // +0x08
};

bool Rva00496B48::rva00496B48()
{
	Object *object = m_obj08;
	if (object != 0) {
		for (; object != 0; object = object->m_containedBy) {
			if (object->m_containedBy == 0)
				break;
		}
		if (object != 0) {
			ObjectInner04 *inner = object->m_04;
			if (inner->m_116 & 0x40) {
				static NameKeyType s_key = TheNameKeyGenerator->nameToKey("AllowBannerSpawnUpgrade");
				Module *module = ObjectHack::find(object, s_key);
				if (module != 0) {
					if (!(&((Rva00496B48ModuleView *)module)->m_10)->allow())
						return false;
				}
			}
		}
	}
	return true;
}
