// cl: /MD /EHsc
// Native RemoveSprite dispatch calls this helper. Donor AptDisplayList.cpp
// names removeClonedObject; retail proves depth signed17 bits at CIH+58,
// query outputs and removeObject call. No full CIH layout claimed.
class EAStringC;
class AptCIH { public: unsigned char prefix[0x58]; int depth:17; unsigned int rest:15; };
class AptDisplayListState { public: void findInst(int,const EAStringC *,AptCIH **,AptCIH **); };
// Donor removeObject is rowed as AptDisplayList::bfmeProcess1279 (0x006F7230); call it by that name.
class AptDisplayList { public: AptDisplayListState *pState; void bfmeProcess1279(void *); void removeClonedObject(AptCIH *); };
void AptDisplayList::removeClonedObject(AptCIH *object)
{
    AptCIH *cur=0;
    AptCIH *prev;
    pState->findInst(object->depth,0,&prev,&cur);
    bfmeProcess1279(cur);
}
#pragma comment(linker, "/alternatename:?findInst@AptDisplayListState@@QAEXHPBVEAStringC@@PAPAVAptCIH@@1@Z=?bfmeQuery1279@BfmeQuery1279@@QAEXHHPAPAX0@Z")
