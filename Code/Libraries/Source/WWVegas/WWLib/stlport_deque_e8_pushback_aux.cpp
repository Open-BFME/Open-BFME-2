// cl: /DNDEBUG /MD /EHsc /Oy-

// Dedicated TU for deque<BfmeE8> auxiliary push-back path. The element's
// second half copies through xmm0 (retail `movss xmm0,[eax+4]`), so BfmeE8
// is {int, float} here -- invisible to the pointer-arithmetic siblings that
// already landed under {int, int} in stlport_deque_e8_o1.cpp -- and the
// frame is ebp (/Oy-), with the reserve call unconditional (STLport
// _M_reserve_map_at_back default 1).
// At the retail call site alignment is zero; the pinned byte allocator accepts
// the same two-word cdecl ABI with a null hint.
#pragma comment(linker, "/alternatename:?vectorSmallAllocate@_STL@@YAPAXII@Z=?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")

struct BfmeE8
{
	int a;
	float b;
};

namespace _STL
{
void *vectorSmallAllocate(unsigned int bytes, unsigned int alignment);

template <class Destination, class Source>
void _Construct(Destination *, const Source &);

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
	void _M_reserve_map_at_back(unsigned int nodesToAdd = 1);

	DequeIterator<Type> start;
	DequeIterator<Type> finish;
	Type **map;
	unsigned int mapSize;
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_back_aux_v(const Type &value)
{
	Type copy;
	copy.a = value.a;
	copy.b = value.b;
	_M_reserve_map_at_back();
	*(finish.node + 1) = (Type *)vectorSmallAllocate(0x80, 0);
	_Construct(finish.current, copy);
	setDequeNode(finish, finish.node + 1);
	finish.current = finish.first;
}

template void deque<BfmeE8, allocator<BfmeE8> >::_M_push_back_aux_v(
	const BfmeE8 &);
}
