// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253D88, 40 bytes. Behavior-side ctor completing the
// HordeNotifyTargetsOfImminentProbableCrushingUpdate file-unit (poolkey
// rowed at 0x253DB2, behavior instance factory rowed at 0x2551CF news 0x34
// with this ctor as sole raw caller; the non-Horde twin keeps its own
// poolkey 0x253E8E, factory 0x255207 and rowed ctor 0x253E64).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 with three explicit vtable stores at +0/+0xC/+0x10 via byte-wise
// pointer casts (StopSpecialPower precedent: explicit stores, no virtuals
// declared anywhere so no vtable is emitted here; all three immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the
// rowed UpdateModule spelling).

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00BF17EC[];  // ??_7Rva00253E19@@6BRva00253E19_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF17EC=??_7Rva00253E19@@6BRva00253E19_B2@@@")
extern "C" const void *const vtbl_00BF17F8[];  // ??_7Rva00253E19@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00BF17F8=??_7Rva00253E19@@6BRva0024A797@@@")

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
};

class HordeNotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule
{
public:
	HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeNotifyTargetsOfImminentProbableCrushingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00253D88
HordeNotifyTargetsOfImminentProbableCrushingUpdate::HordeNotifyTargetsOfImminentProbableCrushingUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BF17F8);
	*(unsigned int *)((char *)this + 0xC) = ((unsigned int)vtbl_00BEFF90);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00BF17EC);
}

// Native4CEB14..4CEB76. STLport4.5.3 _S_merge algorithm, from BFME1
// ba7dd inputs/vendor/stlport/stl/_list.c, using the verified distance helper.
// Nodes carry pointer-sized payloads at8; original list/owner names unknown.
// This helper's comparator home is the neighboring non-Horde constructor TU.
// Keep its declaration out of line: seeing the body changes register allocation.
class Rva004CEAB7 {
public: bool rva004CEAB7(void *,void *);
float x,y,z;
};
namespace _STL {
struct _List_node_base { _List_node_base *next,*prev; };
template <class Dummy> struct _List_global {
 static void _Transfer(_List_node_base *,_List_node_base *,_List_node_base *);
};
}
struct Rva004CEB14Node : _STL::_List_node_base { void *value; };
struct Rva004CEB14List { Rva004CEB14Node *head; };
void Rva004CEB14(Rva004CEB14List &dst, Rva004CEB14List &src, Rva004CEAB7 comp)
{
 Rva004CEB14Node *first1=(Rva004CEB14Node *)dst.head->next;
 Rva004CEB14Node *last1=dst.head;
 Rva004CEB14Node *first2=(Rva004CEB14Node *)src.head->next;
 Rva004CEB14Node *last2=src.head;
 while (first1!=last1 && first2!=last2) {
  if (comp.rva004CEAB7(first2->value, first1->value)) {
   Rva004CEB14Node *next=(Rva004CEB14Node *)first2->next;
   _STL::_List_global<bool>::_Transfer(first1,first2,next);
   first2=next;
  } else first1=(Rva004CEB14Node *)first1->next;
 }
 if (first2!=last2)
  _STL::_List_global<bool>::_Transfer(last1,first2,last2);
}
