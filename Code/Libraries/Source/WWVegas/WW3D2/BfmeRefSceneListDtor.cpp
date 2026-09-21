// cl: /O1 /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??1BfmeRefSceneList@@UAE@XZ, retail 0x0006F29B, 68 bytes.
// Dtor drains the list via the rowed Release_Head, then the rowed generic
// base dtor runs. Single-inheritance chain so one vtable store lands.

class MultiListObjectClass;
class RenderObjClass;

class MultiListNodeClass
{
public:
	class MultiListNodeClass *Prev;
	class MultiListNodeClass *Next;
	class MultiListNodeClass *NextList;
	class MultiListObjectClass *Object;
	class GenericMultiListClass *List;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();

	bool Is_Empty(void)
	{
		return (Head.Next == &Head);
	}

private:
	MultiListNodeClass Head;
};

template <class T>
class RefMultiListClass : public GenericMultiListClass
{
public:
	bool Release_Head(void);
};

class BfmeRefSceneList : public RefMultiListClass<RenderObjClass>
{
public:
	virtual ~BfmeRefSceneList();
};

BfmeRefSceneList::~BfmeRefSceneList()
{
	while (!Is_Empty())
		Release_Head();
}
