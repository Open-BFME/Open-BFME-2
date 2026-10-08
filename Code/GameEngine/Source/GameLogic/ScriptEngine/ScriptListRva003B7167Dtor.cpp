// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva003B7167@@QAE@XZ @0x003B7167 41B
// Destructor of the 0x0C-byte-header object with a pointer at +0 freed last:
// destroys the range at +0xC (rowed destroyRva003B678ARange 0x003B678A), then
// the vector at +0xC (rowed ~vector 0x003B7057), then frees the pointer at +0
// through the base destructor (pinned Rva00030830FreeAllocation 0x00030830).
#include <vector>

struct Rva003B7057Record { Rva003B7057Record(); Rva003B7057Record(const Rva003B7057Record &); ~Rva003B7057Record(); Rva003B7057Record &operator=(const Rva003B7057Record &); char bytes[1]; };

struct Rva003B678ARange
{
	void *m_start;
	void *m_finish;
};

void destroyRva003B678ARange(Rva003B678ARange *range);
void Rva00030830FreeAllocation(void *block);

class Rva003B7167Base
{
public:
	~Rva003B7167Base()
	{
		if (m_ptr)
			Rva00030830FreeAllocation(m_ptr);
	}
	void *m_ptr;
	char m_pad04[8];
};

class Rva003B7167 : public Rva003B7167Base
{
public:
	~Rva003B7167();
private:
	_STL::vector<Rva003B7057Record> m_vec;
};

Rva003B7167::~Rva003B7167()
{
	destroyRva003B678ARange(reinterpret_cast<Rva003B678ARange *>(&m_vec));
}
