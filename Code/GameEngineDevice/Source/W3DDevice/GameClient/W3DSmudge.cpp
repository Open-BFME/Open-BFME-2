// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/zhmd /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmestages /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudge.cpp); this unit had no counterpart under Code/.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// W3DSmudge.cpp ////////////////////////////////////////////////////////////////////////////////
// Smudge System implementation
// Author: Mark Wilczynski, June 2003
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lib/Basetype.h"
#include "always.h"
#include "W3DDevice/GameClient/W3DSmudge.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "Common/GameMemory.h"
#include "GameClient/view.h"
#include "GameClient/display.h"
#include "WW3D2/texture.h"
#include "WW3D2/dx8indexbuffer.h"
#include "dx8wrapper.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/camera.h"
#include "WW3D2/sortingrenderer.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

SmudgeManager *TheSmudgeManager=NULL;

// W3DSmudgeManager::W3DSmudgeManager: defined in W3DSmudgeManagerConstructor.cpp (its row's unit).

// W3DSmudgeManager destructor is ledgered in this home unit.
W3DSmudgeManager::~W3DSmudgeManager()
{
	ReleaseResources();
}

void W3DSmudgeManager::init(void)
{
	SmudgeManager::init();
	ReAcquireResources();
}

// ?W3DSmudgeManager::reset present-unmatched
void W3DSmudgeManager::reset (void)
{
	SmudgeManager::reset();	//base
}

// W3DSmudgeManager::ReleaseResources: defined in W3DSmudgeManagerReleaseResources.cpp (its row's unit).

//Make sure (SMUDGE_DRAW_SIZE * 12) < 65535 because that's the max index buffer size.
#define SMUDGE_DRAW_SIZE	500	//draw at most 50 smudges per call. Tweak value to improve CPU/GPU parallelism.

// W3DSmudgeManager::ReAcquireResources is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva000A6176Finish.cpp (0x000A6176).

/*Copies a portion of the current render target into a specified buffer*/
Int copyRect(unsigned char *buf, Int bufSize, int oX, int oY, int width, int height)
{
 	IDirect3DSurface8 *surface=NULL;	///<previous render target
 	IDirect3DSurface8 *tempSurface=NULL;
	Int result = 0;
	HRESULT hr = S_OK;

 	LPDIRECT3DDEVICE8 m_pDev=DX8Wrapper::_Get_D3D_Device8();

	if (!m_pDev)
		goto error;

 	m_pDev->GetRenderTarget(&surface);

	if (!surface)
		goto error;

 	D3DSURFACE_DESC desc;
 
 	surface->GetDesc(&desc);
 
	RECT srcRect;
	srcRect.left=oX;
	srcRect.top=oY;
	srcRect.right=oX+width;
	srcRect.bottom=oY+height;

	POINT dstPoint;
	dstPoint.x=0;
	dstPoint.y=0;

 	hr=m_pDev->CreateImageSurface(  width, height, desc.Format, &tempSurface);

	if (hr != S_OK)
		goto error;
 
 	hr=m_pDev->CopyRects(surface,&srcRect,1,tempSurface,&dstPoint);

	if (hr != S_OK)
		goto error;

 	D3DLOCKED_RECT lrect;
 
 	hr=tempSurface->LockRect(&lrect,NULL,D3DLOCK_READONLY);

	if (hr != S_OK)
		goto error;

 	tempSurface->GetDesc(&desc);

	if (desc.Size < bufSize)
		bufSize = desc.Size;
		
	memcpy(buf,lrect.pBits,bufSize);
	result = bufSize;

error:
	if (surface)
		surface->Release();
	if (tempSurface)
		tempSurface->Release();

	return result;
}

#define UNIQUE_COLOR	(0x12345678)
#define BLOCK_SIZE	(8)

