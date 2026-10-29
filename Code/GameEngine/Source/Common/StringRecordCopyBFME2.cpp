// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// BFME2 record copy at0x63BE4: seven words, an AsciiString, two tail bytes.
// The original application class and field meanings are unknown.
// The36-byte layout and memberwise copy are read directly from the complete
// retail body. Its string member calls the established copy at0x365F0.
// The placement-copy caller at0x63C8F independently links the same value.
// Canonical BF2 AsciiString preserves retail's one-pointer string layout and
// names cleanup through the real releaseBuffer provider instead of the false
// public StringBase destructor spelling. BF1 revision9cbfb551 record-copy TUs
// also use the shared header; BF2's releaseBuffer ABI is established separately.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &source)
      : word0(source.word0), word1(source.word1), word2(source.word2), word3(source.word3), word4(source.word4), word5(source.word5), word6(source.word6), text(source.text), tail0(source.tail0), tail1(source.tail1) {}
};
#include <memory>
// Codegen view of BFME2 AsciiString's one-pointer StringBase<char> base. Its
// copy operation calls retail 0x000365F0 without changing other record views.
template void _STL::_Construct<BfmeStringRecord00063BE4,BfmeStringRecord00063BE4>(BfmeStringRecord00063BE4*,const BfmeStringRecord00063BE4&);


// Retail copy 0x000B757D: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B757D {
    unsigned int word0, word1; AsciiString text; unsigned int word2; unsigned char tail;
    BfmeStringRecord000B757D(const BfmeStringRecord000B757D &source) : word0(source.word0), word1(source.word1), text(source.text), word2(source.word2), tail(source.tail) {}
};
template void _STL::_Construct<BfmeStringRecord000B757D,BfmeStringRecord000B757D>(BfmeStringRecord000B757D*,const BfmeStringRecord000B757D&);

// Retail copy 0x000B950F: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B950F {
    unsigned int word0; AsciiString text; unsigned int word1;
    BfmeStringRecord000B950F(const BfmeStringRecord000B950F &source) : word0(source.word0), text(source.text), word1(source.word1) {}
};
template void _STL::_Construct<BfmeStringRecord000B950F,BfmeStringRecord000B950F>(BfmeStringRecord000B950F*,const BfmeStringRecord000B950F&);

// Retail copy 0x000B9534: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B9534 {
    AsciiString text; unsigned char flag; unsigned int word0, word1, word2, word3;
    BfmeStringRecord000B9534(const BfmeStringRecord000B9534 &source) : text(source.text), flag(source.flag), word0(source.word0), word1(source.word1), word2(source.word2), word3(source.word3) {}
};
template void _STL::_Construct<BfmeStringRecord000B9534,BfmeStringRecord000B9534>(BfmeStringRecord000B9534*,const BfmeStringRecord000B9534&);

// Retail copy 0x002CF4C6: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord002CF4C6 {
    AsciiString text0, text1; unsigned int word0, word1; unsigned char flag0, flag1;
    BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &source) : text0(source.text0), text1(source.text1), word0(source.word0), word1(source.word1), flag0(source.flag0), flag1(source.flag1) {}
};
template void _STL::_Construct<BfmeStringRecord002CF4C6,BfmeStringRecord002CF4C6>(BfmeStringRecord002CF4C6*,const BfmeStringRecord002CF4C6&);

// Retail copy 0x002CF5B1: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord002CF5B1 {
    unsigned int word0, word1; AsciiString text;
    BfmeStringRecord002CF5B1(const BfmeStringRecord002CF5B1 &source) : word0(source.word0), word1(source.word1), text(source.text) {}
};
template void _STL::_Construct<BfmeStringRecord002CF5B1,BfmeStringRecord002CF5B1>(BfmeStringRecord002CF5B1*,const BfmeStringRecord002CF5B1&);

// Retail copy 0x00395E75: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00395E75 {
    AsciiString text0, text1; unsigned int word;
    BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &source) : text0(source.text0), text1(source.text1), word(source.word) {}
};
template void _STL::_Construct<BfmeStringRecord00395E75,BfmeStringRecord00395E75>(BfmeStringRecord00395E75*,const BfmeStringRecord00395E75&);

// Retail copy 0x00568CE0: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00568CE0 {
    AsciiString text0, text1; unsigned int word0, word1; unsigned char flag;
    BfmeStringRecord00568CE0(const BfmeStringRecord00568CE0 &source) : text0(source.text0), text1(source.text1), word0(source.word0), word1(source.word1), flag(source.flag) {}
};
template void _STL::_Construct<BfmeStringRecord00568CE0,BfmeStringRecord00568CE0>(BfmeStringRecord00568CE0*,const BfmeStringRecord00568CE0&);

