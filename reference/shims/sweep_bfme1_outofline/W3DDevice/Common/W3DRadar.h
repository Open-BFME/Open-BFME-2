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

// FILE: W3DRadar.h ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, January 2002
// Desc:   W3D radar implementation, this has the necessary device dependent drawing
//				 necessary for the radar

///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// BFME shim (TU-scoped): Zero Hour's W3DRadar.h with the BFME 2 layout and the methods the
// rows' mangled names show (a five-argument draw, a public reconstructViewBox). Offsets are
// read from retail's bytes. For W3DRadar.cpp, the one translation unit naming this directory.

#ifndef __W3DRADAR_H_
#define __W3DRADAR_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/Radar.h"
#include "WW3D2/WW3DFormat.h"
#include "WW3D2/surfaceclass.h"
#include "WW3D2/texture.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Anim2D;
class Image;
class RadarObject;
class SurfaceClass;
class TextureClass;
class TerrainLogic;
struct IDirect3DSurface8;

// The surface holder Get_Surface_Level returns: the D3D surface first.
class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() {}
	W3DRadarResetSurface(const W3DRadarResetSurface &);
	~W3DRadarResetSurface();
	void clear(bool white);
	SurfaceClass *operator->() { return (SurfaceClass *)this; }
	IDirect3DSurface8 *m_surface;
};

// A texture holder member: rows 0x00132D70 and 0x0013289D give its surface levels.
class CursorTextureSlot
{
public:
	void *Ptr;
	W3DRadarResetSurface Get_Surface_Level(int level);
	W3DRadarResetSurface Get_Surface_Level();
};

// PROTOTYPES /////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
/** W3D radar class.  This has the device specific implementation of the radar such as
	* the drawing routines */
//-------------------------------------------------------------------------------------------------
class W3DRadar : public Radar
{

public:

	W3DRadar( void );
	~W3DRadar( void );

	virtual void init( void );																		///< subsystem init
	virtual void update( void );																	///< subsystem update
	virtual void reset( void );																		///< subsystem reset

	virtual void newMap( TerrainLogic *terrain );				///< reset radar for new map

	void draw( Int pixelX, Int pixelY, Int width, Int height, Int color );		///< draw the radar
	void rva00050125( const RadarObject *listHead, const CursorTextureSlot *texture, Int color );	///< row 0x00050125
	void rva0004DDBF( Int pixelX, Int pixelY, Int width, Int height, Int index, Int unused );	///< row 0x0004DDBF: one beacon event
	void rva0004ED3D( Int cellX, Int cellY, UnsignedByte level );	///< row 0x0004ED3D: one taint cell
	void drawEvents( Int pixelX, Int pixelY, Int width, Int height, Int color );	///< draw all of the radar events
	void drawViewBox( Int pixelX, Int pixelY, Int width, Int height, Int color );	///< draw view box
	void reconstructViewBox( void );							///< remake the view box

	virtual void rva0004F580();										///< table slot 8: copies the ScrollShroud image
	virtual void clearShroud();
	virtual void setShroudLevel(Int x, Int y, CellShroudStatus setting);

	virtual void refreshTerrain( TerrainLogic *terrain );

protected:

	void drawSingleBeaconEvent( Int pixelX, Int pixelY, Int width, Int height, Int index );
	void drawSingleGenericEvent( Int pixelX, Int pixelY, Int width, Int height, Int index );

	void initializeTextureFormats( void );				///< find format to use for the radar texture
	void deleteResources( void );									///< delete resources used
	void drawHeroIcon( Int pixelX, Int pixelY, Int width, Int height, const Coord3D *pos );	//< draw a hero icon
	void buildTerrainTexture( TerrainLogic *terrain );	 ///< create the terrain texture of the radar
	void drawIcons( Int pixelX, Int pixelY, Int width, Int height );	///< draw all of the radar icons
	void renderObjectList( const RadarObject *listHead, TextureClass *texture, Bool calcHero = FALSE );			 ///< render an object list to the texture
	void interpolateColorForHeight( RGBColor *color, 
																	Real height, 
																	Real hiZ, 
																	Real midZ, 
																	Real loZ );		///< "shade" color according to height value
	void rva0004E3F1( void );											///< row 0x0004E3F1: terrain Image setup
	void radarToPixel( const ICoord2D *radar, ICoord2D *pixel,
										 Int radarUpperLeftX, Int radarUpperLeftY,
										 Int radarWidth, Int radarHeight );  ///< convert radar coord to pixel location

	Bool m_dirty;														///< +0x1464: draw refreshes the overlay
	WW3DFormat m_terrainTextureFormat;			///< +0x1468: format to use for terrain texture
	Image *m_terrainImage;									///< +0x146C: terrain image abstraction for drawing
	CursorTextureSlot m_terrainTexture;			///< +0x1470: terrain background texture
	CursorTextureSlot m_terrainTextureAlt;	///< +0x1474: used when m_useAltTerrainTexture is set
	WW3DFormat m_overlayTextureFormat;			///< +0x1478: format to use for overlay texture
	Image *m_overlayImage;									///< +0x147C: overlay image abstraction for drawing
	CursorTextureSlot m_overlayTexture;			///< +0x1480: overlay texture
	WW3DFormat m_shroudTextureFormat;				///< +0x1484: format to use for shroud texture
	Image *m_shroudImage;										///< +0x1488: shroud image abstraction for drawing
	CursorTextureSlot m_shroudTexture;			///< +0x148C: shroud texture
	WW3DFormat m_fogTextureFormat;					///< +0x1490: format to use for the fourth texture
	Image *m_fogImage;											///< +0x1494: its image abstraction for drawing
	CursorTextureSlot m_fogTexture;					///< +0x1498: the fourth texture, cleared by clearShroud
	Int m_textureWidth;											///< +0x149C: width for all radar textures
	Int m_textureHeight;										///< +0x14A0: height for all radar textures
	char m_pad14A4[ 4 ];
	Anim2D *m_eventImages[ 11 ];						///< +0x14A8: drawn per event type, deleted by deleteResources
	Bool m_reconstructViewBox;							///< +0x14D4: true when we need to reconstruct the box
	Bool m_useAltTerrainTexture;						///< +0x14D5
	Bool m_scrollShroudLoaded;							///< +0x14D6: set once rva0004F580 copied the image
	Real m_viewAngle;												///< +0x14D8: camera angle used for the view box we have
	Real m_viewZoom;												///< +0x14DC: camera zoom used for the view box we have
	Coord2D m_viewBox[ 4 ];									///< +0x14E0: radar points for the 4 corners of view box
};


#endif // __W3DRADAR_H_
