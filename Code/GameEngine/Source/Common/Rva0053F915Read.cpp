// cl: /EHs /MD
// Rva0053FB33::rva0053F915, retail 0x0053F915, 106 bytes.
// Vslot 4 of 0x008694DC (Rva0053FB33): reads AsciiString via rowed
// DataChunkInput::readAsciiString into +0x18 via an inline AsciiString::op=
// forwarding to the rowed StringBase<char>::set 0x000366F0 (member address
// formed before the push, as retail does), reads
// int to +0x1C via rowed readInt, reads +0x20 if version word at second arg
// +8 >= 3 else zeroes. Returns true. Evidence: vslot, donor dtor layout,
// callers 0x00540BEF 0x005423C8.

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")



class DataChunkInput
{
public:
	AsciiString readAsciiString();
	int readInt();
};

struct Rva0053FB33Holder
{
	~Rva0053FB33Holder();
	void *m_ptr;
};

class Rva0053FB33
{
public:
	virtual bool rva0053F915(DataChunkInput *input, void *ver);
private:
	Rva0053FB33Holder m_holder04;
	char m_pad08[0x18 - 0x08];
	AsciiString m_str18;
	int m_1C;
	int m_20;
};

bool Rva0053FB33::rva0053F915(DataChunkInput *input, void *ver)
{
	m_str18 = input->readAsciiString();
	m_1C = input->readInt();
	if (*(unsigned short *)((char *)ver + 8) >= 3)
		m_20 = input->readInt();
	else
		m_20 = 0;
	return true;
}
