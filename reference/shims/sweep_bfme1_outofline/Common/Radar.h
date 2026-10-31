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

// FILE: Radar.h //////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, January 2002
// Desc:   Logical radar implementation
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// BFME shim (TU-scoped): Zero Hour's Common/Radar.h with the BFME 2 layout, read from the
// retail bytes of W3DRadar.cpp's rows and Radar.cpp's, and the Radar methods their mangled
// names show. For W3DRadar.cpp, the one translation unit that names this directory.

#ifndef __RADAR_H_
#define __RADAR_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameMemory.h"
#include "GameClient/Display.h"	// for ShroudLevel
#include "GameClient/Color.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class GameWindow;
class Object;
class Player;
class TerrainLogic;

// GLOBAL /////////////////////////////////////////////////////////////////////////////////////////
//
// the following is used for the resolution of the radar "cells" ... this is how accurate
// the radar is and also reflects directly the size of the image we build ... which with
// WW3D must be a square power of two as well
//
enum 
{ 
	RADAR_CELL_WIDTH  = 128,	// radar created at this horz resolution
	RADAR_CELL_HEIGHT = 128   // radar created at this vert resolution
};

//-------------------------------------------------------------------------------------------------
/** These event types determine the colors radar events happen in to make it easier for us
	* to play events with a consistent color scheme */
//-------------------------------------------------------------------------------------------------
enum RadarEventType
{
	RADAR_EVENT_INVALID = 0,
	RADAR_EVENT_CONSTRUCTION,
	RADAR_EVENT_UPGRADE,
	RADAR_EVENT_UNDER_ATTACK,
	RADAR_EVENT_INFORMATION,
	RADAR_EVENT_BEACON_PULSE,
	RADAR_EVENT_INFILTRATION, //for defection, hijacking, hacking, carbombing, and other sneaks
	RADAR_EVENT_BATTLE_PLAN,
	RADAR_EVENT_STEALTH_DISCOVERED,		// we discovered a stealth unit
	RADAR_EVENT_STEALTH_NEUTRALIZED,	// our stealth unit has been revealed
	RADAR_EVENT_FAKE,					//Internally creates a radar event, but doesn't notify the player (unit lost 
														//for example, so we can use the spacebar to jump to the event).
 
 	RADAR_EVENT_NUM_EVENTS  // keep this last
 	
};

// PROTOTYPES /////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Radar objects are objects that are on the radar, go figure :) */
//-------------------------------------------------------------------------------------------------
class RadarObject : public Snapshot
{

public:
	
	RadarObject( void );
	virtual ~RadarObject( void );

	// color management
	void setColor( Color c ) { m_color = c; }
	inline Color getColor( void ) const { return m_color; }

	inline void friend_setObject( Object *obj ) { m_object = obj; }
	inline Object *friend_getObject( void ) { return m_object; }
	inline const Object *friend_getObject( void ) const { return m_object; }

	inline void friend_setNext( RadarObject *next ) { m_next = next; }
	inline RadarObject *friend_getNext( void ) { return m_next; }
	inline const RadarObject *friend_getNext( void ) const { return m_next; }

	Bool isTemporarilyHidden() const;

protected:

	// snapshot methods
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	Object *m_object;				///< the object
	RadarObject *m_next;		///< next radar object
	Color m_color;					///< color to draw for this object on the radar

};

//-------------------------------------------------------------------------------------------------
/** Radar priorities.  Keep this in sync with the priority names list below */
//-------------------------------------------------------------------------------------------------
enum RadarPriorityType
{
	RADAR_PRIORITY_INVALID,					// a priority that has not been set (in general it won't show up on the radar)
	RADAR_PRIORITY_NOT_ON_RADAR,		// object specifically forbidden from being on the radar
	RADAR_PRIORITY_STRUCTURE,				// structure level drawing priority
	RADAR_PRIORITY_UNIT,						// unit level drawing priority
	RADAR_PRIORITY_LOCAL_UNIT_ONLY,	// unit priority, but only on the radar if controlled by the local player

