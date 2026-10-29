// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00396E92, 154B: a behavior member (ret 4, module data at this+4)
// that looks an object's name up in the module data's record vector at +0x5C
// (12-byte BfmeStringRecord00395E75 entries: two strings and a float, copied
// through 0x00395E75 and destroyed through the rowed 0x00395D77) and returns
// the float of the first record whose leading string equals the object's
// string at Object+0x58, else 0.0. Each record is copied out by value before
// the compare, so the copy is destroyed on both paths. Owner and slot name
// not established: address-derived.

#include <vector>
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

enum NameKeyType { NAMEKEY_INVALID=0 };

typedef float Real;
typedef int Int;

struct Rva00395D77
{
	~Rva00395D77();
};

struct BfmeStringRecord00395E75 : public Rva00395D77
{
	BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &other);
	char *m_name;
	char *m_other;
	Real m_value;
};

enum Relationship { ENEMIES, NEUTRAL, ALLIES };
enum ObjectStatusTypes { OBJECT_STATUS_5=5, OBJECT_STATUS_79=79 };
enum DamageType { DAMAGE_8=8 };
enum DeathType { DEATH_0=0 };
class Module; class CastleBehavior; class Rva003979FB; struct Coord3D; class Drawable; class Player; class Team; class Rva00399959;
class Object
{
protected:
	friend class CastleBehavior;
private:
	friend class Rva003979FB;
protected:
	friend class Rva00399959;
	friend void Rva00396BC5SetCastleId(_STL::vector<ObjectID>*,ObjectID);
public:
	const AsciiString &getName() const { return *(const AsciiString *)((const char *)this + 0x58); }
protected:
	Module *findModule(NameKeyType) const;
public:
	void rva0028CFB2(const int*,const int*);
	float getCastleValue() const { return *(const float*)((const char*)this+0x324); }
	float GetRelativeAngle(const Coord3D*) const;
	Coord3D* getPlanarDirectionTo(Coord3D*,const Object*) const;
	float getBoundingCircleRadius() const { return *(const float*)((const char*)this+0xb8); }
	Relationship getRelationship(const Object*) const;
	int rva0028B511() const;
	bool testStatus(ObjectStatusTypes) const;
	Object* rva002931F5(bool);
	void* rva0028C197() const;
	void teleportTo(const Coord3D*,bool);
	void* rva0028BCF4() const;
	void kill(DamageType,DeathType);
	void rva0028D282(void*);
	Player* getControllingPlayer() const;
	void setStatus(ObjectStatusTypes,bool);
	void setTeam(Team*);
	void rva0028BAC0();
	void rva0028DCC4();
	void rva0028D253();
	void rva0028AE6D();
};

struct Rva00396E92ModuleData
{
	unsigned char m_pad00[0x5C];
	BfmeStringRecord00395E75 *m_recordsBegin;
	BfmeStringRecord00395E75 *m_recordsEnd;
	BfmeStringRecord00395E75 *m_recordsCapacity;
};

class Rva00396E92
{
public:
	Real rva00396E92( Object *obj );

private:
	void *m_vtable;
	const Rva00396E92ModuleData *m_moduleData;
};

Real Rva00396E92::rva00396E92( Object *obj )
{
	if( obj == 0 )
		return 0.0f;

	const Rva00396E92ModuleData *d = m_moduleData;
	Int count = d->m_recordsEnd - d->m_recordsBegin;
	for( Int i = 0; i < count; ++i )
	{
		BfmeStringRecord00395E75 record = d->m_recordsBegin[ i ];
		if( *(const AsciiString *)&record.m_name == obj->getName() )
			return record.m_value;
	}

	return 0.0f;
}
