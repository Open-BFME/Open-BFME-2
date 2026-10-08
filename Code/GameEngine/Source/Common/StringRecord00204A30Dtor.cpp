// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??1BfmeStringRecord00204A30@@QAE@XZ retail 0x00204848 54B.
// Same layout as the 0x00204A30 copy ctor in StringRecordInlineCopyBFME2.cpp
// (word AsciiString word AsciiString word = 0x14). Destroys text1 at +0x0C
// then text0 at +0x04 via the StringBase dtor fold at 0x00036410.
// Same EH scope 0x00B6C7A3 as the copy ctor. Caller 0x00206CBA is the
// 0x14-stride array destroy loop.
template <class T> class StringBase
{
	friend class AsciiString;
	void releaseBuffer();
public:
	void *p;
};
class AsciiString : public StringBase<char>
{
public:
	~AsciiString() { releaseBuffer(); }
};
struct BfmeStringRecord00204A30 {
    unsigned int word0; AsciiString text0; unsigned int word1; AsciiString text1; unsigned int word2;
    ~BfmeStringRecord00204A30();
};
BfmeStringRecord00204A30::~BfmeStringRecord00204A30() {}
