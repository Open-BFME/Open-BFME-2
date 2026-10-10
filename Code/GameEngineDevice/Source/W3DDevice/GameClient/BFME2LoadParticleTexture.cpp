// cl: /Ob1 /DNDEBUG /MD /EHsc
//
// ?BFME2LoadParticleTexture@@YA?AVBFME2ParticleTextureHandle@@PBDHH@Z
// Retail 0x00132D89, 237 bytes. Target disassembly shows a name lookup at
// 0x0061F230, typed-ref conversion at 0x00131DCB, and, on a miss, a 0x3C-byte
// allocation/filename ctor at 0x00132D43 followed by Add_Prototype at
// 0x0061EF90. The two option dwords are stored at object +0x30/+0x34. The
// helper class identities at 0x00131DCB and 0x00132D43 remain address-derived.

#include "BFME2ParticleTextureHandles.h"

template<class T> inline RefCountPtr<T>::~RefCountPtr() { if (Ptr) Ptr->Release_Ref(); }
class BfmeThingSJ : public TextureClass
{
public:
	BfmeThingSJ(int val);
};

extern const void *const g_00BD2690[];

class HierarchyPrototypeRef
{
public:
	HierarchyPrototypeRef() : m_object(0) {}
	HierarchyPrototypeRef(const HierarchyPrototypeRef &that)
		: m_object(that.m_object)
	{
		if (m_object)
			++*(unsigned short *)((char *)m_object + 4);
	}
	~HierarchyPrototypeRef()
	{
		if (m_object)
			((TextureClass *)m_object)->Release_Ref();
	}

	void *m_object;
};

extern HierarchyPrototypeRef Rva0061F230_GetPrototype(const char *name);

struct BfmeResetTagged
{
	virtual int pad00();
	virtual int pad01();
	virtual int pad02();
	virtual int pad03();
	virtual int pad04();
	virtual int pad05();
	virtual int pad06();
	virtual int pad07();
	virtual int pad08();
	virtual int pad09();
	virtual int pad10();
	virtual int pad11();
	virtual int pad12();
	virtual unsigned GetClassId();
};

struct BfmeResetAnyRef
{
	BfmeResetTagged *pointer;
};

struct BfmeResetTextureRef
{
	void *pointer;
	BfmeResetTextureRef &operator=(const BfmeResetAnyRef &rhs);
};

// This opaque wrapper uses the 0x131DCB ctor-shaped helper. Its one-dword
// layout and the subsequent assignment at 0x131D99 follow the target calls.
class Rva00131DCBTextureRef : public RefCountPtr<TextureClass>
{
public:
	Rva00131DCBTextureRef(const BfmeResetAnyRef &rhs);
	__forceinline ~Rva00131DCBTextureRef() {}
};

class Rva00132D43TextureCtor : public BfmeThingSJ
{
	unsigned char m_pad08[0x28];

public:
	int m_option0;
	int m_option1;
	int m_pad38;
	Rva00132D43TextureCtor(const char *filename);
};

extern void Add_Prototype(void *prototype);

