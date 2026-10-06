// cl: /MD /EHsc
// Address-derived recovery of two Apt string helpers in the 0x006D74E0
// cluster.
//
// 0x006D74E0 (191B): builds a string by converting the first AptValue argument
// through the unrowed BfmeAptValue::rva006DD6C0(EAStringC&) at 0x006DD6C0,
// then for each of the int count arguments converts the interpreter stack
// value At(i) (pinned 0x006FE580, global AptBasePtrStack at VA 0x00E182E0)
// and appends it through rowed EAStringC::Rva006D4F00Append 0x006D4F00. The
// result is copied into a freshly created AptString::Create 0x006D7210 at +8
// and returned. MSVC reuses the dead count argument slot for the loop EAStringC
// temporary, which is why the loop object is addressed at [esp+0x20].
//
// 0x006D7C80 (118B): clears one EAStringC temporary, converts the single
// AptValue argument into it through 0x006DD6C0, runs the unrowed normalizer
// 0x006D6100 on the temporary, copies it into the new AptString at +8 and
// returns it. The EAStringC temporary destructor is 0x006D3010.
//
// Both bodies are also `Rva006D6D20` neighbours; the class/layout view is
// address-derived. Identity of the two unrowed callees is not proven; they are
// pinned by address.

class EAStringC
{
    void *m_pData;
public:
    ~EAStringC();
    EAStringC &clear();
    EAStringC() { clear(); }
    EAStringC &operator=(const EAStringC &other);
    EAStringC &Rva006D4F00Append(const EAStringC &other);
    void rva006D6100();
};

class BfmeAptValue006DCD20
{
public:
    void rva006DD6C0(EAStringC &out);
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

// g_aptDateInterpreter: the interpreter global constructed at VA 0x00E182E0;
// the stack sub-object is at offset 0 (matched references already place it
// there).
extern AptActionInterpreter g_aptDateInterpreter;

class AptString
{
public:
    static AptString *Create();
    int m_unk00;
    int m_unk04;
    EAStringC m_string;
};

AptString *rva006d7c80(BfmeAptValue006DCD20 *value)
{
    EAStringC tmp;
    value->rva006DD6C0(tmp);
    tmp.rva006D6100();
    AptString *result = AptString::Create();
    result->m_string = tmp;
    return result;
}

AptString *rva006d74e0(BfmeAptValue006DCD20 *value, int count)
{
    EAStringC result;
    value->rva006DD6C0(result);
    for (int i = 0; i < count; ++i) {
        EAStringC item;
        BfmeAptValue006DCD20 *element = g_aptDateInterpreter.stack.At(i);
        element->rva006DD6C0(item);
        result.Rva006D4F00Append(item);
    }
    AptString *out = AptString::Create();
    out->m_string = result;
    return out;
}
