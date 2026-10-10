// cl: /O2 /MD /EHsc
// Target guide: rowed Rva006CD5A0Copy; native6CE890 passes two
// 8-byte entry pointers and a 12-byte output iterator by value. The hidden
// result is a 12-byte iterator. EAStringC assignment and int-at4 are target
// facts; original entry/container identities are unresolved. Native extent
// 6CDD90..6CDDF8 includes the complete return; old97B boundary cut inside
// the last iterator-field store. Byte104 is RET, followed by8 INT3 bytes.
class EAStringC {public:EAStringC &clear() throw();~EAStringC();EAStringC &operator=(const EAStringC &);void *data;};
struct Rva006CDD50Item {EAStringC name;int value;};
// Same release range-check expression as target Apt.cpp PlaybackIterator;
// WB1750B80 is empty even in debug. Keeping it preserves loop shape.
inline void iteratorRangeCheck(bool,const char*){}
struct Rva006CDD50Iterator {Rva006CDD50Item *position,*begin,*end;
 bool operator!=(const Rva006CDD50Iterator &other){iteratorRangeCheck(begin==other.begin && end==other.end,"Iterators are not in same range");return position!=other.position;}
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
class AptValueNameEntry {public:EAStringC name;int value;__forceinline AptValueNameEntry(){name.clear();value=0;}};
AptValueNameEntry *__cdecl Rva006CDBF0Resize(AptValueNameEntry *,int,int);
class Rva006CE660Vec {public:void rva006CE660(int); void insert(AptValueNameEntry *const &,AptValueNameEntry *const &,const Rva006CDD50Iterator &);int count,capacity;AptValueNameEntry *data;AptValueNameEntry inlineItems[2];
 Rva006CDD50Iterator begin(){Rva006CDD50Item *p=reinterpret_cast<Rva006CDD50Item *>(data);return Rva006CDD50Iterator(p,p,p+count);}
 Rva006CDD50Iterator end(){Rva006CDD50Item *p=reinterpret_cast<Rva006CDD50Item *>(data);return Rva006CDD50Iterator(p+count,p,p+count);}};
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

