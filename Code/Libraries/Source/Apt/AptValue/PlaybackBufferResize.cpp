// cl: /O2 /MD /EHsc
// Target guide: rowed Rva006CD5A0Copy; native6CE890 passes two
// 8-byte entry pointers and a 12-byte output iterator by value. The hidden
// result is a 12-byte iterator. EAStringC assignment and int-at4 are target
// facts; original entry/container identities are unresolved. Native extent
// 6CDD90..6CDDF8 includes the complete return; old97B boundary cut inside
// the last iterator-field store. Byte104 is RET, followed by8 INT3 bytes.
class EAStringC {public:EAStringC(const EAStringC &);__forceinline EAStringC() throw(){clear();} bool IsEqualTo(const EAStringC *) const;EAStringC &clear() throw();~EAStringC();EAStringC &operator=(const EAStringC &);void *data;};
// Default initialization delegates to clear: native owns one16B ICF body
// for both operations, including the empty-root reference increment.
struct Rva006CDD50Item {EAStringC name;int value;};
// Same release range-check expression as target Apt.cpp PlaybackIterator;
// WB1750B80 is empty even in debug. Keeping it preserves loop shape.
inline void iteratorRangeCheck(bool,const char*){}
struct Rva006CDD50Iterator {Rva006CDD50Item *position,*begin,*end;
 bool operator!=(const Rva006CDD50Iterator &other){iteratorRangeCheck(begin==other.begin && end==other.end,"Iterators are not in same range");return position!=other.position;}
 Rva006CDD50Iterator(){}
 Rva006CDD50Iterator(Rva006CDD50Item *p,Rva006CDD50Item *b,Rva006CDD50Item *e):position(p),begin(b),end(e){}
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
AptValueNameEntry *__cdecl Rva006CDBF0Resize(AptValueNameEntry *,int,int);
class Rva006CE660Vec {public:void rva006CEB10(const EAStringC &);void rva006CE660(int); void insert(AptValueNameEntry *const &,AptValueNameEntry *const &,const Rva006CDD50Iterator &);int count,capacity;AptValueNameEntry *data;AptValueNameEntry inlineItems[2];
 Rva006CDD50Iterator begin(){Rva006CDD50Item *p=reinterpret_cast<Rva006CDD50Item *>(data);return Rva006CDD50Iterator(p,p,p+count);}
 Rva006CDD50Iterator end(){return Rva006CDD50Iterator(reinterpret_cast<Rva006CDD50Item *>(data+count),reinterpret_cast<Rva006CDD50Item *>(data),reinterpret_cast<Rva006CDD50Item *>(data+count));}};
void Rva006CE660Vec::rva006CE660(int want){
 if(want<=capacity)return;if(want<=1){capacity=want;return;}
 AptValueNameEntry *newData=Rva006CDBF0Resize(0,0,want+1);
 Rva006CDD50Item *begin=reinterpret_cast<Rva006CDD50Item *>(data),*end=begin+count;
 Rva006CDD50Iterator first(begin,begin,end),last(end,begin,end);
 Rva006CDE00Copy(first,last,reinterpret_cast<Rva006CDD50Item *>(newData));
 capacity=want;if(data!=inlineItems)Rva006CDBF0Resize(data,0,0);
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
  rva006CE660(next);
  Rva006CDD50Item *begin=reinterpret_cast<Rva006CDD50Item *>(data);
  Rva006CDD50Iterator at=this->begin()+offset;
  insert(first,last,at);
 }
}

AptValueNameEntry *__cdecl Rva006CDBF0Resize(AptValueNameEntry *old,int oldCount,int want) {
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
class Rva006D07E0Key {public: unsigned *m_object; __forceinline ~Rva006D07E0Key(){if(m_object && bfmeDecVGO(m_object)==0)bfmeDropVGO(m_object);}};
class Rva006D0A30List {public:Rva006D07E0Key findSpecial(const EAStringC *);};
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
__forceinline void appendPlaybackItem(Rva006CE660Vec &v,const AptValueNameEntry &value,Rva006CDD50Iterator &position) {
 AptValueNameEntry *last=const_cast<AptValueNameEntry *>(&value)+1,*first=last-1;
 position=v.end();v.insert(first,last,position);
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
