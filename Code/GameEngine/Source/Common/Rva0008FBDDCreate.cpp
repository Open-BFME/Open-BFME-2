// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FBDDCreate@@YGPAVRva000A15FE@@PAX@Z @0x0008FBDD 58B: factory creating Rva000A15FE.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A15FE with void* arg.
// Evidence: chain lane (calls 0x000A15FE now resolved); same 58B new+ctor shape as siblings 0x0008F877 0x0008F755 0x0008FBA3.

class Rva000A15FE
{
public:
	Rva000A15FE(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A15FE *__stdcall Rva0008FBDDCreate(void *context)
{
	return new Rva000A15FE(context);
}
