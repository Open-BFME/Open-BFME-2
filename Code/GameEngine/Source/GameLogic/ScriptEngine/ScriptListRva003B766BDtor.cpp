// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva003B766B@@QAE@XZ @0x003B766B 77B
// Destructor of the 0x0C-byte-header object with a pointer at +0 freed last:
// destroys the range at +0xC (rowed destroyRva003B713ERange 0x003B713E), then
// the vector at +0xC (rowed ~vector 0x003B7057), then frees the pointer at +0
// through the base destructor (pinned Rva00030830FreeAllocation 0x00030830).
#include <vector>

struct Rva003B7057Record { Rva003B7057Record(); Rva003B7057Record(const Rva003B7057Record &); ~Rva003B7057Record(); Rva003B7057Record &operator=(const Rva003B7057Record &); char bytes[1]; };

struct Rva003B713ERange
{
	void *m_start;
	void *m_finish;
};

void destroyRva003B713ERange(Rva003B713ERange *range);
void Rva00030830FreeAllocation(void *block);

class Rva003B766BBase
{
public:
	~Rva003B766BBase()
	{
		if (m_ptr)
			Rva00030830FreeAllocation(m_ptr);
	}
	void *m_ptr;
	char m_pad04[8];
};

class Rva003B766B : public Rva003B766BBase
{
public:
	~Rva003B766B();
private:
	_STL::vector<Rva003B7057Record> m_vec;
};

Rva003B766B::~Rva003B766B()
{
	destroyRva003B713ERange(reinterpret_cast<Rva003B713ERange *>(&m_vec));
}
