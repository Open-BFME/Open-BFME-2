// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001B4FE9@SubsystemInterfaceList@@QAEXXZ RVA 0x001B4FE9 47B
// Evidence: leaf lane pin SubsystemInterfaceList::rva001B4FE9; caller
//   GameEngine::rva00225AFF in GameEngineSlots.cpp; notifies each entry via
//   virtual slot 0x20 then clears the vector at +0x18 via rowed 0x31BD55 erase.
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
}

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Dispatch-only view: the canonical data header deliberately omits slots 1-13.
// Retail rva001B4FE9 calls slot 8; resetAll calls slot 9. No objects of this
// view are constructed and it supplies no vtable or named method definition.
class Rva001B4FE9Target
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8();
 virtual void vf9();
};

#include "../../Include/Common/SubsystemInterfaceList.h"

void SubsystemInterfaceList::rva001B4FE9()
{
	for (SubsystemInterface **it = field18.begin(); it != field18.end(); ++it) {
		void *obj = *it;
		if (obj != 0)
			((Rva001B4FE9Target *)obj)->vf8();
	}
	_STL::vector<void *> &v = reinterpret_cast<_STL::vector<void *> &>(field18);
	v.erase(v.begin(), v.end());
}

// ?resetAll@SubsystemInterfaceList@@QAEXXZ RVA 0x001B4F6D 30B (was rva001B4F6D).
// Zero Hour SubsystemInterfaceList::resetAll walks the subsystem list in
// reverse calling reset; GameEngine::init and GameEngine.cpp call it here.
void SubsystemInterfaceList::resetAll()
{
 for(_STL::vector<_STL::pair<SubsystemInterface *, void *> >::reverse_iterator i=m_subsystems.rbegin();i!=m_subsystems.rend();++i)
  ((Rva001B4FE9Target *)i->first)->vf9();
}
