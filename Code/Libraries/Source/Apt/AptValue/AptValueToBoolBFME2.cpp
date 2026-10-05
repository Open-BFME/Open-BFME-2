// cl: /O2 /MD /EHsc
// Semantic lead: audit public-material/230e7c503b5dbf7e-AptValue.cpp,
// AptValue::toBool, with original-era AptValue const-bool declaration.
// Target 006DD550..006DD6B2 independently establishes signed type bits at +4,
// string tags 1/42, boolean 5, integer 7, float 6 and SWF version == 7.
// The complete 354-byte extent includes the five-entry dispatch table and
// 42-byte type map. String storage at +8 and every accessor call are native
// facts; the partial views below do not claim a complete class layout.
class EAStringC {
    unsigned int data;
public:
    bool IsEmpty() const;
    int GetAt(int) const;
    unsigned int rva006D3750() const;
    const char *rva00620090() const;
};
class AptString {
    unsigned char prefix[8];
public:
    EAStringC str;
    __forceinline EAStringC *GetInternalString() { return &str; }
};
class AptBoolean { public: bool GetBool() const; };
class AptInteger { public: int GetInt() const; };
class Rva00723490FloatField { public: float get() const; };
class BfmeAptValue006DCD20 {
public:
    BfmeAptValue006DCD20 *checkedFloat();
    BfmeAptValue006DCD20 *rva006DCEA0();
};
class AptValue {
    virtual void vtableSlot0();
    unsigned int flags;
public:
    AptString *c_string() const;
    AptInteger *c_integer() const;
    bool toBool() const;
};
int Rva006CD220Get();
extern "C" long __cdecl strtol(const char *, char **, int);
extern "C" double Rva006CD070Atof(const char *);
extern AptValue *gpUndefinedValue;

// Existing rowed providers establish the ABI and field reads. The boolean
// return is corroborated by AptBoolean.inl d8bdfcd7e1b3059a and native's tail
// jump to the byte getter; this does not infer a general byte-to-bool cast.
#pragma comment(linker, "/alternatename:?c_string@AptValue@@QBEPAVAptString@@XZ=?checkedString@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?c_integer@AptValue@@QBEPAVAptInteger@@XZ=?checkedInteger@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?GetInt@AptInteger@@QBEHXZ=?Length@?$SimpleVecClass@K@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetBool@AptBoolean@@QBE_NXZ=?get@Rva006D89D0ByteField@@QBEEXZ")

bool AptValue::toBool() const
{
    switch (static_cast<int>(flags) >> 25) {
    case 1:
    case 42:
        if (Rva006CD220Get() == 7) {
            return !c_string()->str.IsEmpty();
        } else {
            AptString *s = c_string();
            EAStringC *buf = s->GetInternalString();
            if (static_cast<int>(buf->rva006D3750()) > 2 &&
                buf->GetAt(0) == '0' && buf->GetAt(1) == 'x') {
                return strtol(buf->rva00620090(), 0, 16) != 0;
            } else {
                return (float)Rva006CD070Atof(
                    c_string()->GetInternalString()->rva00620090()) != 0.f;
            }
        }
    case 5:
        return reinterpret_cast<AptBoolean *>(
            reinterpret_cast<BfmeAptValue006DCD20 *>(
                const_cast<AptValue *>(this))->rva006DCEA0())->GetBool();
    case 7:
        return c_integer()->GetInt() != 0;
    case 6:
        return reinterpret_cast<Rva00723490FloatField *>(
            reinterpret_cast<BfmeAptValue006DCD20 *>(
                const_cast<AptValue *>(this))->checkedFloat())->get() != 0.f;
    default:
        return this != gpUndefinedValue;
    }
}
