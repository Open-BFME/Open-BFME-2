// cl: /MD /EHsc /DNDEBUG
// ?Rva00056EB1Free@@YGXPAX@Z, retail 0x00056EB1 (28B).
// Single-node deleter for the bucket-vector table cleared at 0x00057FC1.
// Destroys the Rva000543F5Record at +4 via the rowed ??1Rva000543F5Record
// dtor then frees the node via rowed _free. Caller at 0x00057FE2 walks
// buckets (begin+4/end+8) and passes each head; next at +0 read off that
// caller. Stdcall per ret-4 with caller doing no cleanup.

struct Rva000543F5Record
{
	~Rva000543F5Record();
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva00056EB1Free(void *ptr)
{
	((Rva000543F5Record *)((char *)ptr + 4))->~Rva000543F5Record();
	if (ptr != 0)
		free(ptr);
}
