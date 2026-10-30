// Native001E7270..001E72B4 RET0; WBADC820141B confirms subsystem construction.
// Existing vtable BDE970 and its scalar deleting dtor1E7EAE establish the
// address-derived class Rva001E72B4. Base12B is native SubsystemInterface.
// Map atC and pointer vector at18; destructor1E72B4 indexes the latter by4.
// Object* is only the existing folded four-byte-pointer constructor ABI view;
// the concrete pointee and map payload identities remain unresolved.
// Sibling Rva001F092ACtor.cpp supplies the verified map/vector transfer pattern.
// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <vector>
// Suppress this TU's non-retail copy of ??1?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Object;
namespace _STL { template <> vector<Object *,allocator<Object *> >::~vector(); }
// Import-inline: this unit's bfmealloc _Vector_base<Object*> dtor copy is not retail's
// EH-framed body (0x001F1609); its uses here are all inlined, so none is emitted.
class Object;
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base() { if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); } }
class Object;
// Only the destructor slot is modelled: the Rva001E72B4Dtor.cpp and
// OpaqueScalarDeletingDtorsB03.cpp views emit the same one-slot vtable copy.
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
class Rva001E72B4:public SubsystemInterface {public:Rva001E72B4();private:_STL::map<int,void*> map;_STL::vector<Object*> entries;public:
	virtual ~Rva001E72B4();	// rowed elsewhere; declared so this unit binds to it
};
Rva001E72B4::Rva001E72B4(){}
