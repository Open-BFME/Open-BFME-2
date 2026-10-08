// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/projectedshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

;////////////////////////////////////////////////////////////////////////////////
;//																																						 //
;//  (c) 2001-2003 Electronic Arts Inc.																				 //
;//																																						 //
;////////////////////////////////////////////////////////////////////////////////

// FILE: W3DTextureShadow.cpp ///////////////////////////////////////////////////////////
//
// Texture based shadow representation.
//
// Author: Mark Wilczynski, February 2002
//
//
///////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "always.h"
// Pull in the shim RenderObjClass (BFME vtable layout stubs) before any WW3D2
// header grabs the ZH reference rendobj.h; both share include guard RENDOBJ_H.
#include "rendobj.h"
#include "GameClient/View.h"
#include "WW3D2/Camera.h"
#include "WW3D2/Light.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/HLod.h"
#include "WW3D2/mesh.h"
#include "WW3D2/meshmdl.h"
#include "WW3D2/assetmgr.h"
#include "WW3D2/texproject.h"
#include "WW3D2/dx8renderer.h"
#include "Lib/BaseType.h"
#include "W3DDevice/GameClient/W3DGranny.h"
#include "W3DDevice/GameClient/Heightmap.h"
#include "D3dx8math.h"
#include "common/GlobalData.h"
#include "W3DDevice/GameClient/W3DProjectedShadow.h"
#include "WW3D2/statistics.h"
#include "Common/Debug.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameClient/drawable.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/Heightmap.h"

// ?setDecalUVAxis@W3DShadowTexture@@QAEXAAVVector3@@0@Z
// retail 0x00108603, 57 bytes. Dedicated TU carrying the Open-BFME-1 donor
// preamble (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/
// W3DProjectedShadow.cpp, reference/open-bfme-1) and only this body; the
// donor's other definitions are omitted. Compiled /Os the donor emits it
// byte-identical to retail (unique masked placement on unclaimed .text).
//
// m_shadowUV[0] sits at this+0x8c and m_shadowUV[1] at this+0x98, which is
// what fixes the two 12-byte Vector3 copies the retail body performs.

class W3DShadowTexture : public RefCountClass, public	HashableClass
{

	public:

		W3DShadowTexture( void )
		{	m_lastLightPosition.Set(0,0,0); m_lastObjectOrientation.Make_Identity();
			m_shadowUV[0].Set(1.0f,0.0f,0.0f);	//u runs along world x axis
			m_shadowUV[1].Set(0.0f,-1.0f,0.0f);	//v runs along world -y axis
		}
		~W3DShadowTexture( void ) { REF_PTR_RELEASE(m_texture);}

		virtual	const char * Get_Key( void )	{ return m_namebuf;	}

		Int init (RenderObjClass *robj);

		const char *	Get_Name(void) const	{ return m_namebuf;}
		void			Set_Name(const char *name)
		{	memset(m_namebuf,0,sizeof(m_namebuf));	//pad with zero so always ends with null character.
			strncpy(m_namebuf,name,sizeof(m_namebuf)-1);
		}
		TextureClass	*getTexture(void)	{ return m_texture;}
		void			setTexture(TextureClass *texture)	{m_texture = texture;}
		void			setLightPosHistory(Vector3 &pos) {m_lastLightPosition=pos;}	///<updates the last position of light
		Vector3&		getLightPosHistory(void) {return m_lastLightPosition;}
		void			setObjectOrientationHistory(Matrix3x3 &mat) {m_lastObjectOrientation=mat;}	///<updates the last position of light
		Matrix3x3&		getObjectOrientationHistory(void) {return m_lastObjectOrientation;}
		SphereClass&	getBoundingSphere(void)	{return m_areaEffectSphere;}
		AABoxClass&		getBoundingBox(void)		{return m_areaEffectBox;}
		void		setBoundingSphere(SphereClass &sphere)	{m_areaEffectSphere=sphere;}
		void		setBoundingBox(AABoxClass &box)		{m_areaEffectBox=box;}
		void		updateBounds(Vector3 &lightPos, RenderObjClass *robj);	///<update extent of shadow
		void		setDecalUVAxis(Vector3 &u, Vector3 &v);
		void		getDecalUVAxis(Vector3 *u, Vector3 *v)	{ *u=m_shadowUV[0]; *v=m_shadowUV[1];}

	private:

		char m_namebuf[2*W3D_NAME_LEN];	///<name of model hierarchy

		TextureClass *m_texture; ///<texture holding the shadow for this renderobject
		Vector3		m_lastLightPosition;		///<position of light source at time of last texture update.
		Matrix3x3	m_lastObjectOrientation;	///<orientation of shadow casting object when texture was generated.
		AABoxClass	m_areaEffectBox;			///<boundary defining object-space volume affected by shadow.
		SphereClass	m_areaEffectSphere;			///<boundary defining object-space volume affected by shadow.
		Vector3		m_shadowUV[2];		///<world-space vectors defining the u and v texture coordinate axis.
};

void W3DShadowTexture::setDecalUVAxis(Vector3 &u, Vector3 &v)
{
	m_shadowUV[0]=u;
	m_shadowUV[1]=v;
}

