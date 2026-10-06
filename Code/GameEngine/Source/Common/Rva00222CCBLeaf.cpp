// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva00222CCBBuild@@YA?AVUnicodeString@@PAPAVRva00222CCB@@0V1@@Z @0x00222CCB 91B
// Free join over pointer range calling slot1 with accumulator then RVO.
// Evidence: EH_prolog plus loop call [eax+4] plus StringBase<G> copy 0x00037050 plus release 0x00036E70 plus callers 0x002252EB 0x0022535F; shape mirrors TempCtor 0x00222719 usage.
#include "unicode_string.h"



class Rva00222CCB
{
public:
    virtual int getLength() const = 0;
    virtual void fill(UnicodeString &out) = 0;
    virtual ~Rva00222CCB() {}
};

UnicodeString Rva00222CCBBuild(Rva00222CCB **begin, Rva00222CCB **end, UnicodeString initial)
{
    for (; begin != end; ++begin)
        (*begin)->fill(initial);
    return initial;
}
