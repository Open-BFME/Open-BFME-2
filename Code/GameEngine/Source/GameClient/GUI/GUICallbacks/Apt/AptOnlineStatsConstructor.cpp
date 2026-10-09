// cl: /O1 /G7 /EHsc /MD /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii
// Native181B5B8F69..5B901E RET4: online Stats screen factory516D09
// allocates90B and calls this at516D38. The command string and singleton
// E06478 independently identify the role; WB names AptOnlineStats.
// Target calls establish primary60B base56DC4C, Stats secondary60..8C
// initialized by named173B AptStats ctor5DD609 with this as its owner,
// and tab8C. Native vptrs C73964 and C73950 establish the two polymorphic
// views. Inheritance spelling is a structural inference from those views.
// Member callback5B8F04, four-word binding and by-value holder57BC63 are
// existing byte-verified providers. Native scalar member-pointer adjustment
// is zero. The AptOnline::Stats declaration supplies its existing ABI;
// its multiple-inheritance representation follows the native binding only.
// No donor code or new pin. A lexical scope ends the name before publishing
// the singleton; by-value binding preserves native MOVSD four-word copy.
#include "ascii_string.h"
class AptOnline;
class Rva0056DC4C
{
public:
    Rva0056DC4C(void *);
    virtual ~Rva0056DC4C();
    unsigned char pad[0x60 - 4];
};
class AptStats
{
public:
    AptStats(void *);
    virtual ~AptStats();
    virtual void *rankValues();
    virtual int rankPoints(int);
    unsigned char pad[0x2c - 4];
};

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding
{
    FunctorBinding(FunctorMethod m, FunctorTarget *t) : target(t), method(m) {}
    FunctorTarget *target;
    unsigned pad;
    FunctorMethod method;
};
class FunctorWrapperHead
{
public:
    void *vt;
    int count;
};
class Rva0057BC63FunctorHolder
{
public:
    Rva0057BC63FunctorHolder(const FunctorBinding &);
    Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &x) : ptr(x.ptr)
    {
        if (ptr) ++ptr->count;
    }
    FunctorWrapperHead *ptr;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template<class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
    AptRef(FunctorBinding b) : Rva0057BC63FunctorHolder(b) {}
    ~AptRef()
    {
        if (ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);
    }
};
class AptCommandMap;
class AptCommandMapAdder
{
public:
    void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
};
class AptOnline
{
public:
    class Stats : public Rva0056DC4C, public AptStats
    {
    public:
        void CurrentTab(const char *);
    };
};
class Rva005B8F69 : public Rva0056DC4C, public AptStats
{
public:
    Rva005B8F69(AptOnline *);
    virtual ~Rva005B8F69();
    virtual void *rankValues();
    virtual int rankPoints(int);
    int tab;
};
class Rva005B7FA4;
extern Rva005B7FA4 *g_00E06478;

Rva005B8F69::Rva005B8F69(AptOnline *host)
    : Rva0056DC4C(host), AptStats(this)
{
    tab = 0;
    FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptOnline::Stats::CurrentTab);
    {
        AsciiString name("AptOnline::Stats::CurrentTab");
        ((AptCommandMapAdder *)((char *)this + 4))->AddCommandMap(name,
            AptRef<AptCommandMap>(FunctorBinding(method, reinterpret_cast<FunctorTarget *>(this))));
    }
    if (!g_00E06478) g_00E06478 = reinterpret_cast<Rva005B7FA4 *>(this);
}
