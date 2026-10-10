// ?rva006D0D70@Rva006D1090@@QAEXPAX@Z
// partial score=0.86 date=2026-10-10
// cl: /O2 /G6 /MD /EHsc /DNDEBUG
// Native6D0D70..6D0F1F RET4 431B; WB1752640 supplies the resource
// release graph and nested handle/string lifetimes. Target proves states
// 1/2/3/4/5, cancel slotE1774C, table14 count28/record2C stride16 and
// named-string recursive release. Lookups82B and contains203B are owned.
// Both explicit reference release and scope teardown are present in native.
// Original resource/container names remain unknown; layouts are narrow
// target views. This bank emits459B: key storage reuses argument slot,
// the persistent owner is reloaded rather than held in EDI, and induction
// /cleanup register plans differ. No missing provider or new pin.
class EAStringC {void *data;public:EAStringC(const char*);~EAStringC();};
struct Rva006D0660Record {const char *text;char pad[12];};
struct Rva006D0660Table {char pad[0x28];int count28;Rva006D0660Record *records2c;};
class Rva006D0280 {public:int m_useCount;int unknown4;EAStringC name8;int typeC;int unknown10;Rva006D0660Table *table14;void *buffer18;~Rva006D0280();};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D07E0Key {public:
 Rva006D07E0Key(Rva006D0280 *p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&other):m_object(other.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280 *r=m_object;if(r && --r->m_useCount==0){Rva006D0280 *p=m_object;if(p){p->~Rva006D0280();g_pChainBlockAllocator->freeBlock(p,0x1c);}}}
 Rva006D0280 *m_object;Rva006D0660Table*getTable()const{return m_object->table14;}
 bool isNull()const{return m_object==0;}
};
class Rva006D0A30List {public:Rva006D07E0Key find(const EAStringC*);void *head;};

class Rva006D07E0List {public:int contains(Rva006D07E0Key);};
extern Rva006D07E0List *g_bfmeAptLinkerAtE176F8;
extern void (__cdecl *g_aptCancelLoadSlot)(void*);
class Rva006D1090 {public:void rva006D0D70(void *name);};
void Rva006D1090::rva006D0D70(void *name){
 Rva006D07E0Key key=((Rva006D0A30List*)this)->find((const EAStringC*)name);
 if(key.isNull())return;
 int type=key.m_object->typeC;
 if(type==1){}
 else if(type==2){if(key.m_object->buffer18)g_aptCancelLoadSlot(key.m_object->buffer18);}
 else if(type==3||type==4||type==5){
  for(int i=0;i<key.getTable()->count28;++i){
   Rva006D07E0Key dependent=((Rva006D0A30List*)this)->find(&EAStringC(key.getTable()->records2c[i].text));
   if(!dependent.isNull()&&!g_bfmeAptLinkerAtE176F8->contains(dependent))
    rva006D0D70(&EAStringC(key.getTable()->records2c[i].text));
  }
 }
 Rva006D0280 *r=key.m_object;
 if(--r->m_useCount==0){r->~Rva006D0280();g_pChainBlockAllocator->freeBlock(r,0x1c);}
}
