// cl: /O2 /G6 /MD
// Native 6F7330..6F73A0 cdecl112B callback; independently decoded after
// earlier wrong-boundary refusal. Sibling6F73A0 is the clip-stack visitor.
// Target calls identify a rendering-context colour/vertex push, CIH draw,
// and balanced pops. CIH colour24/matrixC/parent48 are target access facts.
// Existing rendering stack identities come from APT release PDB evidence;
// the callback's original name remains unknown. No return is consumed.
class AptRenderingContext {public:void pushColourTransform();void popColourTransform();void pushVertexMatrix();void popVertexMatrix();};
struct BfmeS1209;
class BfmeA1209 {public:void bfmeOp1209(const BfmeS1209*);};
class BfmeThingDXH {public:void bfmeGoDXH(void*);};
class BfmeAptValue006DCD20 {public:bool rva006E02B0()const;};
class Rva006E1260 {public:void call(void*);};
class Rva006E15C0 {public:void call(void*,void*,int);};
class AptCIH {public:bool rva006E24E0()const;char unknown00[0x0C];char matrix[0x18];char colour[0x20];char unknown44[4];void *parent;};
void rva006F7330(void *argument1,void *argument2,int argument3)
{
 AptCIH *item=(AptCIH*)argument2;
 if(item->rva006E24E0()){
  AptRenderingContext *context=(AptRenderingContext*)argument1;
  context->pushColourTransform();
  ((BfmeA1209*)context)->bfmeOp1209((const BfmeS1209*)item->colour);
  context->pushVertexMatrix();
  if(((BfmeAptValue006DCD20*)item)->rva006E02B0())((Rva006E1260*)item)->call(item->parent);
  ((BfmeThingDXH*)context)->bfmeGoDXH(item->matrix);
  ((Rva006E15C0*)item)->call(context,0,argument3);
  context->popVertexMatrix();
  context->popColourTransform();
 }
}
