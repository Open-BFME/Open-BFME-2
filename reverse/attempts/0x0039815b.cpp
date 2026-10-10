// ?rva0039815B@CastleBehavior@@QAEPAVObject@@PAVThingTemplate@@PBUCoord3D@@H@Z
// partial score=0.9726053639846743 date=2026-10-10
// ?rva0039815B@CastleBehavior@@QAEPAVObject@@PAVThingTemplate@@PBUCoord3D@@H@Z
// partial score=0.8967113665389528 date=2026-10-10
// ?rva0039815B@CastleBehavior@@QAEPAVObject@@PAVThingTemplate@@PBUCoord3D@@H@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/GameEngine/Source/Common
//
// ?rva0039815B@CastleBehavior@@QAEPAVObject@@PAVThingTemplate@@PBUCoord3D@@H@Z,
// retail 0x0039815B..0x00398243 (232 bytes, RET 12): the CastleBehavior
// member ScriptActions 0x003C66F1 calls to build a template near a position.
// Mode 0 picks the nearest, mode 1 the farthest (any other mode, or no
// template, gives nothing) among the castle's owned objects -- the +0x74 list
// for templates flagged at +0x110, else the +0x50 list -- skipping missing
// objects (rowed GameLogic::findObjectByID), templates flagged 0x40 at +0x11A
// and objects whose rowed 0x0028BCF4 interface is absent or busy (its slot 3),
// by squared distance (rowed distSq). The pinned static 0x00397FEB then
// creates it from the +0x38 context and the chosen object's +0x74 ID.

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct Coord3D;
class ThingTemplate;

struct Rva0039815BTemplate
{
	unsigned char m_pad000[0x110];
	unsigned char m_flags110;				// +0x110
	unsigned char m_pad111[0x11A - 0x111];
	unsigned char m_flags11A;				// +0x11A
};

class Rva0039815BBusy
{
public:
	virtual void b0();
	virtual void b1();
	virtual void b2();
	virtual bool busy();					// slot 3
};

class Object
{
public:
	void *rva0028BCF4() const;

	unsigned char m_pad00[0x04];
	Rva0039815BTemplate *m_template04;		// +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id74;						// +0x74
};

class Rva000CBA20Point;

class Rva000CBA20
{
public:
	float distSq(const Rva000CBA20Point *point);
};

void *rva00397FEB(void *context, unsigned int id, void *tmpl, int flag);

struct Rva0039815BIdList
{
	ObjectID *m_begin;
	ObjectID *m_end;
	ObjectID *m_capacity;
};

class CastleBehavior
{
public:
	Object *rva0039815B(ThingTemplate *tmpl, const Coord3D *pos, int mode);
private:
	unsigned char m_pad00[0x38];
	void *m_context38;						// +0x38
	unsigned char m_pad3C[0x50 - 0x3C];
	Rva0039815BIdList m_owned50;			// +0x50
	unsigned char m_pad5C[0x74 - 0x5C];
	Rva0039815BIdList m_owned74;			// +0x74
};

Object *CastleBehavior::rva0039815B(ThingTemplate *tmpl, const Coord3D *pos, int mode)
{
	if (!tmpl)
		return 0;
	float best;
	switch (mode)
	{
	case 0:
		best = 9999999.0f;
		break;
	case 1:
		best = 0.0f;
		break;
	default:
		return 0;
	}
	ObjectID bestID = INVALID_OBJECT_ID;
	Rva0039815BIdList *list = &m_owned50;
	if (((Rva0039815BTemplate *)tmpl)->m_flags110 & 1)
		list = &m_owned74;
	for (ObjectID *it = list->m_begin; it != list->m_end; ++it)
	{
		Object *obj = (tmpl?TheGameLogic:TheGameLogic)->findObjectByID(*it);
		if (!obj || (obj->m_template04->m_flags11A & 0x40))
			continue;
		Rva0039815BBusy *busy = (Rva0039815BBusy *)obj->rva0028BCF4();
		if (!busy || busy->busy())
			continue;
		float dist = reinterpret_cast<Rva000CBA20 *>(obj)->distSq((const Rva000CBA20Point *)pos);
		switch (mode)
		{
		case 0:
			if (!(dist <= best))
				continue;
			break;
		case 1:
			if (!(best <= dist))
				continue;
			break;
		default:
			continue;
		}
		bestID = obj->m_id74;
		best = dist;
	}
	return (Object *)rva00397FEB(m_context38, bestID, tmpl, 0);
}
