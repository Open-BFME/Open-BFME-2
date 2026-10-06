// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??4BfmeSubobject0022CE19@@QAEAAU0@ABU0@@Z, retail 0x002DDC76, 149 bytes.
// Copy-assign of BfmeSubobject0022CE19: three AsciiString at +4/+8/+0C via
// rowed set 0x000366F0, 16-byte date at +0x10, UnicodeString at +0x20 via
// rowed wide set 0x00037150, dwords +0x24/+0x28, AsciiString +0x2C,
// UnicodeStrings +0x30/+0x34, vector<SaveMapPreview> +0x38 via rowed
// 0x002DD043, subobject +0x44 via rowed 0x002DBC1F. Layout from
// SaveGameInfoCopyBFME2.cpp (copy ctor 0x0022CE19, dtor 0x002DD1E9).
// Evidence: chain lane calls just-landed 0x002DBC1F; pin
// ??4BfmeSubobject0022CE19 at 0x002DDC76; callers 0x002DF029 0x002DF16E
// 0x00401F8B 0x00437566; prev 0x002DD1E9 next 0x002DDD0B.
#include "ascii_string.h"
#include "unicode_string.h"

class Xfer;

class Rva0022CE19SnapshotBase {
public:
	virtual ~Rva0022CE19SnapshotBase();
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
};

struct BfmeSaveDate {
	unsigned short values[8];
};

class SaveMapPreview {
public:
	virtual ~SaveMapPreview();
	unsigned int word04;
	unsigned int word08;
	unsigned int word0C;
	unsigned int word10;
};

namespace _STL {
template <class Type>
class allocator {
};
template <class Type, class Allocator>
class vector {
public:
	vector &operator=(const vector &x);
private:
	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};
}

struct BfmeSubobject00229875 {
	virtual ~BfmeSubobject00229875();
	BfmeSubobject00229875 &rva002DBC1F(const BfmeSubobject00229875 &o);
	unsigned char _pad[0xDA0];
};

struct BfmeSubobject0022CE19 : Rva0022CE19SnapshotBase {
	virtual ~BfmeSubobject0022CE19();
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
	AsciiString text04;
	AsciiString text08;
	AsciiString text0C;
	BfmeSaveDate date10;
	UnicodeString text20;
	unsigned int word24;
	unsigned int word28;
	AsciiString text2C;
	UnicodeString text30;
	UnicodeString text34;
	_STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> > range38;
	BfmeSubobject00229875 object44;
	BfmeSubobject0022CE19 &operator=(const BfmeSubobject0022CE19 &o);
};

BfmeSubobject0022CE19 &BfmeSubobject0022CE19::operator=(const BfmeSubobject0022CE19 &o)
{
	text04 = o.text04;
	text08 = o.text08;
	text0C = o.text0C;
	date10 = o.date10;
	text20 = o.text20;
	word24 = o.word24;
	word28 = o.word28;
	text2C = o.text2C;
	text30 = o.text30;
	text34 = o.text34;
	range38 = o.range38;
	object44.rva002DBC1F(o.object44);
	return *this;
}
