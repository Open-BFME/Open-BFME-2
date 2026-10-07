// ??1Rva00557CCC@@QAE@XZ
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00557CCC@@QAE@XZ @0x00557CCC 204B
// The address-derived class identity comes from its vtable/deleting-destructor
// anchor. Member order and offsets below follow the retail cleanup calls;
// unnamed storage and owned-pointer meanings remain structural inferences.
#include <deque>

namespace _STL { }

struct MutexClass { unsigned int unknown[2]; ~MutexClass(); };
struct Rva00553222 { virtual void virtualSlot(); void rva00553222(); ~Rva00553222() {} };
struct Rva005562DD { unsigned int unknown[3]; ~Rva005562DD(); };
struct Rva0009990D { unsigned int unknown[3]; void clear(); ~Rva0009990D() { clear(); } };

struct BfmeOpaqueOwnedRecord1408 {
	unsigned int head[2];
	unsigned char bytes[1400];
	BfmeOpaqueOwnedRecord1408();
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &);
};
struct BfmeOpaqueOwnedRecord1432 {
	unsigned int words[358];
	unsigned int tail;
	BfmeOpaqueOwnedRecord1432();
	BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &);
};

extern "C" void free(void *);

typedef _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> > BfmeDeque1408;
typedef _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> > BfmeDeque1432;

struct BfmeOpaqueOwnedPointer {
	void *value;
	unsigned int unknown[2];
	~BfmeOpaqueOwnedPointer() { if (value) free(value); }
};

class Rva00557CCC : public Rva00553222 {
public:
	~Rva00557CCC();
private:
	MutexClass m_mutex0;
	MutexClass m_mutex1;
	BfmeDeque1432 m_deque1432;
	BfmeDeque1408 m_deque1408;
	unsigned int m_gap64[2];
	BfmeOpaqueOwnedPointer m_owned6c;
	BfmeOpaqueOwnedPointer m_owned78;
	BfmeOpaqueOwnedPointer m_owned84;
	Rva005562DD m_member90;
	MutexClass m_mutex9c;
	Rva0009990D m_clearA4;
};

Rva00557CCC::~Rva00557CCC()
{
	Rva00553222::rva00553222();
}
