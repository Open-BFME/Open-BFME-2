// ?append@Rva006CE660Vec@@QAEXPAVAptValueNameEntry@@@Z
// partial score=0.9227777777777778 date=2026-10-10
// cl: /O2 /DNDEBUG /MD /EHsc
// Native6CE3D0..6CE554 resizes an array of four-byte refcounted handles.
// The allocation header and array cookie are separate DWORDs. Existing
// element ctor13260 and dtorA9DF3 provide independently verified lifetimes.
// Native advances the input pointer and deletes that advanced pointer; preserve
// this target behaviour without assuming the original template was correct.
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270 {public:void freeBlock(void *,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
class Rva00894D80Accessor {public:static unsigned increment(unsigned *);};
class BfmeRefVGO {
protected:unsigned *value;
public:
 BfmeRefVGO():value(0){}
 ~BfmeRefVGO();
 BfmeRefVGO &operator=(const BfmeRefVGO &other){
  if(&other!=this){
   if(value && !Rva006CFDF0DecRef((int *)value))bfmeDropVGO(value);
   value=other.value;
   if(value)Rva00894D80Accessor::increment(value);
  }
  return *this;
 }
};
class Rva004A9DF3Element:public BfmeRefVGO {
public:
 Rva004A9DF3Element(){}
 ~Rva004A9DF3Element();
 static void *operator new[](unsigned n){unsigned *p=(unsigned *)((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n+4);*p=n;return p+1;}
 static void operator delete[](void *p){unsigned *q=(unsigned *)p-1;g_pChainBlockAllocator->freeBlock(q,*q+4);}
};
Rva004A9DF3Element *Rva006CE3D0Resize(Rva004A9DF3Element *old,int oldCount,int newCount){
 Rva004A9DF3Element *fresh=0;
 if(!old)return new Rva004A9DF3Element[newCount];
 if(newCount){
  fresh=new Rva004A9DF3Element[newCount];
  int count=newCount<oldCount?newCount:oldCount;
  Rva004A9DF3Element *destination=fresh;
  while(count){*destination++=*old++;--count;}
 }
 delete[] old;
 return fresh;
}

// Target guide: rowed Rva006CD5A0Copy; native6CE890 passes two
// 8-byte entry pointers and a 12-byte output iterator by value. The hidden
// result is a 12-byte iterator. EAStringC assignment and int-at4 are target
// facts; original entry/container identities are unresolved. Native extent
// 6CDD90..6CDDF8 includes the complete return; old97B boundary cut inside
// the last iterator-field store. Byte104 is RET, followed by8 INT3 bytes.
class EAStringC {public:EAStringC();EAStringC(const EAStringC &); bool IsEqualTo(const EAStringC *) const;EAStringC &clear();~EAStringC();EAStringC &operator=(const EAStringC &);void *data;};
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
class AptValueNameEntry {public:EAStringC name;int value;__forceinline AptValueNameEntry():value(0){}
 AptValueNameEntry(const EAStringC &s,int v):name(s),value(v){}};
AptValueNameEntry *__cdecl Rva006CDBF0Resize(AptValueNameEntry *,int,int);
class Rva006CE660Vec {public:void rva006CE660(int);void append(AptValueNameEntry *); void insert(AptValueNameEntry *const &,AptValueNameEntry *const &,const Rva006CDD50Iterator &);int count,capacity;AptValueNameEntry *data;AptValueNameEntry inlineItems[2];
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

unsigned __cdecl bfmeDecVGO(unsigned *);
void __cdecl bfmeDropVGO(void *);
class Rva006D07E0Key {public: unsigned *m_object; ~Rva006D07E0Key(){if(m_object && bfmeDecVGO(m_object)==0)bfmeDropVGO(m_object);}};
class Rva006D0A30List {public:Rva006D07E0Key findSpecial(const EAStringC *);};
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
typedef AptValueNameEntry PlaybackItem;
inline void iteratorCheck(bool,const char *){}
struct PlaybackIterator {public:PlaybackItem *cur,*first,*last;
 PlaybackIterator(){}
 PlaybackIterator(PlaybackItem*c,PlaybackItem*f,PlaybackItem*l):cur(c),first(f),last(l){}
 PlaybackIterator &operator++(){++cur;return *this;}
 PlaybackItem &operator*(){iteratorCheck(cur>=first && cur<last,"Trying to dereference an invalid iterator");return *cur;}
 bool operator!=(const PlaybackIterator &other){iteratorCheck(first==other.first && last==other.last,"Iterators are not in same range");return cur!=other.cur;}
};
class Rva006CEB10Playback {public:int size,capacity;PlaybackItem *items;PlaybackItem inlineItems[2];
 void rva006CEB10(const EAStringC &name);
 PlaybackIterator begin(){return PlaybackIterator(items,items,items+size);}
 PlaybackIterator end(){return PlaybackIterator(items+size,items,items+size);}
 void append(const PlaybackItem &value,PlaybackIterator &position){PlaybackItem *last=const_cast<PlaybackItem *>(&value)+1,*first=last-1;position=end();
 reinterpret_cast<Rva006CE660Vec *>(this)->insert(first,last,reinterpret_cast<const Rva006CDD50Iterator &>(position));}
};
void Rva006CEB10Playback::rva006CEB10(const EAStringC &name){
 for(PlaybackIterator it=begin();it!=end();++it){
  if((*it).name.IsEqualTo(&name)){
   if((*it).value==2)(*it).value=3;
   return;
  }
 }
 bool found=reinterpret_cast<Rva006D0A30List *>(g_rva00893030Manager)->findSpecial(&name).m_object!=0;
 PlaybackIterator position;
 if(found)append(PlaybackItem(name,3),position);else append(PlaybackItem(name,1),position);
}

void Rva006CE660Vec::append(AptValueNameEntry *value){AptValueNameEntry *first=value,*last=first+1;insert(first,last,end());}
