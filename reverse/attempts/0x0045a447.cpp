// ?rva0045A447@AutoAbilityBehavior@@QAEPAVObject@@PAUBfmeWideResult@@PBURva0045A447Options@@@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0045A421@AutoAbilityBehavior@@QAEXPAX@Z, retail 0x0045A421, 38 bytes.
// Copies the AsciiString at src+0x10 to the member at +0x20 via the pinned
// AsciiString::operator= at 0x000366F0, then arms wake via the rowed
// UpdateModule::setWakeFrame at 0x0044DF71 with the Object at +8 and delay 1.
// Layout follows the rowed dtor ??1AutoAbilityBehavior at 0x0045A37F
// (AsciiString at +0x20) and the pinned ctor at 0x0045A78F (Object at +8).
// Callers at 0x0045A726 and 0x0045A785 pass through to this leaf.

class Object;

#include "ascii_string.h"


enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
	friend class AutoAbilityBehavior;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime delay);
};

struct Rva0045A421Src
{
	unsigned char m_pad[0x10];
	AsciiString m_str10;
};

class AutoAbilityBehavior
{
public:
	void rva0045A421(void *src);
	Object *rva0045A447(struct BfmeWideResult *result, const struct Rva0045A447Options *options);

private:
	unsigned char m_pad[8];
	Object *m_obj8;
	unsigned char m_mid[0x20 - 0xC];
	AsciiString m_str20;
};

void AutoAbilityBehavior::rva0045A421(void *src)
{
	Object *obj = m_obj8;
	Rva0045A421Src *s = (Rva0045A421Src *)src;
	m_str20 = s->m_str10;
	((UpdateModule *)this)->setWakeFrame(obj, UPDATE_SLEEP_NONE);
}

// Native full180 byte body: module data radiusC/self5F; object pos38/body254.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
class Rva0045A447Body {
public:
    virtual void slot0(); virtual void slot4(); virtual void slot8();
    virtual void slotC(); virtual void slot10(); virtual float query14();
};
class Object {
public:
    const Coord3D *getPosition() const { return &position; }
    Rva0045A447Body *getBody() const { return body; }
private:
    char pad0[0x38]; Coord3D position;
    char pad44[0x254-0x44]; Rva0045A447Body *body;
};
struct Rva0045A447Data {
    char pad0[0xc]; float radius;
    char pad10[0x5f-0x10]; bool allowSelf;
};
struct Rva0045A447Options {
    char pad0[0x138]; bool queryBody;
};
Object *AutoAbilityBehavior::rva0045A447(BfmeWideResult *result, const Rva0045A447Options *options)
{
    const Rva0045A447Data *data = *(const Rva0045A447Data *const *)((const char *)this+4);
    Object *owner = m_obj8;
    Object *candidate;
    while ((candidate = result->next()) != 0) {
        if (!data->allowSelf && candidate == owner) continue;
        if (options && options->queryBody) {
            Rva0045A447Body *body = candidate->getBody();
            if (body && body->query14() > 0.8f) continue;
        }
        if (data->radius > 0.0f) {
            Coord3D difference;
            difference.x = owner->getPosition()->x - candidate->getPosition()->x;
            difference.y = owner->getPosition()->y - candidate->getPosition()->y;
            difference.z = owner->getPosition()->z - candidate->getPosition()->z;
            if (!(data->radius > difference.length())) return candidate;
        } else return candidate;
    }
    return 0;
}
