// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// InGameUI::FormationPreviewPoolObject::dismiss / assign (WorldBuilder names, InGameUI.cpp lines 8200 and 8189: hide/show the +0x00 drawable through 0x002707FA and set +0x08 to 0 / 1).
// was ?rva0029B1C2@Rva0029B1C2@@QAEXXZ 0x0029B1C2 22B evidence: chain via rowed 0x002707FA; clears byte at +8 after forwarding 0
#include "../../Include/Common/Rva002707FA.h"

// InGameUI view: the original member names remain unresolved.
// Native81: four nullable pool pointers +5B4 and 12-byte entry vector +5A0.
// Only nonnull slots are dismissed/cleared. The vector end is captured before
// forming its address; after dismissing each +8 pointer the native calls the
// independently rowed 12-byte vector erase. No allocation layout is asserted.
#include <vector>
#include <map>

struct Gen_p12pod;

struct FormationVectorView
{
	Gen_p12pod *begin;
	Gen_p12pod *end;
	Gen_p12pod *capacity;
};

class ThingTemplate;
class Object;
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"

class Rva0029B63A
{
public:
	_STL::_Rb_tree_node_base *head;
	int count;
	void rva0029E015();
};

class InGameUI
{
public:
	class FormationPreviewPoolObject;
private:
	char unknown[0x590];
	Rva0029B63A tree;
	char gap598[8];
	FormationVectorView entries;
	char gap[8];
	InGameUI::FormationPreviewPoolObject *slots[4];
public:
	__declspec(noinline) void clearFormationPreviewDrawables();
	void rva002A3E24();
	InGameUI::FormationPreviewPoolObject *rva002A3E5A(ThingTemplate *type);
	void rva002A470F(ThingTemplate *type, const ICoord2D *position, RGBColor color);
	void rva002A4BFC(Object *object, ThingTemplate *type, const ICoord2D *position, RGBColor color);
};

class InGameUI::FormationPreviewPoolObject
{
	Rva002707FA *m00;
	char _p04[4];
	unsigned char m08;
public:
	__declspec(noinline) void dismiss();
	void assign();
	void releaseAssets();
};

void InGameUI::FormationPreviewPoolObject::dismiss()
{
	if (m00 != 0)
		m00->rva002707FA(0);
	m08 = 0;
}

void InGameUI::FormationPreviewPoolObject::assign()
{
	if (m00 != 0)
		m00->rva002707FA(1);
	m08 = 1;
}

struct Gen_p12pod
{
	int unknown[2];
	InGameUI::FormationPreviewPoolObject *pool;
};
// Use the byte-verified out-of-line erase owner at 0x002A133B.
namespace _STL {
template <> Gen_p12pod *vector<Gen_p12pod, allocator<Gen_p12pod> >::erase(Gen_p12pod *, Gen_p12pod *);
}
extern template class _STL::vector<Gen_p12pod>;


void InGameUI::clearFormationPreviewDrawables()
{
	InGameUI::FormationPreviewPoolObject **slot = slots;
	for (int remaining = 4; remaining != 0; --remaining, ++slot) {
		if (*slot) {
			(*slot)->dismiss();
			*slot = 0;
		}
	}
	Gen_p12pod *end = entries.end;
	FormationVectorView &range = entries;
	for (Gen_p12pod *it = range.begin; it != end; ++it)
		it->pool->dismiss();
	_STL::vector<Gen_p12pod> &vector =
		*reinterpret_cast<_STL::vector<Gen_p12pod> *>(&range);
	vector.erase(vector.begin(), vector.end());
}

// Native54 2A3E24..2A3E5A: same owner as the dismiss method, then tree+590
// node payload+14 invokes named FormationPreviewPoolObject::releaseAssets.
// The iterator and tree clear both resolve to independently rowed providers.
void InGameUI::rva002A3E24()
{
	clearFormationPreviewDrawables();
	Rva0029B63A &pool = tree;
	for (_STL::_Rb_tree_node_base *it = pool.head->_M_left; it != pool.head;
		it = _STL::_Rb_global<bool>::_M_increment(it)) {
		reinterpret_cast<InGameUI::FormationPreviewPoolObject *>(
			reinterpret_cast<char *>(it) + 0x14)->releaseAssets();
	}
	pool.rva0029E015();
}

// Native2A470F..2A47B3,164B RET14. Its caller2A4BFC and WBdc02d0
// establish a template, screen position and three-float color. The pool
// getter WBdc4300 returns the named FormationPreviewPoolObject payload;
// the 12-byte entry is position.x, position.y and that pool pointer.
// Original receiver/method spelling remains unresolved, so retain this owner.
#include "../../Include/GameClient/Drawable.h"
class Rva0029A469 {public: void rva0029A469(float);};
class Rva0029A41A {public: void rva0029A41A(RGBColor*);};
struct PrereqUnitRec {unsigned m_data[3]; ~PrereqUnitRec(){} };
// A declaration-only view keeps this already-owned provider out of line.
// The native call copies a 12-byte POD footprint, exactly as the canonical
// PrereqUnitRec provider does; this view asserts no preview record identity.
namespace _STL {
template<> class vector<PrereqUnitRec,allocator<PrereqUnitRec> > {
public: void push_back(const PrereqUnitRec&);
private: PrereqUnitRec *first,*last,*limit;
};
}