// ?W3DSmudgeManager::testHardwareSupport present-unmatched
Bool W3DSmudgeManager::testHardwareSupport(void)
{
	if (m_hardwareSupportStatus == SMUDGE_SUPPORT_UNKNOWN)
	{	//we have not done the test yet.

		IDirect3DTexture8 *backTexture=W3DShaderManager::getRenderTexture();
		if (!backTexture)
		{	//do trivial test first to see if render target exists.
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return FALSE;
		}

		if (!W3DShaderManager::isRenderingToTexture())
			return FALSE;	//can't do the test unless we're rendering to texture.

		VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(vmat);
		REF_PTR_RELEASE(vmat);	//no need to keep a reference since it's a preset.
		
		ShaderClass shader=ShaderClass::_PresetOpaqueShader;
		shader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
		shader.Set_Depth_Mask(ShaderClass::DEPTH_WRITE_DISABLE);
		DX8Wrapper::Set_Shader(shader);
		DX8Wrapper::Set_Texture(0,NULL);
		DX8Wrapper::Apply_Render_State_Changes();	//force update of view and projection matrices

		struct _TRANS_LIT_TEX_VERTEX {
			Vector4 p;
			DWORD color;   // diffuse color    
			float	u;
			float	v;
		} v[4];

		//bottom right
		v[0].p = Vector4( BLOCK_SIZE-0.5f, BLOCK_SIZE-0.5f, 0.0f, 1.0f );
		v[0].u = BLOCK_SIZE/(Real)TheDisplay->getWidth();	v[0].v = BLOCK_SIZE/(Real)TheDisplay->getHeight();;
		//top right
		v[1].p = Vector4( BLOCK_SIZE-0.5f, 0-0.5f, 0.0f, 1.0f );
		v[1].u = BLOCK_SIZE/(Real)TheDisplay->getWidth();	v[1].v = 0;
		//bottom left
		v[2].p = Vector4(  0-0.5f, BLOCK_SIZE-0.5f, 0.0f, 1.0f );
		v[2].u = 0;	v[2].v = BLOCK_SIZE/(Real)TheDisplay->getHeight();
		//top left
		v[3].p = Vector4(  0-0.5f,  0-0.5f, 0.0f, 1.0f );
		v[3].u = 0;	v[3].v = 0;

		v[0].color = UNIQUE_COLOR;
		v[1].color = UNIQUE_COLOR;
		v[2].color = UNIQUE_COLOR;
		v[3].color = UNIQUE_COLOR;

		LPDIRECT3DDEVICE8 pDev=DX8Wrapper::_Get_D3D_Device8();

		//draw polygons like this is very inefficient but for only 2 triangles, it's
		//not worth bothering with index/vertex buffers.
		pDev->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));

		DWORD refData[BLOCK_SIZE*BLOCK_SIZE];
		memset(refData,0,sizeof(refData));
		Int bufSize=copyRect((unsigned char *)refData,sizeof(refData),0,0,BLOCK_SIZE,BLOCK_SIZE);	//copy area we just rendered using solid color
		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return FALSE;
		}

		DX8Wrapper::Set_DX8_Texture(0,backTexture);

		DWORD testData[BLOCK_SIZE*BLOCK_SIZE];
		memset(testData,0xff,sizeof(testData));

		v[0].color = 0xffffffff;
		v[1].color = 0xffffffff;
		v[2].color = 0xffffffff;
		v[3].color = 0xffffffff;

		pDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(_TRANS_LIT_TEX_VERTEX));
		bufSize=copyRect((unsigned char *)testData,sizeof(testData),0,0,BLOCK_SIZE,BLOCK_SIZE);

		if (!bufSize)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
			return FALSE;
		}

		//compare the 2 buffers to see if they match.
		if (memcmp(testData,refData,bufSize) == 0)
		{
			m_hardwareSupportStatus = SMUDGE_SUPPORT_YES;
			return TRUE;
		}
		m_hardwareSupportStatus = SMUDGE_SUPPORT_NO;
	}

	return (SMUDGE_SUPPORT_YES == m_hardwareSupportStatus);
}

// Native render at 0x000A6E08 is owned by W3DSmudgeManagerRender.cpp.
// Its verified BFME2 body replaces this obsolete ZH view, including the
// target GlobalData probe and native matrix / dynamic-VB call boundaries.

// Keep the independently rowed native SmudgeSet successor emitted after
// retiring render; the template uses this unit's established node ABI.
template SmudgeSet *DLNodeClass<SmudgeSet>::Succ(void);
