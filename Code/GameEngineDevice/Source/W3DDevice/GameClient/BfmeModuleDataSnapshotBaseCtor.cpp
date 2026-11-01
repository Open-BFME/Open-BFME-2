// cl: /DNDEBUG /MD
//
// ??0Rva001164B6@@QAE@XZ, retail 0x0011646E, 13 bytes.
// Base ctor installing vtable 0x00BCFB24 and zeroing +0x04. Evidence:
// sole matched caller LookupTablePostEffect ctor 0x111B87 constructs this
// base; vtable 0x00BCFB24.

extern "C" const void *const __identifier("??_7Rva001164B6@@6B@")[];

class Rva001164B6
{
public:
	Rva001164B6();
private:
	unsigned char m_pad[4];
	unsigned char m_04;
};

Rva001164B6::Rva001164B6()
{
	*(const void **)this = __identifier("??_7Rva001164B6@@6B@");
	m_04 = 0;
}
