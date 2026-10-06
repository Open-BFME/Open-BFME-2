// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva000E01A3@Rva000E01A3@@QAE_NXZ @0x000E01A3 13B
// Leaf thiscall returning whether the pointee's first dword equals the pointer itself.
// Evidence: retail mov eax [ecx+4] / xor ecx ecx / cmp [eax] eax / sete cl / mov al cl / ret;
// caller 0x003776CC in big FUN_00777613.
class Rva000E01A3
{
public:
	bool rva000E01A3();
private:
	char m_lead[4];
	void *m_ptr;
};

bool Rva000E01A3::rva000E01A3()
{
	void *p = m_ptr;
	return *(void **)p == p;
}
