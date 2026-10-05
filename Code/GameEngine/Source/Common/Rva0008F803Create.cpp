// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F803Create@@YGPAVRva000A3E2B@@PAX@Z @0x0008F803 58B: factory creating Rva000A3E2B.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A3E2B with void* arg.
// Evidence: neighbors same 58B new+ctor shape; callees rowed; prev 0x0008F7C9 next 0x0008F83D same flags.

class Rva000A3E2B
{
public:
	Rva000A3E2B(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A3E2B *__stdcall Rva0008F803Create(void *context)
{
	return new Rva000A3E2B(context);
}
