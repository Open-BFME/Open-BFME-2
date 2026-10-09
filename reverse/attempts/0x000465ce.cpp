// ?rva000465CE@W3DDisplay@@QAEXPAVRva000465CEBuffer@@MMMMH@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 0bef414b52a39a3ab1ec98dca60d8a214de4260e W3DDisplay::drawVideoBuffer
// is the semantic guide: texturing, texture selection and quad submission.
// Native 465CE has six arguments and buffer +18/+20 accesses, unlike the
// seven-argument Image queue at the currently suggested WB vtable slot.
// Thus the target name stays address-derived. Native adds a half-texel UV
// inset and scales the input alpha by the buffer's +20 factor.
class RectClass {
public:
 RectClass(float l,float t,float r,float b):Left(l),Top(t),Right(r),Bottom(b){}
 float Left,Top,Right,Bottom;
};
class TextureClass;
template<class T> class RefCountPtr;
class Rva000425CB {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual bool slot6(); virtual void slot7(); virtual void slot8();
 virtual const RefCountPtr<TextureClass> *texture();
 float rva000425CB(); float rva00042605();
 char pad04[0x18-4]; unsigned int textureHeight18;
};
class Rva000465CEBuffer : public Rva000425CB {
public:
 char pad1C[4]; float alpha20;
};
class Rva000456C9 { public: void rva000456C9(const RefCountPtr<TextureClass> *); };
class Render2DClass {
public:
 void Add_Quad(const RectClass &,const RectClass &,unsigned long,unsigned long,unsigned long,unsigned long);
 char pad00[0x48]; bool texturing48;
};
class W3DDisplay {
public:
 void rva000465CE(Rva000465CEBuffer *buffer,float x0,float y0,float x1,float y1,int color);
 char pad00[0x168]; Render2DClass *render168;
};
void W3DDisplay::rva000465CE(Rva000465CEBuffer *buffer,float x0,float y0,float x1,float y1,int color)
{
 float inset = (1.0f / (float)buffer->textureHeight18) * 0.5f;
 render168->texturing48 = true;
 ((Rva000456C9 *)render168)->rva000456C9(buffer->texture());
 RectClass uv(inset,inset,buffer->rva000425CB()-inset,buffer->rva00042605()-inset);
 unsigned int alpha = (color >> 24) & 0xff;
 color = (color & 0xffffff) | ((unsigned int)((float)alpha * buffer->alpha20) << 24);
 render168->Add_Quad(RectClass(x0,y0,x1,y1),uv,color,color,color,color);
}
