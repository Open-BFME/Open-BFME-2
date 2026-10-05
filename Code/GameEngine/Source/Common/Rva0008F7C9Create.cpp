// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F7C9Create@@YGPAVRva000A3DE3@@PAX@Z @0x0008F7C9 58B: factory creating Rva000A3DE3.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A3DE3 with void* arg.
// Evidence: neighbors of 0x0008F95F same 58B new+ctor shape; callees rowed; prev 0x0008F78F next 0x0008F83D same flags.

class Rva000A3DE3
{
public:
	Rva000A3DE3(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A3DE3 *__stdcall Rva0008F7C9Create(void *context)
{
	return new Rva000A3DE3(context);
}
