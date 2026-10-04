// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F71BCreate@@YGPAVRva000A08D9@@PAX@Z @0x0008F71B 58B: factory creating Rva000A08D9.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A08D9 with void* arg.
// Evidence: chain lane (calls 0x000A08D9 now resolved); same 58B new+ctor shape as siblings 0x0008FC17 0x0008FB2F 0x0008F755.

class Rva000A08D9
{
public:
	Rva000A08D9(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A08D9 *__stdcall Rva0008F71BCreate(void *context)
{
	return new Rva000A08D9(context);
}
