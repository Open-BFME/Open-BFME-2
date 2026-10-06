// cl: /DNDEBUG /MD
//
// ?rva0033E102@@YAXPAXPAVThingTemplate@@@Z @0x0033E102 123B.
//
// Container-record rebuild: when the +0x5e9 flag is set, clear it and erase
// the +0x370 record vector, then construct a record temp (0x0033B0EF),
// fill it from arg1 (0x0033C247), push it (rowed 0x0033E080) and clear the
// +0x37c tree (rowed 0x002CF7DE). Cdecl free function; EH frame over the
// record temp whose string member tears down via the 0x36410 fold.
//
// Evidence: the erase-all reads begin/end through the vec address in ecx
// (the explicit vector pointer local reproduces the lea-first order);
// push_back takes the record by const-ref (the MyRecord-to-record cast is
// layout-only: same 12B {4, string, 4}); the record ctor/fill/erase ride
// TU-local-spelling pins. Member and pad names past the proven offsets
// carry no identity claim. The begin/end inlines emit 3-4B loads identical
// to stlport's own, so they fold at link.
class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}

private:
	void *m_data;
};

struct MyRecord
{
	MyRecord();
	void rva0033C247(void *arg);
	char m_00[4];
	Rva0033B84ETok m_text; // +4, torn down via the 0x36410 fold
	int m_08;
};

struct BfmeContainerRecord002CF46E
{
	char m_00[4];
	char m_text[4];
	int m_08;
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};
	template <class T, class Ax>
	class vector
	{
	public:
		void erase(BfmeContainerRecord002CF46E *a, BfmeContainerRecord002CF46E *b);
		void push_back(const BfmeContainerRecord002CF46E &v);
		T *begin() { return _M_start; }
		T *end() { return _M_finish; }

		T *_M_start;
		T *_M_finish;
		T *_M_end;
	};
}

class Rva002CF7DE
{
public:
	void rva002CF7DE();

private:
	void *m_header;
	int m_size;
};

class ThingTemplate
{
public:
	char m_pad00[0x370];
	_STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> > m_vec370;
	Rva002CF7DE m_tree37c;
	char m_pad384[0x5e9 - 0x384];
	unsigned char m_flag5e9; // +0x5e9
};

void rva0033E102(void *arg1, ThingTemplate *t)
{
	if (t->m_flag5e9 == 1) {
		_STL::vector<BfmeContainerRecord002CF46E, _STL::allocator<BfmeContainerRecord002CF46E> > *v = &t->m_vec370;
		t->m_flag5e9 = 0;
		v->erase(v->begin(), v->end());
	}

	MyRecord rec;
	rec.rva0033C247(arg1);
	t->m_vec370.push_back((const BfmeContainerRecord002CF46E &)rec);
	t->m_tree37c.rva002CF7DE();
}
