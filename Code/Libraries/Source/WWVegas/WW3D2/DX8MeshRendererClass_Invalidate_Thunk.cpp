// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Invalidate@DX8MeshRendererClass@@QAEX_N@Z @ 0x00145FA0 (265B).
// The rigid vector is at +8 and the skin list at +0x18.
class MultiListNodeClass
{
public:
	MultiListNodeClass *prev;
	MultiListNodeClass *next;
	MultiListNodeClass *next_list;
	void *object;
	void *list;

	MultiListNodeClass()
	{
		prev = next = next_list = 0;
		object = 0;
		list = 0;
	}
};

#include "../WWLib/MultiListObjectClass.h"

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	__declspec(dllimport) __forceinline GenericMultiListClass()
	{
		head.next = head.prev = &head;
		head.object = 0;
		head.next_list = 0;
	}

protected:
	MultiListNodeClass head;
	MultiListObjectClass *Internal_Remove_List_Head();
};

class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	virtual ~DX8FVFCategoryContainer();
};

class FVFCategoryList : public GenericMultiListClass
{
public:
	virtual ~FVFCategoryList();
	DX8FVFCategoryContainer *Remove_Head()
	{
		return static_cast<DX8FVFCategoryContainer *>(Internal_Remove_List_Head());
	}
};

class SimpleDynVecFVFLists
{
public:
	virtual ~SimpleDynVecFVFLists();
	virtual bool Resize(int size);

	FVFCategoryList **vector;
	int vector_max;
	int active_count;

	int Count() const
	{
		return active_count;
	}

	FVFCategoryList *operator[](int index)
	{
		return vector[index];
	}

	void Delete_All(bool allow_shrink = true)
	{
		active_count = 0;
		if (allow_shrink && active_count < vector_max / 4) {
			Resize(active_count);
		}
	}
};

class CameraClass;

#include <new>

class DX8MeshRendererClass
{
public:
	void Invalidate(bool shutdown = false);

protected:
	bool enable_lighting;
	CameraClass *camera;
	SimpleDynVecFVFLists texture_category_container_lists_rigid;
	FVFCategoryList *texture_category_container_list_skin;
};

static __forceinline void Invalidate_FVF_Category_Container_List(FVFCategoryList &list)
{
	DX8FVFCategoryContainer *container;
	while ((container = list.Remove_Head()) != 0) {
		::delete container;
	}
}

void DX8MeshRendererClass::Invalidate(bool shutdown)
{
	for (int i = 0; i < texture_category_container_lists_rigid.Count(); ++i) {
		Invalidate_FVF_Category_Container_List(*texture_category_container_lists_rigid[i]);
		::delete texture_category_container_lists_rigid[i];
	}

	if (texture_category_container_list_skin != 0) {
		Invalidate_FVF_Category_Container_List(*texture_category_container_list_skin);
		::delete texture_category_container_list_skin;
		texture_category_container_list_skin = 0;
	}

	if (!shutdown) {
		texture_category_container_list_skin = new FVFCategoryList;
	}

	texture_category_container_lists_rigid.Delete_All();
}
