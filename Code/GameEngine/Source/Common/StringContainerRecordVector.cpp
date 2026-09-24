// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Vector lifecycle for BfmeContainerRecord00048139, the 0x5C string-headed
// record whose placement copy lives in StringContainerRecordCopyBFME2.cpp
// (two AsciiStrings at +0/+4, a 0x4C WeaponTemplateSetHead, two words).
// Retail keeps the record teardown, the range destroyer and the owning
// range destructor as three separate bodies: the record dtor at 0x00470A0
// (EH frame over the two StringBase<char> teardown calls through the
// folded AsciiString pin at 0x36410), the _Destroy range loop at 0x004A9F3
// (25 bytes, stride 0x5C, single call per element into the record dtor)
// and the owning two-pointer range destructor at 0x004B205 (frameless
// destroy plus conditional buffer free through _free at 0x30830).
#include <vector>

template <typename T> class StringBase {
	StringBase(const StringBase &);
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char> {
public:
	~AsciiString();
};

struct BfmeContainerRecord00048139 {
	AsciiString text0;
	AsciiString text1;
	unsigned char m_pad[0x5C - 8];
	~BfmeContainerRecord00048139();
};

// ??1BfmeContainerRecord00048139@@QAE@XZ @0x00470A0
BfmeContainerRecord00048139::~BfmeContainerRecord00048139()
{
}

// ??$_Destroy@PAUBfmeContainerRecord00048139@@@_STL@@YAXPAUBfmeContainerRecord00048139@@0@Z @0x004A9F3
template void _STL::_Destroy<BfmeContainerRecord00048139 *>(BfmeContainerRecord00048139 *, BfmeContainerRecord00048139 *);

extern "C" void free(void *ptr);

// Two-pointer owning range over the record buffer: destroy the live span,
// then free the buffer when one was allocated.
struct BfmeRecordRange004B205 {
	BfmeContainerRecord00048139 *m_begin;
	BfmeContainerRecord00048139 *m_end;
	~BfmeRecordRange004B205();
};

// ??1BfmeRecordRange004B205@@QAE@XZ @0x004B205
BfmeRecordRange004B205::~BfmeRecordRange004B205()
{
	_STL::_Destroy(m_begin, m_end);
	if (m_begin != 0) {
		free(m_begin);
	}
}
