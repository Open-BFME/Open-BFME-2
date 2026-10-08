// cl: /O2 /MD
// BFME1 6583b3c1 game/Libraries/Source/EA/Apt/AptValue_toNumber.cpp
// supplies the conversion semantics. BFME2 6DD460..6DD502 has its own
// signed type bits at +4 and checked cast calls; the existing matched
// AptValueToIntegerBFME2 and checked-cast units establish those interfaces.
// Retail's dispatch table selects strings for tags 1/42, boolean for 5,
// integer for 7, float for 6; other values compare with the undefined pointer.
// The string resolver returns an opaque object with EAStringC at +8, proved
// by this body's LEA and the matched toInteger path. No full string-class
// layout or original numeric-converter member name is claimed.
class EAStringC
{
    unsigned int m_data;
public:
    const char *rva00620090() const;
};
class BfmeAptValue006DCD20
{
    virtual void vtableSlot0();
    unsigned int m_flags;
public:
    bool isUndefined() const;
    BfmeAptValue006DCD20 *checkedString();
    BfmeAptValue006DCD20 *rva006DCEA0();
    BfmeAptValue006DCD20 *checkedInteger();
    BfmeAptValue006DCD20 *checkedFloat();
    float rva006DD460();
};
class Rva006D89D0ByteField { public: unsigned char get() const; };
class Rva00723490FloatField { public: float get() const; };
class Rva00144010Opaque { public: int rva00144010(); };
extern "C" double Rva006CD070Atof(const char *);
extern const float BfmeZeroRange;
struct NumberStringView
{
    unsigned char pad[8];
    EAStringC text;
};
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;
float BfmeAptValue006DCD20::rva006DD460()
{
    if (isUndefined())
        return BfmeZeroRange;
    switch (static_cast<int>(m_flags) >> 25) {
    case 1:
    case 42: {
        NumberStringView *string = reinterpret_cast<NumberStringView *>(checkedString());
        return (float)Rva006CD070Atof(string->text.rva00620090());
    }
    case 5:
        return reinterpret_cast<const Rva006D89D0ByteField *>(rva006DCEA0())->get() ? 1.0f : BfmeZeroRange;
    case 7:
        return static_cast<float>(reinterpret_cast<Rva00144010Opaque *>(checkedInteger())->rva00144010());
    case 6:
        return reinterpret_cast<const Rva00723490FloatField *>(checkedFloat())->get();
    default:
        return this != g_aptUndefinedAtE18078 ? 1.0f : BfmeZeroRange;
    }
}
// Shared readonly zero at native VA BBAEAC. Keep storage declared before
// use and defined afterward so MSVC retains the target memory loads.
extern const float BfmeZeroRange = 0.0f;

