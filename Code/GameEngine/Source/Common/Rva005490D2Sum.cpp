// stlport
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?rva005490AE@Rva005490D2@@QBEHXZ, RVA 0x005490AE, 36B
// ?rva005490D2@Rva005490D2@@QBEHXZ, RVA 0x005490D2, 31B
// Max and summing loops over the array at +4 with count at +0 via double
// indirection; retail places them back to back. The max takes the dword at
// +0x564 with cmovg (callers 0x00549403 and 0x0054945F), which MSVC 7.1
// emits only under /arch:SSE; the sum adds the dword at +0x568 (single
// caller at 0x005493CC). xor-first and dec/jne point to /O1; neighbours are
// Disp getters and a clamped setter.
struct Leaf005490D2 {
	char pad[0x564];
	int field564;
	int field568;
};
#include "../../../Libraries/Include/Lib/Coord2D.h"
struct FormationKind {char pad[0x78];int kind;};
struct FormationAIUpdate {int unused;FormationKind*data;};
struct FormationUnitGate {char pad[0x1f0];FormationAIUpdate*update;};
struct Mid005490D2 {
	int unk0;
	Leaf005490D2 *leaf;
 char pad8[0x250];FormationUnitGate*gate;char pad25C[0x1b4];int formationId;Coord2D formationOffset;
};
struct Rva005490D2 {
	
	int count;
	Mid005490D2 *array[6];
	int rva005490AE() const;
	int rva005490D2() const;
 void rva005490F1(const Coord2D*origin,int formationId);
};
int Rva005490D2::rva005490AE() const
{
	int best = 0;
	for (int i = 0; i < count; ++i) {
		int v = array[i]->leaf->field564;
		if (v > best)
			best = v;
	}
	return best;
}
int Rva005490D2::rva005490D2() const
{
	int total = 0;
	int n = count;
	if (n > 0) {
		Mid005490D2 **p = (Mid005490D2 **)array;
		do {
			total += (*p)->leaf->field568;
			++p;
		} while (--n);
	}
	return total;
}



#include <deque>
// Formation rows are 0x1C: count plus six unit pointers. Width clamp
// 0x549237 and row stride in the formation builder independently prove this.
// TheAI/data offsets are target facts; the original spacing names are unknown.
struct FormationSpacingView {char pad[0xa0];float spacingA0,spacingA4;char padA8[0xc];int widthB4;};
class AI {public:char pad[0x18];FormationSpacingView*data;};
extern AI*TheAI;
class Rva00549252 {public:void rva00549252();};
class Rva0015A390Inner {public:int dword_0,dword_4,dword_8,dword_c,dword_10,dword_14;};
class Rva0015A390Bucket {public:Rva0015A390Bucket();int dword_0;Rva0015A390Inner inner_4;};
class FormationSquad {
public:
 FormationSquad();
 void rva00549425(Coord2D*out);
 void rva00549345(const Coord2D*origin,int formationId);

 int rows,width;
 Rva0015A390Bucket rowStorage[10];
 int unitCount;
 Mid005490D2*units[36];
 int totalHeight;
 bool ready;
};
// Target549425..549489 (100B). The served123B boundary includes two
// independent count getters at549489 and549493. The target loop repeatedly
// reads row[0], with no row-pointer advance; preserve that observable behavior.
// WB identifies the family, but its ApplyUnitPositions pairing is broader
// than this body, so the member's original name remains unknown.
void FormationSquad::rva00549425(Coord2D*out){
 if(!ready)reinterpret_cast<Rva00549252*>(this)->rva00549252();
 FormationSpacingView*data=TheAI->data;
 float height=totalHeight*data->spacingA0;
 int widthTotal=0;
 for(int i=0;i<rows;++i)widthTotal+=reinterpret_cast<Rva005490D2*>(rowStorage)[0].rva005490AE();
 out->x=widthTotal*data->spacingA4;
 out->y=height;
}

// Retail's independent getters subtract two16B deque iterators over8B
// elements. This is a typed ABI view of the existing concrete owner; it
// does not establish the original element type or container field names.
struct BfmeE8 {int a,b;};
template<> int _STL::_Deque_iterator_base<BfmeE8>::_M_subtract(const _STL::_Deque_iterator_base<BfmeE8>&)const;
struct FormationDequeView {
 _STL::_Deque_iterator_base<BfmeE8>start,finish;
 int size()const{return finish._M_subtract(start);}
};
class Rva00549489 {public:int get()const;FormationDequeView view;};
int Rva00549489::get()const{return view.size();}
class Rva00549493 {public:int get()const;char pad[0x14];FormationDequeView view;};
int Rva00549493::get()const{return view.size();}

// Native5491E4..549237 83B; WB caller array stride1BC establishes
// this as the FormationSquad constructor. Row default lifetimes initialize
// ten count/six-pointer records before resetting the remaining unit list.
// Existing neutral Bucket constructor clears precisely these seven words;
// its 28B storage view preserves the provider declaration and original name
// uncertainty. Width default is the target AI data field+B4 doubled.
FormationSquad::FormationSquad():rows(0),width(TheAI->data->widthB4*2),unitCount(0),totalHeight(0),ready(false){
 for(int i=0;i<36;++i)units[i]=0;
}

// Native5490F1..5491E4 complete243B. Target unit+410 ID and+414
// local offset plus gate258/1F0/kind78 are independently visible here.
// A scalar float copy preserves the native SSE loads and both spill homes;
// the canonical aggregate assignment stores the resulting eight bytes.
struct FormationPosition:Coord2D {FormationPosition(const Coord2D&rhs){x=rhs.x;y=rhs.y;}};
void Rva005490D2::rva005490F1(const Coord2D*origin,int formationId){
 int depth=0;
 for(int i=0;i<count;++i){
  int height=array[i]->leaf->field568;
  FormationSpacingView*data=TheAI->data;
  FormationPosition position(*origin);position.y+=(depth+height*0.5f)*data->spacingA0;position.x-=array[i]->leaf->field564*data->spacingA4*0.5f;
  array[i]->formationId=formationId;
  Mid005490D2*unit=array[i];
  if(unit->gate&&unit->gate->update&&unit->gate->update->data->kind==0){position.x*=0.5f;position.y*=0.5f;}
  unit->formationOffset=position;
  depth+=height;
 }
}

// Native549345..54941E complete219B. Scalar origin copying keeps
// both floats live through the visible integer-only row sum; starting
// columns before the row clamp preserves native initialization order.
void FormationSquad::rva00549345(const Coord2D*origin,int formationId){
 float halfColumn=TheAI->data->spacingA4*0.5f;
 float height=totalHeight*TheAI->data->spacingA0;
 int columns=0;
 if(rows>10)rows=10;
 for(int i=0;i<rows;++i){
  FormationSpacingView*data=TheAI->data;
  Rva005490D2*current=reinterpret_cast<Rva005490D2*>(&rowStorage[i]);
  FormationPosition position(*origin);
  position.x-=columns*data->spacingA4;
  position.x+=halfColumn;
  position.y+=(height-current->rva005490D2()*data->spacingA0)*0.5f;
  current->rva005490F1(&position,formationId);
  columns+=current->rva005490AE();
 }
}
