// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FAF5Create@@YGPAVRva000A0CE7@@PAX@Z @0x0008FAF5 58B: factory creating Rva000A0CE7.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A0CE7 with void* arg.
// Evidence: chain lane (calls 0x000A0CE7 now resolved); same 58B new+ctor shape as siblings 0x0008F83D 0x0008F71B 0x0008F877.

class Rva000A0CE7
{
public:
	Rva000A0CE7(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A0CE7 *__stdcall Rva0008FAF5Create(void *context)
{
	return new Rva000A0CE7(context);
}
