// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// The range overload of WWMath::Random_Float (0x0006598A) is the exact
// inline body already emitted by camerashakesystem_shaker.cpp's callers.
// Its row belongs there; this unit owns only the verified list destructors.

// ??1CameraShakeSystemClass@@QAE@XZ retail 0x00065D52 (91B): the reference
// destructor verbatim, over the WWLib multilist layout (Zero Hour multilist.h:
// vptr, then the Head node whose Next is +8). The list member's destructor
// 0x00065CA4 (68B) is multilist.h's inline ~MultiListClass, emitted out of line
// here as retail calls it. Internal_Remove_List_Head and Internal_Remove are the
// rowed multilist.cpp bodies. Placed by compiling the Open-BFME-1 donor at /O1.
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass(void);
};

class GenericMultiListClass;

class MultiListNodeClass
{
public:
	MultiListNodeClass		*Prev;
	MultiListNodeClass		*Next;
	MultiListNodeClass		*NextList;
	MultiListObjectClass	*Object;
	GenericMultiListClass	*List;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass(void);
	bool Is_Empty(void) { return (Head.Next == &Head); }

protected:
	bool Internal_Remove(MultiListObjectClass *obj);
	MultiListObjectClass *Internal_Remove_List_Head(void);

	MultiListNodeClass Head;
};

template <class ObjectType>
class MultiListClass : public GenericMultiListClass
{
public:
	virtual ~MultiListClass(void) { while (!Is_Empty()) { Remove_Head(); } }
	ObjectType *Remove_Head(void) { return (ObjectType *)Internal_Remove_List_Head(); }
	bool Remove(ObjectType *obj) { return Internal_Remove(obj); }
};

class CameraShakeSystemClass
{
public:
	~CameraShakeSystemClass(void);

	class CameraShakerClass : public MultiListObjectClass
	{
	};

protected:
	MultiListClass<CameraShakerClass> CameraShakerList;
};

CameraShakeSystemClass::~CameraShakeSystemClass(void)
{
	/*
	** delete all of the objects out of the list
	*/
	while (!CameraShakerList.Is_Empty()) {
		CameraShakerClass * obj = CameraShakerList.Remove_Head();
		CameraShakerList.Remove(obj);
		delete obj;
	}
}
