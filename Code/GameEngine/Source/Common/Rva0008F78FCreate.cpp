// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F78FCreate@@YGPAVRva000A4969@@PAX@Z @0x0008F78F 58B: factory creating Rva000A4969.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A4969 with void* arg.
// Evidence: chain lane (calls 0x000A4969 now resolved); same 58B new+ctor shape as siblings 0x0008FAF5 0x0008F83D 0x0008F755.

class Rva000A4969
{
public:
	Rva000A4969(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A4969 *__stdcall Rva0008F78FCreate(void *context)
{
	return new Rva000A4969(context);
}
