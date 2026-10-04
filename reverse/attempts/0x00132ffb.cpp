// ?Load_Texture@@YA?AVBFME2ParticleTextureHandle@@AAVChunkLoadClass@@@Z
// partial score=0.8 date=2026-10-04
// cl: /O1 /Ob1 /DNDEBUG /MD /EHsc
// Reference reconstruction of native 0x00132FFB..0x00133283 (648 bytes).
// Primary source: GeneralsMD WW3D2/texture.cpp Load_Texture, through
// Open-BFME-1 6583b3c1ff. Target establishes the hidden handle return,
// .tga -> .dds -> .jpg registry fallback, caps offsets, and reference lifetime.
// All real calls resolve except SetMip: native 0x0013ED10 is the already-rowed
// 10-byte ICF store of arg1 to this+8 (currently named ios_base::_M_clear_nothrow).
// The /alternatename below supplies link closure; byte resolution still needs
// an independently checked SetMip pin if this attempt is continued.
// Remaining shape: retail homes no_lod at EBP-0xD, mipcount in EBX and zero
// in EDI; this version holds no_lod in BL and mipcount in EDI. The first
// 316 bytes and the complete filename fallback match. G7 unchanged;
// volatile no_lod expands to 651 bytes; uninitialized mipcount gives 644.
#include <string.h>
class ChunkLoadClass {
public:
 bool Open_Chunk(); bool Close_Chunk(); unsigned long Cur_Chunk_ID();
 unsigned long Cur_Chunk_Length(); unsigned long Read(void *, unsigned long);
};
class TextureClass {
public:
 virtual void slot00();
 unsigned short refs, pad;
 void Release_Ref();
};
class BFME2ParticleTextureHandle {
public:
 TextureClass *p;
 BFME2ParticleTextureHandle() : p(0) {}
 BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &other) : p(other.p) { if(p) ++p->refs; }
 ~BFME2ParticleTextureHandle() { if(p) p->Release_Ref(); }
};
extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, int, int);
bool Render_Obj_Exists(const char *);
enum WW3DFormat { WW3D_FORMAT_UNKNOWN=0 };
class W3DRadarFormatCaps {
public:
 char before[0x13c]; bool bump;
 bool supportTextureFormat(WW3DFormat);
};
extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;
#pragma comment(linker, "/alternatename:?TheW3DRadarFormatCaps@@3PAVW3DRadarFormatCaps@@A=?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A")
extern bool TextureDeviceInitted;
#pragma comment(linker, "/alternatename:?TextureDeviceInitted@@3_NA=?IsInitted@DX8Wrapper@@1_NA")
class ShroudFilter {
public:
 int unused[2], mip, u, v;
 void SetMip(int);
};
#pragma comment(linker, "/alternatename:?SetMip@ShroudFilter@@QAEXH@Z=?_M_clear_nothrow@ios_base@_STL@@IAEXH@Z")
class ShroudTexture {
public: ShroudFilter *getFilter();
};
struct TextureInfo { unsigned short Attributes, AnimType; unsigned int FrameCount; float FrameRate; };
BFME2ParticleTextureHandle Load_Texture(ChunkLoadClass &cload)
{
 char name[256];
 if(cload.Open_Chunk() && cload.Cur_Chunk_ID()==0x31) {
  TextureInfo texinfo;
  bool hastexinfo=false;
  name[0]=0;
  while(cload.Open_Chunk()) {
   switch(cload.Cur_Chunk_ID()) {
    case 0x32: cload.Read(name,cload.Cur_Chunk_Length()); break;
    case 0x33: cload.Read(&texinfo,sizeof(texinfo)); hastexinfo=true; break;
   }
   cload.Close_Chunk();
  }
  cload.Close_Chunk();
  char *ext=strrchr(name,'.');
  if(ext && !_stricmp(ext,".tga")) {
   char alternate[256];
   strcpy(alternate,name);
   char *altExt=alternate+(ext-name);
   strcpy(altExt,".dds");
   if(!Render_Obj_Exists(alternate)) {
    strcpy(altExt,".jpg");
    if(!Render_Obj_Exists(alternate)) goto keep_name;
   }
   strcpy(name,alternate);
  }
keep_name:
  if(hastexinfo) {
   int mipcount=4;
   bool no_lod=(texinfo.Attributes&4)==4;
   if(no_lod) mipcount=1;
   else switch(texinfo.Attributes&0xc0) {
    case 0: mipcount=0;break;
    case 0x40: mipcount=2;break;
    case 0x80: mipcount=3;break;
    case 0xc0: break;
    default:mipcount=0;break;
   }
   int format=0;
   if((texinfo.Attributes&0x1000) && TextureDeviceInitted && TheW3DRadarFormatCaps->bump) {
    mipcount=1;
    if(TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)60)) format=60;
    else if(TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)62)) format=62;
    else if(TheW3DRadarFormatCaps->supportTextureFormat((WW3DFormat)61)) format=61;
   }
   BFME2ParticleTextureHandle tex=BFME2LoadParticleTexture(name,mipcount,format);
   if(no_lod) reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->SetMip(0);
   bool u=(texinfo.Attributes&8)!=0;
   reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->u=u?1:0;
   bool v=(texinfo.Attributes&16)!=0;
   reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->v=v?1:0;
   return tex;
  } else return BFME2LoadParticleTexture(name,0,0);
 }
 return BFME2ParticleTextureHandle();
}
