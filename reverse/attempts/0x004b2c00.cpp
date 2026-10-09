// ?rva004B2C00@ReplaceObjectUpdate@@QAEXPAVObject@@PAVRva004B2A9D@@@Z
// partial score=0.742011199809365 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /arch:SSE /ICode/Libraries/Include
class Player;
class Object;
struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// The AI command entry at AIUpdateInterface +0x20 (0x0047ED64).
class Rva0047ED64
{
public:
	void rva0047ED64(void *obj, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	Rva0047ED64 m_20;	// +0x20
};

class DamageInfo
{
public:
	DamageInfo();		// 0x00263895
	char m_pad00[0x08];
	ObjectID m_sourceID;	// +0x08
	char m_pad0C[0x24 - 0x0C];
	bool m_24;		// +0x24
	char m_pad25[0x7C - 0x25];
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void *rva0028C197() const;		// 0x0028C197
	void attemptDamage(DamageInfo *info);	// 0x0029848E
	const Coord3D *getPosition() const { return &m_pos; }
	float getOrientation() const { return m_44; }
	ObjectID getID() const { return m_id; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	float m_44;		// +0x44
	char m_pad048[0x74 - 0x48];
	ObjectID m_id;		// +0x74
	char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_258;	// +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_274;		// +0x274
};

class GameLogic
{
public:
	void destroyObject(Object *obj);	// 0x00242C09
};
extern GameLogic *TheGameLogic;

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

class PlayerList
{
public:
	char m_pad00[0x18];
	void *m_18;		// +0x18
};
extern PlayerList *ThePlayerList;

// The object maker at 0x00DFE7B8... (g_00A027B8): slot 14 builds an object
// of a template at a point and angle for a creator.
class Rva00A027B8
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual Object *rva00A027B8Create(Object *creator, const ThingTemplate *tmpl,
		const Coord3D *pos, float angle, void *owner);	// slot 14
};
extern Rva00A027B8 *g_00A027B8;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

// A replacement entry: 0x004B2A9D picks one of its template names at random.
class Rva004B2A9D
{
public:
	int *rva004B2A9D();	// 0x004B2A9D
};

class ReplaceObjectUpdateModuleData
{
public:
	char m_pad00[0xC8];
	Rva004B2A9D **m_C8;	// +0xC8 the entries
	Rva004B2A9D **m_CC;	// +0xCC their end
	char m_padD0[4];
	float m_D4;		// +0xD4 the radius
	const FXList *m_D8;	// +0xD8
	bool m_DC;		// +0xDC
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();	// slot 17 (0x0045108D)
	Object *getObject() const { return m_object; }
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class ReplaceObjectUpdate : public SpecialAbilityUpdate
{
public:
	virtual void rva004B2D28();
	void rva004B2C00(Object *obj, Rva004B2A9D *entry);
	void rva004B2A60(Object *obj);
private:
	const ReplaceObjectUpdateModuleData *getReplaceObjectData() const
	{
		return (const ReplaceObjectUpdateModuleData *)m_moduleData;
	}
	char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;		// +0x44
};

void ReplaceObjectUpdate::rva004B2C00(Object *obj, Rva004B2A9D *entry)
{
	const ReplaceObjectUpdateModuleData *data=getReplaceObjectData();
 const ThingTemplate *tmpl = TheThingFactory->findTemplate(*(const AsciiString*)entry->rva004B2A9D());
	Object *self = getObject();
	Object *created = g_00A027B8->rva00A027B8Create(self, tmpl, obj->getPosition(), obj->getOrientation(), ThePlayerList->m_18);
	if (created) {
		FXList::doFXObj(data->m_D8, created, 0);
		if (data->m_DC) {
			AIUpdateInterface *ai = created->m_258;
			if (ai)
				ai->m_20.rva0047ED64(getObject(), (CommandSourceType)2);
		}
	}
	rva004B2A60(obj);
}

