// cl: /DNDEBUG /MD /EHsc
// AutoPoolClass::operator new from BFME1 a7c38d3b2597121f178ab5190b3062478823257d
// game/Libraries/Source/WWVegas/WWLib/mempool.h and the Zero Hour GeneralsMD
// WWVegas/WW3D2/dx8renderer.cpp DEFINE_AUTO_POOL declarations.
// Existing operator-delete bodies at 0x001449B0/0x001449E0 identify the
// task types and their separate static Allocator globals. Both task layouts
// are independently 12 bytes. Allocation delegates to the complete verified
// ObjectPoolClass body at 0x001440C0; no element access occurs in this wrapper.
class PolyRenderTaskClass;

template<class T, int BLOCK_SIZE> class ObjectPoolClass {
public:
    T *Allocate_Object_Memory();
};
template<class T, int BLOCK_SIZE> class AutoPoolClass {
public:
    static void *operator new(unsigned int size);
private:
    static ObjectPoolClass<T, BLOCK_SIZE> Allocator;
};
template<class T, int BLOCK_SIZE>
void *AutoPoolClass<T, BLOCK_SIZE>::operator new(unsigned int size) {
    return Allocator.Allocate_Object_Memory();
}
template void *AutoPoolClass<PolyRenderTaskClass,256>::operator new(unsigned int);
