// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FA47Create@@YGPAVRva000A270F@@PAX@Z @0x0008FA47 58B: factory creating Rva000A270F.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A270F with void* arg.
// Evidence: chain lane calls 0x000A270F now resolved; same 58B new+ctor shape as siblings 0x0008FA0D 0x0008FAF5.

class Rva000A270F
{
public:
	Rva000A270F(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A270F *__stdcall Rva0008FA47Create(void *context)
{
	return new Rva000A270F(context);
}
