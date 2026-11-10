// cl: /O2 /arch:SSE /MD /EHsc
// Native0x006CDE50..0x006CDF55 RET8, 261B. WB0x0174E530
// identifies _AptLoad.h:76 and the j<nMaxSize assertion. Caller6CF09E
// supplies a96-element four-byte retained-handle array to managerE176CC;
// the existing handle destructor0x004A9DF3 independently supports that role.
// The list/value wrappers are partial views; original class names are unknown.
// Counter storage is ordinary; only the comparison performs the native volatile
// access. A volatile declaration instead changes both bound and increment webs.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "../../../../GameEngine/Include/Common/Rva00894D80Accessor.h"
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
// The out-of-line ~BfmeRefVGO this unit emits for its unwind path must be the
// kept retail copy (0x000A9822, /O1 shape); in-class members take the optimize
// state of their definition, while the rows still inline them under /O2.
#pragma optimize("s", on)
class BfmeRefVGO {
protected:unsigned *value;
public:
 BfmeRefVGO(unsigned *p):value(p){if(value)Rva00894D80Accessor::increment(value);}
 ~BfmeRefVGO(){if(value && !Rva006CFDF0DecRef((int*)value))bfmeDropVGO(value);}
 BfmeRefVGO &operator=(const BfmeRefVGO &other){
  if(&other!=this){
   if(value && !Rva006CFDF0DecRef((int*)value))bfmeDropVGO(value);
   value=other.value;if(value)Rva00894D80Accessor::increment(value);
  }return *this;
 }
};
#pragma optimize("", on)
class Rva004A9DF3Element:public BfmeRefVGO {public:Rva004A9DF3Element &operator=(const BfmeRefVGO &x){BfmeRefVGO::operator=(x);return *this;}};
struct Rva006CDE50Cursor {
 Rva004A9DF3Element *position;
 Rva006CDE50Cursor(Rva004A9DF3Element *p):position(p){}
 Rva006CDE50Cursor operator++(int){Rva006CDE50Cursor old=*this;++position;return old;}
 Rva004A9DF3Element &operator*(){return *position;}
};
struct Rva006CDE50Node {unsigned *value;Rva006CDE50Node *next;};
class Rva00893030Manager {Rva006CDE50Node *head;public:void rva006CDE50(Rva004A9DF3Element *,int);};
void Rva00893030Manager::rva006CDE50(Rva004A9DF3Element *output,volatile int nMaxSize){
 int j=0;
 Rva006CDE50Node *node=head;
 if(!node)return;
 Rva006CDE50Cursor cursor(output);
 for(;node;node=node->next){
  if(!((*(volatile int *)&j)<nMaxSize)){
   g_bfmeAptAssertAtE17734("j < nMaxSize","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptLoad.h",0x4C);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
  }
  BfmeRefVGO held(node->value);
  ++j;
  *cursor++=held;
 }
}
