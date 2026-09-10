// cl: /O1 /DNDEBUG /MD
//
// RefMultiListClass<RenderObjClass>::Remove, retail 0x0006EF4E, 47 bytes.
// Dedicated TU so multilist.cpp cannot see this body. Internal_Remove is
// already landed; Release_Ref is inlined as dec-at-+4 then vtable slot 0.

class MultiListObjectClass
{
};

class RefCountClass
{
public:
	virtual void Delete_This();
	int RefCount;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
};

class GenericMultiListClass
{
protected:
	bool Internal_Remove(MultiListObjectClass *obj);
};

template <class T>
class RefMultiListClass : public GenericMultiListClass
{
public:
	bool Remove(T *obj);
};

bool RefMultiListClass<RenderObjClass>::Remove(RenderObjClass *obj)
{
	bool result = Internal_Remove(obj);
	if (result)
	{
		if (--obj->RefCount == 0)
			obj->Delete_This();
	}
	return result;
}
