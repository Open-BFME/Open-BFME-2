// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0008F925Create@@YGPAVRva0009FD78@@PAX@Z @0x0008F925 58B: factory creating Rva0009FD78.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x0009FD60 with void* arg.
// Evidence: chain lane calls 0x0009FD60 now resolved; same 58B new+ctor shape as siblings 0x0008F877 0x0008F95F.

class Rva0009FD78
{
public:
	Rva0009FD78(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva0009FD78 *__stdcall Rva0008F925Create(void *context)
{
	return new Rva0009FD78(context);
}
