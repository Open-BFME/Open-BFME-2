// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /ICode/GameEngine/Include /ICode/GameEngine/Source/Common
// Native [0004FAFF,000500E5), 1510B through the native RET4.
// Existing refreshTerrain500F7 call proves the protected terrain-builder role.
// ZH W3DRadar::buildTerrainTexture is the semantic/loop guide (BF1 pointer
// 575ba2b04); target supplies map-art early path, counted surface and lock,
// centre-height sample and fixed water colour. Every accessed field/vslot is
// native evidence. Extra field names and global subsystem role remain unknown.
// The canonical AsciiString/StringBase header establishes its pointer+8 data;
// direct header indexing reproduces the native commuted SIB byte. Existing
// GameState storage is viewed through its already-owned Player::getBaseSide
// call ABI; this does not establish that the singleton is a Player.
// Registry lookup uses its existing by-value AsciiString call view. TerrainType
// getTexture is an existing pin to the witnessed shared string getter at+8;
// its original Bridge method name remains unproven. No new pins or data names.
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
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
struct RGBColor { float red,green,blue; };
struct ICoord2D { int x,y; };
class Player { public: AsciiString getBaseSide() const; };
class GameState; extern GameState *TheGameState;
class FileSystem { public: bool doesFileExist(const char*) const; }; extern FileSystem *TheFileSystem;
class TextureClass { public: void Release_Ref(); };
class BfmeMapPictureTexture { public: TextureClass *ptr; BfmeMapPictureTexture(const char*); BfmeMapPictureTexture &operator=(const BfmeMapPictureTexture&); ~BfmeMapPictureTexture(){if(ptr)ptr->Release_Ref();} };
class BfmeResetTextureRef { public: void clear(); };
class W3DRadarResetSurface { void *ptr; public: ~W3DRadarResetSurface(); };
class CursorTextureSlot { public: W3DRadarResetSurface Get_Surface_Level(); };
class SurfaceClass { public: void DrawPixel(unsigned,unsigned,unsigned); };
void BFME_DX8_Thread_Lock(); bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock { public: BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();} ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();} };
class Radar { public: bool radarToWorld(const ICoord2D*,Coord3D*); float getTerrainAverageZ() const {return averageZ;} private: char pad0[0x1c];float averageZ;char pad20[0x1430-0x20]; };
struct Rva002DB4DANode;
struct Rva002DB4DA { Rva002DB4DANode *rva002DB4DA(AsciiString); };
class TerrainRoadCollection;extern TerrainRoadCollection *TheTerrainRoads;
struct TerrainRoadType {char pad[0x28];RGBColor radarColor; RGBColor getRadarColor(){return radarColor;} };
class TerrainType { public: AsciiString getTexture() const; };
struct Bridge { char pad[0x30];float z0;char p34[8];float z1;char p40[8];float z2;char p4c[8];float z3;char p58[8];ObjectID objectID; };
class RadarBodyView {public:
virtual void p0();virtual void p1();virtual void p2();virtual void p3();virtual void p4();virtual void p5();virtual void p6();virtual void p7();virtual int getDamageState();};
struct RadarObjectView {char pad[0x254];RadarBodyView *body;};
class TerrainLogic {public:
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual float getGroundHeight(float,float,void*);
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual bool isUnderwater(float,float,float*,float* = 0,void* = 0);
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual Bridge *findBridgeAt(const Coord3D*);
};extern TerrainLogic *TheTerrainLogic;
extern GameLogic *TheGameLogic;
class G00DFF080Obj {public: virtual void p0();virtual void p1();virtual void p2();virtual void p3();virtual void p4();virtual void p5();virtual void getTerrainColorAt(float,float,RGBColor*);};extern G00DFF080Obj *g_00DFF080;
class W3DRadar : public Radar { protected: void buildTerrainTexture(TerrainLogic*);protected: void rva0004E3F1();void interpolateColorForHeight(RGBColor*,float,float,float,float);private:
    char pad1430[4];Coord3D extentLo,extentHi;
    char pad144c[0x1468-0x144c];
    int format0;void *image0;BfmeMapPictureTexture m_terrainTexture,m_terrainTextureAlt;
    char pad1478[0x149c-0x1478];int m_textureWidth,m_textureHeight;
    char pad14a4[0x14d4-0x14a4];bool m_reconstructViewBox,m_useAltTerrainTexture;
};
inline int GameMakeColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a){return(a<<24)|(r<<16)|(g<<8)|b;}
void W3DRadar::buildTerrainTexture( TerrainLogic *terrain )
{
	
	RGBColor waterColor;

	m_reconstructViewBox = true;

    AsciiString filename=((Player*)TheGameState)->getBaseSide();
    if(!filename.isEmpty()) {
        int i=filename.getLength();
        while(--i>0 && ((char*)*(void**)&filename)[i+8]!='.') {}
        if(i>0) {
            while(filename.getLength()>i) filename.removeLastChar();
            ((StringBase<char>*)&filename)->concat("_art.tga");
            if(TheFileSystem->doesFileExist(filename.str())) {
                ((BfmeResetTextureRef*)&m_terrainTextureAlt)->clear();
                m_terrainTextureAlt=BfmeMapPictureTexture(filename.str());
                m_useAltTerrainTexture=true;
                rva0004E3F1();
                return;
            }
        }
    }
    m_useAltTerrainTexture=false;
    rva0004E3F1();
    BFMEDX8DeviceLock lock;
    W3DRadarResetSurface surface=((CursorTextureSlot*)&m_terrainTexture)->Get_Surface_Level();
    waterColor.red=0.55f;waterColor.green=0.55f;waterColor.blue=1.0f;
	
	RGBColor sampleColor;
	RGBColor color;
	int i, j, samples;
	int x, y;
	ICoord2D radarPoint;
	Coord3D worldPoint;
	Bridge *bridge;
	for( y = 0; y < m_textureHeight; y++ )
	{

		for( x = 0; x < m_textureWidth; x++ )
		{

			radarPoint.x = x;
			radarPoint.y = y;
			radarToWorld( &radarPoint, &worldPoint );

			int centreHeight=(int)terrain->getGroundHeight(worldPoint.x,worldPoint.y,0);
            bool workingBridge = false;
			bridge = TheTerrainLogic->findBridgeAt( &worldPoint );
			if( bridge != 0 )
			{
				Object *obj = TheGameLogic->findObjectByID( bridge->objectID );

				if( obj )
				{
					RadarBodyView *body = ((RadarObjectView*)obj)->body;

					if( body->getDamageState() != 3 )
						workingBridge = true;

				}  

			}  

			float waterZ;
			if( workingBridge == false && terrain->isUnderwater( worldPoint.x, worldPoint.y, &waterZ ) )
			{
				const int waterSamplesAway = 1;		

				sampleColor.red = sampleColor.green = sampleColor.blue = 0.0f;
				samples = 0;

				for( j = y - waterSamplesAway; j <= y + waterSamplesAway; j++ )
				{

					if( j >= 0 && j < m_textureHeight )
					{

						for( i = x - waterSamplesAway; i <= x + waterSamplesAway; i++ )
						{

							if( i >= 0 && i < m_textureWidth )
							{

								radarPoint.x = i;
								radarPoint.y = j;
								radarToWorld( &radarPoint, &worldPoint );

                float underwaterZ=terrain->getGroundHeight(worldPoint.x,worldPoint.y,0);
								if( terrain->isUnderwater( worldPoint.x, worldPoint.y, 0 ) )
								{
									
									color = waterColor;									

									interpolateColorForHeight( &color, underwaterZ, waterZ,
																						 waterZ,
																						 extentLo.z );

									sampleColor.red += color.red;
									sampleColor.green += color.green;
									sampleColor.blue += color.blue;
									samples++;

								}  

							}  

						}  

					}  

				}  

				if( samples == 0 )
					samples = 1;

				color.red = sampleColor.red / (float)samples;
				color.green = sampleColor.green / (float)samples;
				color.blue = sampleColor.blue / (float)samples;

			}  
			else  
			{
				const int samplesAway = 1;  

				sampleColor.red = sampleColor.green = sampleColor.blue = 0.0f;
				samples = 0;

				for( j = y - samplesAway; j <= y + samplesAway; j++ )
				{

					if( j >= 0 && j < m_textureHeight )
					{

						for( i = x - samplesAway; i <= x + samplesAway; i++ )
						{

							if( i >= 0 && i < m_textureWidth )
							{

								radarPoint.x = i;
								radarPoint.y = j;
								radarToWorld( &radarPoint, &worldPoint );

								if( workingBridge )
								{
									AsciiString bridgeTName = ((TerrainType*)bridge)->getTexture();
									TerrainRoadType *bridgeTemplate = (TerrainRoadType*)((Rva002DB4DA*)TheTerrainRoads)->rva002DB4DA(bridgeTName);

									if ( bridgeTemplate )
										color = bridgeTemplate->getRadarColor();
									else
										{color.red=1.0f;color.green=1.0f;color.blue=1.0f;}

									float bridgeHeight = (bridge->z3 + 
																			 bridge->z2 +
																			 bridge->z1 +
																			 bridge->z0) / 4.0f;

									interpolateColorForHeight( &color, bridgeHeight,
																						 getTerrainAverageZ(),
																						 extentHi.z, extentLo.z );

								}  
								else
								{

									g_00DFF080->getTerrainColorAt( worldPoint.x, worldPoint.y, &color );

									interpolateColorForHeight( &color, (float)centreHeight, getTerrainAverageZ(), 
																						 extentHi.z, extentLo.z );

								}  

								sampleColor.red += color.red;
								sampleColor.green += color.green;
								sampleColor.blue += color.blue;
								samples++;

							}  

						}  

					}  

				}  

				if( samples == 0 )
					samples = 1;

				color.red = sampleColor.red / (float)samples;
				color.green = sampleColor.green / (float)samples;
				color.blue = sampleColor.blue / (float)samples;

			}  

			((SurfaceClass*)&surface)->DrawPixel( x, y, GameMakeColor( color.red * 255, 
																							 color.green * 255,
																							 color.blue * 255,
																							 255 ) );

		}  

	}  

}  