// cl: /O2 /MD /EHsc
// Semantic guide: rowed Rva006CD5A0Copy; native6CE890 passes two
// 8-byte entry pointers and a 12-byte output iterator by value. The hidden
// result is a 12-byte iterator. EAStringC assignment and int-at4 are target
// facts; original entry/container identities are unresolved. Native extent
// 6CDD90..6CDDF8 includes the complete return; old97B boundary cut inside
// the last iterator-field store. Byte104 is RET, followed by8 INT3 bytes.
class EAStringC {public:EAStringC &operator=(const EAStringC &);void *data;};
struct Rva006CDD50Item {EAStringC name;int value;};
struct Rva006CDD50Iterator {Rva006CDD50Item *position,*begin,*end;
 Rva006CDD50Iterator operator++(int){Rva006CDD50Iterator old=*this;++position;return old;}
};
Rva006CDD50Iterator __cdecl Rva006CDD90Copy(Rva006CDD50Item *first,Rva006CDD50Item *last,Rva006CDD50Iterator result){
 for(;first!=last;++first){Rva006CDD50Iterator destination=result++;destination.position->name=first->name;destination.position->value=first->value;}
 return result;
}
