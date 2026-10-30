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
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleInner
{
public:
	virtual bool allow();
};

#include "../../../../Include/Common/Module.h"

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

class Object
{
public:
	char m_pad00[4];
	ObjectInner04 *m_04;
	char m_pad08[0x274 - 8];
	Object *m_next274;
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
private:
	char m_pad00[8];
	Object *m_obj08;
};

bool Rva00496B48::rva00496B48()
{
	Object *object = m_obj08;
	if (object != 0) {
		for (; object != 0; object = object->m_next274) {
			if (object->m_next274 == 0)
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
