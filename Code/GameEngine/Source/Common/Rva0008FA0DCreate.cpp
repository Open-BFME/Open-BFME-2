// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0008FA0DCreate@@YGPAVRva000A26F7@@PAX@Z @0x0008FA0D 58B: factory creating Rva000A26F7.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A26F7 with void* arg.
// Evidence: chain lane calls 0x000A26F7 now resolved; same 58B new+ctor shape as siblings 0x0008F95F 0x0008FAF5.

class Rva000A26F7
{
public:
	Rva000A26F7(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A26F7 *__stdcall Rva0008FA0DCreate(void *context)
{
	return new Rva000A26F7(context);
}
