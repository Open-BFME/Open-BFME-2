// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
//
// ??A?$hash_map@VAsciiString@@W4BuildableStatus@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@_STL@@@_STL@@QAEAAW4BuildableStatus@@ABVAsciiString@@@Z, retail 0x002460c3, 121 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
//
#include <hash_map>
#include <stddef.h>
#include "ascii_string.h"

enum BuildableStatus
{
	BUILDABLE_STATUS_UNKNOWN = 0
};

namespace rts
{
	template <class T> struct hash
	{
		size_t operator()(const T &value) const;
	};

	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
typedef _STL::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>,
	rts::equal_to<AsciiString>, _STL::allocator<BuildableStatusPair> > BuildableMap;


class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
};
class Rva00242F1A { public: void *rva00242F1A(const void *); };
struct BuildableSlotPair {
    AsciiString name;
    BuildableStatus status;
    BuildableSlotPair(const AsciiString &asciiString, BuildableStatus s) : name(asciiString), status(s) {}
};
// Native 0x002460C3..0x0024613C: GameLogic's +0x10 override map returns
// node+8 or inserts the copied key and enum zero, then returns pair+4.
// The 0x41534B provider has a proven nonthrowing hash/compare-only chain.
// ??A?$hash_map@VAsciiString@@W4BuildableStatus@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@_STL@@@_STL@@QAEAAW4BuildableStatus@@ABVAsciiString@@@Z
template<>
BuildableStatus &BuildableMap::operator[](const AsciiString &name)
{
    void *node;
    {
        Rva0041534BIter found = ((Rva00056F61 *)this)->rva0041534B(&name);
        node = found.m_node;
    }
    return *(BuildableStatus *)(node == 0
        ? (char *)((Rva00242F1A *)this)->rva00242F1A(
            &static_cast<const BuildableSlotPair &>(BuildableSlotPair(name, BUILDABLE_STATUS_UNKNOWN))) + 4
        : (char *)node + 8);
}

// Emit the owned specialization directly, without a synthetic GameLogic caller.
template BuildableStatus &BuildableMap::operator[](const AsciiString &name);
