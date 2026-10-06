// cl: /O1 /MD /arch:SSE
//
// ??0Rva0039AE30@@QAE@PAVRva0039AE30Arg@@@Z @0x0039AE30 69B: member setup
// plus int lookup, range-17 dump lane.
//
// Zeroes +0x10, stores the arg at +0x4, installs the 0xC1AD60 table by
// immediate, 1.0f at +0x8 and 1 at +0xC, then resolves +0x10 through the
// pinned 0x00288AF2 lookup on the g_00DFECC4 global with (arg+4)+0x9c and
// returns this. /O1 for the and-zero shape; /arch:SSE for the movss 1.0f.

class Rva00288CFA
{
public:
	int rva00288AF2(void *p);
};

extern Rva00288CFA *g_00DFECC4;

class Rva0039AE30Arg
{
public:
	char m_pad00[4]; // +0x00
	void *m_ptr04; // +0x04
};

class Rva0039AE30
{
public:
	Rva0039AE30(Rva0039AE30Arg *a);

private:
	// +0x00 holds the 0xC1AD60 table address by immediate (retail's own
	// linked vtable ref); kept as int so the store stays a single mov.
	int m_table00; // +0x00
	Rva0039AE30Arg *m_arg04; // +0x04
	float m_08; // +0x08
	int m_0c; // +0x0C
	int m_10; // +0x10
};

// ??0Rva0039AE30@@QAE@PAVRva0039AE30Arg@@@Z
Rva0039AE30::Rva0039AE30(Rva0039AE30Arg *a)
{
	m_10 = 0;
	m_arg04 = a;
	m_table00 = 0xC1AD60;
	m_08 = 1.0f;
	m_0c = 1;
	m_10 = g_00DFECC4->rva00288AF2((char *)a->m_ptr04 + 0x9c);
}