Rva00132D43TextureCtor::Rva00132D43TextureCtor(const char *filename)
	: BfmeThingSJ((int)filename)
{
	*(const void **)this = g_00BD2690;
}

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(
	const char *filename, int option0, int option1)
{
	if (!filename)
		return BFME2ParticleTextureHandle();

	Rva00131DCBTextureRef texture(
		(const BfmeResetAnyRef &)Rva0061F230_GetPrototype(filename));
	if (!texture.Ptr)
	{
		Add_Prototype(new Rva00132D43TextureCtor(filename));
		*reinterpret_cast<BfmeResetTextureRef *>(&texture) =
			(const BfmeResetAnyRef &)Rva0061F230_GetPrototype(filename);
	}
	else
	{
		Rva00132D43TextureCtor *resource =
			(Rva00132D43TextureCtor *)texture.Ptr;
		resource->m_option0 = option0;
		((Rva00132D43TextureCtor *)texture.Ptr)->m_option1 = option1;
	}
	return BFME2ParticleTextureHandle((TextureClass *)texture.Ptr, BFME2ParticleTextureHandle::ACQUIRE_INLINE);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDoBNH@@YAXPAVBfmeThingBNH@@PAXHH@Z=?BFME2LoadParticleTexture@@YA?AVBFME2ParticleTextureHandle@@PBDHH@Z")

// 0x00131DCB..0x00131DFC: typed owning handle starts empty and delegates to
// the established TEX-tag assignment. Its exception cleanup is the existing
// RefCountPtr<TextureClass> destructor, proving a nontrivial owning base.
Rva00131DCBTextureRef::Rva00131DCBTextureRef(const BfmeResetAnyRef &rhs)
{
	*reinterpret_cast<BfmeResetTextureRef *>(this) = rhs;
}

// Texture chunk loader: WB 0x009D4930 explicitly names TextureAsset::Load
// at texture.cpp:1688..1808. Retail 0x00132FFB..0x00133283 proves the
// cdecl owning hidden return, chunk IDs, filename fallback and filter options.
// Load_Texture is the existing mesh reader's ABI spelling. Its neutral
// BfmeHandleCX pin and BFME2ParticleTextureHandle are established ownership views,
// not a claim about the target's original C++ type names.
// Semantic donor: BFME1 575ba2b04743 game/Libraries/Source/WWVegas/WW3D2/
// texture.cpp Load_Texture (ZH-derived). Target adds DDS/JPG lookup and
// 16-bit references. Unknown class prefixes below are offset views only.
#include <string.h>
class ChunkLoadClass {
public:
 bool Open_Chunk(); bool Close_Chunk(); unsigned long Cur_Chunk_ID();
 unsigned long Cur_Chunk_Length(); unsigned long Read(void *, unsigned long);
};
extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, int, int);
bool Render_Obj_Exists(const char *);
enum WW3DFormat { WW3D_FORMAT_UNKNOWN=0 };
class W3DRadarFormatCaps {
public:
 char before[0x13c]; bool bump;
 bool supportTextureFormat(WW3DFormat);
};
class DX8Caps;
class DX8Wrapper {
protected:
 static DX8Caps *CurrentCaps;
 static bool IsInitted;
 friend BFME2ParticleTextureHandle Load_Texture(ChunkLoadClass &);
};
class ShroudFilter {
public:
 int unused[2], mip, u, v;
 __declspec(noinline) void SetMip(int);
};
// Full 10-byte zero-relocation body at 0x0013ED10 is independently
// verified against every owner extent; its ICF ledger twin records this view.
// ?SetMip@ShroudFilter@@QAEXH@Z
void ShroudFilter::SetMip(int value) { mip=value; }
class ShroudTexture {
public: ShroudFilter *getFilter();
};
struct TextureInfo { unsigned short Attributes, AnimType; unsigned int FrameCount; float FrameRate; };
// ?Load_Texture@@YA?AVBFME2ParticleTextureHandle@@AAVChunkLoadClass@@@Z
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
  if(ext && !_strcmpi(ext,".tga")) {
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
   if((texinfo.Attributes&0x1000) && DX8Wrapper::IsInitted && reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->bump) {
    mipcount=1;
    if(reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)60)) format=60;
    else if(reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)62)) format=62;
    else if(reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)61)) format=61;
   }
   BFME2ParticleTextureHandle tex=BFME2LoadParticleTexture(name,mipcount,format);
   if(no_lod) reinterpret_cast<ShroudTexture*>(&tex)->getFilter()->SetMip(0);
   bool u=(texinfo.Attributes&8)!=0;
   ShroudFilter *ufilter=reinterpret_cast<ShroudTexture*>(&tex)->getFilter();
   ufilter->u=u?1:0;
   bool v=(texinfo.Attributes&16)!=0;
   ShroudFilter *vfilter=reinterpret_cast<ShroudTexture*>(&tex)->getFilter();
   vfilter->v=v?1:0;
   return BFME2ParticleTextureHandle(tex.Ptr, BFME2ParticleTextureHandle::ACQUIRE_INLINE);
  } else {
   // The returned ownership is transferred directly by the shared one-pointer ABI.
   return BFME2LoadParticleTexture(name,0,0);
  }
 }
 return BFME2ParticleTextureHandle();
}
