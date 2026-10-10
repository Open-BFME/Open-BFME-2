// ?rva006CDE50@Rva00893030Manager@@QAEXPAVRva004A9DF3Element@@H@Z
// partial score=0.931951286261631 date=2026-10-10
// cl: /O2 /MD /EHsc
// Native6CDE50..6CDF55 RET8; head/next at0/4 and four-byte ref payload.
// Apt.cpp frame update consumes up to96 retained values from this manager.
// Target assertions independently identify _AptLoad.h line76 and output bound.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva00894D80Accessor {public:static unsigned increment(unsigned *);};
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
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
class Rva004A9DF3Element:public BfmeRefVGO {public:Rva004A9DF3Element &operator=(const BfmeRefVGO &x){BfmeRefVGO::operator=(x);return *this;}};
struct Rva006CDE50Cursor {
 Rva004A9DF3Element *position;
 Rva006CDE50Cursor(Rva004A9DF3Element *p):position(p){}
 Rva006CDE50Cursor operator++(int){Rva006CDE50Cursor old=*this;++position;return old;}
 Rva004A9DF3Element &operator*(){return *position;}
};
struct Rva006CDE50Node {unsigned *value;Rva006CDE50Node *next;};
class Rva00893030Manager {Rva006CDE50Node *head;public:void rva006CDE50(Rva004A9DF3Element *,int);};
void Rva00893030Manager::rva006CDE50(Rva004A9DF3Element *output,int nMaxSize){
 volatile int j=0;
 Rva006CDE50Cursor cursor(output);
 for(Rva006CDE50Node *node=head;node;node=node->next){
  if(!(j<nMaxSize)){
   g_bfmeAptAssertAtE17734("j < nMaxSize","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptLoad.h",0x4C);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
  }
  BfmeRefVGO held(node->value);
  ++j;
  *cursor++=held;
 }
}
