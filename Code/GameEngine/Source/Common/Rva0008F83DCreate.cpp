// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008F83DCreate@@YGPAVRva000A435C@@PAX@Z @0x0008F83D 58B: factory creating Rva000A435C.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A435C with void* arg.
// Evidence: chain lane (calls 0x000A435C now resolved); same 58B new+ctor shape as siblings 0x0008F71B 0x0008FC17 0x0008F755.

class Rva000A435C
{
public:
	Rva000A435C(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A435C *__stdcall Rva0008F83DCreate(void *context)
{
	return new Rva000A435C(context);
}