	RADAR_PRIORITY_NUM_PRIORITIES		// keep this last
};
#ifdef DEFINE_RADAR_PRIORITY_NAMES
static const char *RadarPriorityNames[] = 
{
	"INVALID",											// a priority that has not been set (in general it won't show up on the radar)
	"NOT_ON_RADAR",									// object specifically forbidden from being on the radar
	"STRUCTURE",										// structure level drawing priority
	"UNIT",													// unit level drawing priority
	"LOCAL_UNIT_ONLY",							// unit priority, but only on the radar if controlled by the local player

	NULL														// keep this last
};
#endif  // DEFINE_RADAR_PRIOTITY_NAMES

//-------------------------------------------------------------------------------------------------
/** Interface for the radar */
//-------------------------------------------------------------------------------------------------
class Radar : public Snapshot,
							public SubsystemInterface
{

public:
	
	Radar( void );
	virtual ~Radar( void );

	virtual void init( void ) { }														///< subsystem initialization
	virtual void reset( void );															///< subsystem reset
	virtual void update( void );														///< subsystem per frame update

	// is the game window parameter the radar window
	Bool isRadarWindow( GameWindow *window ) { return (m_radarWindow == window) && (m_radarWindow != NULL); }

	Bool radarToWorld( const ICoord2D *radar, Coord3D *world );		///< radar point to world point on terrain
	Bool radarToWorld2D( const ICoord2D *radar, Coord3D *world );		///< radar point to world point (x,y only!)
	Bool worldToRadar( const Coord3D *world, ICoord2D *radar );		///< translate world point to radar (x,y)
	Bool localPixelToRadar( const ICoord2D *pixel, ICoord2D *radar );	///< translate pixel (with UL of radar being (0,0)) to logical radar coords
	Bool screenPixelToWorld( const ICoord2D *pixel, Coord3D *world ); ///< translate pixel (with UL of the screen being (0,0)) to world position in the world
	Object *objectUnderRadarPixel( const ICoord2D *pixel );				///< return the object (if any) represented by the pixel coords passed in
	void rva0004F515( Int a, Int b, Int c, Int d );						///< row 0x0004F515
	void rva002D790A( Real *widthRatio, Real *heightRatio );	///< row 0x002D790A: the extent's aspect ratios
	void findDrawPositions( Int startX, Int startY, Int width, Int height,
													ICoord2D *ul, ICoord2D *lr );					///< make translation for screen area of radar square to scaled aspect ratio preserving points inside the radar area

	// priority inquiry
	Bool isPriorityVisible( RadarPriorityType priority ) const;		///< is the priority passed in a "visible" one on the radar

	// radar events
	void createEvent( const Coord3D *world, RadarEventType type, Real secondsToLive = 4.0f );	///< create radar event at location in world
	void createPlayerEvent( Player *player, const Coord3D *world, RadarEventType type, Real secondsToLive = 4.0f );  ///< create radar event using player colors

	Bool getLastEventLoc( Coord3D *eventPos );							///< get last event loc (if any)
	void tryUnderAttackEvent( const Object *obj );					///< try to make an "under attack" event if it's the proper time
	void tryInfiltrationEvent( const Object *obj );					///< try to make an "infiltration" event if it's the proper time
 	Bool tryEvent( RadarEventType event, const Coord3D *pos );	///< try to make a "stealth" event

	// adding and removing objects from the radar
	void addObject( Object *obj );													///< add object to radar
	void removeObject( Object *obj );												///< remove object from radar
	void examineObject( Object *obj );											///< re-examine object and resort if needed

	// radar options
	void hide( Bool hide ) { m_radarHidden = hide; }				///< hide/unhide the radar
	Bool isRadarHidden( void ) { return m_radarHidden; }		///< is radar hidden
	// other radar option methods here like the ability to show a certain
	// team, show buildings, show units at all, etc

	// forcing the radar on/off regardless of player situation
	void forceOn( Bool force ) { m_radarForceOn = force; }				///< force the radar to be on
	Bool isRadarForced( void ) { return m_radarForceOn; }		///< is radar forced on?

	// retail table 0x00BC4E34 slot 2: BFME's Snapshot has one virtual more than Zero Hour's
	virtual const char *GetSnapshotName() const;

	/// refresh the water values for the radar
	virtual void refreshTerrain( TerrainLogic *terrain );

	/// queue a refresh of the terran at the next available time
	virtual void queueTerrainRefresh( void );

	virtual void newMap( TerrainLogic *terrain );	///< reset radar for new map

	virtual void draw( Int pixelX, Int pixelY, Int width, Int height ) = 0;	///< draw the radar

	// retail W3DRadar table 0x00BC4E34 holds these in slots 8, 9 and 10
	virtual void rva0004F580() = 0;
	/// set the shroud level at shroud cell x,y
	virtual void setShroudLevel( Int x, Int y, CellShroudStatus setting ) = 0;
	/// empty the entire shroud
	virtual void clearShroud() = 0;

protected:

	// snapshot methods
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	/// internal method for creating a radar event with specific colors
	void internalCreateEvent( const Coord3D *world, RadarEventType type, Real secondsToLive,
														const RGBAColorInt *color1, const RGBAColorInt *color2 );

	void deleteListResources( void );			///< delete list radar resources used
	Bool deleteFromList( Object *obj, RadarObject **list );	///< try to remove object from specific list

	inline Real getTerrainAverageZ() const { return m_terrainAverageZ; }
	inline Real getWaterAverageZ() const { return m_waterAverageZ; }
	inline const RadarObject* getObjectList() const { return m_objectList; }
	inline const RadarObject* getLocalObjectList() const { return m_localObjectList; }

	void clearAllEvents( void );					///< remove all radar events in progress

	// search the object list for an object that maps to the given logical radar coords
	Object *searchListForRadarLocationMatch( RadarObject *listHead, ICoord2D *radarMatch );

	char m_subsystemTail[ 4 ];						///< +0x0C: retail's SubsystemInterface is twelve bytes
	Bool m_radarHidden;										///< +0x10: true when radar is not visible
	Bool m_radarForceOn;									///< +0x11: true when radar is forced to be on
	RadarObject *m_objectList;						///< +0x14: list of objects in the radar
	RadarObject *m_localObjectList;				///< +0x18: list of objects for the local player
	Real m_terrainAverageZ;								///< +0x1C: average Z for terrain samples
	Real m_waterAverageZ;									///< +0x20: average Z for water samples
	Real m_xSample;												///< +0x24
	Real m_ySample;												///< +0x28

	enum { MAX_RADAR_EVENTS = 64 };
	struct RadarEvent
	{
		RadarEventType type;								///< type of this radar event
		Bool active;												///< TRUE when event is "active", otherwise it's just historical information
		UnsignedInt createFrame;						///< frame event was created on
		UnsignedInt dieFrame;								///< frame the event will go away on
		UnsignedInt fadeFrame;							///< start fading out on this frame
		RGBAColorInt color1;								///< color 1 for drawing
		RGBAColorInt color2;								///< color 2 for drawing
		Coord3D worldLoc;										///< location of event in the world
		ICoord2D radarLoc;									///< +0x40: 2D radar location of the event
		Bool soundPlayed;										///< TRUE when we have played the radar sound for this
		class RadarEventRef *ref;						///< +0x4C: retail's event stride is 80 bytes
	};
	RadarEvent m_event[ MAX_RADAR_EVENTS ];///< +0x2C: our radar events
	Int m_nextFreeRadarEvent;							///< +0x142C: index into m_event for where to store the next event
	GameWindow *m_radarWindow;						///< +0x1430: window we display the radar in
	Region3D m_mapExtent;									///< +0x1434: extents of the current map
	Real m_clipRect[ 4 ];									///< +0x144C: display clip rectangle
	Bool m_clip;													///< +0x145C: clip while drawing
	UnsignedInt m_queueTerrainRefreshFrame;  ///< +0x1460: frame we requested the last terrain refresh on


};

// EXTERNALS //////////////////////////////////////////////////////////////////////////////////////
extern Radar *TheRadar;  ///< the radar singleton extern

#endif  // __RADAR_H_



