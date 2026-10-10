// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0010F873@AsyncServiceQueue@@QAE?AU?$_List_iterator@URva0073EEE0ListValue@@U?$_Nonconst_traits@URva0073EEE0ListValue@@@_STL@@@_STL@@VAudioEventInfoRef@@@Z
// @0x0010F873 93B
//
// RET 8 (hidden iterator return plus one by-value reference). Copies the
// incoming reference into the argument of the rowed factory at 0x0010F760
// (copy ctor 0x000A8C7C) whose result is built straight into the argument
// slot of the rowed AsyncServiceQueue::enqueue (0x0073F37F) on the same this;
// enqueue's list iterator is returned and the by-value reference is dropped
// afterwards (inlined Release_Ref 0x00050ED3; one EH state). Caller: the
// banked submission helper 0x0010F8D0 builds the reference with the rowed
// AudioEventInfoRef ctor 0x00051914. AudioEventInfoRef and Rva0036CA00Str
// are two address-derived views of one refcounted handle; the factory is
// called through a placeholder spelling whose return type agrees with
// enqueue's parameter so the result is constructed in place as in retail.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0036CA00Str
{
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str()
	{
		if (m_item)
			((OpaqueRefCounted *)m_item)->Release_Ref();
	}

	void *m_item;
};

class AudioEventInfoRef : public Rva0036CA00Str
{
};

struct Rva0073EEE0ListValue;

namespace _STL
{
template <class _Tp> struct _Nonconst_traits;
template <class _Tp, class _Traits> struct _List_iterator
{
	void *_M_node;
	_List_iterator();
};
}

typedef _STL::_List_iterator<Rva0073EEE0ListValue,
	_STL::_Nonconst_traits<Rva0073EEE0ListValue> > Rva0073EEE0ListIterator;

Rva0036CA00Str Rva0010F760(Rva0036CA00Str handle);

class AsyncServiceQueue
{
public:
	Rva0073EEE0ListIterator enqueue(Rva0036CA00Str item);
	Rva0073EEE0ListIterator rva0010F873(AudioEventInfoRef ref);
};

Rva0073EEE0ListIterator AsyncServiceQueue::rva0010F873(AudioEventInfoRef ref)
{
	return enqueue(Rva0010F760(ref));
}
