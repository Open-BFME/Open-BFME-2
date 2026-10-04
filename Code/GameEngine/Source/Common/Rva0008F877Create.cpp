// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F877Create@@YGPAVRva000A43A4@@PAX@Z @0x0008F877 58B: factory creating Rva000A43A4.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A43A4 with void* arg.
// Evidence: chain lane (calls 0x000A43A4 now resolved); same 58B new+ctor shape as siblings 0x0008F755 0x0008F6E1 0x0008FB69.

class Rva000A43A4
{
public:
	Rva000A43A4(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A43A4 *__stdcall Rva0008F877Create(void *context)
{
	return new Rva000A43A4(context);
}
