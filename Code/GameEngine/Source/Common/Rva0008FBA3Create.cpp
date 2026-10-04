// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva0008FBA3Create@@YGPAVRva000A1346@@PAX@Z @0x0008FBA3 58B: factory creating Rva000A1346.
// Calls rowed operator new 0x0002FDA0 with 0x2F0 then rowed ctor 0x000A1346 with void* arg.
// Evidence: chain lane (calls just-landed 0x000A1346 now resolved); EH prolog with null check;
// ret 4 with 1 void* arg; no callers; neighbours share /O1 /DNDEBUG /MD.

class Rva000A1346
{
public:
	Rva000A1346(void *context);
private:
	char m_pad[0x2F0];
};

void *__cdecl operator new(unsigned int size);

Rva000A1346 *__stdcall Rva0008FBA3Create(void *context)
{
	return new Rva000A1346(context);
}
