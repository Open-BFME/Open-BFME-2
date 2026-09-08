// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Ported verbatim from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WW3D2/dx8fvf.cpp); this unit had no counterpart under Code/.
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
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/dx8fvf.h                               $*
 *                                                                                             *
 *              Original Author:: Jani Penttinen                                               *
 *                                                                                             *
 *                      $Author:: Kenny Mitchell                                               * 
 *                                                                                             * 
 *                     $Modtime:: 06/26/02 5:06p                                             $*
 *                                                                                             *
 *                    $Revision:: 7                                                          $*
 *                                                                                             *
 * 06/26/02 KM VB Vertex format update for shaders                                       *
 * 07/17/02 KM VB Vertex format update for displacement mapping                               *
 * 08/01/02 KM VB Vertex format update for cube mapping                               *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "dx8fvf.h"
#include "wwstring.h"
#include <D3dx8core.h>

static unsigned Get_FVF_Vertex_Size(unsigned FVF)
{
	return D3DXGetFVFVertexSize(FVF);
}

// ??0FVFInfoClass@@ present-unmatched
FVFInfoClass::FVFInfoClass(unsigned FVF_, unsigned vertex_size) 
	:
	FVF(FVF_),
	fvf_size(FVF!=0 ? Get_FVF_Vertex_Size(FVF) : vertex_size)
{
	location_offset=0;
	blend_offset=location_offset;
	
	if ((FVF&D3DFVF_XYZ)==D3DFVF_XYZ) blend_offset+=3*sizeof(float);
	normal_offset=blend_offset;

	if ( ((FVF&D3DFVF_XYZB4)==D3DFVF_XYZB4) &&
		  ((FVF&D3DFVF_LASTBETA_UBYTE4)==D3DFVF_LASTBETA_UBYTE4) ) normal_offset+=3*sizeof(float)+sizeof(DWORD);
	diffuse_offset=normal_offset;

	if ((FVF&D3DFVF_NORMAL)==D3DFVF_NORMAL) diffuse_offset+=3*sizeof(float);
	specular_offset=diffuse_offset;

	if ((FVF&D3DFVF_DIFFUSE)==D3DFVF_DIFFUSE) specular_offset+=sizeof(DWORD);
	texcoord_offset[0]=specular_offset;

	if ((FVF&D3DFVF_SPECULAR)==D3DFVF_SPECULAR) texcoord_offset[0]+=sizeof(DWORD);	

	for (unsigned int i=1; i<D3DDP_MAXTEXCOORD; i++)
	{
		texcoord_offset[i]=texcoord_offset[i-1];

		if ((int(FVF)&D3DFVF_TEXCOORDSIZE1(i-1))==D3DFVF_TEXCOORDSIZE1(i-1)) texcoord_offset[i]+=sizeof(float);
		else if ((int(FVF)&D3DFVF_TEXCOORDSIZE2(i-1))==D3DFVF_TEXCOORDSIZE2(i-1)) texcoord_offset[i]+=2*sizeof(float);
		else if ((int(FVF)&D3DFVF_TEXCOORDSIZE3(i-1))==D3DFVF_TEXCOORDSIZE3(i-1)) texcoord_offset[i]+=3*sizeof(float);
		else if ((int(FVF)&D3DFVF_TEXCOORDSIZE4(i-1))==D3DFVF_TEXCOORDSIZE4(i-1)) texcoord_offset[i]+=4*sizeof(float);
	}
}

void FVFInfoClass::Get_FVF_Name(StringClass& fvfname) const
{
	switch (Get_FVF()) {
	case DX8_FVF_XYZ: fvfname="D3DFVF_XYZ"; break;
	case DX8_FVF_XYZN: fvfname="D3DFVF_XYZ|D3DFVF_NORMAL"; break;
	case DX8_FVF_XYZNUV1: fvfname="D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1"; break;
	case DX8_FVF_XYZNUV2: fvfname="D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2"; break;
	case DX8_FVF_XYZNDUV1: fvfname="D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1|D3DFVF_DIFFUSE"; break;
	case DX8_FVF_XYZNDUV2: fvfname="D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX2|D3DFVF_DIFFUSE"; break;
	case DX8_FVF_XYZDUV1: fvfname="D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE"; break;
	case DX8_FVF_XYZDUV2: fvfname="D3DFVF_XYZ|D3DFVF_TEX2|D3DFVF_DIFFUSE"; break;
	case DX8_FVF_XYZUV1: fvfname="D3DFVF_XYZ|D3DFVF_TEX1"; break;
	case DX8_FVF_XYZUV2: fvfname="D3DFVF_XYZ|D3DFVF_TEX2"; break;
	case DX8_FVF_XYZNDUV1TG3 : fvfname="(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX4|D3DFVF_TEXCOORDSIZE2(0)|D3DFVF_TEXCOORDSIZE3(1)|D3DFVF_TEXCOORDSIZE3(2)|D3DFVF_TEXCOORDSIZE3(3))"; break;
	case DX8_FVF_XYZNUV2DMAP :	fvfname="(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX3|D3DFVF_TEXCOORDSIZE1(0)|D3DFVF_TEXCOORDSIZE4(1)|D3DFVF_TEXCOORDSIZE2(2))"; break;
	case DX8_FVF_XYZNDCUBEMAP : fvfname="(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVFTEXCOORDSIZE3(0)"; break;
	default: fvfname="Unknown!";
	}
}

