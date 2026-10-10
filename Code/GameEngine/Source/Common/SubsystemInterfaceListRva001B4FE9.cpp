// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001B4FE9@SubsystemInterfaceList@@QAEXXZ RVA 0x001B4FE9 47B
// Evidence: leaf lane pin SubsystemInterfaceList::rva001B4FE9; caller
//   GameEngine::rva00225AFF in GameEngineSlots.cpp; notifies each entry via
//   virtual slot 0x20 then clears the vector at +0x18 via rowed 0x31BD55 erase.
#include <vector>

class SubsystemInterface
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

struct SubsystemEntry8 {SubsystemInterface *object;unsigned extra;};

class SubsystemInterfaceList
{
public:
	void rva001B4FE9();
 void resetAll();

private:
	_STL::vector<SubsystemEntry8> m_primary;
 _STL::vector<void*> m_pending;
	_STL::vector<void *> m_vec; // +0x18
};

void SubsystemInterfaceList::rva001B4FE9()
{
	for (void **it = m_vec.begin(); it != m_vec.end(); ++it) {
		void *obj = *it;
		if (obj != 0)
			((SubsystemInterface *)obj)->vf8();
	}
	_STL::vector<void *> &v = m_vec;
	v.erase(v.begin(), v.end());
}

// ?resetAll@SubsystemInterfaceList@@QAEXXZ RVA 0x001B4F6D 30B (was rva001B4F6D).
// Zero Hour SubsystemInterfaceList::resetAll walks the subsystem list in
// reverse calling reset; GameEngine::init and GameEngine.cpp call it here.
void SubsystemInterfaceList::resetAll()
{
 for(_STL::vector<SubsystemEntry8>::reverse_iterator i=m_primary.rbegin();i!=m_primary.rend();++i)
  i->object->vf9();
}
