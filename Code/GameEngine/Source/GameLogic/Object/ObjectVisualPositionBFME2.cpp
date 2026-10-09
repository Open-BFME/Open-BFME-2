// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native28D4E0..28D611305B: return the drawable matrix's translation,
// with terrain-layer height/normal handling and contained-object delegation.
// Caller275C82/275CC0 and target vslot190 prove a Coord3D value return plus
// one optional normal pointer. Layout, flags and ABI are target witnesses;
// the original public method spelling is unresolved.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Twelve-byte target return view, sharing the canonical coordinates;
// native returns copy each float. No original return-type name is asserted.
struct Rva0028D4E0Value:Coord3D {
 Rva0028D4E0Value(){}
 Rva0028D4E0Value(const Rva0028D4E0Value &v){x=v.x;y=v.y;z=v.z;}
};
static __forceinline bool visualGroundBit(unsigned v){return(v>>6)&1;}
class Matrix3D;
struct VisualMatrixTranslation {float values[3][4];};
class Drawable {public:const Matrix3D *getTransformMatrix() const;};
class Object;
class VisualContain {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
#undef V
 virtual Object *resolveObject();
};
enum PathfindLayerEnum { PATHFIND_LAYER_GROUND=0 };
class TerrainLogic {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6)
#undef V
 virtual float getLayerHeight(float,float,PathfindLayerEnum,Coord3D *,bool) const;
 PathfindLayerEnum getLayerForDestination(Object *,const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class Object {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
 V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
 V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
 V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
 V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
 V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
 V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)

#undef V
 virtual Rva0028D4E0Value rva0028D4E0(Coord3D *normal);
private:
 char pad04[0x84-4];Drawable *m_drawable84;
 char pad88[0x94-0x88];unsigned m_status94;
 char pad98[0x250-0x98];VisualContain *m_contain250;
 char pad254[0x40c-0x254];PathfindLayerEnum m_layer40C;
};
Rva0028D4E0Value Object::rva0028D4E0(Coord3D *normal) {
 VisualContain *contain=m_contain250;
 if(contain) {
  Object *other=contain->resolveObject();
  if(other)return other->rva0028D4E0(normal);
 }
 if(m_drawable84) {
  const VisualMatrixTranslation *matrix=reinterpret_cast<const VisualMatrixTranslation *>(m_drawable84->getTransformMatrix());
  Rva0028D4E0Value original;
  original.x=matrix->values[0][3];original.y=matrix->values[1][3];original.z=matrix->values[2][3];
  Rva0028D4E0Value position;position.x=original.x;position.y=original.y;position.z=original.z;
  if(visualGroundBit(m_status94)) {
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(this,&position);
   position.z=TheTerrainLogic->getLayerHeight(position.x,position.y,layer,normal,true);
  }else if(normal)TheTerrainLogic->getLayerHeight(original.x,original.y,m_layer40C,normal,true);
  return position;
 }
 if(normal) {normal->x=0.0f;normal->y=0.0f;normal->z=1.0f;}
 Rva0028D4E0Value position;position.x=position.y=position.z=0.0f;
 return position;
}
