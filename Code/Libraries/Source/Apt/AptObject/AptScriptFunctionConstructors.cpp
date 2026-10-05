// cl: /O2 /MD /EHsc /GR-
#include "AptScriptFunction.h"
// Native constructor tags43/44 and field+30 agree with original PDB classes.

AptScriptFunction1::AptScriptFunction1(AptScriptFunctionBase *creator,const AptAction_DefineFunction *definition,AptCIH *cih)
    : AptScriptFunctionBase((AptVirtualFunctionTable_Indices)43,creator,cih,true),mpFunction(definition) {}
AptScriptFunction2::AptScriptFunction2(AptScriptFunctionBase *creator,const AptAction_DefineFunction2 *definition,AptCIH *cih)
    : AptScriptFunctionBase((AptVirtualFunctionTable_Indices)44,creator,cih,true),mpFunction(definition) {}
