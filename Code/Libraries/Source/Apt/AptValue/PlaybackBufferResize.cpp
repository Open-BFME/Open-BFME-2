// cl: /O2 /MD /EHsc
// Target guide: rowed Rva006CD5A0Copy; native6CE890 passes two
// 8-byte entry pointers and a 12-byte output iterator by value. The hidden
// result is a 12-byte iterator. EAStringC assignment and int-at4 are target
// facts; original entry/container identities are unresolved. Native extent
// 6CDD90..6CDDF8 includes the complete return; old97B boundary cut inside
// the last iterator-field store. Byte104 is RET, followed by8 INT3 bytes.
#include "../EAStringC.h"
// Default construction uses the existing16B provider, ICF-folded with clear.
// A TU-local clear forwarder would be the first competing constructor copy.
struct Rva006CDD50Item {EAStringC name;int value;};
// Same release range-check expression as target Apt.cpp PlaybackIterator;
// WB1750B80 is empty even in debug. Keeping it preserves loop shape.
inline void iteratorRangeCheck(bool,const char*){}
struct Rva006CDD50Iterator {Rva006CDD50Item *position,*begin,*end;
 bool operator!=(const Rva006CDD50Iterator &other){iteratorRangeCheck(begin==other.begin && end==other.end,"Iterators are not in same range");return position!=other.position;}
 Rva006CDD50Iterator(){}
 Rva006CDD50Iterator(Rva006CDD50Item *current,Rva006CDD50Item *rangeBegin,Rva006CDD50Item *rangeEnd):position(current),begin(rangeBegin),end(rangeEnd){}
 int operator-(const Rva006CDD50Iterator &other)const{iteratorRangeCheck(begin==other.begin && end==other.end,"Iterators are not in same range");return position-other.position;}
 Rva006CDD50Iterator operator+(int amount)const {return Rva006CDD50Iterator(position+amount,begin,end);}
 Rva006CDD50Iterator operator++(int){Rva006CDD50Iterator old=*this;++position;return old;}
};
Rva006CDD50Iterator __cdecl Rva006CDD90Copy(Rva006CDD50Item *,Rva006CDD50Item *,Rva006CDD50Iterator);
Rva006CDD50Item *__cdecl Rva006CDD50Copy(Rva006CDD50Iterator,Rva006CDD50Iterator,Rva006CDD50Item *);
Rva006CDD50Item *__cdecl Rva006CDE00Copy(Rva006CDD50Iterator,Rva006CDD50Iterator,Rva006CDD50Item *);

// Native6CE660 and allocation6CF956 establish count/capacity/data
// and two8B entries at+0C. Original container name is unresolved.
class AptValueNameEntry {public:EAStringC name;int value;AptValueNameEntry(const EAStringC&n,int v):name(n),value(v){} __forceinline AptValueNameEntry(){value=0;}};
AptValueNameEntry *__cdecl resizeArray(AptValueNameEntry *,int,int);
class Rva006CE660Vec {public:void rva006CEB10(const EAStringC &);void updatePlaybackState(const EAStringC *,int,int,int);void rva006D0A10(const EAStringC *);void reserve(int); void insert(AptValueNameEntry *const &,AptValueNameEntry *const &,const Rva006CDD50Iterator &);void append(AptValueNameEntry *);int count,capacity;AptValueNameEntry *data;AptValueNameEntry inlineItems[2];
 Rva006CDD50Iterator begin(){Rva006CDD50Item *firstItem=reinterpret_cast<Rva006CDD50Item *>(data);return Rva006CDD50Iterator(firstItem,firstItem,firstItem+count);}
 Rva006CDD50Iterator end(){return Rva006CDD50Iterator(reinterpret_cast<Rva006CDD50Item *>(data+count),reinterpret_cast<Rva006CDD50Item *>(data),reinterpret_cast<Rva006CDD50Item *>(data+count));}};
void Rva006CE660Vec::reserve(int want){
 if(want<=capacity)return;if(want<=1){capacity=want;return;}
 AptValueNameEntry *newData=resizeArray(0,0,want+1);
 Rva006CDD50Item *begin=reinterpret_cast<Rva006CDD50Item *>(data),*end=begin+count;
 Rva006CDD50Iterator first(begin,begin,end),last(end,begin,end);
 Rva006CDE00Copy(first,last,reinterpret_cast<Rva006CDD50Item *>(newData));
 capacity=want;if(data!=inlineItems)resizeArray(data,0,0);
 data=newData;data[count]=AptValueNameEntry();
}

