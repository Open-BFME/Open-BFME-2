// Retail69DB1..69F22, RET0: auxiliary BaseHeightMap draw path.
// Target-verified: enable byte at global+61, readiness/counts37AC/B0/B4,
// buffer members37A4/A8, texture holder3850, Is_Hidden slot100. Exact target
// shader preset is Multiplicative, HardwareFog label and projection bias1/0.
// ZH DX8Wrapper inline Set_Material/Set_Shader supply the semantic guide;
// BF2 texture ownership and depth-bias providers are independently rowed.
// Function purpose/type of the enable flag remain descriptive/inferred;
// original method name is unknown. Shader snapshot StringClass is real.
// cl: /O1 /G7 /MD /EHsc
class StringClass {public:
 StringClass(int,bool);__forceinline ~StringClass(){Free_String();
}char*p;private:void Free_String();
};
class VertexMaterialClass {public:
 virtual void Delete_This();int refs;enum PresetType{PRELIT_DIFFUSE=1};static VertexMaterialClass*Get_Preset(PresetType);__forceinline void Release_Ref(){if(!--refs)Delete_This();
}};
class ShaderClass {public:
 unsigned bits;void Enable_Fog(const char*);static ShaderClass _PresetMultiplicativeShader;protected:
 static bool ShaderDirty;friend class DX8Wrapper;
};
struct RenderStateStruct {ShaderClass shader;VertexMaterialClass*material;
};
class IndexBufferClass;class VertexBufferClass;
class DX8Wrapper {public:
 static void Set_Index_Buffer(const IndexBufferClass*,unsigned short);static void Set_Vertex_Buffer(const VertexBufferClass*,unsigned);static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);static __forceinline void BindAuxiliaryMaterial(VertexMaterialClass*m){if(m)++m->refs;
 if(render_state.material)render_state.material->Release_Ref();render_state.material=m;render_state_changed|=0x4000;
}
static __forceinline void BindAuxiliaryShader(const ShaderClass&s){if(!ShaderClass::ShaderDirty&&s.bits==render_state.shader.bits)return;render_state.shader=s;render_state_changed|=0x8000;StringClass str(0,false);
}
protected:
 static bool FogEnable;static RenderStateStruct render_state;static unsigned render_state_changed;friend class Rva00069DB1;
};
class TextureBaseClass {public:
 void Release_Ref();
};
class AssetReference {public:
 TextureBaseClass*p;AssetReference(const AssetReference&);~AssetReference(){if(p)p->Release_Ref();
}};
class Rva00069322 {public:
 AssetReference rva00069322();
};
struct BFME2TextureRef {TextureBaseClass*p;
};
void BFME2Set_Texture(unsigned,const BFME2TextureRef&);void bfmeSetProjectionDepthBias(float);
class GlobalData {public:
 char pad[0x61];bool drawAux;
};extern GlobalData*TheWritableGlobalData;
class Rva00069DB1 {public:
 void draw();
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual int IsHidden();char pad[0x37A4-4];VertexBufferClass*vb;IndexBufferClass*ib;int ready,vertices,indices;char gap[0x3850-0x37B8];Rva00069322*texture;
};
void Rva00069DB1::draw(){
 if(!TheWritableGlobalData->drawAux||!ready||!vertices||!indices||IsHidden())return;
 ShaderClass shader=ShaderClass::_PresetMultiplicativeShader;
 if(DX8Wrapper::FogEnable)shader.Enable_Fog("HardwareFog");
 VertexMaterialClass*material=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 DX8Wrapper::BindAuxiliaryMaterial(material);
 DX8Wrapper::BindAuxiliaryShader(shader);
 DX8Wrapper::Set_Index_Buffer(ib,0);
 DX8Wrapper::Set_Vertex_Buffer(vb,0);
 BFME2Set_Texture(0,(const BFME2TextureRef&)texture->rva00069322());
 bfmeSetProjectionDepthBias(1.0f);
 DX8Wrapper::Draw_Triangles(0,indices/3,0,vertices);
 bfmeSetProjectionDepthBias(0.0f);
 if(material)material->Release_Ref();
}
