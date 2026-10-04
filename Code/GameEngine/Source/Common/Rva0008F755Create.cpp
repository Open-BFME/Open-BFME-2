// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F755Create@@YGPAVRva000A4916@@PAX@Z @0x0008F755 58B: factory creating Rva000A4916.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A4916 with void* arg.
// Evidence: chain lane (calls 0x000A4916 now resolved); same 58B new+ctor shape as siblings 0x0008F6E1 0x0008FB69.

class Rva000A4916
{
public:
	Rva000A4916(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A4916 *__stdcall Rva0008F755Create(void *context)
{
	return new Rva000A4916(context);
}
