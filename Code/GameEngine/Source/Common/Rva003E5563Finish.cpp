// ??0Rva003E5563@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// retail 0x003E5563, 36 bytes.
// Evidence: default constructor of an address-derived class. It zeroes the int
// at +0x10, the four floats at +0..+0xc, then stores the 0x7ffffffe sentinel at
// +0x14. The `mov eax, ecx` prologue and eax-based stores are MSVC's constructor
// shape -- a plain void method with the same body compiles to 34 bytes -- and
// the sole caller 0x3E60BD (`lea ecx,[ebp-0x18]; call`) constructs a local.
// The banked attempt named this void; the constructor signature is what the
// bytes prove.

class Rva003E5563
{
public:
	Rva003E5563();

private:
	float m_00;
	float m_04;
	float m_08;
	float m_0c;
	int m_10;
	int m_14;
};

Rva003E5563::Rva003E5563()
{
	m_10 = 0;
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_14 = 0x7ffffffe;
}