// Retail copy 0x000B75AE: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B75AE {
    AsciiString text; unsigned int word0, word1, word2, word3, word4, word5; unsigned char flag0, flag1, flag2, flag3;
    BfmeStringRecord000B75AE(const BfmeStringRecord000B75AE &source) : text(source.text), word0(source.word0), word1(source.word1), word2(source.word2), word3(source.word3), word4(source.word4), word5(source.word5), flag0(source.flag0), flag1(source.flag1), flag2(source.flag2), flag3(source.flag3) {}
};
template void _STL::_Construct<BfmeStringRecord000B75AE,BfmeStringRecord000B75AE>(BfmeStringRecord000B75AE*,const BfmeStringRecord000B75AE&);

// Retail copy 0x003B3F78: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord003B3F78 {
    unsigned int word0, word1; AsciiString text; unsigned char flag; unsigned short short0; unsigned int word2;
    BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &source) : word0(source.word0), word1(source.word1), text(source.text), flag(source.flag), short0(source.short0), word2(source.word2) {}
};
template void _STL::_Construct<BfmeStringRecord003B3F78,BfmeStringRecord003B3F78>(BfmeStringRecord003B3F78*,const BfmeStringRecord003B3F78&);

// Retail copy 0x0040360E: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord0040360E {
    unsigned int word0; AsciiString text; unsigned int word1, word2;
    BfmeStringRecord0040360E(const BfmeStringRecord0040360E &source) : word0(source.word0), text(source.text), word1(source.word1), word2(source.word2) {}
};
template void _STL::_Construct<BfmeStringRecord0040360E,BfmeStringRecord0040360E>(BfmeStringRecord0040360E*,const BfmeStringRecord0040360E&);

// Retail copy 0x00404BF3: the 0x00404BC5 sibling ctor establishes an
// AsciiString at +0 and five floats at +4..+0x14; their meanings are unknown.
// The shared one-pointer AsciiString now owns the observed string field.
struct BfmeStringRecord00404BF3 {
    AsciiString text; float f0, f1, f2, f3, f4;
    BfmeStringRecord00404BF3(const BfmeStringRecord00404BF3 &source) : text(source.text), f0(source.f0), f1(source.f1), f2(source.f2), f3(source.f3), f4(source.f4) {}
};
template void _STL::_Construct<BfmeStringRecord00404BF3,BfmeStringRecord00404BF3>(BfmeStringRecord00404BF3*,const BfmeStringRecord00404BF3&);

// Retail copy 0x001EA478: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord001EA478 {
    AsciiString text0, text1;
    BfmeStringRecord001EA478(const BfmeStringRecord001EA478 &source) : text0(source.text0), text1(source.text1) {}
};
template void _STL::_Construct<BfmeStringRecord001EA478,BfmeStringRecord001EA478>(BfmeStringRecord001EA478*,const BfmeStringRecord001EA478&);

// Retail copy 0x00426A5B: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00426A5B {
    AsciiString text; unsigned char flag0, flag1, flag2;
    BfmeStringRecord00426A5B();
    BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &source) : text(source.text), flag0(source.flag0), flag1(source.flag1), flag2(source.flag2) {}
    BfmeStringRecord00426A5B &operator=(const BfmeStringRecord00426A5B &source);
};
BfmeStringRecord00426A5B::BfmeStringRecord00426A5B() : text(AsciiString::TheEmptyString), flag0(0), flag1(1), flag2(0) {}
inline BfmeStringRecord00426A5B &BfmeStringRecord00426A5B::operator=(const BfmeStringRecord00426A5B &source) {
    ((StringBase<char> &)text).set((const StringBase<char> &)source.text);
    flag0 = source.flag0;
    flag1 = source.flag1;
    flag2 = source.flag2;
    return *this;
}
template void _STL::_Construct<BfmeStringRecord00426A5B,BfmeStringRecord00426A5B>(BfmeStringRecord00426A5B*,const BfmeStringRecord00426A5B&);
#include <vector>
// Retail __copy 0x00426A82 47B: forward copy of 8-byte BfmeStringRecord00426A5B via operator= at 0x004267A5; sar 3 stride 8; caller at 0x00426B29; same shape as 47B __copy at 0x00215696 and 0x001737C0.
template BfmeStringRecord00426A5B* _STL::__copy<BfmeStringRecord00426A5B*, BfmeStringRecord00426A5B*, int>(BfmeStringRecord00426A5B*, BfmeStringRecord00426A5B*, BfmeStringRecord00426A5B*, const _STL::random_access_iterator_tag&, int*);

