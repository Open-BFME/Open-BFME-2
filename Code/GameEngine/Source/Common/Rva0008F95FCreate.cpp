// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F95FCreate@@YGPAVRva0009FDBD@@PAX@Z @0x0008F95F 58B: factory creating Rva0009FDBD.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x0009FDBD with void* arg.
// Evidence: chain lane calls 0x0009FDBD now resolved; same 58B new+ctor shape as siblings 0x0008F877 0x0008FAF5.

class Rva0009FDBD
{
public:
	Rva0009FDBD(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva0009FDBD *__stdcall Rva0008F95FCreate(void *context)
{
	return new Rva0009FDBD(context);
}
