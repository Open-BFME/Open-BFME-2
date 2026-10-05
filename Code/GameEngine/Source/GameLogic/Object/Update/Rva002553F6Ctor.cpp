// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
//
// ??0Rva002553F6@@QAE@XZ @0x002553F6 74B
// Ctor storing vtable 0x00BF35C0, Rva0024C7B3Member at +8 (double zero is
// retail, CrateTemplate precedent), float kF7C at +0x24, ints at +0x28/+0x2c,
// Rva0025342CMember construct at +0x30 (ends at +0x140), int at +0x140,
// then explicit memset of +8. Neighbours StealthDetector/Invisibility
// friend_new give TU and flags.

#pragma function(memset)

extern "C" void *memset(void *dst, int value, unsigned int size);
extern "C" float kF7C;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	unsigned char m_data[0x1C];
};

class Rva0025342CMember
{
public:
	Rva0025342CMember *construct();

private:
	unsigned char m_data[0x110];
};

class Rva002553F6
{
public:
	Rva002553F6();
	virtual void rva002553F6_dummy();

private:
	int m_04;
	Rva0024C7B3Member m_08;
	float m_24;
	int m_28;
	int m_2C;
	Rva0025342CMember m_30;
	int m_140;
};

Rva002553F6::Rva002553F6()
{
	float tmp = kF7C;
	m_28 = 0;
	m_24 = tmp;
	_ReadWriteBarrier();
	m_2C = 0;
	m_30.construct();
	m_140 = 0;
	memset(&m_08, 0, 0x1C);
}

// _kF7C: the global at VA 0xbc292c is ?g_objectSpacingDefault@@3MA.
#pragma comment(linker, "/alternatename:_kF7C=?g_objectSpacingDefault@@3MA")
// ?rva002553F6_dummy@Rva002553F6@@UAEXXZ present-unmatched
void Rva002553F6::rva002553F6_dummy()
{
}
