// ?insert@?$vector@URva000C8E19Element@@V?$allocator@URva000C8E19Element@@@_STL@@@_STL@@QAEPAURva000C8E19Element@@PAU3@ABU3@@Z
// partial score=0.65 date=2026-09-25
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector::insert emitter for target boundary 0x000C8E19/214.
// Rva000C8E19Element is an opaque 248-byte nontrivial codegen view; it does
// not claim an application record type or full element layout.
#include <vector>

template<class T> class StringBase {
	void *m_data;
	void releaseBuffer();
public:
	StringBase();
	StringBase(const StringBase &);
	StringBase &operator=(const StringBase &);
protected:
	__forceinline ~StringBase() { releaseBuffer(); }
};

class AsciiString : private StringBase<char> {
public:
	__forceinline AsciiString() {}
	__forceinline AsciiString(const AsciiString &o) : StringBase<char>(o) {}
	__forceinline ~AsciiString() {}
	AsciiString &operator=(const AsciiString &);
};

struct Rva000C8E19Element {
	AsciiString string_head;
	int opaque[61];
	Rva000C8E19Element() {}
	Rva000C8E19Element(const Rva000C8E19Element &);
	Rva000C8E19Element &operator=(const Rva000C8E19Element &);
	~Rva000C8E19Element();
};

namespace _STL {
template <> void _Construct<Rva000C8E19Element, Rva000C8E19Element>(
	Rva000C8E19Element *, const Rva000C8E19Element &);
}

template Rva000C8E19Element *
_STL::vector<Rva000C8E19Element>::insert(
	Rva000C8E19Element *, const Rva000C8E19Element &);
