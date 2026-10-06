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
private:
	OpaqueRefCounted *m_ptr;
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
