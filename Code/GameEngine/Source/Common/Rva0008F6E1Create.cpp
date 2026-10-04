// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F6E1Create@@YGPAVRva000A0891@@PAX@Z @0x0008F6E1 58B: factory creating Rva000A0891.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A0891 with void* arg.
// Evidence: chain lane (calls 0x000A0891 now resolved); same 58B new+ctor shape as siblings 0x0008FBA3 0x0008FB69.

class Rva000A0891
{
public:
	Rva000A0891(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A0891 *__stdcall Rva0008F6E1Create(void *context)
{
	return new Rva000A0891(context);
}
