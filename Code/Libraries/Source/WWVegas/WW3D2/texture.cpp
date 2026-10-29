// cl: /DBFME_WWSTRING_NATIVE_CSTR_CONSTRUCTOR /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme_dx8wrapper_home_link /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ob1
// stlport

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/texture.cpp                            $*
 *                                                                                             *
 *                  $Org Author:: Steve_t                                                     $*
 *                                                                                             *
 *                       Author : Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 08/05/02 1:27p                                              $*
 *                                                                                             *
 *                    $Revision:: 85                                                          $*
 *                                                                                             *
 * 06/27/02 KM Texture class abstraction																			*
 * 08/05/02 KM Texture class redesign (revisited)
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   FileListTextureClass::Load_Frame_Surface -- Load source texture                           *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "texture.h"

#include <d3d8.h>
#include <stdio.h>
#include <D3dx8core.h>
#include "dx8wrapper.h"
#include "targa.h"
#include <nstrdup.h>
#include "w3d_file.h"
#include "assetmgr.h"
#include "formconv.h"
#include "textureloader.h"
#include "missingtexture.h"
#include "ffactory.h"
#include "dx8caps.h"
#include "dx8texman.h"
#include "meshmatdesc.h"
#include "texturethumbnail.h"
#include "wwprofile.h"

//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")

// Zero Hour's texture creation, loading, invalidation and statistics ports had no
// BFME 2 caller here and were removed (docs/linking_obstacles.md, LINK-004 texture).



//**********************************************************************************************
//! Returns a pointer to the d3d texture
/*! 
*/
namespace
{
class BFMETextureBaseVirtuals
{
public:
    virtual void Slot_0() = 0;
    virtual void Slot_1() = 0;
    virtual void Slot_2() = 0;
    virtual void Slot_3() = 0;
    virtual void Slot_4() = 0;
    virtual void Slot_5() = 0;
    virtual void Slot_6() = 0;
    virtual void Slot_7() = 0;
    virtual void Slot_8() = 0;
    virtual void Slot_9() = 0;
    virtual bool Is_Initialized() const = 0;
    virtual void Init() = 0;
};

struct BFMED3DTextureHandle
{
    unsigned int Unknown[2];
    IDirect3DBaseTexture8 *Texture;
};
}

IDirect3DBaseTexture8 *TextureBaseClass::Peek_D3D_Base_Texture() const
{
    BFMETextureBaseVirtuals *texture =
        *(BFMETextureBaseVirtuals *const *)this;
    if (texture == 0) {
        return 0;
    }

    if (!texture->Is_Initialized()) {
        texture->Init();
    }

    BFMED3DTextureHandle *handle =
        *(BFMED3DTextureHandle **)((char *)texture + 0x14);
    return handle->Texture;
}
//**********************************************************************************************
//! Get D3D surface from mip level
/*! 
*/
// ?Get_D3D_Surface_Level@TextureClass@@ present-unmatched
IDirect3DSurface8 *TextureClass::Get_D3D_Surface_Level(unsigned int level)
{
	if (!Peek_D3D_Texture()) 
	{
		WWASSERT_PRINT(0, "Get_D3D_Surface_Level: D3DTexture is NULL!\n");
		return 0;
	}

	IDirect3DSurface8 *d3d_surface = NULL;
	DX8_ErrorCode(Peek_D3D_Texture()->GetSurfaceLevel(level, &d3d_surface));
	return d3d_surface;
}

// Utility function used by Save_Texture
void setup_texture_attributes(TextureClass * tex, W3dTextureInfoStruct * texinfo)
{
	texinfo->Attributes = 0;

	if (tex->Get_Filter().Get_Mip_Mapping() == TextureFilterClass::FILTER_TYPE_NONE) texinfo->Attributes |= W3DTEXTURE_NO_LOD;
	if (tex->Get_Filter().Get_U_Addr_Mode() == TextureFilterClass::TEXTURE_ADDRESS_CLAMP) texinfo->Attributes |= W3DTEXTURE_CLAMP_U;
	if (tex->Get_Filter().Get_V_Addr_Mode() == TextureFilterClass::TEXTURE_ADDRESS_CLAMP) texinfo->Attributes |= W3DTEXTURE_CLAMP_V;
}


void Save_Texture(TextureClass * texture,ChunkSaveClass & csave)
{
	const char * filename;
	W3dTextureInfoStruct texinfo;
	memset(&texinfo,0,sizeof(texinfo));

	filename = texture->Get_Full_Path();

	setup_texture_attributes(texture, &texinfo);

	csave.Begin_Chunk(W3D_CHUNK_TEXTURE_NAME);
	csave.Write(filename,strlen(filename)+1);
	csave.End_Chunk();

	if ((texinfo.Attributes != 0) || (texinfo.AnimType != 0) || (texinfo.FrameCount != 0)) {
		csave.Begin_Chunk(W3D_CHUNK_TEXTURE_INFO);
		csave.Write(&texinfo, sizeof(texinfo));
		csave.End_Chunk();
	}
}


