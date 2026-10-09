// cl: /Ireference/shims/bfmestages /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ZH dx8renderer.cpp at BFME1 9cbfb551fe20 is the semantic donor.
// Target1465C0..146930 RET16 independently proves the 880-byte material path;
// Ghidra877 omits the return. Rowed model replacement172D40 and category
// search145290 corroborate identity. Category offsets and 20-byte move records
// come from retail; smart-reference names remain the established modeled types.
// The transient move list uses the existing opaque1447B0/BD34EC provider;
// no new destructor identity is claimed. Native global singleton is a pointer.
#include "multilist.h"

class TextureClass
{
public:
	virtual void Delete_This() = 0;
	unsigned short NumRefs;
	void Release_Ref();
};

struct BFME2TextureRef;
template<class T> class RefCountPtr
{
public:
	T* p;
 RefCountPtr &operator=(const BFME2TextureRef&);
	RefCountPtr() : p(0) {}
	~RefCountPtr() { if (p) p->Release_Ref(); }
	bool operator==(const RefCountPtr& o) const { return p == o.p; }
	bool operator!=(const RefCountPtr& o) const { return p != o.p; }
};

class BfmeHandleCX
{
public:
	TextureClass* p;
	~BfmeHandleCX() { if (p) p->Release_Ref(); }
};

struct BFME2TextureResource { unsigned Vtable; unsigned short Refs; void Release_Ref(); };
struct BFME2TextureRef {
	BFME2TextureResource* Ptr;
	BFME2TextureRef(BFME2TextureResource* q) : Ptr(q) { if (Ptr) ++Ptr->Refs; }
	BFME2TextureRef(const BFME2TextureRef& q) : Ptr(q.Ptr) { if (Ptr) ++Ptr->Refs; }
	~BFME2TextureRef() { if (Ptr) Ptr->Release_Ref(); }
};

template<class T> inline RefCountPtr<T>& RefCountPtr<T>::operator=(const BFME2TextureRef &x) {
 if(x.Ptr) ++((T*)x.Ptr)->NumRefs;
 if(p) p->Release_Ref();
 p=(T*)x.Ptr;
 return *this;
}
class BFME2TextureCategory {
	unsigned Prefix[3];
	BFME2TextureResource* Textures[2];
public:
	BFME2TextureRef Get_Texture(int stage) throw();
};

inline bool operator==(const BFME2TextureRef& l, const RefCountPtr<TextureClass>& r)
{
	return (TextureClass*)l.Ptr == r.p;
}
inline bool operator==(const BFME2TextureRef& l, const BfmeHandleCX& r)
{
	return (TextureClass*)l.Ptr == r.p;
}
inline bool operator==(const BFME2TextureRef& l, const BFME2TextureRef& r)
{
	return l.Ptr == r.Ptr;
}

class ShaderClass
{
public:
	unsigned ShaderBits;
	ShaderClass() {}
	ShaderClass(const ShaderClass& s) { ShaderBits = s.ShaderBits; }
};
class VertexMaterialClass
{
public:
	virtual void Delete_This() = 0;
	unsigned long Get_CRC() const;
};

class DX8PolygonRendererClass;
class DX8TextureCategoryClass;
class DX8FVFCategoryContainer;

typedef MultiListClass<DX8TextureCategoryClass> TextureCategoryList;
typedef MultiListIterator<DX8TextureCategoryClass> TextureCategoryListIterator;
typedef MultiListClass<DX8PolygonRendererClass> DX8PolygonRendererList;
typedef MultiListIterator<DX8PolygonRendererClass> DX8PolygonRendererListIterator;

class DX8PolygonRendererClass : public MultiListObjectClass
{
	char m_pad04[4];
	DX8TextureCategoryClass* Category;
public:
	DX8TextureCategoryClass* Get_Texture_Category() { return Category; }
	void Set_Texture_Category(DX8TextureCategoryClass* c) { Category = c; }
};

struct TextureCategoryDeleteListView
{
	unsigned char pad[0x1C];
	TextureCategoryList list;
};

class DX8TextureCategoryClass : public MultiListObjectClass
{
	int pass;
	TextureClass* textures[2];
	ShaderClass shader;
	VertexMaterialClass* material;
	MultiListClass<DX8PolygonRendererClass> PolygonRendererList;
	DX8FVFCategoryContainer* container;
	void* render_task_head;
public:
	DX8TextureCategoryClass(DX8FVFCategoryContainer* c, TextureClass** t, ShaderClass s, VertexMaterialClass* m, int p);
	ShaderClass Get_Shader() { return shader; }
	const ShaderClass& Peek_Shader() { return shader; }
	VertexMaterialClass* Peek_Material() { return material; }
	void Remove_Polygon_Renderer(DX8PolygonRendererClass* p_renderer);
	void Add_Polygon_Renderer(DX8PolygonRendererClass* p_renderer, DX8PolygonRendererClass* a = 0);
};

extern class DX8MeshRendererClass *TheDX8MeshRenderer;
class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	enum { MAX_PASSES = 4 };
protected:
	TextureCategoryList texture_category_list[MAX_PASSES];
public:
	DX8TextureCategoryClass* Find_Matching_Texture_Category(const BfmeHandleCX& t, unsigned pass, unsigned stage, DX8TextureCategoryClass* ref);
	void Remove_Texture_Category(DX8TextureCategoryClass* t);
	void Change_Polygon_Renderer_Material(DX8PolygonRendererList&,VertexMaterialClass*,VertexMaterialClass*,unsigned);
