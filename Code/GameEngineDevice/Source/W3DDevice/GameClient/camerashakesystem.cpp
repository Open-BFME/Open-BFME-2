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
class MultiListNodeClass;

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass(void);

private:
	// The actual constructor65A39 clears ListNode+4 before Position+8.
	MultiListNodeClass *ListNode;
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
	public:
		void Timestep(float dt);
		bool Is_Expired(void);

	protected:
		// Existing constructor65A39 and Compute_Rotations65B09 prove
		// Duration+18 and ElapsedTime+20 in the real 3C-byte shaker.
		// Opaque ranges preserve the other fields without a Vector3 copy.
		unsigned char m_unreconstructed_08[0x10];
		float Duration;
		float Intensity;
		float ElapsedTime;
		unsigned char m_unreconstructed_24[0x18];
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

// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 camerashakesystem.h supplies
// these inline semantics, compiled /O1 /arch:SSE /G7. Target65898..658AB
// follows a prior RET and ends RET4;658AB..658BA ends RET0. The existing
// named constructor65A39 and rotation method65B09 establish the actual
// Duration18/ElapsedTime20 fields; outer timestep65E3C independently inlines
// this add/compare at65E6C..65E7F. Thus class ownership and the timing state
// relationship come from target evidence as well as the clean donor header.
void CameraShakeSystemClass::CameraShakerClass::Timestep(float dt)
{
	ElapsedTime += dt;
}

bool CameraShakeSystemClass::CameraShakerClass::Is_Expired(void)
{
	return ElapsedTime >= Duration;
}
