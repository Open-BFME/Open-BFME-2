// cl: /O1 /G7 /arch:SSE /MD
// Native 0x0029493F..0x002949AE, 111B, RET8. Object identity and ABI
// follow rowed canCrushOrSquishNoAlly 0x00294898. ZH Object.cpp crush
// logic supplies the subsystem lead; target extends it with status 39/32,
// KindOf84, enemy relationship and the current weapon template byte query.
// The weapon view only asserts its native +4 template pointer. Its queried
// byte uses the rowed address-derived holder getter at 0x002C9400.
// The original predicate name and the weapon byte's meaning remain unknown.
enum ObjectStatusTypes { STATUS_39=0x39, STATUS_32=0x32 };
enum KindOfType { KINDOF_84=0x84 };
enum Relationship { ENEMIES=0,NEUTRAL=1,ALLIES=2 };
enum WeaponSlotType { PRIMARY=0 };
class Rva002C9400ByteField { public: unsigned char get() const; };
class Weapon { public: char pad[4]; Rva002C9400ByteField *info; };
class Object {
public:
 bool rva0029493F(Object *,int);
 bool canCrushOrSquishNoAlly(Object *,int);
 bool testStatus(ObjectStatusTypes) const;
 bool isKindOf(KindOfType) const;
 Relationship getRelationship(const Object *) const;
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
};
bool Object::rva0029493F(Object *victim,int mode) {
 if (!canCrushOrSquishNoAlly(victim,mode)) return false;
 if (testStatus(STATUS_39) || testStatus(STATUS_32) || isKindOf(KINDOF_84)) return true;
 if (getRelationship(victim)!=ENEMIES) return false;
 const Weapon *weapon=getCurrentWeapon(0);
 if (weapon && !weapon->info->get()) return false;
 return true;
}
