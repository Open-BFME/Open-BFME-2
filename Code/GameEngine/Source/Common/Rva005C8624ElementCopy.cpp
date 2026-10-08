// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Target 0x005C9217..0x005C9311; caller _Construct at 0x005C83CD supplies
// the existing element spelling. WB LargeGroupAudioGridCell copy constructor
// 0x01567F60 supplies an algorithm/layout lead, not a proved target name.
// Target independently proves scalar +0/+4, ref +8, eight pointers +C,
// 12-byte containers +2C/+38, word +44, byte +46 and two nibble fields +47.
// Container value identities remain inferred; only default/copy operations
// whose existing complete providers reproduce retail are used here.
#include <map>
#include <vector>

namespace _STL {
template <> const unsigned int& max<unsigned int>(const unsigned int&, const unsigned int&);
}

class OpaqueRefCounted { public: void Release_Ref(); };
struct BfmePoolHolder88 { char m_pad[0x88]; OpaqueRefCounted m_ref; };
class BfmePoolRef10
{
public:
    BfmePoolHolder88 *m_target;
    BfmePoolRef10() : m_target(0) {}
    ~BfmePoolRef10() { if (m_target) m_target->m_ref.Release_Ref(); }
    void rva000519BD();
    void rva00053D26(BfmePoolHolder88 *p);
};

struct BfmeAudioEventPrefix136;
class Rva0051D93
{
public:
    Rva0051D93(const BfmeAudioEventPrefix136 &source);
private:
    char m_bytes[0x90];
};

struct Rva004E1D4EElement { char bytes[12]; };
class HostClass005C8E0A { public: void method_005C9069(); };
class GameMessageList;
class GameMessage { public: void friend_setList(GameMessageList *); };

class AudioInterface005C9217
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3C(); virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual void slot4C(); virtual void slot50();
    virtual void slot54(); virtual void slot58(); virtual void slot5C();
    virtual unsigned int slot60(BfmePoolRef10 *);
};
extern AudioInterface005C9217 *TheAudio;

struct Rva005C8624Element
{
    int m_00, m_04;
    BfmePoolRef10 m_ref;
    void *m_overlaps[8];
    _STL::map<int, void *> m_map;
    _STL::vector<Rva004E1D4EElement> m_vector;
    unsigned short m_44;
    unsigned char m_46;
    unsigned char m_low : 4;
    unsigned char m_high : 4;
    Rva005C8624Element(const Rva005C8624Element &that);
};
typedef char Verify005C8624Element[(sizeof(Rva005C8624Element) == 0x48) ? 1 : -1];

Rva005C8624Element::Rva005C8624Element(const Rva005C8624Element &that)
    : m_00(that.m_00), m_04(that.m_04), m_ref(), m_map(),
      m_vector(that.m_vector), m_44(that.m_44), m_46(that.m_46),
      m_low(that.m_low), m_high(that.m_high)
{
    for (unsigned int i = 0; i < 8; ++i)
        m_overlaps[i] = that.m_overlaps[i];
    if (!that.m_ref.m_target) {
        m_ref.rva000519BD();
    } else {
        Rva0051D93 *copy = new Rva0051D93(*(const BfmeAudioEventPrefix136 *)that.m_ref.m_target);
        m_ref.rva00053D26((BfmePoolHolder88 *)copy);
        // The existing setter owner is an ICF provider for this +4 store;
        // this cast does not claim that an audio record is a GameMessage.
        GameMessage *record = (GameMessage *)m_ref.m_target;
        record->friend_setList((GameMessageList *)TheAudio->slot60(&m_ref));
        ((HostClass005C8E0A *)this)->method_005C9069();
    }
}