// Native recolor ABI view; the address-derived name is retained.
// WB twin 9D2F80 (texture.cpp 1129..1334): the pixel pass is switch(desc.Format)
// {case 21; case 26}; retail lowers it as cmp 15/je, cmp 1A/jne, case-26 fall-in.
// Case 26 follows the WB loops: for(y..,dst+=pitch/2-W,src+=sourcePitch/2-W)
// for(x..,++dst,++src) reading *src; cl hoists sourcePitch/2 (sar in memory).
// Visible byte-exact setter, getter and dispatcher fix the allocation; the volatile count reference
// reproduces retail's in-memory store and AND, which keeps every frame home (0x001321a7-20261019-w5-resume.md).
#include <string.h>
#include <new>
struct TextureRecolorGUID
{
 unsigned long a;
 unsigned short b,c;
 unsigned char d[8];

};
// Read directly from native VA 0x00CE0AD8; IID_IDirect3DTexture9.
static const TextureRecolorGUID TextureRecolorIID=
{
 0x85c31227,0x3de5,0x4f00,
 {
  0x9b,0x3a,0xf1,0x1a,0xc3,0x8c,0x18,0xb5
 }

};
struct TextureRecolorCOM;
class SurfaceResource;
struct TextureRecolorCOM
{
 virtual long __stdcall QueryInterface(const TextureRecolorGUID &,void **)=0;
 virtual unsigned long __stdcall AddRef()=0;
 virtual unsigned long __stdcall Release()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual long __stdcall GetSurfaceLevel(unsigned,SurfaceResource **)=0;

};
class SurfaceResource
{
 public:
 virtual long __stdcall QueryInterface(const TextureRecolorGUID &,void **)=0;
 virtual unsigned long __stdcall AddRef()=0;
 virtual unsigned long __stdcall Release()=0;

};
class W3DRadarResetSurface
{
 public:
 SurfaceResource *m_surface;
 W3DRadarResetSurface(SurfaceResource *);
 ~W3DRadarResetSurface();

};
class Rva00116680
{
 public:void *rva00116680(int *,bool);

};
class Member0C00739C70
{
 public:void clear();

};
struct TextureRecolorSurfaceLock
{
 W3DRadarResetSurface &surface;
 TextureRecolorSurfaceLock(W3DRadarResetSurface &w3DRadarResetSurface,void *&bits,int &pitch,bool discard):surface(w3DRadarResetSurface)
 {
  bits=reinterpret_cast<Rva00116680 *>(&w3DRadarResetSurface)->rva00116680(&pitch,discard);

 }
 ~TextureRecolorSurfaceLock()
 {
  reinterpret_cast<Member0C00739C70 *>(&surface)->clear();

 }

};
void Log_DX8_ErrorCode(unsigned);
struct TextureRecolorFlags
{
 unsigned bits;
 __forceinline unsigned count() const
 {
  return bits&7;

 }
 __forceinline bool dynamic() const
 {
  return ((bits>>30)&1)!=0;

 }

};
class Rva000B4653
{
 public:
 TextureRecolorFlags flags;
 void *rva000B4653(int);

};
class Rva00131D7D
{
 public:
 void rva00131D7D(unsigned);
 int red,green,blue;

};
struct TextureRecolorImpl
{
 unsigned char prefix[8];
 TextureRecolorCOM *texture;
 unsigned type;

};
class BfmeThing937B
{
 unsigned char prefix[0x14];
 TextureRecolorImpl *impl;
 unsigned char unused18[0x28];
 TextureRecolorFlags flags;
 unsigned char unused44[0xC];
 unsigned char *dynamicSource;
 public:
 void rva001321A7(void *);

};
static __forceinline const unsigned &TextureRecolorMin(const unsigned &a,const unsigned &b)
{
 return b<a?b:a;

}
inline __declspec(noinline) void Rva00131D7D::rva00131D7D(unsigned c)
{
 red=(c>>16)&255;
 green=(c>>8)&255;
 blue=c&255;
}
class Rva000B2361 { public: int *rva000B2361(int); int m_00,m_04,m_08,m_0C; };
inline __declspec(noinline) int *Rva000B2361::rva000B2361(int which)
{
 switch(which) { case 0: return &m_04; case 1: return &m_08; case 2: return &m_0C; default: return &m_04; }
}
inline __declspec(noinline) void *Rva000B4653::rva000B4653(int a)
{
 if((unsigned)a<flags.count())
  return *reinterpret_cast<void **>(reinterpret_cast<Rva000B2361 *>(this)->rva000B2361(a));
 return 0;
}
void BfmeThing937B::rva001321A7(void *settings)

