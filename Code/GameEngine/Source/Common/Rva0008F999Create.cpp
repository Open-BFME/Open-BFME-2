// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F999Create@@YGPAVRva000A2670@@PAX@Z @0x0008F999 58B: factory creating Rva000A2670.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A2670 with void* arg.
// Evidence: chain lane calls 0x000A2670 now resolved; same 58B new+ctor shape as siblings 0x0008F9D3 0x0008FA0D.

class Rva000A2670
{
public:
	Rva000A2670(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A2670 *__stdcall Rva0008F999Create(void *context)
{
	return new Rva000A2670(context);
}
