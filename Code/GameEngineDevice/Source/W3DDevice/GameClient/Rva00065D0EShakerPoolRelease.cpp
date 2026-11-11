// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// AutoPoolClass<CameraShakeSystemClass::CameraShakerClass,256>'s operator new
// (65D04..65D0E, 10B) and operator delete (65D0E..65D24, 22B), from the
// WWLib mempool.h template (Zero Hour GeneralsMD WWVegas/WWLib/mempool.h
// AutoPoolClass::operator new/delete) instantiated by camerashakesystem.cpp's
// DEFINE_AUTO_POOL(CameraShakeSystemClass::CameraShakerClass,256).
// Identity: retail's own unwind funclet of Add_Camera_Shake (0x0075E697, the
// new-expression cleanup the compiler binds to the class's operator delete)
// calls 65D0E, and the deleting destructor 65D24 of CameraShakerClass calls it
// too; 65D04 directly precedes it, loads the same Allocator (VA DE1E98) and
// tail-jumps to the pool's allocate 658DB, as the rowed operator new/delete
// pairs of the MultiListNode, GridLink and HAnimComboData pools do.
// The pool's allocate and free are the rowed BFME bodies 658DB and 65964.
class CameraShakeSystemClass { public: class CameraShakerClass; };
#include "../../../../GameEngine/Include/GameLogic/Rva00065964ObjectPool.h"
template<class T, int BLOCK_SIZE> class ObjectPoolClass {
public:
    __forceinline T *Allocate_Object_Memory()
    { return (T *)((Rva00065964ObjectPool *)this)->rva000658DB(); }
    __forceinline void Free_Object_Memory(T *obj)
    { ((Rva00065964ObjectPool *)this)->FreeObject(obj); }
};
template<class T, int BLOCK_SIZE> class AutoPoolClass {
public:
    static void *operator new(unsigned int size);
    static void operator delete(void *memory);
private:
    static ObjectPoolClass<T, BLOCK_SIZE> Allocator;
};
template<class T, int BLOCK_SIZE>
void *AutoPoolClass<T, BLOCK_SIZE>::operator new(unsigned int size)
{
    return (void *)(Allocator.Allocate_Object_Memory());
}
template<class T, int BLOCK_SIZE>
void AutoPoolClass<T, BLOCK_SIZE>::operator delete(void *memory)
{
    if (memory == 0) return;
    Allocator.Free_Object_Memory((T *)memory);
}
template void *AutoPoolClass<CameraShakeSystemClass::CameraShakerClass, 256>::operator new(unsigned int);
template void AutoPoolClass<CameraShakeSystemClass::CameraShakerClass, 256>::operator delete(void *);
