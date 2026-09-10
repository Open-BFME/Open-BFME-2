// cl: /O2 /G7 /Oy /DNDEBUG /MD
//
// DX8TextureCategoryClass::Remove_Polygon_Renderer, retail 0x001460E0, 78 bytes.
// Dedicated TU so the matched bodies in dx8renderer.cpp stay untouched.
// BFME2 null-checks the delete-list pointer before Internal_Add_Tail.

class MultiListObjectClass;
class GenericMultiListClass;
class DX8TextureCategoryClass;

class MultiListNodeClass
{
public:
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
	GenericMultiListClass *List;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();

	MultiListObjectClass *Internal_Get_List_Head()
	{
		if (Head.Next == &Head)
			return 0;
		return Head.Next->Object;
	}

protected:
	bool Internal_Add_Tail(MultiListObjectClass *obj, bool onlyonce);
	bool Internal_Remove(MultiListObjectClass *obj);

private:
	MultiListNodeClass Head;
};

class PolygonRendererListClass : public GenericMultiListClass
{
public:
	bool Remove(MultiListObjectClass *obj)
	{
		return Internal_Remove(obj);
	}
};

class TextureCategoryListClass : public GenericMultiListClass
{
public:
	bool Add_Tail(MultiListObjectClass *obj, bool onlyonce)
	{
		return Internal_Add_Tail(obj, onlyonce);
	}
};

class MultiListObjectClass
{
	void *list_node;
};

class DX8PolygonRendererClass : public MultiListObjectClass
{
	unsigned char pad[8];
	void *texture_category;

public:
	void Set_Texture_Category(void *category)
	{
		texture_category = category;
	}
};

class DX8FVFCategoryContainer
{
public:
	void Remove_Texture_Category(DX8TextureCategoryClass *tex_category);
};

class DX8TextureCategoryClass : public MultiListObjectClass
{
	unsigned char pad[0x18];
	PolygonRendererListClass PolygonRendererList;
	DX8FVFCategoryContainer *container;

public:
	void Remove_Polygon_Renderer(DX8PolygonRendererClass *p_renderer);
};

struct TextureCategoryDeleteList
{
	unsigned char pad[0x1C];
	TextureCategoryListClass list;
};

TextureCategoryDeleteList *texture_category_delete_list;

void DX8TextureCategoryClass::Remove_Polygon_Renderer(DX8PolygonRendererClass *p_renderer)
{
	PolygonRendererList.Remove(p_renderer);
	p_renderer->Set_Texture_Category(0);
	if (PolygonRendererList.Internal_Get_List_Head() == 0)
	{
		container->Remove_Texture_Category(this);
		if (texture_category_delete_list)
			texture_category_delete_list->list.Add_Tail(this, true);
	}
}