protected:
 DX8TextureCategoryClass *Find_Matching_Texture_Category(VertexMaterialClass*,unsigned,DX8TextureCategoryClass*);
};

inline void DX8TextureCategoryClass::Remove_Polygon_Renderer(DX8PolygonRendererClass* p_renderer)
{
	PolygonRendererList.Remove(p_renderer);
	p_renderer->Set_Texture_Category(0);
	if (PolygonRendererList.Peek_Head() == 0) {
		container->Remove_Texture_Category(this);
		TextureCategoryDeleteListView* dl = *(TextureCategoryDeleteListView**)&TheDX8MeshRenderer;
		if (dl)
			dl->list.Add_Tail(this, true);
	}
}
inline void DX8TextureCategoryClass::Add_Polygon_Renderer(DX8PolygonRendererClass* p_renderer, DX8PolygonRendererClass* a)
{
	if (a != 0) {
		PolygonRendererList.Add_After(p_renderer, a, false);
	} else {
		PolygonRendererList.Add(p_renderer);
	}
	p_renderer->Set_Texture_Category(this);
}

class MeshMatDescClass { public: enum { MAX_TEX_STAGES = 2 }; };

class PolyRemover : public MultiListObjectClass
{
public:
	DX8TextureCategoryClass* src;
	DX8TextureCategoryClass* dest;
	DX8PolygonRendererClass* pr;
};
typedef MultiListClass<PolyRemover> PolyRemoverList;
typedef MultiListIterator<PolyRemover> PolyRemoverListIterator;

class Rva001447B0 : public GenericMultiListClass {public:virtual ~Rva001447B0();};
void DX8FVFCategoryContainer::Change_Polygon_Renderer_Material(
		DX8PolygonRendererList& polygon_renderer_list,
		VertexMaterialClass* vmat,
		VertexMaterialClass* new_vmat,
		unsigned pass)
{
	

	Rva001447B0 prl;
 PolyRemoverList *prlList=(PolyRemoverList*)&prl;

	bool foundtexture=false;

	if (vmat==new_vmat) return;

	// Find source texture category, then find all polygon renderers who belong to that category
	// and move them to destination category.
	TextureCategoryListIterator src_it(&texture_category_list[pass]);
	while (!src_it.Is_Done()) {
		DX8TextureCategoryClass* src_tex_category=src_it.Peek_Obj();
		if (src_tex_category->Peek_Material()==vmat) {			
			DX8PolygonRendererListIterator poly_it(&polygon_renderer_list);
			while (!poly_it.Is_Done()) {
				// If source texture category contains polygon renderer, move to destination category
				DX8PolygonRendererClass* polygon_renderer=poly_it.Peek_Obj();
				DX8TextureCategoryClass *prc=polygon_renderer->Get_Texture_Category();
				if (prc==src_tex_category) {
					foundtexture=true;
					DX8TextureCategoryClass* dest_tex_category=Find_Matching_Texture_Category(new_vmat,pass,src_tex_category);

					if (!dest_tex_category) {
						RefCountPtr<TextureClass> tmp_textures[MeshMatDescClass::MAX_TEX_STAGES];
						for (int s=0;s<MeshMatDescClass::MAX_TEX_STAGES;++s) {
							tmp_textures[s]=((BFME2TextureCategory*)src_tex_category)->Get_Texture(s);
						}						

						DX8TextureCategoryClass * new_tex_category=new DX8TextureCategoryClass(
							this,
							(TextureClass**)tmp_textures,
							src_tex_category->Peek_Shader(),
							const_cast<VertexMaterialClass*>(new_vmat),
							pass);
		
						/*
						** Add the texture category object into the list, immediately after any existing
						** texture category object which uses the same texture.  This will result in
						** the list always having matching texture categories next to each other.
						*/
						bool found_similar_category = false;
						TextureCategoryListIterator tex_it(&texture_category_list[pass]);
						while (!tex_it.Is_Done()) {
							// Categorize according to first stage's texture for now
							if (((BFME2TextureCategory*)tex_it.Peek_Obj())->Get_Texture(0) == tmp_textures[0]) {
								texture_category_list[pass].Add_After(new_tex_category,tex_it.Peek_Obj());
								found_similar_category = true;
								break;
							}
							tex_it.Next();
						}

						if (!found_similar_category) {
							texture_category_list[pass].Add_Tail(new_tex_category);
						}
						dest_tex_category=new_tex_category;
					}
					PolyRemover *rem=new PolyRemover;
					rem->src=src_tex_category;
					rem->dest=dest_tex_category;
					rem->pr=polygon_renderer;
					prlList->Add(rem);
				}
				poly_it.Next();
			} // while			
		} // if 
		else
			if (foundtexture) break;
		src_it.Next();
	} // while

	PolyRemoverListIterator prli((PolyRemoverList*)&prl);

	while (!prli.Is_Done())
	{
		PolyRemover *rem=prli.Peek_Obj();
		rem->src->Remove_Polygon_Renderer(rem->pr);
		rem->dest->Add_Polygon_Renderer(rem->pr);		
		prli.Remove_Current_Object();
		::delete rem;
	}
}
