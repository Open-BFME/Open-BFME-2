// ?rva006CE1C0@@YAXH@Z
// partial score=0.9157625002 date=2026-10-09
// cl: /O2 /MD /EHsc
// Native CE1C0..CE37A sweep and WB174FD80 independently establish the
// reverse vector iteration, CIH flags5C, name8, animation4C, file-ref34,
// warning texts, reference drop, virtual teardown order and final dirty flag.
// Address-derived worker retains the existing caller spelling/pin.
class EAStringC {void *data;public:const char *rva00620090() const;};
class BfmeAptValue006DCD20 {public:BfmeAptValue006DCD20 *rva006DCF60(bool);void setGCRootCount(unsigned);};
class AptValue;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptValueVector {int capacity;int count;AptValue **items;int high;public:
 int GetNumValues() const;void rva006CC0A0(int);
 AptValue *at(int i) {
  if(!(i>=0 && i<count)) {
   g_bfmeAptAssertAtE17734("iPos >= 0 && iPos < mCurrentNum","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValueVector.h",0x39);
   if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
  }
  return items[i];
 }
};
extern AptValueVector *g_aptOptionalValueVector;
extern unsigned char g_Va00E1770C;
class Rva006CD650 {public:void *rva006CD650();};
int Rva006CFDF0DecRef(int *);
void bfmeDropVGO(void *);
struct Rva006CE1C0File {int refs,size;EAStringC name;int state;};
class Rva006CE1C0Ref {public:Rva006CE1C0File *value;
 Rva006CE1C0Ref():value(0){}
 ~Rva006CE1C0Ref(){if(value && !Rva006CFDF0DecRef((int *)value))bfmeDropVGO(value);}
 Rva006CE1C0Ref &operator=(const Rva006CE1C0Ref &other) {
  if(this!=&other){if(value && !Rva006CFDF0DecRef((int *)value))bfmeDropVGO(value);value=other.value;}
  return *this;
 }
};
struct Rva006CE1C0State {char pad[0x34];Rva006CE1C0Ref file;};
class Rva006CE1C0Animation {public:virtual void slot0();virtual ~Rva006CE1C0Animation();virtual void slot2();};
struct Rva006CE1C0CIH {char pad0[8];EAStringC name;char padC[0x4c-12];Rva006CE1C0Animation *animation;char pad50[12];unsigned flags;};
void Rva006CC110Log(int,const char *,...);
void rva006CE1C0(int force) {
 if(!g_aptOptionalValueVector)return;
 for(int i=g_aptOptionalValueVector->GetNumValues()-1;i>=0;--i) {
  AptValue *value=g_aptOptionalValueVector->at(i);
  if(value) {
   Rva006CE1C0CIH *cih=(Rva006CE1C0CIH *)((BfmeAptValue006DCD20 *)value)->rva006DCF60(true);
   if((cih->flags&0xc0000)==0x40000 && ((unsigned char)force || !(cih->flags&0xffff))) {
    Rva006CE1C0State *state=(Rva006CE1C0State *)((Rva006CD650 *)cih)->rva006CD650();
    g_aptOptionalValueVector->rva006CC0A0(i);
    cih->flags&=0xfff3ffff;
    Rva006CE1C0File *file=state->file.value;file->state=4;
    if(file->refs>2 && !(unsigned char)force)
     Rva006CC110Log(3,"WARNING :: ZOMBIE SPRITE[name = %s  file = %s.swf  size = %d bytes] NO LONGER HAS EXTERNAL FUNCTION REFERENCES, REMOVING SPRITE FROM MEMORY NOW\n",cih->name.rva00620090(),state->file.value->name.rva00620090(),state->file.value->size);
    else
     Rva006CC110Log(3,"WARNING :: ANIMATION[name = %s  file = %s.swf  size = %d bytes] NO LONGER HAS EXTERNAL FUNCTION REFERENCES, REMOVING FILE FROM MEMORY NOW\n",cih->name.rva00620090(),state->file.value->name.rva00620090(),state->file.value->size);
    Rva006CC110Log(3,"           REFER TO BUG253 ON COREFORGE FOR MORE INFORMATION [http://coreforge.eac.ad.ea.com/tracker/index.php?func=detail&aid=253&group_id=41&atid=247].  EVALUATION OF YOUR SWF FILES IS HIGHLY RECOMMENDED\n");
    state->file=Rva006CE1C0Ref();
    ((BfmeAptValue006DCD20 *)cih)->setGCRootCount(0);
    cih->animation->slot0();cih->animation->slot2();
    delete cih->animation;cih->animation=0;
    g_Va00E1770C=1;
   }
  }
 }
}
