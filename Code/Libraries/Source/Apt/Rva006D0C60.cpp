// cl: /MD /EHsc
// Retail6D0C60..6D0D6A RET4,266B; WB1751FE0 confirms dependency
// lookup through the same tracker and a counted owner argument. Target
// table14 has count28, records2c stride16, leading C-string per record.
// Existing Bfme5ThirtyFour findSpecial and counted-key layout are the
// semantic guide. Original method/container/record names remain unknown.
// A named counted pointer for decrement, followed by a fresh pointer for
// deletion, plus getTable accessor restores the native register schedule.
class EAStringC {void *data;public:EAStringC(const char*);~EAStringC();};
struct Rva006D0660Record {const char *text;char pad[12];};
struct Rva006D0660Table {char pad[0x28];int count28;Rva006D0660Record *records2c;};
class Rva006D0280 {public:int m_useCount;int unknown4;EAStringC name8;int typeC;int unknown10;Rva006D0660Table *table14;int unknown18;void teardown();};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D07E0Key {public:
 Rva006D07E0Key(Rva006D0280 *p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&other):m_object(other.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280 *r=m_object;if(r && --r->m_useCount==0){Rva006D0280 *p=m_object;if(p){p->teardown();g_pChainBlockAllocator->freeBlock(p,0x1c);}}}
 Rva006D0280 *m_object;Rva006D0660Table*getTable()const{return m_object->table14;}
 bool isNull()const{return m_object==0;}
};
class Rva006D0A30List {public:Rva006D07E0Key findSpecial(const EAStringC*);bool rva006D0C60(Rva006D07E0Key key);void *head;};
bool Rva006D0A30List::rva006D0C60(Rva006D07E0Key key){
 bool result=true;
 for(int i=0;i<key.getTable()->count28 && result;++i){
  bool missing=findSpecial(&EAStringC(key.getTable()->records2c[i].text)).isNull();
  if(missing){result=false;break;}
 }
 return result;
}