// Retail copy 0x004071F7: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord004071F7 {
    AsciiString text; unsigned int word0, word1;
    BfmeStringRecord004071F7(const BfmeStringRecord004071F7 &source) : text(source.text), word0(source.word0), word1(source.word1) {}
};
template void _STL::_Construct<BfmeStringRecord004071F7,BfmeStringRecord004071F7>(BfmeStringRecord004071F7*,const BfmeStringRecord004071F7&);

// Retail copy 0x004D05B8: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord004D05B8 {
    unsigned short short0; AsciiString text;
    BfmeStringRecord004D05B8(const BfmeStringRecord004D05B8 &source) : short0(source.short0), text(source.text) {}
};
template void _STL::_Construct<BfmeStringRecord004D05B8,BfmeStringRecord004D05B8>(BfmeStringRecord004D05B8*,const BfmeStringRecord004D05B8&);

// Retail copy 0x00331962: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00331962 {
    unsigned int word; AsciiString text; unsigned char flag;
    BfmeStringRecord00331962(const BfmeStringRecord00331962 &source) : word(source.word), text(source.text), flag(source.flag) {}
};
template void _STL::_Construct<BfmeStringRecord00331962,BfmeStringRecord00331962>(BfmeStringRecord00331962*,const BfmeStringRecord00331962&);

// Retail copy 0x000B94D2: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B94D2 {
    AsciiString text0, text1;
    BfmeStringRecord000B94D2(const BfmeStringRecord000B94D2 &source) : text0(source.text0), text1(source.text1) {}
};
template void _STL::_Construct<BfmeStringRecord000B94D2,BfmeStringRecord000B94D2>(BfmeStringRecord000B94D2*,const BfmeStringRecord000B94D2&);

// Retail copy 0x00466E64: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00466E64 {
    AsciiString text0, text1; unsigned int word;
    BfmeStringRecord00466E64(const BfmeStringRecord00466E64 &source) : text0(source.text0), text1(source.text1), word(source.word) {}
};
template void _STL::_Construct<BfmeStringRecord00466E64,BfmeStringRecord00466E64>(BfmeStringRecord00466E64*,const BfmeStringRecord00466E64&);

// Native lookup 0x00467799 consumes the existing 12-byte string record
// view: the first string is compared through verified worker 0x000069D6.
// Only the owner pointer at +4 and its vector at +0x180 are established;
// the original owner and lookup names remain unknown.
struct Rva00467799Vector
{
    BfmeStringRecord00466E64 *begin;
    BfmeStringRecord00466E64 *end;
    BfmeStringRecord00466E64 *capacity;
    unsigned int size() const { return (unsigned int)(end - begin); }
};
struct Rva00467799Owner
{
    unsigned char opaque_00[0x180];
    Rva00467799Vector records;
};
class Rva00467799
{
public:
    BfmeStringRecord00466E64 *rva00467799(const StringBase<char> &key);
private:
    unsigned char opaque_00[4];
    Rva00467799Owner *owner;
};

// ?rva00467799@Rva00467799@@QAEPAUBfmeStringRecord00466E64@@ABV?$StringBase@D@@@Z
// Ghidra extent 0x00467799..0x004677FD; RET 4. The IDIV 12 and record
// compare establish the stride and consumed string; each iteration
// rechecks the vector size after the call.
BfmeStringRecord00466E64 *Rva00467799::rva00467799(const StringBase<char> &key)
{
    Rva00467799Vector *records = &owner->records;
    for (unsigned int i = 0; i < records->size(); ++i)
    {
        if (key.compare(*(const StringBase<char> *)&records->begin[i].text0) == 0)
            return &records->begin[i];
    }
    return 0;
}

// Retail copy 0x00239B46: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00239B46 {
    AsciiString text; unsigned short short0;
    BfmeStringRecord00239B46(const BfmeStringRecord00239B46 &source) : text(source.text), short0(source.short0) {}
};
template void _STL::_Construct<BfmeStringRecord00239B46,BfmeStringRecord00239B46>(BfmeStringRecord00239B46*,const BfmeStringRecord00239B46&);

// Retail dtor 0x001EA443 (53B) and deleting dtor 0x001EA4B5 (28B): two
// narrow-string members at +0/+4 destroyed in reverse order through the
// shared string releaseBuffer at 0x36410, with /EHsc states. Identity unproven
// beyond the string-pair layout shared with BfmeStringRecord001EA478, so
// both land under an honest Rva address name in this TU (same flags).
class Rva001EA443
{
public:
	~Rva001EA443();
private:
	AsciiString m_text0;
	AsciiString m_text1;
};
Rva001EA443::~Rva001EA443() {}
void famgenDelete001EA443(Rva001EA443 *p) { delete p; }

