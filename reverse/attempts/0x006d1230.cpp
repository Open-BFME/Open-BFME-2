// ?rva006D1230@Rva006D1130@@QAEXPAPAVBfmeRefVGO@@0PAURva006D1130Iterator@@@Z
// partial score=0.8345104752588245 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
unsigned __cdecl bfmeDecVGO(unsigned *);
void __cdecl bfmeDropVGO(void*);
class BfmeRefVGO {public:BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO&);unsigned*m_bfmeP;};
class Rva006D1130Item:public BfmeRefVGO {public:Rva006D1130Item(){m_bfmeP=0;}~Rva006D1130Item(){if(m_bfmeP&&bfmeDecVGO(m_bfmeP)==0)bfmeDropVGO(m_bfmeP);}};
struct Rva006D1130Iterator {BfmeRefVGO *position,*begin,*end;};
BfmeRefVGO*Rva006D0460Copy(BfmeRefVGO*,BfmeRefVGO*,BfmeRefVGO*);
BfmeRefVGO*Rva006D04D0CopyBackward(Rva006D1130Iterator,Rva006D1130Iterator,BfmeRefVGO*);
Rva006D1130Iterator Rva006D0540Copy(BfmeRefVGO*,BfmeRefVGO*,Rva006D1130Iterator);
class Rva006D1130 {public:int count,capacity;Rva006D1130Item *data;Rva006D1130Item inlineData[1];void grow(int);void rva006D1230(BfmeRefVGO**first,BfmeRefVGO**last,Rva006D1130Iterator*dest);};
void Rva006D1130::rva006D1230(BfmeRefVGO**first,BfmeRefVGO**last,Rva006D1130Iterator*dest){
 BfmeRefVGO *end=*last;BfmeRefVGO *begin=*first;int added=end-begin;
 if(!added)return;
 int total=count+added;int oldCapacity=capacity;
 if(total<oldCapacity){
  BfmeRefVGO*oldEnd=data+count;
  if(dest->position==oldEnd){
   Rva006D0460Copy(begin,end,oldEnd);
   const Rva006D1130Item empty;
   data[total].bfmeAssignVGO(empty);
   __assume(empty.m_bfmeP==0);
   count=total;
  }else{
   Rva006D1130Iterator oldLast={oldEnd,data,oldEnd};
   Rva006D04D0CopyBackward(*dest,oldLast,data+(dest->position-data)+added);
   Rva006D0540Copy(*first,*last,*dest);
   const Rva006D1130Item empty;
   data[total].bfmeAssignVGO(empty);
   __assume(empty.m_bfmeP==0);
   count=total;
  }
 }else{
  int newCapacity=(int)(double(oldCapacity)*2.0);
  if(newCapacity<*(volatile int*)&total)newCapacity=total;
  int index=dest->position-data;
  grow(newCapacity);
  Rva006D1130Iterator next={data+index,data,data+count};
  rva006D1230(first,last,&next);
 }
}
