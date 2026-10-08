// cl: /O1 /Oy- /MD /EHsc /arch:SSE /G7 /D_CRTIMP= /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
// WorldBuilder 1506950 names build at assertions 54..64. Native
// 573C7C..573CFB uses the order's producer +08, name +0C and result +24.
// These are accessed-prefix and virtual-call views, not complete class layouts.
// Slots 13 and 17 return Coord3D by hidden result and float respectively;
// AI slot 126 takes the template, position, rotation, owner and two zero flags.
// BFME1 and ZH have no corresponding AIBuildableStructure reference unit.
extern GameLogic *TheGameLogic;
class Player;
class ThingTemplate;
class AIUpdateView {
public:
#define SLOT(n) virtual void s##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79) SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89) SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97) SLOT(98) SLOT(99) SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108) SLOT(109)
 virtual bool canUseDozer();
 SLOT(111) SLOT(112) SLOT(113) SLOT(114) SLOT(115) SLOT(116) SLOT(117) SLOT(118) SLOT(119) SLOT(120) SLOT(121) SLOT(122) SLOT(123) SLOT(124) SLOT(125)
 virtual Object *buildStructure(const ThingTemplate *,const Coord3D *,float,Player *,int,int);
#undef SLOT
};
class Object { public: char pad[0x74]; ObjectID id; char pad78[0x258-0x78]; AIUpdateView *ai; };
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva0055ADD8 { public: int rva0055ADD8(int); };
class AIBuildableStructure {
public:
#define SLOT(n) virtual void s##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3)
 virtual int canMake(Player *);
 SLOT(5)
 virtual bool build(Player *);
 SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
 virtual Coord3D position();
 SLOT(14) SLOT(15) SLOT(16)
 virtual float rotation();
#undef SLOT
 bool rva00573B5E();
 float field04; ObjectID producer; AsciiString name;
 char pad10[0x24-0x10]; ObjectID produced;
};
bool AIBuildableStructure::build(Player *player)
{
 Object *dozer=TheGameLogic->findObjectByID(producer);
 const ThingTemplate *thing=(const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&name);
 AIUpdateView *ai=dozer->ai;
 Object *created=ai->buildStructure(thing,&position(),rotation(),player,0,0);
 if (created) { produced=created->id; return true; }
 ((Rva0055ADD8 *)this)->rva0055ADD8((int)player);
 return false;
}



