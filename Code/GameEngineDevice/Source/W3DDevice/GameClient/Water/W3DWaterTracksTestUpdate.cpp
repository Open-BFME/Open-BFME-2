// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's GameEngineDevice/Source/W3DDevice/GameClien
// t/Water/W3DWaterTracksTestUpdate.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// WaterTracksRenderSystem::bindTrack 0x000FDF4C (181B). Callee addresses are
// read off retail's call sites (reverse/symbols.csv). Only the placed bodies
// are carried; the donor's other definitions are omitted.
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
// Identity: landed WaterTracksRenderSystem::flush caller and ZH water editor twin.
// The native bindTrack companion is intentionally visible: its alias information
// preserves currentWaveType across calls. Its ledger remains in W3DWaterTracks.cpp.
// Companion independently probes exact at RVA 007AABA0 / 193 bytes.
// WaterTracksObj +30/+3C/+68/+74/+B0/+B4 and system +10/+14 are verified by
// that exact body; field names come from the ZH W3DWaterTracks header.
#include "StringInline.h"
#include "vector2.h"
#include <windows.h>
extern "C" __declspec(dllimport) short __stdcall GetAsyncKeyState(int);
extern "C" __declspec(dllimport) int __stdcall GetCursorPos(POINT*);
extern "C" __declspec(dllimport) int __stdcall ScreenToClient(void*,POINT*);
enum { VK_F5=0x74,VK_F6=0x75,VK_F7=0x76,VK_F8=0x77,VK_DELETE=0x2e,VK_INSERT=0x2d };
typedef int Int; typedef float Real; typedef bool Bool;
struct Coord3D { float x,y,z; Coord3D() {} ~Coord3D() {} };
struct ICoord2D { int x,y; };
enum waveType
{
	WaveTypeFirst,
	WaveTypePond=WaveTypeFirst,
	WaveTypeOcean,
	WaveTypeCloseOcean,
	WaveTypeCloseOceanDouble,
	WaveTypeRadial,
	WaveTypeLast = WaveTypeRadial,
	WaveTypeStationary,
	WaveTypeMax,
};

struct waveInfo
{
	Real m_finalWidth;
	Real m_finalHeight;
	Real m_waveDistance;
	Real m_initialVelocity;
	Int m_fadeMs;
	Real m_initialWidthFraction;
	Real m_initialHeightWidthFraction;
	Int m_timeToCompress;
	Int m_secondWaveTimeOffset;
	char *m_textureName;
	char *m_waveTypeName;
};

extern waveInfo waveTypeInfo[WaveTypeMax];
class WaterTracksObj { public: char pad[0x30]; waveType m_type; char pad34[8]; bool m_bound; char pad3d[0x68-0x3d]; int m_initTimeOffset; char pad6c[8]; int m_elapsedMs; char pad78[0xb0-0x78]; WaterTracksObj *m_nextSystem,*m_prevSystem; void init(float,float,Vector2&,Vector2&,char*,int); };
class WaterTracksRenderSystem { public: char pad[0x10]; WaterTracksObj *m_usedModules,*m_freeModules; WaterTracksObj *bindTrack(waveType); void saveTracks(); void loadTracks(); void reset(); };
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
struct BfmeNodeOJ;
class BfmeThingOJ { public: void bfmeFrontOJ(BfmeNodeOJ*); };
class InGameUI;
extern InGameUI *TheInGameUI;

class Rva007ACBD0UI { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2c();
virtual void slot30();
virtual void __cdecl message(UnicodeString,...);
};
class View; extern View *TheTacticalView;
class Rva007ACBD0View { public:
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00c();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01c();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02c();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03c();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04c();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05c();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06c();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual void slot07c();
virtual void slot080();
virtual void slot084();
virtual void slot088();
virtual void slot08c();
virtual void slot090();
virtual void slot094();
virtual void slot098();
virtual void slot09c();
virtual void slot0a0();
virtual void slot0a4();
virtual void slot0a8();
virtual void slot0ac();
virtual void slot0b0();
virtual void slot0b4();
virtual void slot0b8();
virtual void slot0bc();
virtual void slot0c0();
virtual void slot0c4();
virtual void slot0c8();
virtual void slot0cc();
virtual void slot0d0();
virtual void slot0d4();
virtual void slot0d8();
virtual void slot0dc();
virtual void slot0e0();
virtual void slot0e4();
virtual void slot0e8();
virtual void slot0ec();
virtual void slot0f0();
virtual void slot0f4();
virtual void slot0f8();
virtual void slot0fc();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10c();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11c();
virtual void slot120();
virtual void slot124();
virtual void slot128();
virtual void slot12c();
virtual void slot130();
virtual void slot134();
virtual void slot138();
virtual void slot13c();
virtual void slot140();
virtual void slot144();
virtual void slot148();
virtual void slot14c();
virtual void slot150();
virtual void slot154();
virtual void slot158();
virtual void slot15c();
virtual void slot160();
virtual void screenToTerrain(const ICoord2D*,Coord3D*,bool);
};
class Display; extern Display *TheDisplay;
extern void j_0004a35e();
struct Rva007ACBD0DisplayCall {};

class DX8Wrapper { public: static void Invalidate_Cached_Render_States(); };
extern char g_rva007A2330Flag;
extern void *ApplicationHWnd;
static Bool pauseWaves;
WaterTracksObj *WaterTracksRenderSystem::bindTrack(waveType type)
{
	WaterTracksObj *mod,*nextmod,*prevmod;

	mod = m_freeModules;
	if( mod )
	{

		if( mod->m_nextSystem )
			mod->m_nextSystem->m_prevSystem = mod->m_prevSystem;
		if( mod->m_prevSystem )
			mod->m_prevSystem->m_nextSystem = mod->m_nextSystem;
		else
			m_freeModules = mod->m_nextSystem;

		mod->m_type=type;

		nextmod=NULL,prevmod=NULL;
		for( nextmod = m_usedModules; nextmod; prevmod=nextmod,nextmod = nextmod->m_nextSystem )
		{
			if (nextmod->m_type==type)
			{
				mod->m_nextSystem=nextmod;
				mod->m_prevSystem=prevmod;
				nextmod->m_prevSystem=mod;
				if (prevmod)
				{	prevmod->m_nextSystem=mod;
				}
				else
					m_usedModules=mod;
				break;
			}
		}

		if (nextmod==NULL)
		{
			mod->m_nextSystem = m_usedModules;
			if (m_usedModules)
				m_usedModules->m_prevSystem=mod;
			m_usedModules = mod;
		}

		mod->m_bound=true;
	}

	nextmod=m_usedModules;

	while(nextmod)
	{
		nextmod->m_elapsedMs=nextmod->m_initTimeOffset;
		nextmod=nextmod->m_nextSystem;
	}

	return mod;
}
