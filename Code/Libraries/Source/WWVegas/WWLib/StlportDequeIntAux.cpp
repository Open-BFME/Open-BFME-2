// cl: /DNDEBUG /MD /EHsc

// deque<int> auxiliary push paths.  Retail builds every deque on 128-byte
// nodes (32 ints; see QueueDefaultCtorAnchors.cpp), calls _M_reallocate_map
// directly instead of going through _M_reserve_map_at_front/back, and guards
// the value store against a null edge iterator, so the stock STLport 4.5.3
// bodies in stlport_deque_int.cpp never appear in the binary.  This TU reuses
// the minimal-deque pattern from Rva008FB570DequePushBackAux.cpp with a
// four-byte element: node last = first + 32, value copied to a register,
// direct reallocate call, node from vectorSmallAllocate(0x80, 0).
namespace _STL
{
void *vectorSmallAllocate(unsigned int bytes, unsigned int alignment);

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
	iterator.last = iterator.first + 32;
}

template <class Type, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(const Type &value);
	void _M_push_front_aux_v(const Type &value);
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

	*(finish.node + 1) = (Type *)vectorSmallAllocate(0x80, 0);
	if (finish.current != 0)
		*finish.current = copy;
	setDequeNode(finish, finish.node + 1);
	finish.current = finish.first;
}

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_push_front_aux_v(const Type &value)
{
	Type copy = value;
	if (1 > (unsigned int)(start.node - map))
		_M_reallocate_map(1, true);

	*(start.node - 1) = (Type *)vectorSmallAllocate(0x80, 0);
	setDequeNode(start, start.node - 1);
	start.current = start.last - 1;
	if (start.current != 0)
		*start.current = copy;
}

template void deque<int, allocator<int> >::_M_push_back_aux_v(const int &);
template void deque<int, allocator<int> >::_M_push_front_aux_v(const int &);
}