// Retail dtor 0x00395D77 (53B): two narrow-string members at +0/+4 destroyed
// in reverse order through the shared string releaseBuffer at 0x36410 with /EHsc
// states. Same 53B shape as 0x001EA443 in this TU (mov eax scope-table reloc
// plus EH prolog plus two releaseBuffer calls). Callers at 0x3962CE 0x396EF2
// 0x396F22 0x39933F 0x39A618 plus jmp tail at 0x39698F prove dtor role.
// Next copy 0x395E75 (BfmeStringRecord00395E75 text0 text1 word) shares the
// string-pair layout. Honest Rva address name; same flags.
class Rva00395D77
{
public:
	~Rva00395D77();
private:
	AsciiString m_text0;
	AsciiString m_text1;
};
Rva00395D77::~Rva00395D77() {}

// Retail dtor 0x00568C4E (53B): two narrow-string members at +0/+4 destroyed
// in reverse order through the shared string releaseBuffer at 0x36410 with /EHsc
// states. Same 53B shape as 0x001EA443 and 0x00395D77 in this TU (mov eax
// scope-table reloc plus EH prolog plus two releaseBuffer calls). Destroy loop
// at 0x569A5B steps 0x14 (20-byte BfmeStringRecord00568CE0) plus deleting-dtor
// caller at 0x568E17 and parse caller at 0x56A96F prove dtor role.
// Honest Rva address name; same flags.
class Rva00568C4E
{
public:
	~Rva00568C4E();
private:
	AsciiString m_text0;
	AsciiString m_text1;
};
Rva00568C4E::~Rva00568C4E() {}
void famgenDelete00568C4E(Rva00568C4E *p) { delete p; }

// Retail _Construct 0x000BB993 45B: placement copy of Rva000BB491 via the
// rowed copy ctor at 0x000BB491; same 45B EH shape as 0x000BB9ED in this TU;
// callers at 0x000BBAD5 0x000BBB00 0x000C3543 0x000C46A0.
class Rva000BB491
{
public:
	Rva000BB491(const Rva000BB491 &source);
};
template void _STL::_Construct<Rva000BB491, Rva000BB491>(Rva000BB491 *, const Rva000BB491 &);

// Retail _Construct 0x000BB9C0 45B: placement copy of Rva000BB4AC via the
// rowed copy ctor at 0x000BB4AC; same 45B EH shape as neighbours in this TU;
// callers at 0x000BBB20 0x000BBB4B 0x000C35FA 0x000C46D7.
class Rva000BB4AC
{
public:
	Rva000BB4AC(const Rva000BB4AC &source);
};
template void _STL::_Construct<Rva000BB4AC, Rva000BB4AC>(Rva000BB4AC *, const Rva000BB4AC &);

// Retail _Construct 0x00568C83 18B: placement copy of Rva00568A20 via the
// rowed copy ctor at 0x00568A20; null-checked; callers at 0x00568CA3 0x00568CCE
// 0x0056A23A 0x0056A33D; step 0xC matches 12-byte Rva00568A20.
class Rva00568A20
{
public:
	Rva00568A20(const Rva00568A20 &source) throw();
};
template void _STL::_Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &);

// BFME 1 donor compiled with BFME 2 /O1 settings from revision 968ca36c3265b295297e6aed45a6bd89ffe59c40.
// The retail insertion-sort caller at 0x00331BD7 names this specialization; donor_sweep placed its 75-byte body at 0x00331A46.
struct S4Name
{
    S4Name(const S4Name &other) : m_base(other.m_base) {}
    ~S4Name(void) {}
    S4Name &operator=(const S4Name &other)
    {
        ((StringBase<char> &)m_base).set((const StringBase<char> &)other.m_base);
        return *this;
    }
    AsciiString m_base;
};

struct S4SortElem12
{
    int m_bfmeA;
    S4Name m_bfmeName;
    char m_bfmeC;
    S4SortElem12 &operator=(const S4SortElem12 &);
};

struct S4Cmp002E1690
{
    int m_bfmeSlot;
    bool operator()(const S4SortElem12 &left, const S4SortElem12 &right) const
    {
        return left.m_bfmeA < right.m_bfmeA;
    }
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
    RandomAccessIter next = last;
    --next;
    while (comp(val, *next))
    {
        *last = *next;
        last = next;
        --next;
    }
    *last = val;
}

