// cl: /O1 /MD /DNDEBUG
// Native1EB984..1EB9AC complete40B pool-backed Object-pointer list header.
// Existing Rva001EB984Init.cpp establishes the one-word sentinel and the
// unused allocator argument; this is its typed STLport constructor spelling.
// The strong exact copy supplies callers built with different frame flags.
class Object;
// Native DB8FEC freelist policy is distinct from the generic 41B allocator.
template<class T>class Rva001EB984PoolAllocator {};
class FreelistProxyHead {public:void setup(const void*,void*);};
class FreelistPool {public:void*pop();};
extern FreelistPool g_freelistPool00DB8FEC;
namespace _STL {
template<class T>class allocator;
template<class T,class A>class _List_base;
template<>class _List_base<Object*,Rva001EB984PoolAllocator<Object*> > {
public:_List_base(const Rva001EB984PoolAllocator<Object*>&);
private:void*head;
};
_List_base<Object*,Rva001EB984PoolAllocator<Object*> >::_List_base(const Rva001EB984PoolAllocator<Object*>&a)
{
 char dummy;
 ((FreelistProxyHead*)this)->setup(&dummy,0);
 void*n=g_freelistPool00DB8FEC.pop();
 ((void**)n)[0]=n;((void**)n)[1]=n;head=n;
}
}
