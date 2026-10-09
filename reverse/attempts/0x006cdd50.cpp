// ?Rva006CDD50Copy@@YAPAURva006CDD50Item@@URva006CDD50Iterator@@0PAU1@@Z
// partial score=0.4062 date=2026-10-09
// cl: /O2 /MD /EHsc
// Semantic guide: rowed Rva006CD5A0Copy; native6CE890 establishes
// the first two 12-byte arguments and eight-byte entry assignment ABI.
class EAStringC {public:EAStringC &operator=(const EAStringC &);void *data;};
struct Rva006CDD50Item {EAStringC name;int value;};
struct Rva006CDD50Iterator {Rva006CDD50Item *position,*begin,*end;
 Rva006CDD50Iterator operator++(int){Rva006CDD50Iterator old=*this;++position;return old;}
};
Rva006CDD50Item *__cdecl Rva006CDD50Copy(Rva006CDD50Iterator first,Rva006CDD50Iterator last,Rva006CDD50Item *result){
 int count=last.position-first.position;
 Rva006CDD50Item *source=last.position-1;
 Rva006CDD50Item *destination=result+count-1;
 while(count){destination->name=source->name;destination->value=source->value;--source;--destination;--count;}
 return destination;
}
