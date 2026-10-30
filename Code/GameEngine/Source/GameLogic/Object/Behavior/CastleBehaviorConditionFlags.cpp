// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native 3979FB..397B03 (264B), WB EC0B70 independently confirms all
// seven callees, parent ObjectID38 and child ObjectID vector5C.
// Both paths change object flags, refresh the drawable, then notify the
// CastleMemberBehavior module through recovered audio-flags helper395BCB.
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;
#include "../../../../Include/GameClient/DrawableBFME2.h"
class Module;
enum Relationship { ENEMIES, NEUTRAL, ALLIES };
enum ObjectStatusTypes { OBJECT_STATUS_5=5, OBJECT_STATUS_79=79 };
enum DamageType { DAMAGE_8=8 };
enum DeathType { DEATH_0=0 };
class CastleBehavior;
class Rva00399959;
class AsciiString;
struct Coord3D;
class Player;
class Team;
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
class Rva00395BCB {public:void rva00395BCB(const void*,const void*);};
class Rva003979FB {
public:
 void rva003979FB(const int *oldFlags,const int *newFlags);
 char unknown00[0x38];
 ObjectID parentID;
 char unknown3C[0x5C-0x3C];
 _STL::vector<ObjectID> children;
};
void Rva003979FB::rva003979FB(const int *oldFlags,const int *newFlags)
{
 static const NameKeyType key=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 Object *parent=TheGameLogic->findObjectByID(parentID);
 if(parent) {
  parent->rva0028CFB2(oldFlags,newFlags);
  ((Thing *)parent)->getDrawable()->rva00274176(false);
  Module *module=parent->findModule(key);
  if(module)((Rva00395BCB *)module)->rva00395BCB(oldFlags,newFlags);
 }
 for(unsigned int i=0;i<children.size();++i) {
  Object *child=TheGameLogic->findObjectByID(children[i]);
  if(child) {
   child->rva0028CFB2(oldFlags,newFlags);
   ((Thing *)child)->getDrawable()->rva00274176(false);
   Module *module=child->findModule(key);
   if(module)((Rva00395BCB *)module)->rva00395BCB(oldFlags,newFlags);
  }
 }
}
