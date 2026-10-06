// cl: /O2 /MD
//
// 0x00AD9D70, qsort comparator for the Apt array sort natives. The rowed
// caller ?rva006D9F00 at 0x006D9F00 passes this address to qsort for mode 0;
// its extern "C" spelling is rva006D9D70Comparator. Each qsort element is a
// BfmeAptValue006DCD20*, so the comparator dereferences its void* arguments
// to the two values, fills one EAStringC key from each through the pinned
// 0x006DD6C0 key builder, and returns strcmp of the two null-terminated keys.
// EAStringC::clear 0x006D2F90 (default-construct), rva00620090 0x00620090
// (data+8) and ~EAStringC 0x006D3010 are the rowed string helpers.

class BfmeAptValue006DCD20;

class EAStringC
{
	void *m_pData;

public:
	EAStringC();
	EAStringC &clear();
	const char *rva00620090() const;
	~EAStringC();
};

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	void rva006DD6C0(EAStringC *pBuffer);
};

extern "C" int __cdecl strcmp(const char *left, const char *right);
#pragma intrinsic(strcmp)

// _rva006D9D70Comparator
extern "C" int __cdecl rva006D9D70Comparator(const void *a, const void *b)
{
	BfmeAptValue006DCD20 *left = *(BfmeAptValue006DCD20 **)a;
	BfmeAptValue006DCD20 *right = *(BfmeAptValue006DCD20 **)b;

	EAStringC leftKey;
	EAStringC rightKey;
	left->rva006DD6C0(&leftKey);
	right->rva006DD6C0(&rightKey);

	return strcmp(leftKey.rva00620090(), rightKey.rva00620090());
}
