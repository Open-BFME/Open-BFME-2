// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F9D3Create@@YGPAVRva000A26C7@@PAX@Z @0x0008F9D3 58B: factory creating Rva000A26C7.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A26C7 with void* arg.
// Evidence: chain lane calls 0x000A26C7 now resolved; same 58B new+ctor shape as siblings 0x0008FA0D 0x0008FA47.

class Rva000A26C7
{
public:
	Rva000A26C7(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A26C7 *__stdcall Rva0008F9D3Create(void *context)
{
	return new Rva000A26C7(context);
}
