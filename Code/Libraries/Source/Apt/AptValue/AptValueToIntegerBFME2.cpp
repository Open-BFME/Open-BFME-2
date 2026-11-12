// cl: /MD
// Ported from the BFME1 AptValue::toInteger donor at
// reference/open-bfme-1/game/Libraries/Source/EA/Apt/AptValueToInteger.cpp.
// Target evidence: the +4 flags hold a signed 7-bit type and defined bit 4;
// target toInteger calls the rowed isUndefined, EAStringC accessors, and the
// byte/float getters. Its type-1 string path first calls the opaque 0x6DCE50
// resolver; default values compare with the target undefined singleton. The
// donor's separate BFME1 flag layout and indirect-string behavior are not
// claimed as target layout facts.
// Retail calls the atoi and strtol import thunks directly (RVAs 0x629838
// and 0x629ABA). Use the header's _CRTIMP guard to retain those direct calls.
#define _CRTIMP
#include <stdlib.h>

#include "../EAStringC.h"

class Rva006D89D0ByteField
{
public:
    unsigned char get() const;
};

#include "../Rva00723490FloatField.h"

class Rva00144010Opaque
{
public:
    int rva00144010();
};

#include "../BfmeAptValue006DCD20.h"

class AptValue; extern AptValue *gpUndefinedValue;

int BfmeAptValue006DCD20::toInteger() const
{
    if (isUndefined())
        return 0;

    int type = static_cast<int>(field04) >> 25;
    switch (type) {
    // Retail's index table (+0xD0) sends type 42 to the string conversion,
    // the same jump-table slot as type 1; there is no separate 42 case.
    case 1:
    case 42: {
        EAStringC *string = reinterpret_cast<EAStringC *>(reinterpret_cast<char *>(
            const_cast<BfmeAptValue006DCD20 *>(this)->checkedString()) + 8);
        if (static_cast<int>(string->rva006D3750()) > 2 &&
            string->GetAt(0) == '0' && string->GetAt(1) == 'x')
            return strtol(string->rva00620090(), 0, 16);
        return atoi(string->rva00620090());
    }
    case 5:
        return reinterpret_cast<const Rva006D89D0ByteField *>(this)->get();
    case 7:
        return reinterpret_cast<Rva00144010Opaque *>(
            const_cast<BfmeAptValue006DCD20 *>(this))->rva00144010();
    case 6:
        return static_cast<int>(reinterpret_cast<const Rva00723490FloatField *>(this)->get());
    default:
        return this != (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
    }
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeVal1034@BfmeN1034@@QAEHXZ=?toInteger@BfmeAptValue006DCD20@@QBEHXZ")
