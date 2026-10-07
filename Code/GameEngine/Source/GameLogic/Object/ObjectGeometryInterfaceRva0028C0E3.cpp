// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native complete body 28C0E3..28C0F2: forward the first stack argument,
// adjust the interface receiver by -0x70, call rowed Object geometry test
// 28B35B and return while removing three 4-byte arguments. AL is passed through.
// BFC290 table slot +20 independently contains this entry; existing constructor
// 298EA9 / destructor 299CE4 evidence places that interface at Object+70.
// Accepted runtime packet (archive SHA256 3d974bf055b14b83983430e6ed98de423a60901217b4b9cd815c5b1b401e41b9)
// confirms a transfer from 758E87 through that slot. This packet proves a call
// relationship, not an original method name. Unsigned arguments below describe
// only the two ignored 4-byte ABI slots; their original types remain unknown.
struct Coord3D;
enum ObjectStatusTypes;
class Object { public: bool rva0028B35B(const Object *) const; bool testStatus(ObjectStatusTypes) const; };
struct Rva0028E868OtherPrefix {
 char pad00[0x74]; unsigned word74;
 char pad78[0x484-0x78]; unsigned word484;
};
struct Rva0028E868Collide {
 virtual void onCollide(Object *,const Coord3D *,const Coord3D *)=0;
};
struct Rva0028E868BehaviorInterface {
 virtual void slot00()=0;
 virtual Rva0028E868Collide *getCollide()=0;
};
class Rva0028C0E3Receiver {
public:
 bool geometryTest(const Object *,unsigned,unsigned) const;
 void collisionDispatch(Object *,const Coord3D *,const Coord3D *);
private:
 char pad00[4]; unsigned word04;
 char pad08[0x1d4-8]; void **behaviors;
 char pad1d8[0x414-0x1d8]; unsigned word414;
};
bool Rva0028C0E3Receiver::geometryTest(const Object *other,unsigned,unsigned) const {
 return ((const Object *)((const char *)this-0x70))->rva0028B35B(other);
}

// Native 28E868..28E8D4 ends RET12. The same BFC290 table's slot +24
// and accepted runtime transfers at 758EBE/758F1D establish this neighboring
// interface body. BFME1 ba7ddda7 Object_onCollide.cpp and the ZH Object.cpp
// onCollide loop provide the primary behavioral lead: traverse null-terminated
// module pointers, get the collision interface at module+0C slot1, check status
// for each live callback, then dispatch all three arguments via callback slot0.
// Retail independently establishes receiver+04/+1D4/+414, other+74/+484,
// both early filters and rowed Object::testStatus(4) after adjusting by -70.
// Field meanings, full allocation and original slot spelling remain unasserted.
void Rva0028C0E3Receiver::collisionDispatch(Object *other,const Coord3D *loc,const Coord3D *normal) {
 Rva0028E868OtherPrefix *otherFields=(Rva0028E868OtherPrefix *)other;
 if(word414==otherFields->word74)return;
 if(otherFields->word484!=0 && word04!=0)return;
 for(void **m=behaviors;*m;++m) {
  Rva0028E868Collide *collide=((Rva0028E868BehaviorInterface *)((char *)*m+0xc))->getCollide();
  if(!collide)continue;
  if(((const Object *)((const char *)this-0x70))->testStatus((ObjectStatusTypes)4))break;
  collide->onCollide(other,loc,normal);
 }
}
