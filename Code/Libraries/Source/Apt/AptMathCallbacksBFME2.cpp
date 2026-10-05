// cl: /O2 /MD
// BFME1 6583b3c1ff21db4a561285717028fdafc780b7db supplies the Math.pow
// algorithm in game/Libraries/Source/EA/Apt/Rva008A5160MathPow.cpp.
// Target 6E8990..6E89E8 has two stack arguments, cdecl return, and int3
// padding after the complete 88-byte body. Callback construction at 6EA1F6
// takes its address. Its At(0)/At(1), numeric conversion, _CIpow, and float
// factory calls establish its operation independently of the donor name.
// BFME2 calls the checked stack accessor instead of reading donor fields.
// The numeric converter retains an address-derived member name.
#include <math.h>

class AptValue;
class BfmeAptValue006DCD20
{
public:
    float rva006DD460();
};

class AptBasePtrStack
{
public:
    BfmeAptValue006DCD20 *At(int nPos);
};

struct AptActionInterpreter
{
    AptBasePtrStack stack;
};

extern AptActionInterpreter g_aptDateInterpreter;
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;
AptValue *Rva008A4EA0MakeFloat(float value);

AptValue *aptMathPow(void *self, int argc)
{
    if (argc < 2)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    BfmeAptValue006DCD20 *base = g_aptDateInterpreter.stack.At(0);
    BfmeAptValue006DCD20 *exponent = g_aptDateInterpreter.stack.At(1);
    return Rva008A4EA0MakeFloat((float)pow(base->rva006DD460(), exponent->rva006DD460()));
}

// Native 6E8A20..6E8A4F: checked top value followed by x87 fsqrt.
AptValue *aptMathSqrt(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)sqrt(value));
}

// Native 6E8A50..6E8A81: checked top value followed by x87 fptan.
AptValue *aptMathTan(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)tan(value));
}
