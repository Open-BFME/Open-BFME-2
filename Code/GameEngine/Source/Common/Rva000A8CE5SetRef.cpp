// cl: /MD /EHsc /DNDEBUG /O1 /arch:SSE /G7
// ?rva000A8CE5@Rva000A8C9B@@QAEXPAVOpaqueRefCounted@@@Z, retail 0x000A8CE5, 38 bytes.
// Class relationship inferred from the direct call to Rva000A8C9B::clear on this and the shared pointer-at-zero layout. Target evidence establishes the value pointer, its reference count at +4, and the InterlockedIncrement IAT call.

class OpaqueRefCounted
{
public:
	void Release_Ref();
	void *vtable;
	long volatile references;
};

class Rva000A8C9B
{
public:
	void clear();
	void rva000A8CE5(OpaqueRefCounted *value);
	void rva000A8D0B(int a, int b, int c);
private:
	OpaqueRefCounted *m_ptr;
};

// The 0x28-byte object 0x000A8D0B allocates; constructor and member names
// follow the banked 0x0010F058 / 0x0010F962 attempts (address-derived).
class Rva0010F058
{
public:
	Rva0010F058(int a);
private:
	char unknown00[0x28];
};

class Rva0010F962
{
public:
	void rva0010F962(int a, int b);
};

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);

void Rva000A8C9B::rva000A8CE5(OpaqueRefCounted *value)
{
	if (value != m_ptr)
	{
		clear();
		m_ptr = value;
		if (value)
			InterlockedIncrement(&value->references);
	}
}

// ?rva000A8D0B@Rva000A8C9B@@QAEXHHH@Z, retail 0x000A8D0B, 84 bytes (ret 0xC):
// rebinds this reference to a fresh 0x28-byte object built from the first
// argument (operator new 0x2FDA0, constructor 0x10F058 under the EH frame),
// then forwards the other two arguments to the pointee's 0x10F962.
void Rva000A8C9B::rva000A8D0B(int a, int b, int c)
{
	rva000A8CE5(reinterpret_cast<OpaqueRefCounted *>(new Rva0010F058(a)));
	reinterpret_cast<Rva0010F962 *>(m_ptr)->rva0010F962(b, c);
}