template void __unguarded_linear_insert<S4SortElem12 *, S4SortElem12, S4Cmp002E1690>(
    S4SortElem12 *, S4SortElem12, S4Cmp002E1690);

}

#include <list>

// Use the typed node comparison here; the iterator-base out-of-line wrapper
// belongs to the retail STLport owner compiled with its own settings.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12 {public:void rva0004CBC0()throw();};
class BfmeParticleSystemHandle {public:
 ParticleSystem *ptr;void *previous,*next;
 __forceinline ~BfmeParticleSystemHandle()throw(){if(ptr)((RvaSmartPtr12*)this)->rva0004CBC0();}
 __forceinline operator bool()const{return ptr!=0;}
 __forceinline ParticleSystem *operator->()const{return ptr?ptr:Make001FCBD7();}
};
enum ParticleSystemID {INVALID_PARTICLE_SYSTEM_ID=0};
class Rva000B75FF;
class ParticleSystemManager {BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID);friend class Rva000B75FF;};
extern ParticleSystemManager *TheParticleSystemManager;
class Rva001F3852ByteOneSetter {public:void enable();};
class Rva001F384AByteZeroSetter {public:void disable();};
class Rva001F3C13ByteSlot {public:void set(unsigned char);};
struct Rva001F38C1Arg {int words[12];};
class Rva001F38C1Slot {public:void set(const Rva001F38C1Arg&);};
struct ParticleFlagView {char pad[0x1a7];bool active;};
struct ParticleMDView {char pad[0x12a];bool useDrawableBones;};
struct ParticleTrackerNode {ParticleTrackerNode*next,*previous;BfmeStringRecord000B757D value;};
class Drawable {public:bool rva00272835(int,int);};
struct ParticleMatrixView {float values[12];};
class ParticleRenderCallView {public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44();
 virtual void s45();
 virtual void s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual ParticleMatrixView Get_Bone_Transform(int)const;
 virtual void s52();
 virtual bool Is_Bone_Captured(int)const;
};
class Rva000B75FF {public:
 char pad00[8];void *state;char pad0c[0x44-0xc];ParticleRenderCallView *render;char pad48[0x58-0x48];_STL::list<BfmeStringRecord000B757D> systems;
 __forceinline const ParticleMDView *data()const{return *(const ParticleMDView*const*)((const char*)this-8);}
 __forceinline Drawable *drawable()const{return *(Drawable*const*)((const char*)this-4);}
 bool rva000B75FF(bool ignoreInactive);
};
// WB twin 0x92EF60 (callgraph score 1.0): three early-out guards, then a walk
// over the tracked particle-system records. Each record's id is resolved via
// TheParticleSystemManager; inactive systems end the update when
// ignoreInactive is set. Drawable-bone systems copy the record and ask the
// Drawable for the named bone transform, and on success apply it and continue
// (the twin destroys the record and handle and jumps to the increment).
// Otherwise a nonzero bone index drives captured/enabled state and the render
// object's bone transform. Fields are read through the iterator as in the twin.
bool Rva000B75FF::rva000B75FF(bool ignoreInactive)
{
 if(!state)return true;
 if(!render)return true;
 if(!drawable())return true;
 for(_STL::list<BfmeStringRecord000B757D>::const_iterator it=systems.begin();it!=systems.end();++it)
 {
  BfmeParticleSystemHandle sys=TheParticleSystemManager->findParticleSystemByID((ParticleSystemID)it->word0);
  if(!sys)continue;
  if(!((ParticleFlagView*)sys.operator->())->active && ignoreInactive)return true;
  int bone=it->word1;
  if(data()->useDrawableBones)
  {
   ParticleMatrixView transform;
   BfmeStringRecord000B757D record(*it);
   if(drawable()->rva00272835((int)record.text.str(),(int)&transform))
   {
    ((Rva001F38C1Slot*)sys.operator->())->set(*(const Rva001F38C1Arg*)&transform);
    ((Rva001F3C13ByteSlot*)sys.operator->())->set(1);
    continue;
   }
  }
  else if(bone)
  {
   if(render->Is_Bone_Captured(bone))((Rva001F384AByteZeroSetter*)sys.operator->())->disable();
   else ((Rva001F3852ByteOneSetter*)sys.operator->())->enable();
   const ParticleMatrixView transform=render->Get_Bone_Transform(bone);
   ((Rva001F38C1Slot*)sys.operator->())->set(*(const Rva001F38C1Arg*)&transform);
   ((Rva001F3C13ByteSlot*)sys.operator->())->set(1);
  }
 }
 return true;
}
