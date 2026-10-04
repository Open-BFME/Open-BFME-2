// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FB2FCreate@@YGPAVRva000A0D3A@@PAX@Z @0x0008FB2F 58B: factory creating Rva000A0D3A.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A0D3A with void* arg.
// Evidence: chain lane (calls 0x000A0D3A now resolved); same 58B new+ctor shape as siblings 0x0008FBDD 0x0008F877 0x0008F755.

class Rva000A0D3A
{
public:
	Rva000A0D3A(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A0D3A *__stdcall Rva0008FB2FCreate(void *context)
{
	return new Rva000A0D3A(context);
}
