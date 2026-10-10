// ?intern@Rva006D1450@@QAEXVRva006D07E0Key@@@Z
// partial score=0.7927900407992468 date=2026-10-10
// ?intern@Rva006D1450@@QAEXVRva006D07E0Key@@@Z
// partial score=0.7927900407992468 date=2026-10-09
// cl: /MD /EHsc
class EAStringC {void*data;};
class Rva006D0280 {public:int m_useCount;int unused4;EAStringC name8;int typeC;int argument10;void*object14;void*buffer18;~Rva006D0280();};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D07E0Key {public:
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&o):m_object(o.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*r=m_object;if(r&&--r->m_useCount==0){Rva006D0280*p=m_object;if(p){p->~Rva006D0280();g_pChainBlockAllocator->freeBlock(p,0x1c);}}}
 Rva006D0280*m_object;
};
class BfmeRefVGO {public:unsigned*m_bfmeP;};
struct Rva006D1130Iterator {BfmeRefVGO *position,*begin,*end;};
class Rva006D1130 {public:int count,capacity;BfmeRefVGO *data;BfmeRefVGO inlineData[1];__forceinline bool contains(Rva006D0280*key){for(BfmeRefVGO *p=data,*last=p+count;p!=last;++p)if(p->m_bfmeP==(unsigned*)key)return true;return false;}__forceinline void append(void *source){BfmeRefVGO *end=(BfmeRefVGO*)source+1,*begin=(BfmeRefVGO*)source;BfmeRefVGO*last=data+count;Rva006D1130Iterator dest={last,data,last};rva006D1230(&begin,&end,&dest);}void rva006D1230(BfmeRefVGO**,BfmeRefVGO**,Rva006D1130Iterator*);};
class Rva006D1450 {public:int unknown0;Rva006D1130 entries;void intern(Rva006D07E0Key);};
void Rva006D1450::intern(Rva006D07E0Key key){if(!entries.contains(key.m_object))entries.append(&key);}
