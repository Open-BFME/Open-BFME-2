// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva00407137@Rva00407137@@QAEXABVUnicodeString@@@Z retail 0x00407137 88B
// Evidence: unlock lane; AsciiString from UnicodeString 0x00038250 plus CRC::String 0x00619B00 plus releaseBuffer 0x00036410; caller 0x004071AA; prev StringRecordCopy same /O1 /EHsc.
class UnicodeString;
class CRC
{
public:
	static unsigned long String(const char *string, unsigned long crc);
};

template <typename T>
struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class Rva00407137
{
public:
	void rva00407137(const UnicodeString &u);
	void rva0040710C(const AsciiString &s);
private:
	unsigned long m_crc;
	bool m_flag;
};

void Rva00407137::rva00407137(const UnicodeString &u)
{
	m_flag = true;
	AsciiString s(u);
	const char *str = s.str();
	m_crc = CRC::String(str, m_crc);
}

// ?rva0040710C@Rva00407137@@QAEXABVAsciiString@@@Z @0x0040710C, 43 bytes.
// Target evidence: body sets the same flag and CRC field as the Unicode overload;
// packet identifies the AsciiString parameter and CRC::String callee.
void Rva00407137::rva0040710C(const AsciiString &s)
{
	m_flag = true;
	m_crc = CRC::String(s.str(), m_crc);
}

// ?Rva004071AAForward@@YAXPAVRva004071AAVirt@@ABVUnicodeString@@HPAVRva00407137@@@Z retail 0x004071AA 45B
// Evidence: chain lane calls rowed 0x00407137 plus virtual slot 0x68 plus AsciiString 0x00038250 plus releaseBuffer 0x00036410; caller 0x00408CA9; prev same TU same flags.
class Rva004071AAVirt
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual void v26(const UnicodeString &u);
	virtual void v27(const AsciiString &s);
};
void Rva004071AAForward(Rva004071AAVirt *p, const UnicodeString &u, int dummy, Rva00407137 *r)
{
	p->v26(u);
	r->rva00407137(u);
	AsciiString tmp(u);
}

// ?Rva0040718FForward@@YAXPAXABVAsciiString@@HPAVRva00407137@@@Z @0x0040718F, 27 bytes.
// Target evidence: this dispatches virtual slot 0x6C then calls the landed ASCII CRC overload.
void Rva0040718FForward(void *v, const AsciiString &s, int dummy, Rva00407137 *r)
{
	((Rva004071AAVirt *)v)->v27(s);
	r->rva0040710C(s);
}
