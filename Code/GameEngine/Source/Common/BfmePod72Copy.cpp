// cl: /Ireference/shims/bfme2_ascii /EHs /MD
//
// ??0BfmePod72@@QAE@ABU0@@Z @0x002DFC1B 219B: existing pin (copy constructor
// called by the byte-verified _Construct 0x002DFD82; also 0x002E00C1). The
// 72-byte record's memberwise copy: AsciiString +0, word +4, bytes +8/+9, seven
// AsciiStrings +0xC..+0x24, words +0x28/+0x2C and two vector<unsigned int>
// (+0x30, +0x3C; rowed copy 0x002CFAB9), each constructed member advancing the
// EH state. Field meanings are not recovered.

#include "ascii_string.h"

namespace _STL
{
template <class T>
class allocator;

template <class T, class Alloc = allocator<T> >
class vector
{
public:
	vector(const vector<T, Alloc> &other);
	~vector();

private:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};
}

struct BfmePod72
{
	BfmePod72(const BfmePod72 &other);

	AsciiString m_00;
	int m_04;
	char m_08;
	char m_09;
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1C;
	AsciiString m_20;
	AsciiString m_24;
	int m_28;
	int m_2C;
	_STL::vector<unsigned int> m_30;
	_STL::vector<unsigned int> m_3C;
};

BfmePod72::BfmePod72(const BfmePod72 &other) :
	m_00(other.m_00),
	m_04(other.m_04),
	m_08(other.m_08),
	m_09(other.m_09),
	m_0C(other.m_0C),
	m_10(other.m_10),
	m_14(other.m_14),
	m_18(other.m_18),
	m_1C(other.m_1C),
	m_20(other.m_20),
	m_24(other.m_24),
	m_28(other.m_28),
	m_2C(other.m_2C),
	m_30(other.m_30),
	m_3C(other.m_3C)
{
}
