// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva000427195@@QAE@XZ @0x001FDEDB 57B.
// Hash-table destructor for the AsciiString-keyed bucket table: clears via
// the rowed rva003A2A41, then the inline bucket-handle member dtor frees the
// bucket array at +4 via free 0x00030830 with a null guard. Same EH
// clear-plus-free shape as the rowed tree dtors ??1Rva001FD42B@@QAE@XZ
// 0x001FD6BC (Rva001FD42BDtor.cpp precedent: C++-linkage free emits
// retail's unwind state store; /EHsc for the stores). Header at +4 costs
// one disp8 byte over the tree dtors. Callers at 0x001FE26E 0x002B1390
// 0x002B139F and jmp at 0x001FE065; unblocks 0x002B11A7.
// C++-linkage free (?free@@YAXPAX@Z, pinned at 0x00030830): the C++
// decoration is what makes the caller emit the unwind state store retail
// carries; same body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva000427195BucketHandle
{
	~Rva000427195BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

struct Rva000427195
{
	Rva000427195 &operator=(const Rva000427195 &other);
	void rva003A2A41();
	~Rva000427195();
	void *m_unused00;
	Rva000427195BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva000427195::~Rva000427195()
{
	rva003A2A41();
}

// Pinned unrowed copy worker at 0x001FDC0F (Ghidra FUN_005fdc0f, 192B):
// thiscall taking one pointer (proven by the push-arg plus ecx call site
// below). Identity beyond the address is unrecovered, so the honest
// address-derived class keeps the pin target stable.
class Rva001FDC0F
{
public:
	void rva001FDC0F(void *other);
};

// ??4Rva000427195@@QAEAAV0@ABV0@Z present-unmatched
Rva000427195 &Rva000427195::operator=(const Rva000427195 &other)
{
	if (&other != this) {
		rva003A2A41();
		reinterpret_cast<Rva001FDC0F *>(this)->rva001FDC0F(const_cast<Rva000427195 *>(&other));
	}
	return *this;
}
