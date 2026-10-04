// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FB69Create@@YGPAVRva000A12FE@@PAX@Z @0x0008FB69 58B: factory creating Rva000A12FE.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A12FE with void* arg.
// Evidence: chain lane (calls 0x000A12FE now resolved); same 58B new+ctor shape as sibling 0x0008FBA3.

class Rva000A12FE
{
public:
	Rva000A12FE(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A12FE *__stdcall Rva0008FB69Create(void *context)
{
	return new Rva000A12FE(context);
}
