// cl: /O2 /MD /EHsc
// Native RemoveSprite dispatch calls this helper. Donor AptDisplayList.cpp
// names removeClonedObject; retail proves depth signed17 bits at CIH+58,
// query outputs and removeObject call. No full CIH layout claimed.
class EAStringC;
class AptCIH { public: unsigned char prefix[0x58]; int depth:17; unsigned int rest:15; };
class AptDisplayListState { public: void findInst(int,const EAStringC *,AptCIH **,AptCIH **); };
class AptDisplayList { public: AptDisplayListState *pState; void removeObject(AptCIH *); void removeClonedObject(AptCIH *); };
void AptDisplayList::removeClonedObject(AptCIH *object)
{
    AptCIH *cur=0;
    AptCIH *prev;
    pState->findInst(object->depth,0,&prev,&cur);
    removeObject(cur);
}
#pragma comment(linker, "/alternatename:?findInst@AptDisplayListState@@QAEXHPBVEAStringC@@PAPAVAptCIH@@1@Z=?bfmeQuery1279@BfmeQuery1279@@QAEXHHPAPAX0@Z")
#pragma comment(linker, "/alternatename:?removeObject@AptDisplayList@@QAEXPAVAptCIH@@@Z=?bfmeProcess1279@BfmeWrapper1279@@QAEXPAX@Z")
