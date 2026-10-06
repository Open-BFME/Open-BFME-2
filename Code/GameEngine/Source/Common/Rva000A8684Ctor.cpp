// ??0Rva000A8684@@QAE@XZ
// partial score=0.92 date=2026-09-29
// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva000A8684@@QAE@XZ, retail 0x000A8684, 74 bytes.
// Honest-address default ctor (size 0x18 via new at 0x00051107).
// Zeroes +0/+4, sets +8=1, default-constructs UnicodeString at +0xC
// via the rowed ??0UnicodeString@@QAE@XZ, zeroes five bytes at
// +0x10-0x14. Callers at 0x00051128 and 0x0005595D are unclaimed
// new+ctor sequences so owner is unknown. EH via /EHsc.
class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString();
private:
	char * volatile m_data;
};
class UnicodeString
{
public:
	UnicodeString();
	~UnicodeString();
private:
	unsigned short *m_text;
};
class Rva000A8684
{
public:
	Rva000A8684();
private:
	AsciiString m_0;
	volatile int m_4;
	int m_8;
	UnicodeString m_str;
	volatile unsigned char m_10;
	volatile unsigned char m_11;
	volatile unsigned char m_12;
	volatile unsigned char m_13;
	volatile unsigned char m_14;
	char m_pad15;
	char m_pad16;
	char m_pad17;
};

Rva000A8684::Rva000A8684()
	: m_0()
	, m_4(0)
	, m_8(1)
	, m_str()
	, m_10(0)
	, m_11(0)
	, m_12(0)
	, m_13(0)
	, m_14(0)
{
}