void InGameUI::rva002A470F(ThingTemplate *type,const ICoord2D *position,RGBColor color) {
 InGameUI::FormationPreviewPoolObject *pool=rva002A3E5A(type);
 // These borrowed ABI views preserve the existing pool's drawable/holder
 // declarations; the complete native helper establishes these operations.
 Drawable *drawable=*reinterpret_cast<Drawable**>(pool);
 if(drawable) {
  drawable->field_0b0=1.0f;
  RGBColor grey={0.5f,0.5f,0.5f};
  drawable->colorTint(&grey);
 }
 Rva0029A469 *decal=*reinterpret_cast<Rva0029A469**>(reinterpret_cast<char*>(pool)+4);
 if(decal) {
  decal->rva0029A469(1.0f);
  reinterpret_cast<Rva0029A41A*>(decal)->rva0029A41A(&color);
 }
 unsigned *empty=reinterpret_cast<unsigned*>(&color);
 empty[0]=0;empty[1]=0;empty[2]=0;
 reinterpret_cast<_STL::vector<PrereqUnitRec>&>(entries).push_back(reinterpret_cast<const PrereqUnitRec&>(color));
 Gen_p12pod *entry=entries.end-1;
 entry->unknown[0]=position->x;
 entry->unknown[1]=position->y;
 entry->pool=pool;
}

// Native 2A3E5A and 2A4BFC both read this one-byte formation-preview
// setting. Retail .data starts it at 1; its original identifier is unknown.
bool BfmeFormationPreviewUseDecals=true;

// Native 2A4BFC..2A4E1F (547B, RET 18): the formation-preview placement that
// InGameUI's formation preview (WB twin DC02D0, MathCoord2D.h asserts) calls
// per selected object. Target facts: for a horde (template +0x115 bit 5) with
// the decal flag set and a horde decal name on the object's or the given
// template, it walks the object's formation interface (slot 0x204 groups
// vector, slot 0x180 member count), averages the first `count` member
// positions (16-byte records in a vector at group +8), and places one preview
// per member at the screen position offset by the swapped average-minus-member
// delta through 0x2A470F; otherwise one preview at the position with the base
// template's decal. Structural: the containers are real STLport vectors (size()
// and operator[] re-derived at each use, as the WB twin's inlines show); names
// of the interface, groups and record fields are role-derived.
class Rva0029B732 { public: bool rva0029B732(); private: void *storage; };
class ThingTemplate {
public:
 char prefix[0x14]; Rva0029B732 decalName; float decalX,decalY;
 Rva0029B732 hordeName; char gap24[0x115-0x24]; unsigned char kindOf115;
};
class Object { public: char prefix[4]; ThingTemplate *type; void *rva0028C197() const; };
#include "../../../Libraries/Include/Lib/Coord2D.h"
struct FormationPosition { Coord2D pos; unsigned unknown[2]; };
struct FormationGroup { char prefix[8]; _STL::vector<FormationPosition> positions; };
class FormationInterface {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual unsigned count(int);
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual _STL::vector<FormationGroup *> *groups();
};
void InGameUI::rva002A4BFC(Object *object,ThingTemplate *type,const ICoord2D *position,RGBColor color) {
 if(!type) type=object->type;
 Rva0029B732 *name=&object->type->hordeName;
 if((object->type->kindOf115 & 0x20) && BfmeFormationPreviewUseDecals &&
    (name->rva0029B732() || type->hordeName.rva0029B732())) {
  if(name->rva0029B732()) type=object->type;
  FormationInterface *iface=static_cast<FormationInterface*>(object->rva0028C197());
  if(!iface) return;
  _STL::vector<FormationGroup *> *groups=iface->groups();
  unsigned total=iface->count(0);
  if(total<=0) return;
  int remaining=total;
  _STL::vector<FormationGroup *>::iterator end=groups->end();
  ICoord2D point;
  Coord2D average; average.x=0.0f; average.y=0.0f;
  _STL::vector<FormationGroup *>::iterator begin=groups->begin();
  for(_STL::vector<FormationGroup *>::iterator it=begin; remaining>0 && it!=end; ++it) {
   FormationGroup *group=*it;
   int count=group->positions.size();
   for(int i=0; remaining>0 && i<count; ++i) {
    --remaining;
    const Coord2D &p=group->positions[i].pos;
    average.x+=p.x;
    average.y+=p.y;
   }
  }
  float reciprocal=1.0f/total;
  average.x*=reciprocal; average.y*=reciprocal;
  remaining=total;
  for(_STL::vector<FormationGroup *>::iterator it=begin; remaining>0 && it!=end; ++it) {
   FormationGroup *group=*it;
   int count=group->positions.size();
   for(int i=0; remaining>0 && i<count; ++i) {
    --remaining;
    const Coord2D &p=group->positions[i].pos;
    Coord2D offset;
    offset.x=p.x; offset.y=p.y;
    point.x=(int)((float)position->x+average.y-offset.y);
    point.y=(int)((float)position->y+average.x-offset.x);
    rva002A470F(type,&point,color);
   }
  }
 } else {
  ThingTemplate *base=object->type;
  if(base->decalName.rva0029B732()) type=base;
  rva002A470F(type,position,color);
 }
}