// BFME2's extended descriptor is a distinct 96-byte layout. The retained
// Generals FVFInfoClass above has the older layout and two-argument constructor.
// Recovered roles and complete caller/table evidence are documented in
// docs/reconstruction/dx8fvf-descriptor.md.
// The bundled original DX8.1 SDK d3d8types.h defines XYZB4 as 0x00C.
// Keep that SDK value explicit here while the shared shim is repaired.
enum { BFME_FVF_XYZB4 = 0x00C };
unsigned bfmeKnownFVFFormats[15]={
 DX8_FVF_XYZ,DX8_FVF_XYZN,DX8_FVF_XYZNUV1,DX8_FVF_XYZNUV2,
 DX8_FVF_XYZNDUV1,DX8_FVF_XYZNDUV2,DX8_FVF_XYZDUV1,DX8_FVF_XYZDUV2,
 DX8_FVF_XYZUV1,DX8_FVF_XYZUV2,DX8_FVF_XYZNDUV1TG3,DX8_FVF_XYZNUV2DMAP,
 DX8_FVF_XYZNDCUBEMAP,D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX3,
 D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX4
};
struct BfmeFVFDescriptor {
 unsigned fvf;                       // 0x00
 bool additionalBasis;              // 0x04
 unsigned extensionCount;           // 0x08
 unsigned stride;                   // 0x0C
 unsigned locationOffset;           // 0x10
 unsigned extensionOffset;          // 0x14
 unsigned normalOffset;             // 0x18
 unsigned extensionEnd;             // 0x1C
 unsigned blendOffset;              // 0x20
 unsigned textureOffsets[8];        // 0x24
 unsigned diffuseOffset;            // 0x44
 unsigned specularOffset;           // 0x48
 unsigned basisOffset;              // 0x4C
 unsigned basisSecondOffset;        // 0x50
 unsigned basisEnd;                 // 0x54
 unsigned extensionDataOffset;      // 0x58
 unsigned formatIndex;              // 0x5C
 void Initialize(unsigned,unsigned,bool,unsigned);
};
typedef char BfmeFVFDescriptorSize[(sizeof(BfmeFVFDescriptor)==96)?1:-1];
void BfmeFVFDescriptor::Initialize(unsigned format,unsigned vertex_size,bool basis,unsigned count)
{
 fvf=format;
 additionalBasis=basis;
 extensionCount=count;
 if(fvf) {
  stride=D3DXGetFVFVertexSize(fvf);
  if(basis) stride+=6*sizeof(float);
  if(count>0) {
   stride+=((count+3)/4)*sizeof(unsigned);
   if(count>1) stride+=(count+(count-1)*6)*sizeof(float);
  }
 } else stride=vertex_size;
 locationOffset=0;
 blendOffset=locationOffset;
 if((fvf&D3DFVF_XYZ)==D3DFVF_XYZ) blendOffset+=3*sizeof(float);
 normalOffset=blendOffset;
 if(((fvf&BFME_FVF_XYZB4)==BFME_FVF_XYZB4) && ((fvf&D3DFVF_LASTBETA_UBYTE4)==D3DFVF_LASTBETA_UBYTE4)) normalOffset+=3*sizeof(float)+sizeof(unsigned);
 diffuseOffset=normalOffset;
 if((fvf&D3DFVF_NORMAL)==D3DFVF_NORMAL) diffuseOffset+=3*sizeof(float);
 specularOffset=diffuseOffset;
 if((fvf&D3DFVF_DIFFUSE)==D3DFVF_DIFFUSE) specularOffset+=sizeof(unsigned);
 textureOffsets[0]=specularOffset;
 if((fvf&D3DFVF_SPECULAR)==D3DFVF_SPECULAR) textureOffsets[0]+=sizeof(unsigned);
 unsigned textureCount=(fvf>>8)&15;
 for(unsigned i=0;i<8;++i) {
  unsigned size=0;
  unsigned code=(fvf>>(16+i*2))&3;
  if(i<textureCount) {
   if(code==3) size=1;
   else if(code==0) size=2;
   else if(code==1) size=3;
   else if(code==2) size=4;
  }
  unsigned next=textureOffsets[i]+size*sizeof(float);
  if(i+1<8) textureOffsets[i+1]=next;else basisOffset=next;
 }
 basisSecondOffset=basisOffset;
 basisEnd=basisOffset;
 if(basis) {basisSecondOffset+=3*sizeof(float);basisEnd=basisSecondOffset+3*sizeof(float);}
 extensionDataOffset=basisEnd+((count+3)/4)*sizeof(unsigned);
 extensionOffset=extensionDataOffset+(count>1?count:0)*sizeof(float);
 extensionEnd=extensionOffset+(count>1?3:0)*sizeof(float);
 formatIndex=15;
 if(!additionalBasis && extensionCount==0) {
  for(int i=0;i<15;++i) if(fvf==bfmeKnownFVFFormats[i]) formatIndex=i;
 }
}