{
 if(!impl || !impl->texture || impl->type!=0)return;
 TextureRecolorCOM *texture=0;
 if(impl->texture->QueryInterface(TextureRecolorIID,reinterpret_cast<void **>(&texture))<0 || !texture)return;
 SurfaceResource *surface=0;
 long hr=texture->GetSurfaceLevel(0,&surface);
 if(hr!=0)Log_DX8_ErrorCode(hr);
 W3DRadarResetSurface holder(surface);
 if(surface)surface->Release();
 texture->Release();
 texture=0;
 void *bits=0;
 int pitch=0;

 {
  TextureRecolorSurfaceLock lock(holder,bits,pitch,false);
  SurfaceClass::SurfaceDescription desc;
  reinterpret_cast<SurfaceClass *>(&holder)->Get_Description(desc);
  Rva000B4653 *options;
  unsigned pixelSize=0;
  if(desc.Format==21)pixelSize=4;
  else if(desc.Format==26)pixelSize=2;
  if(!pixelSize)goto captureReturn;
  options=reinterpret_cast<Rva000B4653 *>(settings);
  if(options->flags.dynamic() && !dynamicSource)
  {
   dynamicSource=new unsigned char[desc.Height*desc.Width*pixelSize];
   if(!dynamicSource)goto captureReturn;
   for(unsigned y=0;y<desc.Height;++y)
   memcpy(dynamicSource+y*desc.Width*pixelSize,reinterpret_cast<unsigned char *>(bits)+y*pitch,desc.Width*pixelSize);
captureReturn:
   return;

  }
  unsigned char *source=0;
  int sourcePitch=0;
  if(flags.dynamic())
  {
   if(!dynamicSource)return;
   source=dynamicSource;
   sourcePitch=desc.Width*pixelSize;

  }
  else
  {
   source=reinterpret_cast<unsigned char *>(bits);
   sourcePitch=pitch;

  }
  unsigned count;
  // These are the count store and in-memory mask used by retail.
  volatile unsigned &mask=count;
  mask=options->flags.bits;
  unsigned i=0;
  Rva00131D7D colors[3];
  if(0U<(mask&=7))
  {
   do
   {
    colors[i].rva00131D7D(reinterpret_cast<unsigned>(options->rva000B4653(i)));
    ++i;
   } while(i<count);
  }
  switch(desc.Format)
  {
  case 21:
  {
   unsigned char *src=source;
   unsigned char *dst=reinterpret_cast<unsigned char *>(bits);
   int srcGap=sourcePitch-desc.Width*4;
   int dstGap = pitch-desc.Width*4;
   switch(count)
   {
    case 0:
    for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
    for(unsigned x=desc.Width;x;--x,src+=4,dst+=4)
    *reinterpret_cast<unsigned *>(dst)=*reinterpret_cast<unsigned *>(src);
    break;
    case 1:
    for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
    for(unsigned x=desc.Width;x;--x,src+=4,dst+=4)
    {
     unsigned red=src[2];
     dst[0]=(red*colors[0].blue)>>8;
     dst[1]=(red*colors[0].green)>>8;
     dst[2]=(red*colors[0].red)>>8;
     dst[3]=src[3];

    }
    break;
    case 2:
    for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
    for(unsigned x=desc.Width;x;--x,src+=4,dst+=4)
    {
     unsigned red=src[2],green=src[1];
     dst[0]=TextureRecolorMin(((red*colors[0].blue)>>8)+((green*colors[1].blue)>>8),255U);
     dst[1]=TextureRecolorMin(((red*colors[0].green)>>8)+((green*colors[1].green)>>8),255U);
     dst[2]=TextureRecolorMin(((red*colors[0].red)>>8)+((green*colors[1].red)>>8),255U);
     dst[3]=src[3];

    }
    break;
    case 3:
    for(unsigned y=desc.Height;y;--y,src+=srcGap,dst+=dstGap)
    for(unsigned x=desc.Width;x;--x,src+=4,dst+=4)
    {
     unsigned red=src[2],green=src[1],blue=src[0];
     dst[0]=TextureRecolorMin(((blue*colors[2].blue)>>8)+((green*colors[1].blue)>>8)+((red*colors[0].blue)>>8),255U);
     dst[1]=TextureRecolorMin(((blue*colors[2].green)>>8)+((green*colors[1].green)>>8)+((red*colors[0].green)>>8),255U);
     dst[2]=TextureRecolorMin(((blue*colors[2].red)>>8)+((green*colors[1].red)>>8)+((red*colors[0].red)>>8),255U);
     dst[3]=src[3];

    }
    break;

   }

  }
  break;
  case 26:
  {
   unsigned short *dst=reinterpret_cast<unsigned short *>(bits);
   unsigned short *src=reinterpret_cast<unsigned short *>(source);
   for(unsigned y=desc.Height;y;--y,dst+=pitch/2-desc.Width,src+=sourcePitch/2-desc.Width)
   for(unsigned x=desc.Width;x;--x,++dst,++src)
   *dst=static_cast<unsigned short>((*src&0xF000) | (((*src*colors[0].red)/255)&0xF00) |
   (((*src*colors[0].green)/255)&0xF0) | (((*src*colors[0].blue)/255)&0xF));
  }
  break;
  }

 }
 D3DXFilterTexture(reinterpret_cast<IDirect3DTexture8 *>(impl->texture),0,0,-1);

}
