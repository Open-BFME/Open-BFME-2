// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// stlport
//
// ??0Rva00507823@@QAE@XZ retail 0x0050775B 172B
// Base ctor storing vtable 0x00864010 same as dtor 0x00507823. Zeroes two
// 0x80 mask blocks at +0x04 and +0x84 via rowed clear80 0x001EAE6F plus
// and-zero at +0x104 then builds two 12B vectors at +0x108 and +0x114 via
// pinned Vector_base 0x00211E58 plus filter at +0x120 via pinned ctor
// 0x003623E5 plus two FixedStorage temps from 0x009FEFA4 via rowed copy
// 0x0004543D consumed by pinned initFromStorages 0x00362087 plus bool at
// +0x124. Evidence: deleting dtor 0x00507807 calls dtor 0x00507823 plus
// derived 0x00507C2D calls here as base plus slot 8 resolve 0x00507877
// proves AsciiString vectors at +0x108/+0x114 and masks at +0x04/+0x84.
// Same EH 0/1/2 shape as EmotionTracker precedent.
#include <vector>

// Retail VA 0x00DFEFA4: 28-byte prototype copied as BfmeFixedStorage by
// filter constructors. The consumers establish the copy type; the bytes are
// preserved verbatim from game.dat, without assigning member semantics.
unsigned char g_00DFEFA4StoragePrototype[28] = {
	0xEF, 0x37, 0x01, 0x38, 0x13, 0x38, 0x25, 0x38,
	0x37, 0x38, 0x49, 0x38, 0x5B, 0x38, 0x6D, 0x38,
	0x7F, 0x38, 0x91, 0x38, 0xA3, 0x38, 0xB5, 0x38,
	0xC7, 0x38, 0xD9, 0x38
};

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper() { clear80(); }
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};

#include "ascii_string.h"


class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	Rva001EAE6FHelper m_bits04;
	Rva001EAE6FHelper m_bits84;
	int m_104;
	_STL::vector<AsciiString> m_vec108;
	_STL::vector<AsciiString> m_vec114;
	Rva003623E5Member m_filter120;
	bool m_124;
};

Rva00507823::Rva00507823()
	: m_104(0)
	, m_124(false)
{
	m_filter120.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)));
}