// Ghidra boundary at 0x00109236 is 131 bytes. Retail clears three linked
// heads at +0x04/+0x08/+0x0C; each node's link is at +0x114 and each payload
// is released through slot 0 with flag 0, followed by scalar operator delete.
// It then clears +0x250 and tail-calls the already matched 0x00108842 body.
// The TU placement follows the recovered W3DProjectedShadow source family,
// but this body's class owner and higher-level purpose remain unproven, so the
// method keeps an address-derived name. The 0x00108842 identity is donor-derived;
// only its call target and ABI are facts established from this retail body.
struct Rva00109236Node
{
	virtual void *deleteInstance(int flags);
	char m_pad04[0x110];
	Rva00109236Node *m_next114;
};

class BfmeThing928F
{
public:
	void bfmeTwo928F();
};

class Rva00109236
{
	char m_pad00[4];
	Rva00109236Node *m_head04;
	Rva00109236Node *m_head08;
	Rva00109236Node *m_head0C;
	char m_pad10[0x240];
	int m_value250;

public:
	void rva00109236();
};

void __cdecl operator delete(void *pointer);

void Rva00109236::rva00109236()
{
	Rva00109236Node *cursor = m_head0C;
	m_head0C = 0;
	Rva00109236Node *current;
	goto check0C;
loop0C:
	{
		Rva00109236Node *&link = cursor->m_next114;
		cursor = link;
		link = 0;
		::operator delete(current->deleteInstance(0));
	}
check0C:
	current = cursor;
	if (cursor != 0) goto loop0C;

	cursor = m_head04;
	m_head04 = 0;
	goto check04;
loop04:
	{
		Rva00109236Node *&link = cursor->m_next114;
		cursor = link;
		link = 0;
		::operator delete(current->deleteInstance(0));
	}
check04:
	current = cursor;
	if (cursor != 0) goto loop04;

	cursor = m_head08;
	m_head08 = 0;
	goto check08;
loop08:
	{
		Rva00109236Node *&link = cursor->m_next114;
		cursor = link;
		link = 0;
		::operator delete(current->deleteInstance(0));
	}
check08:
	current = cursor;
	if (cursor != 0) goto loop08;
	m_value250 = 0;
	((BfmeThing928F *)this)->bfmeTwo928F();
}

// Native 10C578..10C6C4; WB8D61F0 independently names addShadow.
// ZH W3DProjectedShadow.cpp supplies the size/offset semantics; BFME2 uses
// its string handle, force flag, shared texture lookup and13-word factory.
// TheWritableGlobalData is the owned singleton at VA DFE758. Bounds slot110
// is witnessed here; this view does not change the reference RenderObj ABI.
class GlobalData; extern GlobalData *TheWritableGlobalData;
class RenderObjClass; class Drawable; class W3DProjectedShadow; class W3DShadowTexture;
struct ShadowNameBuffer {int refs; unsigned short length,capacity; char text[1];};
struct ShadowInfoView { ShadowNameBuffer *name; int unused; int type; float sizeX,sizeY,offsetX,offsetY,unused1,height; unsigned char force; };
struct ShadowBounds {float center[3];float extent[3];};
class ShadowBoundsCall {public:
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
virtual void getBounds(ShadowBounds&);
};
class Rva0010BC90ShadowManager { public: W3DShadowTexture *getTexture(const char*); };
class Rva0010BB11ShadowFactory {public: W3DProjectedShadow *create(W3DShadowTexture*,RenderObjClass*,int,unsigned char,float,float,float,float,float,void*,unsigned char,int,unsigned char);};
W3DProjectedShadow *W3DProjectedShadowManager::addShadow(RenderObjClass *object,Shadow::ShadowTypeInfo *raw,Drawable *draw)
{
    ShadowInfoView *info=reinterpret_cast<ShadowInfoView*>(raw);
    if (!info) goto reject;
    if (!reinterpret_cast<unsigned char*>(TheWritableGlobalData)[0x61] && !info->force) {
reject:
        return 0;
    }
    const char *name;
    if ((info->name ? info->name->length : 0) <= 1) name="shadow";
    else name=info->name ? info->name->text : "";
    W3DShadowTexture *texture=reinterpret_cast<Rva0010BC90ShadowManager*>(this)->getTexture(name);
    int type=info->type;
    float sizeX=info->sizeX, sizeY=info->sizeY;
    float offsetX=info->offsetX,offsetY=info->offsetY;
    float height=info->height;
    if(sizeX==0.0f || sizeY==0.0f) {
        ShadowBounds bounds;
        reinterpret_cast<ShadowBoundsCall*>(object)->getBounds(bounds);
        if(sizeX==0.0f) sizeX=2.0f*bounds.extent[0];
        if(sizeY==0.0f) sizeY=-2.0f*bounds.extent[1];
    }
    return reinterpret_cast<Rva0010BB11ShadowFactory*>(this)->create(texture,object,type,0,sizeX,sizeY,height,0.0f-offsetX,0.0f-offsetY,reinterpret_cast<char*>(this)+4,0,0,0);
}
