// cl: /O2 /MD /D_CRTIMP=
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

// Native 6E8570..6E859F: checked top value followed by x87 fsin.
AptValue *aptMathSin(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)sin(value));
}

// Native 6E85A0..6E85CF: checked top value followed by x87 fcos.
AptValue *aptMathCos(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)cos(value));
}

// Native 6E8840..6E8871: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathAtan.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathAtan(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)atan(value));
}

// Native 6E88C0..6E8903: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathExp.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathExp(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)exp(value));
}

// Native 6E8950..6E8983: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathLog.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathLog(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)log(value));
}

// Native 6E87C0..6E87F6: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathAcos.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathAcos(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)acos(value));
}

// Native 6E8800..6E8836: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathAsin.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathAsin(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)asin(value));
}

// Native 6E8910..6E894A: checked top value and the CRT floor call.
AptValue *aptMathFloor(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)floor(value));
}

// Native 6E8880..6E88BA: checked top value and the CRT ceil call.
AptValue *aptMathCeil(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)ceil(value));
}
