// cl: /DNDEBUG /MD /EHsc

// The exact push_back caller at 0x008FBC70 proves this is its 8-byte payload's
// auxiliary path.  A distinct address-scoped payload avoids colliding with the
// generator's non-POD approximation of the same caller.
struct Gen_t_008fb570_p8pod
{
	int value[2];
};

// The node allocation calls STLport's static allocator<char>::allocate(bytes,
// hint), rowed at 0x000307F0 (GameMemory.cpp). Bind its real name: the former
// private _STL::vectorSmallAllocate spelling resolved only through a link-wide
// alternatename that d96297b68e retired.
extern "C" char *__cdecl __identifier("?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")(unsigned int bytes, const void *hint);

namespace _STL
{

template <class Destination, class Source>
void _Construct(Destination *, const Source &);

// Link: nothing defines _Construct<Gen_t_008fb570_p8pod>. Retail's 0x0060C9D9
// is the rowed two-word copy _Construct<pair<const int, int> >
// (Rva002EF239CreateNode.cpp); an inline forwarder reaches it with the same
// pushes.
template <class First, class Second>
struct pair;
template <> void _Construct<pair<const int, int>, pair<const int, int> >(
	pair<const int, int> *, const pair<const int, int> &);
template <> __declspec(dllimport) __forceinline void _Construct<Gen_t_008fb570_p8pod, Gen_t_008fb570_p8pod>(
	Gen_t_008fb570_p8pod *destination, const Gen_t_008fb570_p8pod &source)
{
	_Construct((pair<const int, int> *)destination, *(const pair<const int, int> *)&source);
}

template <class Type>
class allocator
{
};

template <class Type>
struct DequeIterator
{
	Type *current;
	Type *first;
	Type *last;
	Type **node;
};

template <class Type>
static __forceinline void setDequeNode(DequeIterator<Type> &iterator, Type **newNode)
{
	iterator.node = newNode;
	iterator.first = *newNode;
	iterator.last = iterator.first + 16;
}

template <class Type, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(const Type &value);
	void _M_reallocate_map(unsigned int nodesToAdd, bool addAtFront);

	DequeIterator<Type> start;
	DequeIterator<Type> finish;
	Type **map;
	unsigned int mapSize;
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(const Type &value)
{
	Type copy = value;
	if (2 > mapSize - (unsigned int)(finish.node - map))
		_M_reallocate_map(1, false);

	*(finish.node + 1) = (Type *)__identifier("?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")(0x80, 0);
	_Construct(finish.current, copy);
	setDequeNode(finish, finish.node + 1);
	finish.current = finish.first;
}

template void deque<Gen_t_008fb570_p8pod, allocator<Gen_t_008fb570_p8pod> >::_M_push_back_aux_v(
	const Gen_t_008fb570_p8pod &);
}

// The retail call in this body reads 0x0073D5E0, an address the ledger already
// carries as ?_M_reallocate_map@?$deque@HV?$allocator@H@_STL@@@_STL@@IAEXI_N@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?_M_reallocate_map@?$deque@UGen_t_008fb570_p8pod@@V?$allocator@UGen_t_008fb570_p8pod@@@_STL@@@_STL@@IAEXI_N@Z=?_M_reallocate_map@?$deque@HV?$allocator@H@_STL@@@_STL@@IAEXI_N@Z")
