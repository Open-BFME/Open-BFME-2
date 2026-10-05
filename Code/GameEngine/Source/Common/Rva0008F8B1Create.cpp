// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F8B1Create@@YGPAVRva000A3307@@PAX@Z @0x0008F8B1 58B: factory creating Rva000A3307.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A3307 with void* arg.
// Evidence: neighbors same 58B new+ctor shape; callees rowed; prev 0x0008F877 next 0x0008F925 same flags.

class Rva000A3307
{
public:
	Rva000A3307(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A3307 *__stdcall Rva0008F8B1Create(void *context)
{
	return new Rva000A3307(context);
}
