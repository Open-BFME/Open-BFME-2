// ?rva006CE660@Rva006CE660Vec@@QAEXH@Z
// partial score=0.9317 date=2026-10-09
// cl: /O2 /MD /EHsc
// Semantic guide: rowed Rva006CD5A0Copy; native6CE890 passes two
// 8-byte entry pointers and a 12-byte output iterator by value. The hidden
// result is a 12-byte iterator. EAStringC assignment and int-at4 are target
// facts; original entry/container identities are unresolved. Native extent
// 6CDD90..6CDDF8 includes the complete return; old97B boundary cut inside
// the last iterator-field store. Byte104 is RET, followed by8 INT3 bytes.
class EAStringC {public:void clear();~EAStringC();EAStringC &operator=(const EAStringC &);void *data;};
struct Rva006CDD50Item {EAStringC name;int value;};
// Same release range-check expression as target Apt.cpp PlaybackIterator;
// WB1750B80 is empty even in debug. Keeping it preserves loop shape.
inline void iteratorRangeCheck(bool,const char*){}
struct Rva006CDD50Iterator {Rva006CDD50Item *position,*begin,*end;
 bool operator!=(const Rva006CDD50Iterator &other){iteratorRangeCheck(begin==other.begin && end==other.end,"Iterators are not in same range");return position!=other.position;}
 Rva006CDD50Iterator operator++(int){Rva006CDD50Iterator old=*this;++position;return old;}
};
Rva006CDD50Iterator __cdecl Rva006CDD90Copy(Rva006CDD50Item *first,Rva006CDD50Item *last,Rva006CDD50Iterator result){
 for(;first!=last;++first){Rva006CDD50Iterator destination=result++;destination.position->name=first->name;destination.position->value=first->value;}
 return result;
}

// Native6CDD50..6CDD90;6CE966 passes two12B iterator values plus
// destination-begin pointer. The count-loop copies8B entries backward
// and returns the pointer one before destination-begin, including empty ranges.
Rva006CDD50Item *__cdecl Rva006CDD50Copy(Rva006CDD50Iterator first,Rva006CDD50Iterator last,Rva006CDD50Item *result){
 int count=last.position-first.position; result+=count-1; --last.position;
 while(count){result->name=last.position->name;result->value=last.position->value;--last.position;--result;--count;} return result;
}

Rva006CDD50Item *__cdecl Rva006CDE00Copy(Rva006CDD50Iterator first,Rva006CDD50Iterator last,Rva006CDD50Item *result){
 for(;;){if(!(first!=last))break;Rva006CDD50Item *destination=result++;Rva006CDD50Iterator source=first++;destination->name=source.position->name;destination->value=source.position->value;}return result;
}

// Corrected growth model. BF1 Rva00893CE0ContainerResize.cpp is the
// semantic guide; inline storage at+0C is two8B entries, not a last pointer.
class AptValueNameEntry {public:EAStringC name;int value;AptValueNameEntry(){name.clear();value=0;}};
AptValueNameEntry *__cdecl Rva006CDBF0Resize(AptValueNameEntry *,int,int);
class Rva006CE660Vec {public:void rva006CE660(int);int count,capacity;AptValueNameEntry *data;AptValueNameEntry inlineItems[2];};
void Rva006CE660Vec::rva006CE660(int want){
 if(want<=capacity)return;if(want<=1){capacity=want;return;}
 AptValueNameEntry *newData=Rva006CDBF0Resize(0,0,want+1);
 Rva006CDD50Item *begin=reinterpret_cast<Rva006CDD50Item *>(data),*end=begin+count;
 Rva006CDD50Iterator first={begin,begin,end},last={end,begin,end};
 Rva006CDE00Copy(first,last,reinterpret_cast<Rva006CDD50Item *>(newData));
 capacity=want;if(data!=inlineItems)Rva006CDBF0Resize(data,0,0);
 data=newData;data[count]=AptValueNameEntry();
}