class Rva006CD5A0Elem;
Rva006CD5A0Elem *__cdecl Rva006CD5A0Copy(Rva006CD5A0Elem *,Rva006CD5A0Elem *,Rva006CD5A0Elem *);
void Rva006CE660Vec::insert(AptValueNameEntry *const &first,AptValueNameEntry *const &last,const Rva006CDD50Iterator &position) {
 
 int added=last-first;
 if(!added)return;
 int want=count+added;
 if(want<capacity){
  AptValueNameEntry *end=data+count;
  if(position.position==reinterpret_cast<Rva006CDD50Item *>(end)){
   Rva006CD5A0Copy(reinterpret_cast<Rva006CD5A0Elem *>(first),reinterpret_cast<Rva006CD5A0Elem *>(last),reinterpret_cast<Rva006CD5A0Elem *>(end));
   data[want]=AptValueNameEntry();
  }else{
   Rva006CDD50Item *begin=reinterpret_cast<Rva006CDD50Item *>(data),*finish=reinterpret_cast<Rva006CDD50Item *>(end);
   Rva006CDD50Iterator tail(finish,begin,finish);
   Rva006CDD50Copy(position,tail,begin+((position.position-begin)+added));
   Rva006CDD90Copy(reinterpret_cast<Rva006CDD50Item *>(first),reinterpret_cast<Rva006CDD50Item *>(last),position);
   data[want]=AptValueNameEntry();
  }
  count=want;
 }else{
  int next=(int)(2.0*capacity);
  if(next<want)next=want;
  int offset=position-begin();
  reserve(next);
  Rva006CDD50Item *begin=reinterpret_cast<Rva006CDD50Item *>(data);
  Rva006CDD50Iterator at=this->begin()+offset;
  insert(first,last,at);
 }
}

AptValueNameEntry *__cdecl resizeArray(AptValueNameEntry *old,int oldCount,int want) {
 AptValueNameEntry *result=0;
 if(!old)return new AptValueNameEntry[want];
 if(want){
  result=new AptValueNameEntry[want];
  int count=want<oldCount?want:oldCount;
  AptValueNameEntry *destination=result;
  while(count){
   AptValueNameEntry *cur=destination++;
   cur->name=old->name;
   cur->value=old->value;
   ++old;
   --count;
  }
 }
 delete[] old;
 return result;
}


// Native6CEB10..6CEC85 /373B and WB174EC90 establish playback-name
// checkpoint transitions2->3 and insertion of state3 or1. The original
// method/container names remain unresolved; the existing Vec owner has
// the independently proved count/capacity/items/inline2 layout.
unsigned __cdecl bfmeDecVGO(unsigned *);
void __cdecl bfmeDropVGO(void *);
class Rva006D07E0Key {public: unsigned *m_object; __declspec(dllimport) __forceinline ~Rva006D07E0Key(){if(m_object && bfmeDecVGO(m_object)==0)bfmeDropVGO(m_object);}};
#include "../Rva006D0A30List.h"
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
__forceinline void appendPlaybackItem(Rva006CE660Vec &buffer,const AptValueNameEntry &value,Rva006CDD50Iterator &position) {
 AptValueNameEntry *last=const_cast<AptValueNameEntry *>(&value)+1,*first=last-1;
 position=buffer.end();buffer.insert(first,last,position);
}
void Rva006CE660Vec::rva006CEB10(const EAStringC &name) {
 for(Rva006CDD50Iterator it=begin();it!=end();it++){
  if(it.position->name.IsEqualTo(&name)){
   if(it.position->value==2)it.position->value=3;
   return;
  }
 }
 bool found=reinterpret_cast<Rva006D0A30List *>(g_rva00893030Manager)->findSpecial(&name).m_object!=0;
 Rva006CDD50Iterator position;
 if(found)appendPlaybackItem(*this,AptValueNameEntry(name,3),position);
 else appendPlaybackItem(*this,AptValueNameEntry(name,1),position);
}

// Native6D0930..6D0A0D RET10: the general form of rva006CEB10. A key
// already present has its value replaced only when it equals the expected
// one; an absent key is appended with the initial value. Callers and the
// original member name are unresolved.
void Rva006CE660Vec::updatePlaybackState(const EAStringC *key,int expected,int replacement,int initial) {
 for(Rva006CDD50Iterator it=begin();it!=end();it++){
  if(it.position->name.IsEqualTo(key)){
   if(it.position->value==expected)it.position->value=replacement;
   return;
  }
 }
 Rva006CDD50Iterator position;
 appendPlaybackItem(*this,AptValueNameEntry(*key,initial),position);
}

// Native 0x006CEA90..0x006CEACF: append one entry; last must be computed before first (retail
// lea value+8 into the spilled home before the container loads).
void Rva006CE660Vec::append(AptValueNameEntry *value){AptValueNameEntry *last=value+1,*first=value;insert(first,last,end());}

// Native6D0A10..6D0A22 RET4: the fixed-argument forwarder beside the rowed
// rva006D0930 -- the same name with the constants 1, 3 and 2 on the same
// receiver. Address name.
void Rva006CE660Vec::rva006D0A10(const EAStringC *name){updatePlaybackState(name,1,3,2);}
