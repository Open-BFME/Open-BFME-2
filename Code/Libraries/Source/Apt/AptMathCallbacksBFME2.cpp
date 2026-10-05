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
    int isInteger() const;
    int toInteger() const;
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

// Native 6E85D0..6E861E: two checked values, numeric conversion, fpatan.
// BFME1 aptMathAtan2 supplies the operation; target passes the second value
// as x and the top value as y, storing x in the unused self argument slot.
AptValue *aptMathAtan2(void *self, int argc)
{
    if (argc < 2)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    BfmeAptValue006DCD20 *top = g_aptDateInterpreter.stack.At(0);
    BfmeAptValue006DCD20 *second = g_aptDateInterpreter.stack.At(1);
    float x = second->rva006DD460();
    float y = top->rva006DD460();
    return Rva008A4EA0MakeFloat((float)atan2(y, x));
}

class AptInteger { public: static AptValue *Create(int value); };
// Native 6E8760..6E87B3: integer abs preserves integer type; otherwise fabs.
// The BFME1 abs donor only has the integer path. The target's isInteger()
// predicate and separate float factory independently establish this extension.
AptValue *aptMathAbs(void *self, int argc)
{
    if (argc < 1) return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    BfmeAptValue006DCD20 *value = g_aptDateInterpreter.stack.At(0);
    if (static_cast<unsigned char>(value->isInteger()))
        return AptInteger::Create(abs(value->toInteger()));
    return Rva008A4EA0MakeFloat((float)fabs(value->rva006DD460()));
}

// Native 6E8680..6E86E5: compare two numeric values, select the lesser,
// then convert the selected value again. The BFME1 aptMin donor supplies
// this structure; its selection direction is not treated as target proof.
AptValue *aptMathMin(void *self, int argc)
{
    if (argc < 2) return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    BfmeAptValue006DCD20 *first = g_aptDateInterpreter.stack.At(0);
    BfmeAptValue006DCD20 *second = g_aptDateInterpreter.stack.At(1);
    BfmeAptValue006DCD20 *selected = first->rva006DD460() < second->rva006DD460() ? first : second;
    float result = selected->rva006DD460();
    return Rva008A4EA0MakeFloat(result);
}

// Native 6E86F0..6E8755: select the greater of two checked numeric values,
// then reconvert it. BFME1 aptMax is the structural donor; retail's x87
// comparison establishes the selection direction, including unordered cases.
AptValue *aptMathMax(void *self, int argc)
{
    if (argc < 2) return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    BfmeAptValue006DCD20 *first = g_aptDateInterpreter.stack.At(0);
    BfmeAptValue006DCD20 *second = g_aptDateInterpreter.stack.At(1);
    BfmeAptValue006DCD20 *selected = first->rva006DD460() > second->rva006DD460() ? first : second;
    float result = selected->rva006DD460();
    return Rva008A4EA0MakeFloat(result);
}

// Native 6E8620..6E8678: round to nearest with ties away from zero using
// shared zero and half literals, then the CRT integer helper. BFME1 6583b3c1
// aptMathRound supplies the algorithm; checked stack access is target-specific.
extern const float g_aptNumberZeroAtBBAEAC;
extern const float g_aptMathHalfAtBC26F0;
AptValue *aptMathRound(void *self, int argc)
{
    if (argc <= 0) return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    if (value > g_aptNumberZeroAtBBAEAC) {
        value += g_aptMathHalfAtBC26F0;
        return AptInteger::Create((int)value);
    }
    value -= g_aptMathHalfAtBC26F0;
    return AptInteger::Create((int)value);
}
extern const float g_aptMathHalfAtBC26F0 = 0.5f;
