// ?rva006CEB10@Rva006CEB10Playback@@QAEXABVEAStringC@@@Z
// partial score=1.0 date=2026-10-10
// ?rva006CEB10@Rva006CEB10Playback@@QAEXABVEAStringC@@@Z
// partial score=0.9311 date=2026-10-09
// cl: /O2 /MD /EHsc
// Native6CEB10..6CEC85; WB174EC90. The containing Apt.cpp provides
// the count/capacity/items/inline2 view; original owner name is unknown.
class EAStringC {public: EAStringC(const EAStringC &); ~EAStringC(); bool IsEqualTo(const EAStringC *) const; void *data;};
unsigned __cdecl bfmeDecVGO(unsigned *);
void __cdecl bfmeDropVGO(void *);
class Rva006D07E0Key {public: unsigned *m_object; ~Rva006D07E0Key(){if(m_object && bfmeDecVGO(m_object)==0)bfmeDropVGO(m_object);}};
class Rva006D0A30List {public:Rva006D07E0Key findSpecial(const EAStringC *);};
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
class AptValueNameEntry {public:EAStringC m_name; int m_value; AptValueNameEntry(const EAStringC &name,int value):m_name(name),m_value(value){}};
typedef AptValueNameEntry PlaybackItem;
inline void iteratorCheck(bool,const char *){}
struct Rva006CDD50Iterator {public:PlaybackItem *cur,*first,*last;
 Rva006CDD50Iterator(){}
 Rva006CDD50Iterator(PlaybackItem*c,PlaybackItem*f,PlaybackItem*l):cur(c),first(f),last(l){}
 Rva006CDD50Iterator &operator++(){++cur;return *this;}
 PlaybackItem &operator*(){iteratorCheck(cur>=first && cur<last,"Trying to dereference an invalid iterator");return *cur;}
 bool operator!=(const Rva006CDD50Iterator &other){iteratorCheck(first==other.first && last==other.last,"Iterators are not in same range");return cur!=other.cur;}
};
class Rva006CE660Vec {public:void insert(PlaybackItem *const &first,PlaybackItem *const &last,const Rva006CDD50Iterator &position);};
class Rva006CEB10Playback {public:int size,capacity;PlaybackItem *items;PlaybackItem inlineItems[2];
 void rva006CEB10(const EAStringC &name);
 Rva006CDD50Iterator begin(){return Rva006CDD50Iterator(items,items,items+size);}
 Rva006CDD50Iterator end(){return Rva006CDD50Iterator(items+size,items,items+size);}
 void append(const PlaybackItem &value,Rva006CDD50Iterator &position){PlaybackItem *last=const_cast<PlaybackItem *>(&value)+1,*first=last-1;position=end();
 reinterpret_cast<Rva006CE660Vec *>(this)->insert(first,last,position);}
};
void Rva006CEB10Playback::rva006CEB10(const EAStringC &name){
 for(Rva006CDD50Iterator it=begin();it!=end();++it){
  if((*it).m_name.IsEqualTo(&name)){
   if((*it).m_value==2)(*it).m_value=3;
   return;
  }
 }
 bool found=reinterpret_cast<Rva006D0A30List *>(g_rva00893030Manager)->findSpecial(&name).m_object!=0;
 Rva006CDD50Iterator position;
 if(found)append(PlaybackItem(name,3),position);else append(PlaybackItem(name,1),position);
}
