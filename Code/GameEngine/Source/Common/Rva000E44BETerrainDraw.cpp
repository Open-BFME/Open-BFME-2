// cl: /O1 /G7 /arch:SSE /MD /EHsc
// ?rva000E44BE@Rva000E44BE@@QAEXPAVRenderingMethod@FXShader@@V?$RefCountPtr@VTextureClass@@@@@Z
// TargetE44BE..E4567 RET8. BF1 FloorBuffer006F9380Draw's floor draw guide;
// target replaces texture stages with RenderingMethod slot4 and terrain shader.
class TextureClass {public:void Release_Ref();};
class TextureBaseClass {public:void Release_Ref();};
template<class T> class RefCountPtr {
public:
 RefCountPtr(const RefCountPtr&);
 RefCountPtr(T*p):pointer(p){if(p)++*reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(p)+4);}
 ~RefCountPtr(){if(pointer)reinterpret_cast<TextureBaseClass*>(pointer)->Release_Ref();}
 T *Peek()const{return pointer;}
private:T *pointer;
};
class TextureArg : public RefCountPtr<TextureClass> {
public:
 TextureArg(const RefCountPtr<TextureClass> &r):RefCountPtr<TextureClass>(r){}
 TextureArg(TextureClass *p):RefCountPtr<TextureClass>(p){}
 TextureArg(const TextureArg &r):RefCountPtr<TextureClass>(r){}
 ~TextureArg(){}
};
namespace FXShader {class RenderingMethod {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4(int);};}
class Rva000E19A3Interface {public:virtual void setRenderingMode(int);virtual void setBaseTexture(TextureArg);virtual void setNormalTexture(TextureArg);virtual void clearTextures();};
extern Rva000E19A3Interface *g_00DEBC60;
class DX8Wrapper {public:static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);};
class Rva000E44BE {
public:void rva000E44BE(FXShader::RenderingMethod*,RefCountPtr<TextureClass>);
private:
 char pad00[0x20];RefCountPtr<TextureClass> base20,normal24;char pad28[0x14];
 unsigned start3c,vertices40,minimum44,polygons48;
 char pad4c[0x34];bool active80;
};
void Rva000E44BE::rva000E44BE(FXShader::RenderingMethod*volatile method,RefCountPtr<TextureClass>fallback)
{
 if(active80) {
  if(method) {
   g_00DEBC60->setBaseTexture(base20);
   if(normal24.Peek())g_00DEBC60->setNormalTexture(normal24);
   else g_00DEBC60->setNormalTexture(TextureArg(fallback.Peek()));
   method->slot4(2);
  }
  DX8Wrapper::Draw_Triangles(start3c,polygons48,minimum44,vertices40);
 }
}
