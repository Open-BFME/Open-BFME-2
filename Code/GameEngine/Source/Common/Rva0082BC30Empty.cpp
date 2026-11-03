// cl: /Od
void rva0082BC40Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

class Rva0082BFD0Slot
{
public:
	Rva0082BFD0Slot *assignFrom(const int *src);

private:
	int m_value;
};

Rva0082BFD0Slot *Rva0082BFD0Slot::assignFrom(const int *src)
{
	int tmp = *src;
	m_value = tmp;
	return this;
}

int setMallocHandler(int value);

// The slot is STLport's __malloc_alloc<0>::__oom_handler, defined in
// Code/Libraries/Source/WWVegas/WWLib/STLMallocAlloc0OutOfMemory.cpp (the
// ledger owner of 0x009DF4CC); this setter has STLport's
// __set_malloc_handler shape.
namespace _STL
{
typedef void (__cdecl *__oom_handler_type)();

template <int Instance>
class __malloc_alloc
{
private:
	static __oom_handler_type __oom_handler;
	friend int ::setMallocHandler(int value);
};
}

int setMallocHandler(int value)
{
	int old = (int)_STL::__malloc_alloc<0>::__oom_handler;
	_STL::__malloc_alloc<0>::__oom_handler = (_STL::__oom_handler_type)value;
	return old;
}

int *rva0082BBC0Find(int *node, int value)
{
	while (node != 0 && *node != value)
		node = (int *)*node;
	return node;
}

int rva0082BAF0Count(int *node)
{
	int count = 0;
	for (; node != 0; node = (int *)*node)
		count++;
	return count;
}

