// cl: /O1 /EHs /MD /D_CRTIMP=
//
// Opaque dtor 0x0059EA42 (97 B), called by the rowed scalar deleting dtor
// 0x0059EAA3 (vtable 0x00C71138#0). Deletes the owned record at +0x04 (an
// AsciiString set at record+0x08, rowed tree dtor 0x000589BE), then the
// inline buffer member at +0x14 frees its block through the CRT, then the
// AsciiString vector member at +0x08 runs the rowed dtor 0x0002CC70.
class AsciiString;

namespace _STL
{
template <class T> class allocator {};
template <class T> struct _Identity {};
template <class T> struct less {};
template <class T, class A> class vector
{
public:
	~vector();
	void *m_start;
	void *m_finish;
	void *m_end;
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	~_Rb_tree();
	void *m_header;
	int m_count;
	int m_compare;
};
}

extern "C" void __cdecl free(void *);

struct Rva0059EA42Record
{
	int m_0;
	int m_4;
	_STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set;
};

struct Rva0059EA42Buffer
{
	void *m_block;
	~Rva0059EA42Buffer()
	{
		if (m_block)
			free(m_block);
	}
};

class Rva0059EA42
{
public:
	virtual ~Rva0059EA42();

	Rva0059EA42Record *m_record; // +0x04
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_names; // +0x08
	Rva0059EA42Buffer m_buffer; // +0x14
};

Rva0059EA42::~Rva0059EA42()
{
	if (m_record)
		delete m_record;
}
