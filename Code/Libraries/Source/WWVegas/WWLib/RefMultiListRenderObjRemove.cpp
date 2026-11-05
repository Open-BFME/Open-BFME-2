// cl: /O1 /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// RefMultiListClass<RenderObjClass>::Remove, retail 0x0006EF4E, 47 bytes.
// Dedicated TU so multilist.cpp cannot see this body. Internal_Remove is
// already landed; Release_Ref is inlined as dec-at-+4 then vtable slot 0.

#include "MultiListObjectClass.h"
#include "RefCountData.h"

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
};

#include "GenericMultiListClass.h"

template <class T>
class RefMultiListClass : public GenericMultiListClass
{
public:
	bool Remove(T *obj);
	bool Release_Head(void);
};

template <class T>
bool RefMultiListClass<T>::Remove(T *obj)
{
	bool result = Internal_Remove(obj);
	if (result)
	{
		if (--obj->NumRefs == 0)
			obj->Delete_This();
	}
	return result;
}

// Sibling of the matched Remove above (0x0006EF4E, 47B): same Release_Ref
// shape (dec at +4 then vtable slot 0) and same bool return in al, but for
// the list head via Internal_Remove_List_Head (already matched at 0x6109A0).
// Retail 0x0006EF8C, 33 bytes.
template <class T>
bool RefMultiListClass<T>::Release_Head(void)
{
	T *headObject = (T *)Internal_Remove_List_Head();
	if (headObject != 0) {
		if (--headObject->NumRefs == 0)
			headObject->Delete_This();
		return true;
	}
	return false;
}

template bool RefMultiListClass<RenderObjClass>::Remove(RenderObjClass *obj);
template bool RefMultiListClass<RenderObjClass>::Release_Head(void);
