// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport
#include <vector>
#include <stl/_hashtable.h>
#include <stl/_hash_fun.h>
class TextureClass { public: void Release_Ref(); };
template<class T> class RefCountPtr { public:
 RefCountPtr():Ptr(0) {}
 ~RefCountPtr() { if (Ptr) Ptr->Release_Ref(); }
 RefCountPtr const &operator=(RefCountPtr const &other);
 T *Ptr;
};
class BFME2ParticleTextureHandle { public:
 TextureClass *Ptr;
 ~BFME2ParticleTextureHandle() { if(Ptr) Ptr->Release_Ref(); }
};
extern BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *,int,int);

class Vector3 { public:float x,y,z; };
class Vector2 { public:float x,y;Vector2(float a,float b):x(a),y(b){} };
class ShaderClass { public:ShaderClass(const ShaderClass &s):bits(s.bits){} ShaderClass(unsigned x):bits(x){} unsigned bits;static ShaderClass _PresetAlphaShader;};
class SegLineRendererClass { public:enum TextureMapMode { Tile=2 }; };
class RenderObjClass { public: virtual void Delete_This(); int refs; };
class SegmentedLineClass:public RenderObjClass { public:
 SegmentedLineClass();
 void Set_Texture(TextureClass *);
 void Set_Shader(ShaderClass);
 void Set_Width(float);
 void Set_Color(const Vector3 &);
 void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode);
 void Set_Texture_Tile_Factor(float);
 void Set_UV_Offset_Rate(const Vector2 &);
 char bytes[292];
};
class RenderInfoClass { public: ~RenderInfoClass(); };
extern RenderObjClass *Create_Render_Obj(const char *);
class LightEnvironmentClass { public:LightEnvironmentClass();~LightEnvironmentClass();char bytes[0x22c];};
struct Rva00390729Element { int opaque[3]; };
struct Rva000E0AC3Element { char bytes[1]; bool operator<(const Rva000E0AC3Element&)const; bool operator==(const Rva000E0AC3Element&)const; };
namespace _STL {template<> struct hash<Rva000E0AC3Element> { unsigned operator()(const Rva000E0AC3Element&) const; };
template<> void vector<Rva00390729Element>::reserve(unsigned);

}
enum NameKeyType { NativeNameKeyUnknown=0 };
class ArmorTemplate {float donorCoefficients[38];};
namespace rts {template<class T>struct hash {unsigned operator()(T)const;};template<class T>struct equal_to {bool operator()(T,T)const;};}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,_STL::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > ArmorTable;
namespace _STL {template<> void ArmorTable::clear();}
// The native generic table destructor57B has its own EH handler, so the old
// gen-alias placeholder is replaced by this actual separately emitted body.
// Only the zero-initialized bucket header and clear/free contract are claimed.
class Rva000E025FHashTableView { public:
 __declspec(noinline) ~Rva000E025FHashTableView() { ((ArmorTable *)this)->clear(); }
 unsigned prefix;_STL::vector<void *> buckets;unsigned count;
};
namespace _STL {
template<class K,class V,class H=hash<K>,class P=equal_to<K>,class A=allocator<pair<const K,V> > >
class hash_map { public: hash_map(); ~hash_map() { ((Rva000E025FHashTableView *)this)->~Rva000E025FHashTableView(); } private:char header[20]; };
}
// Native initialized mutable RGB triplets, read at E0C0C/E0C9A.
// Names describe this use; no original global identifier is asserted.
float terrainNormalColor[3]={.96f,.77f,.47f};
float terrainSpecialColor[3]={.98f,.51f,.58f};
// BaseHeightMap ctor6C9CF allocates26C and stores this owner at3868.
// WB87D140 confirms the four line setups and named assets; native offsets
// supersede its debug layout. ZH segline/ShaderClass/LightEnvironment and
// BF1 WaypointBufferCtor575ba2b04 are semantic/ABI guides, not class identity.
// Native EH state2 destroys LightEnvironment20 via owned no-op69E440;
// state3 destroys vector24C; state4 destroys 20B hash header258 via E03DD.
// E03DD is a five-byte tail wrapper to the existing generic hashtable dtor
// E025F, whose clear/free behavior is independently visible in target bytes.
// ArmorTable's existing spelling below is only an ABI view of that provider;
// its donor payload is not a claim about this map's elements.
class Rva000E0AE2 { public:Rva000E0AE2();~Rva000E0AE2();
 RenderObjClass *hint;SegmentedLineClass *lines[4];
 RefCountPtr<TextureClass> normalTexture,specialTexture;
 RenderInfoClass *unknown1c;LightEnvironmentClass light;
 _STL::vector<Rva00390729Element> records;
 _STL::hash_map<int,Rva000E0AC3Element> entries;
};
Rva000E0AE2::Rva000E0AE2():unknown1c(0) {
 records.reserve(50);
 hint=Create_Render_Obj("SCMoveHintSml");
 normalTexture=(const RefCountPtr<TextureClass> &)BFME2LoadParticleTexture("EXLaser.tga",0,0);
 specialTexture=(const RefCountPtr<TextureClass> &)BFME2LoadParticleTexture("EXLaser2.tga",0,0);
 ShaderClass shader(ShaderClass::_PresetAlphaShader.bits|7);
 lines[0]=new SegmentedLineClass;
 lines[0]->Set_Texture((TextureClass *)&normalTexture);
 lines[0]->Set_Shader(shader);
 lines[0]->Set_Width(1.5f);
 { Vector3 color={terrainNormalColor[0],terrainNormalColor[1],terrainNormalColor[2]};lines[0]->Set_Color(color); }
 lines[0]->Set_Texture_Mapping_Mode(SegLineRendererClass::Tile);
 lines[1]=new SegmentedLineClass;
 lines[1]->Set_Texture((TextureClass *)&normalTexture);
 lines[1]->Set_Shader(shader);
 lines[1]->Set_Width(1.5f);
 { Vector3 color={terrainSpecialColor[0],terrainSpecialColor[1],terrainSpecialColor[2]};lines[1]->Set_Color(color); }
 lines[1]->Set_Texture_Mapping_Mode(SegLineRendererClass::Tile);
 lines[2]=new SegmentedLineClass;
 lines[2]->Set_Texture((TextureClass *)&specialTexture);
 lines[2]->Set_Shader(shader);
 lines[2]->Set_Width(1.5f);
 { Vector3 color={terrainNormalColor[0],terrainNormalColor[1],terrainNormalColor[2]};lines[2]->Set_Color(color); }
 lines[2]->Set_Texture_Mapping_Mode(SegLineRendererClass::Tile);
 lines[2]->Set_Texture_Tile_Factor(50.0f);
 { Vector2 rate(.001f,.001f);lines[2]->Set_UV_Offset_Rate(rate); }
 lines[3]=new SegmentedLineClass;
 lines[3]->Set_Texture((TextureClass *)&specialTexture);
 lines[3]->Set_Shader(shader);
 lines[3]->Set_Width(1.5f);
 { Vector3 color={terrainSpecialColor[0],terrainSpecialColor[1],terrainSpecialColor[2]};lines[3]->Set_Color(color); }
 lines[3]->Set_Texture_Mapping_Mode(SegLineRendererClass::Tile);
 lines[3]->Set_Texture_Tile_Factor(50.0f);
 { Vector2 rate(.001f,.001f);lines[3]->Set_UV_Offset_Rate(rate); }
}

Rva000E0AE2::~Rva000E0AE2() {
 { RenderObjClass *p=hint; if(p) { if(--p->refs==0) p->Delete_This(); hint=0; } }
 { RenderObjClass *p=lines[0]; if(p) { if(--p->refs==0) p->Delete_This(); lines[0]=0; } }
 { RenderObjClass *p=lines[1]; if(p) { if(--p->refs==0) p->Delete_This(); lines[1]=0; } }
 { RenderObjClass *p=lines[2]; if(p) { if(--p->refs==0) p->Delete_This(); lines[2]=0; } }
 { RenderObjClass *p=lines[3]; if(p) { if(--p->refs==0) p->Delete_This(); lines[3]=0; } }
 delete unknown1c;
}
