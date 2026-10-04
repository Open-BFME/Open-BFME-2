// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FC17Create@@YGPAVRva000A1646@@PAX@Z @0x0008FC17 58B: factory creating Rva000A1646.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A1646 with void* arg.
// Evidence: chain lane (calls 0x000A1646 now resolved); same 58B new+ctor shape as siblings 0x0008FB2F 0x0008FBDD 0x0008F877.

class Rva000A1646
{
public:
	Rva000A1646(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A1646 *__stdcall Rva0008FC17Create(void *context)
{
	return new Rva000A1646(context);
}
