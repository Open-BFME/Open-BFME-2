// cl: /O2 /G6 /MD
// Native 6F7330..6F73A0 cdecl112B callback; independently decoded after
// earlier wrong-boundary refusal. Sibling6F73A0 is the clip-stack visitor.
// Target calls identify a rendering-context colour/vertex push, CIH draw,
// and balanced pops. CIH colour24/matrixC/parent48 are target access facts.
// Existing rendering stack identities come from APT release PDB evidence;
// the callback's original name remains unknown. No return is consumed.
#include "AptRenderingContext.h"
struct BfmeS1209;
class BfmeA1209 {public:void bfmeOp1209(const BfmeS1209*);};
#include "BfmeThingDXH.h"
#include "BfmeAptValue006DCD20.h"
#include "Rva006E1260.h"
#include "Rva006E15C0.h"
#include "AptCIHClass.h"
void rva006F7330(void *argument1,void *argument2,int argument3)
{
 AptCIH *item=(AptCIH*)argument2;
 if(item->rva006E24E0()){
  AptRenderingContext *context=(AptRenderingContext*)argument1;
  context->pushColourTransform();
  ((BfmeA1209*)context)->bfmeOp1209((const BfmeS1209*)&item->field24);
  context->pushVertexMatrix();
  if((unsigned char)((BfmeAptValue006DCD20*)item)->rva006E02B0())((Rva006E1260*)item)->call(item->field48);
  ((BfmeThingDXH*)context)->bfmeGoDXH(&item->field0C);
  ((Rva006E15C0*)item)->call(context,0,argument3);
  context->popVertexMatrix();
  context->popColourTransform();
 }
}
