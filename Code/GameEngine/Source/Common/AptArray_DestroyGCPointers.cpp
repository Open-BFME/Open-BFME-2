// cl: /MD
// Apt array clear at retail 0x006D93D0 (195 bytes), reconstructed from the
// retail ABI. Layout follows the approved TU's AptArray (mpValues +0x20,
// mnCapacity +0x24, mnLength +0x28); the two assert triples name AptArray.cpp lines
// 0x82/0x83 and their file string. The body first calls the base
// AptObject::DestroyGCPointers 0x0070DFE0 (rowed), then nulls each element through the
// AptValue::Release (vtable slot 1), hands the backing store to the pool 0x00E176E8
// (freeBlock 0x006DB270 with mnCapacity*4 bytes) and clears all three fields.

extern "C" void __cdecl __debugbreak(void);
#pragma intrinsic(__debugbreak)

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

#include "../../../Libraries/Source/Apt/AptObject/AptScriptFunction.h"
#include "../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // VA 0x00E176E8

// The approved TU's AptArray view (Code/Libraries/Source/Apt/AptArray.cpp):
// AptObject base, mpValues +0x20, mnCapacity +0x24, mnLength +0x28.
class AptArray : public AptObject {
public:
    virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const,const EAStringC *const,AptValue *const);
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
protected:
    virtual ~AptArray();
private:
    AptValue **mpValues;
    int mnCapacity,mnLength;
};

void AptArray::DestroyGCPointers()
{
	AptObject::DestroyGCPointers();

	if (!(mpValues != 0 || mnLength == 0)) {
		g_bfmeAptAssertAtE17734("mpValues != NULL || mnLength == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x82);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	if (!(mnLength <= mnCapacity)) {
		g_bfmeAptAssertAtE17734("mnLength <= mnCapacity", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x83);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}

	for (int i = 0; i < mnLength; ++i) {
		AptValue *pValue = mpValues[i];
		if (pValue != 0) {
			pValue->Release();
			mpValues[i] = 0;
		}
	}

	if (mpValues != 0)
		g_pChainBlockAllocator->freeBlock(mpValues, mnCapacity * 4);

	mpValues = 0;
	mnLength = 0;
	mnCapacity = 0;
}
