// ?rva006E5940@Rva006E5940@@QAEXH@Z
// partial score=0.949571647118817 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" void Rva006FD040(void*,void*,void*);
class Rva0070EDC0 {public:void rva0070EDC0(int,void*);};
class Rva006E3410 {public:int rva006E3410(int);};
extern void *g_aptFreeRenderingUnitSlot,*g_aptFreeSoundSlot,*g_aptFreeTextureSlot;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
int Rva006CFDF0DecRef(int*);
void bfmeDropVGO(void*);
template<class T> inline T* shift(T*p,int delta){return (T*)((char*)p-delta);}
#define SLIDE(p) if(p) p=shift(p,delta)
struct Handle {int *p;Handle(int *q):p(q){} ~Handle(){if(p && !Rva006CFDF0DecRef(p))bfmeDropVGO(p);}Handle &operator=(const Handle&x){if(&x!=this){if(p&&!Rva006CFDF0DecRef(p))bfmeDropVGO(p);p=x.p;if(p)++*p;}return *this;}};
struct Import {char *p0,*p4;int id;Handle handle;};
struct Link {char *p;int unused;};
struct Sub4 {char *p[4];};
struct Record68 {int a,b;char pad[60];};
struct Record8 {int a;char *p;};
struct Record56 {char pad[52];char *p;};
struct Object {int kind,marker;union{struct {char *p8;int count;int *indices;} t3;struct{char pad[28];char *p24,*p28;int count;Record68 *records;int count8;Record8 *records8;Sub4 *sub;}t4;struct{char pad[44];char *p34,*p38;}t2;struct{char pad[40];int count;Record56 *records;}t10;int words[14];};};
class Rva006E5940 {public:char pad0[12];int count;Object **objects;char pad14[12];int importCount;Import *imports;int linkCount;Link *links;void *gc;void rva006E5940(int delta);
 inline int importIndex(int value){for(int j=0;j<importCount;++j)if(imports[j].id==value)return j;return -1;}

};
#define INDEX(v) ((Rva006E3410*)this)->rva006E3410(v)
#define O objects[i]
void Rva006E5940::rva006E5940(int delta){
 void **g=&gc;*g=0;
 for(int i=0;i<count;++i)if(O && importIndex(i)==-1){
  switch(O->kind){case 8:{O->words[0]=INDEX(O->words[0]);O->words[1]=INDEX(O->words[1]);break;}case 4:{Sub4 *p=O->t4.sub;if(p){if(p->p[1])p->p[1]=(char*)INDEX((int)p->p[1]);if(p->p[3])p->p[3]=(char*)INDEX((int)p->p[3]);if(p->p[0])p->p[0]=(char*)INDEX((int)p->p[0]);if(p->p[2])p->p[2]=(char*)INDEX((int)p->p[2]);}SLIDE(O->t4.sub);break;}}
 }
 for(int i=0;i<count;++i)if(O && importIndex(i)==-1){
  switch(O->kind){
   case 5:((Rva0070EDC0*)((char*)O+8))->rva0070EDC0(delta,g);break;
   case 1:((void(__cdecl*)(int))g_aptFreeRenderingUnitSlot)(O->words[4]);O->words[4]=i;break;
   case 4:SLIDE(O->t4.p24);SLIDE(O->t4.p28);for(int j=0;j<O->t4.count;++j)O->t4.records[j].b=INDEX(O->t4.records[j].b);SLIDE(O->t4.records);for(int j=0;j<O->t4.count8;++j){Rva006FD040(O->t4.records8[j].p,(void*)delta,g);SLIDE(O->t4.records8[j].p);}SLIDE(O->t4.records8);break;
   case 2:SLIDE(O->t2.p34);SLIDE(O->t2.p38);break;
   case 3:SLIDE(O->t3.p8);for(int j=0;j<O->t3.count;++j)O->t3.indices[j]=INDEX(O->t3.indices[j]);SLIDE(O->t3.indices);break;
   case 6:((void(__cdecl*)(int))g_aptFreeSoundSlot)(O->words[0]);O->words[0]=i;break;
   case 7:((void(__cdecl*)(int))g_aptFreeTextureSlot)(O->words[0]);O->words[0]=i;break;
   case 9:((Rva0070EDC0*)((char*)O+8))->rva0070EDC0(delta,g);if(i){g_bfmeAptAssertAtE17734("i == 0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp",390);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}break;
   case 10:for(int j=0;j<O->t10.count;++j){SLIDE(O->t10.records[j].p);}SLIDE(O->t10.records);break;
  }
 }
 for(int i=0;i<importCount;++i){Handle null(0);imports[i].handle=null;objects[imports[i].id]=0;}
 for(int i=0;i<count;++i)if(O){O->marker=0x9876543;SLIDE(O);}
 SLIDE(objects);
 for(int i=0;i<importCount;++i){SLIDE(imports[i].p0);SLIDE(imports[i].p4);}
 for(int i=0;i<linkCount;++i){SLIDE(links[i].p);}
 SLIDE(imports);SLIDE(links);*g=0;
}
