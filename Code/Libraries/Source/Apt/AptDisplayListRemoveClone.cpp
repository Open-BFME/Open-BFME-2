// cl: /MD /EHsc
// Native RemoveSprite dispatch calls this helper. Donor AptDisplayList.cpp
// names removeClonedObject; retail proves depth signed17 bits at CIH+58,
// query outputs and removeObject call. No full CIH layout claimed.
#include "AptCIHClass.h"
#include "AptDisplayListState.h"
// Donor removeObject is rowed as AptDisplayList::bfmeProcess1279 (0x006F7230); call it by that name.
#include "AptDisplayList.h"
// The canonical header keeps AptDisplayList opaque; this unit reads only its
// state pointer at +0x00 through a local view.
struct AptDisplayListStateView { AptDisplayListState *pState; };
void AptDisplayList::removeClonedObject(AptCIH *object)
{
    AptCIH *cur=0;
    AptCIH *prev;
    ((AptDisplayListStateView *)this)->pState->findInst((int)(object->field58 << 15) >> 15,0,&prev,&cur);
    bfmeProcess1279(cur);
}
#pragma comment(linker, "/alternatename:?findInst@AptDisplayListState@@QAEXHPBVEAStringC@@PAPAVAptCIH@@1@Z=?bfmeQuery1279@BfmeQuery1279@@QAEXHHPAPAX0@Z")
