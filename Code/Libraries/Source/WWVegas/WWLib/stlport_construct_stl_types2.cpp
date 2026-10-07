// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Fourth batch of STLport _Construct<T> placement-copy helpers, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own rowed copy ctor, and __EH_prolog resolves via its matched row.
// Game mapped types are declared minimally (opaque payloads, matching the
// struct/class-ness of their rowed copy ctors); no member is ever touched,
// so the emitted code is identical apart from the callee.

#include <memory>
#include <vector>

class AsciiString
{
public:
	AsciiString(const AsciiString &other);

private:
	char m_pad[4];
};

struct BfmePod88
{
	char m_body[88];
};

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition(const MultiplayerColorDefinition &other);

private:
	char m_pad[4];
};

struct TreeHintPayload003012F0
{
	char m_body[12];
};

struct TargetRef00217D4C;
struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;
};

typedef _STL::vector<BfmePod88> ConstructPodVec;
typedef _STL::pair<const int, MultiplayerColorDefinition> ConstructPairMP;
typedef _STL::pair<const AsciiString, TreeHintPayload003012F0> ConstructPairHP;
typedef _STL::pair<const AsciiString, TreeHintRef00217D4C> ConstructPairHR;

// The placement-copy helpers call external complete copy constructors.
// Their providers already own the target bodies; instantiating the generic
// copies here emitted competing definitions. The mapped handle is four bytes,
// proven by the canonical 358B43 copy's +4 pointer and pointee +4 AddRef.
namespace _STL {
template <> ConstructPodVec::vector(const ConstructPodVec &);
template <> ConstructPairHP::pair(const ConstructPairHP &);
template <> ConstructPairHR::pair(const ConstructPairHR &);
}


template void _STL::_Construct<ConstructPodVec, ConstructPodVec>(ConstructPodVec *, const ConstructPodVec &);
template void _STL::_Construct<ConstructPairMP, ConstructPairMP>(ConstructPairMP *, const ConstructPairMP &);
template void _STL::_Construct<ConstructPairHP, ConstructPairHP>(ConstructPairHP *, const ConstructPairHP &);
template void _STL::_Construct<ConstructPairHR, ConstructPairHR>(ConstructPairHR *, const ConstructPairHR &);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@URva0056644EElement@@U1@@_STL@@YAXPAURva0056644EElement@@ABU1@@Z=??$_Construct@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@0@ABU10@@Z")
#pragma comment(linker, "/alternatename:?Rva0052C404Construct@@YAXPAXPBX@Z=??$_Construct@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@0@ABU10@@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?dup_00223168@@YAXXZ=??$_Construct@U?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@0@ABU10@@Z")
#pragma comment(linker, "/alternatename:?dup_002057A8@@YAXXZ=??$_Construct@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@0@ABU10@@Z")
#pragma comment(linker, "/alternatename:?dup_002BF35B@@YAXXZ=??$_Construct@U?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@UTreeHintRef00217D4C@@@0@ABU10@@Z")
