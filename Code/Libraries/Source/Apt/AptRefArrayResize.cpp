// cl: /O2 /DNDEBUG /MD /EHsc
// Native6CE3D0..6CE554 resizes an array of four-byte refcounted handles.
// The allocation header and array cookie are separate DWORDs. Existing
// element ctor13260 and dtorA9DF3 provide independently verified lifetimes.
// Native advances the input pointer and deletes that advanced pointer; preserve
// this target behaviour without assuming the original template was correct.
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270 {public:void freeBlock(void *,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
class Rva00894D80Accessor {public:static unsigned increment(unsigned *);};
class BfmeRefVGO {
protected:unsigned *value;
public:
 BfmeRefVGO():value(0){}
 ~BfmeRefVGO();
 BfmeRefVGO &operator=(const BfmeRefVGO &other){
  if(&other!=this){
   if(value && !Rva006CFDF0DecRef((int *)value))bfmeDropVGO(value);
   value=other.value;
   if(value)Rva00894D80Accessor::increment(value);
  }
  return *this;
 }
};
class Rva004A9DF3Element:public BfmeRefVGO {
public:
 Rva004A9DF3Element(){}
 ~Rva004A9DF3Element();
 static void *operator new[](unsigned n){unsigned *p=(unsigned *)((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n+4);*p=n;return p+1;}
 static void operator delete[](void *p){unsigned *q=(unsigned *)p-1;g_pChainBlockAllocator->freeBlock(q,*q+4);}
};
Rva004A9DF3Element *Rva006CE3D0Resize(Rva004A9DF3Element *old,int oldCount,int newCount){
 Rva004A9DF3Element *fresh=0;
 if(!old)return new Rva004A9DF3Element[newCount];
 if(newCount){
  fresh=new Rva004A9DF3Element[newCount];
  int count=newCount<oldCount?newCount:oldCount;
  Rva004A9DF3Element *destination=fresh;
  while(count){*destination++=*old++;--count;}
 }
 delete[] old;
 return fresh;
}
