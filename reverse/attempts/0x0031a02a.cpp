// ?updatePresentation@Rva0031A02A@@QAEXXZ
// partial score=0.97 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Include/Lib /EHsc /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
// Whole 0x0031A02A..0x0031A129 updates an army presentation. Every field
// offset and helper ABI here comes from this body and the existing matched
// provider rows. The helper source types are ABI views of the calls; they
// do not establish this owner's original class or method identity.
#include <vector>
#include "Coord2D.h"
class Rva0031934BOwner { public: void rva0031934B(const AsciiString *); };
class Rva003FDE1AHelper { public: void rva003FDE1A(int); };
class Rva003193EC { public: void rva003190E7(bool); };
class Rva005398CD
{
public:
    Rva005398CD(const UnicodeString &, const UnicodeString &);
private:
    char opaque[12];
};
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C
{
    // ?TreeHintRef00217D4C::TreeHintRef00217D4C absent-from-retail
    TreeHintRef00217D4C(TargetRef00217D4C *p) : m_ptr(p) { if (m_ptr) ++m_ptr->references; }
    // ?TreeHintRef00217D4C::TreeHintRef00217D4C absent-from-retail
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) { if (m_ptr) ++m_ptr->references; }
    // ?TreeHintRef00217D4C::~TreeHintRef00217D4C present-unmatched
    __forceinline ~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
    TargetRef00217D4C *m_ptr;
};
class Rva003FE0B3 { public: void rva003FE0B3(TreeHintRef00217D4C); };
class LivingWorldArmyLine { public: void rva00539141(); private: char opaque[8]; };
class Rva00319AA0 { public: void rva00319AA0(const Coord2D *); };
struct TWheelInfo;
class Drawable { public: const TWheelInfo *getWheelInfo() const; };
struct BfmeE16 { float x, y, z, w; };
struct Elem003AF9E0
{
    virtual ~Elem003AF9E0();
    char opaque04[12];
    Elem003AF9E0();
    Elem003AF9E0(const Elem003AF9E0 &);
    Elem003AF9E0 &operator=(const Elem003AF9E0 &);
};
class Rva00538E22
{
public:
    void rva00538ED1(int);
    void rva00538F10(const _STL::vector<BfmeE16> &, int);
};
class Rva0031A02AImpl
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void setState(bool show, int flags);
};
struct Rva0031A02ASummary { char opaque00[0x1C]; int owner; };
class Rva003195C9Owner { public: void rva003195C9(); };
class Rva0031A02A
{
public:
    void updatePresentation();
private:
    char opaque00[0x20];
    int owner;
    AsciiString name;
    char opaque28[0x44 - 0x28];
    Coord2D position;
    char opaque4C[0x65 - 0x4C];
    bool show;
    char opaque66[2];
    UnicodeString title, help;
    int mode;
    bool locked;
    char opaque75[3];
    Rva0031A02ASummary *summary;
    _STL::vector<Elem003AF9E0> points;
    Rva0031A02AImpl *impl;
    int opaque8C;
    LivingWorldArmyLine line;
};
void Rva0031A02A::updatePresentation()
{
    reinterpret_cast<Rva0031934BOwner *>(this)->rva0031934B(&name);
    if (mode != -1)
    {
        if (impl)
        {
            reinterpret_cast<Rva003FDE1AHelper *>(impl)->rva003FDE1A(mode);
            impl->setState(show, 0);
            reinterpret_cast<Rva003FE0B3 *>(impl)->rva003FE0B3(
                TreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(new Rva005398CD(title, help))));
        }
    }
    else
        reinterpret_cast<Rva003193EC *>(this)->rva003190E7(true);
    if (!locked)
        line.rva00539141();
    reinterpret_cast<Rva00319AA0 *>(this)->rva00319AA0(&position);
    Rva0031A02ASummary *currentSummary = summary;
    currentSummary->owner = owner;
    Rva00538E22 *wheel = reinterpret_cast<Rva00538E22 *>(const_cast<TWheelInfo *>(
        reinterpret_cast<const Drawable *>(this)->getWheelInfo()));
    if (wheel)
    {
        wheel->rva00538ED1(0);
        wheel->rva00538F10(reinterpret_cast<const _STL::vector<BfmeE16> &>(points), 0);
        _STL::vector<Elem003AF9E0> &pending = points;
        pending.erase(pending.begin(), pending.end());
    }
    if (!locked)
        reinterpret_cast<Rva003195C9Owner *>(this)->rva003195C9();
}
