// cl: /O2 /MD /D_CRTIMP=
// BFME1 6583b3c1ff21db4a561285717028fdafc780b7db supplies the Math.pow
// algorithm in game/Libraries/Source/EA/Apt/Rva008A5160MathPow.cpp.
// Target 6E8990..6E89E8 has two stack arguments, cdecl return, and int3
// padding after the complete 88-byte body. Callback construction at 6EA1F6
// takes its address. Its At(0)/At(1), numeric conversion, _CIpow, and float
// factory calls establish its operation independently of the donor name.
// BFME2 calls the checked stack accessor instead of reading donor fields.
// The numeric converter retains an address-derived member name.
// The CRT math declarations this unit needs, in place of <math.h> (this TU compiles with
// /D_CRTIMP= and /O2, so these are the same plain, intrinsic-eligible declarations). <math.h>'s
// float overloads would emit this /O2 x87 unit's copies of floor(float), sqrt(float), sinf, cosf
// ... as COMDATs that differ from the copies the rest of the link keeps (retail's _sinf/_cosf are
// the 17-byte rows at 0x0008516D/0x0008515C). The callbacks call the double functions; only
// sin(float), cos(float) (rowed here, 0x0002FBB0/0x0002FBC0) and pow(float, float) keep float
// overloads, written with the bodies <math.h> gives them after inlining sinf/cosf.
extern "C" {
int __cdecl abs(int);
double __cdecl acos(double);
double __cdecl asin(double);
double __cdecl atan(double);
double __cdecl atan2(double, double);
double __cdecl ceil(double);
double __cdecl cos(double);
double __cdecl exp(double);
double __cdecl fabs(double);
double __cdecl floor(double);
double __cdecl log(double);
double __cdecl pow(double, double);
double __cdecl sin(double);
double __cdecl sqrt(double);
double __cdecl tan(double);
inline float powf(float _X, float _Y)
        {return ((float)pow((double)_X, (double)_Y)); }
}
inline float __cdecl cos(float _X)
        {return ((float)cos((double)_X)); }
inline float __cdecl sin(float _X)
        {return ((float)sin((double)_X)); }
inline float __cdecl pow(float _X, float _Y)
        {return (powf(_X, _Y)); }

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
    return Rva008A4EA0MakeFloat((float)sqrt((double)value));
}

// Native 6E8A50..6E8A81: checked top value followed by x87 fptan.
AptValue *aptMathTan(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)tan((double)value));
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
    return Rva008A4EA0MakeFloat((float)atan((double)value));
}

// Native 6E88C0..6E8903: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathExp.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathExp(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)exp((double)value));
}

// Native 6E8950..6E8983: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathLog.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathLog(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)log((double)value));
}

// Native 6E87C0..6E87F6: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathAcos.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathAcos(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)acos((double)value));
}

// Native 6E8800..6E8836: complete return followed by int3 padding.
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/aptMathAsin.cpp supplies
// the operation; the target uses checked At(0) and the shared numeric converter.
AptValue *aptMathAsin(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)asin((double)value));
}

// Native 6E8910..6E894A: checked top value and the CRT floor call.
AptValue *aptMathFloor(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)floor((double)value));
}

// Native 6E8880..6E88BA: checked top value and the CRT ceil call.
AptValue *aptMathCeil(void *self, int argc)
{
    if (argc < 1)
        return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    return Rva008A4EA0MakeFloat((float)ceil((double)value));
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
    return Rva008A4EA0MakeFloat((float)atan2((double)y, (double)x));
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
    return Rva008A4EA0MakeFloat((float)fabs((double)value->rva006DD460()));
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
AptValue *aptMathRound(void *self, int argc)
{
    if (argc <= 0) return reinterpret_cast<AptValue *>(g_aptUndefinedAtE18078);
    float value = g_aptDateInterpreter.stack.At(0)->rva006DD460();
    if (value > 0.0f) {
        value += 0.5f;
        return AptInteger::Create((int)value);
    }
    value -= 0.5f;
    return AptInteger::Create((int)value);
}

// Native 6FF500..6FF5C6: callback argument checks; x87 bounds comparisons.
// The owned AptCIH::rva006E1DD0 body proves the four-float bounds output.
// No source name or donor identity is inferred from the byte match.
class AptCIH { public: void rva006E1DD0(void *); };
struct Rva006FF500Rect { float xMin,yMin,xMax,yMax; };
AptValue *Rva006FF500(AptValue *self,int nParams)
{
    AptValue *undefined=(AptValue*)g_aptUndefinedAtE18078;
    if(nParams==1) return undefined;
    if(nParams>1) {
        float x=g_aptDateInterpreter.stack.At(0)->rva006DD460();
        float y=g_aptDateInterpreter.stack.At(1)->rva006DD460();
        if(nParams>2) g_aptDateInterpreter.stack.At(2)->toInteger();
        Rva006FF500Rect rect;
        ((AptCIH*)self)->rva006E1DD0(&rect);
        if(x>=rect.xMin && x<=rect.xMax && y>=rect.yMin && y<=rect.yMax)
            return AptInteger::Create(1);
    }
    return undefined;
}
