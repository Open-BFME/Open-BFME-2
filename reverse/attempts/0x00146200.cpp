// ?Change_Polygon_Renderer_Texture@DX8FVFCategoryContainer@@QAEXAAV?$MultiListClass@VDX8PolygonRendererClass@@@@ABV?$RefCountPtr@VTextureClass@@@@1II@Z
// partial score=0.8852 date=2026-10-05
// cl: /Ireference/shims/bfmestages /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
#include "multilist.h"

class TextureClass
{
public:
	virtual void Delete_This() = 0;
	unsigned short NumRefs;
	void Release_Ref();
};

template<class T> class RefCountPtr
{
public:
	T* p;
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

class BFME2TextureCategory {
	unsigned Prefix[3];
	BFME2TextureResource* Textures[2];
public:
	BFME2TextureRef Get_Texture(int stage);
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

class DX8FVFCategoryContainer : public MultiListObjectClass
{
public:
	enum { MAX_PASSES = 4 };
protected:
	TextureCategoryList texture_category_list[MAX_PASSES];
public:
	DX8TextureCategoryClass* Find_Matching_Texture_Category(const BfmeHandleCX& t, unsigned pass, unsigned stage, DX8TextureCategoryClass* ref);
	void Remove_Texture_Category(DX8TextureCategoryClass* t);
	void Change_Polygon_Renderer_Texture(DX8PolygonRendererList& l, const RefCountPtr<TextureClass>& t, const RefCountPtr<TextureClass>& n, unsigned pass, unsigned stage);
};

inline void DX8TextureCategoryClass::Remove_Polygon_Renderer(DX8PolygonRendererClass* p_renderer)
{
	PolygonRendererList.Remove(p_renderer);
	p_renderer->Set_Texture_Category(0);
	if (PolygonRendererList.Peek_Head() == 0) {
		container->Remove_Texture_Category(this);
		TextureCategoryDeleteListView* dl = *(TextureCategoryDeleteListView* volatile*)0x00DF363C;
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

class Rva001447B0 : public GenericMultiListClass
{
public:
	virtual ~Rva001447B0();
};

inline static bool Equal_Material(const VertexMaterialClass* a, const VertexMaterialClass* b)
{
	return true;
}

// ?Change_Polygon_Renderer_Texture@DX8FVFCategoryContainer@@QAEXAAV?$MultiListClass@VDX8PolygonRendererClass@@@@ABV?$RefCountPtr@VTextureClass@@@@1II@Z present-unmatched
void DX8FVFCategoryContainer::Change_Polygon_Renderer_Texture(
	DX8PolygonRendererList& polygon_renderer_list,
	const RefCountPtr<TextureClass>& texture,
	const RefCountPtr<TextureClass>& new_texture,
	unsigned pass,
	unsigned stage)
{
	Rva001447B0 prl;
	PolyRemoverList* prlList = reinterpret_cast<PolyRemoverList*>(&prl);
	bool foundtexture = false;
	if (texture == new_texture)
		return;
	TextureCategoryListIterator src_it(&texture_category_list[pass]);
	while (!src_it.Is_Done()) {
		DX8TextureCategoryClass* src_tex_category = src_it.Peek_Obj();
		if (reinterpret_cast<BFME2TextureCategory*>(src_tex_category)->Get_Texture(stage) == texture) {
			foundtexture = true;
			DX8PolygonRendererListIterator poly_it(&polygon_renderer_list);
			while (!poly_it.Is_Done()) {
				DX8PolygonRendererClass* polygon_renderer = poly_it.Peek_Obj();
				DX8TextureCategoryClass* prc = polygon_renderer->Get_Texture_Category();
				if (prc == src_tex_category) {
					DX8TextureCategoryClass* dest_tex_category = Find_Matching_Texture_Category(reinterpret_cast<const BfmeHandleCX&>(new_texture), pass, stage, src_tex_category);
					if (!dest_tex_category) {
						RefCountPtr<TextureClass> tmp_textures[2];
						for (int s = 0; s < 2; ++s) {
							BFME2TextureRef t = reinterpret_cast<BFME2TextureCategory*>(src_tex_category)->Get_Texture(s);
							if (t.Ptr)
								++((TextureClass*)t.Ptr)->NumRefs;
							if (tmp_textures[s].p)
								tmp_textures[s].p->Release_Ref();
							tmp_textures[s].p = (TextureClass*)t.Ptr;
						}
						{
							TextureClass* np = new_texture.p;
							RefCountPtr<TextureClass>& slot = tmp_textures[stage];
							if (np)
								++np->NumRefs;
							if (slot.p)
								slot.p->Release_Ref();
							slot.p = np;
						}
						DX8TextureCategoryClass* new_tex_category = new DX8TextureCategoryClass(
							this,
							(TextureClass**)tmp_textures,
							src_tex_category->Peek_Shader(),
							src_tex_category->Peek_Material(),
							pass);
						bool found_similar_category = false;
						TextureCategoryListIterator tex_it(&texture_category_list[pass]);
						while (!tex_it.Is_Done()) {
							if (reinterpret_cast<BFME2TextureCategory*>(tex_it.Peek_Obj())->Get_Texture(0) == tmp_textures[0]) {
								texture_category_list[pass].Add_After(new_tex_category, tex_it.Peek_Obj());
								found_similar_category = true;
								break;
							}
							tex_it.Next();
						}
						if (!found_similar_category) {
							texture_category_list[pass].Add_Tail(new_tex_category);
						}
						dest_tex_category = new_tex_category;
					}
					PolyRemover* rem = new PolyRemover;
					rem->src = src_tex_category;
					rem->dest = dest_tex_category;
					rem->pr = polygon_renderer;
					prlList->Add(rem);
				}
				poly_it.Next();
			}
		} else {
			if (foundtexture)
				break;
		}
		src_it.Next();
	}
	PolyRemoverListIterator prli(reinterpret_cast<PolyRemoverList*>(&prl));
	while (!prli.Is_Done()) {
		PolyRemover* rem = prli.Peek_Obj();
		rem->src->Remove_Polygon_Renderer(rem->pr);
		rem->dest->Add_Polygon_Renderer(rem->pr);
		prli.Remove_Current_Object();
		delete rem;
	}
}
