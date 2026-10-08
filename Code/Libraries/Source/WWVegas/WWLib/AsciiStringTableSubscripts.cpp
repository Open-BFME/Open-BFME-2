// cl: /O1 /G7 /arch:SSE /Oy- /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// Name-keyed table subscripts recovered from their complete native bodies.
// Native call sites establish each existing lookup/insert provider and payload
// access. Application names remain unknown except where the rowed callers say
// otherwise; address-derived owner names preserve that uncertainty.
#include "ascii_string.h"

// These insert signatures preserve the providers' existing ledger identities.
// Their record types are opaque here: no provider record is constructed and
// no size is inferred from those old donor spellings. The native callers prove
// the temporary's four-byte key and mapped word (or byte), and the reference/
// pointer ABI projects that actual temporary into the existing callee's view.
namespace _STL { template<class A, class B> struct pair; }
struct NoCaseTreeValue4;
struct TreeHintPayload0005808E;
struct TreeHintPayload00207343;
struct TreeHintPayload00410B17;
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> StoredPair4;
typedef _STL::pair<const AsciiString, TreeHintPayload0005808E> StoredPair5808E;
typedef _STL::pair<const AsciiString, TreeHintPayload00207343> StoredPair07343;
typedef _STL::pair<const AsciiString, TreeHintPayload00410B17> StoredPair10B17;
struct AudioEventInfo;

class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
    // 41534B -> 56F61 -> 55041/2BA61 and 69D6/6733/memcmp: read-only,
    // no allocations, callbacks, or C++ throws. Its provider uses this contract.
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
    bool *rva003A3763(const AsciiString *);
};
struct WordSlotPair {
    AsciiString name;
    unsigned int value;
    WordSlotPair(const AsciiString &n, unsigned int v) : name(n), value(v) {}
};
struct FloatSlotPair {
    AsciiString name;
    float value;
    FloatSlotPair(const AsciiString &n, float v) : name(n), value(v) {}
};
struct BoolSlotPair {
    AsciiString name;
    bool value;
    BoolSlotPair(const AsciiString &n, bool v) : name(n), value(v) {}
};
class Rva000427195 {
public:
    StoredPair5808E *rva00058C6F(const StoredPair5808E *);
    void *rva000A7A63(const StoredPair4 *);
    StoredPair4 *rva002234BA(const StoredPair4 *);
    void *rva003A2F08(const StoredPair07343 &);
    StoredPair10B17 *rva00410E67(const StoredPair10B17 *);
    void *rva000A7B3C(const AsciiString *);
    void *rva004112A0(const AsciiString *);
};
class Rva00059FBBMap { public: AudioEventInfo *&rva00059FBB(const AsciiString &); };
class Rva001FDE3F { public: float &rva001FDE3F(const AsciiString &); };
class Rva002235F3 { public: void *rva002235F3(const void *); };
class Rva002AE4C5 { public: int &rva002AE4C5(const AsciiString *); };
class Rva002CFEA5 { public: void *rva002CFEA5(const AsciiString *); };
class Rva002ADD31 { public: void *rva002ADD31(const void *); };
class Rva002CFB4C { public: void *rva002CFB4C(const void *); };

// 59FBB..5A034 RET4; MilesAudioManager::addUnownedAudioEventInfo at 5ADA3 stores an event-info pointer in its +BC name map; WB7AD3F0 and native insert58C6F prove copied-key/default slot.
AudioEventInfo *& Rva00059FBBMap::rva00059FBB(const AsciiString &name) {
 const AsciiString *key=&name;
 void *node;
 { Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(key); node=found.m_node; }
 return *(AudioEventInfo **)(node==0 ? (char *)((Rva000427195 *)this)->rva00058C6F((const StoredPair5808E *)&static_cast<const WordSlotPair &>(WordSlotPair(*key, 0)))+4 : (char *)node+8);
}

// A7B3C..A7BB5 RET4; full native body copies key365F0 and zero word then calls existing insertA7A63; mapped slot is insert result+4 or node+8; original application identity remains unproven.
void * Rva000427195::rva000A7B3C(const AsciiString *key) {
 void *node;
 { Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(key); node=found.m_node; }
 return (void *)(node==0 ? (char *)((Rva000427195 *)this)->rva000A7A63((const StoredPair4 *)&static_cast<const WordSlotPair &>(WordSlotPair(*key, 0)))+4 : (char *)node+8);
}

// 1FDE3F..1FDEBC RET4; PlayerTemplate::parseProductionTimeChange at1FDF73 uses map+100 and stores a float through this reference; native xorps/movss default zero and insert58C6F establish payload; WBA79920 supplies structural lead.
float & Rva001FDE3F::rva001FDE3F(const AsciiString &name) {
 const AsciiString *key=&name;
void *node;
 { Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(key); node=found.m_node; }
 return *(float *)(node==0 ? (char *)((Rva000427195 *)this)->rva00058C6F((const StoredPair5808E *)&static_cast<const FloatSlotPair &>(FloatSlotPair(*key, 0)))+4 : (char *)node+8);
}
