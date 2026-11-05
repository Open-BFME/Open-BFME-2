// cl: /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
// cl: /O1 /DNDEBUG /MD /GX
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


// DozerAIUpdate::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Update/AIUpdate/DozerAIUpdate.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "DozerAIUpdate".
//
// BFME 2 order: the AIUpdateInterface base (0x00267EDD) first, then the
// light-CRC gate and Version(1, 2), then ZH's body. ZH's throw SC_INVALID_DATA
// becomes XferException tag 5 (constructor 0x0060C36E). After the build
// subtask, BFME 2 hands Xfer and the +0x408 member to TheAudio's xferAudioHandle (slot 88) when
// there is an audio manager. It then adds a flag (+0x40C) and an ObjectID
// (+0x4A4).

#include "Common/Snapshot.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../../Libraries/Include/Lib/Coord3DBase.h"

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

#include "../../../../../Include/Common/XferException.h"

#include "../../../../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

enum DozerTask
{
	DOZER_TASK_INVALID = -1,
	DOZER_TASK_FIRST = 0,
	DOZER_TASK_BUILD = DOZER_TASK_FIRST,
	DOZER_TASK_REPAIR,
	DOZER_TASK_FORTIFY,

	DOZER_NUM_TASKS
};

enum DozerDockPoint
{
	DOZER_DOCK_POINT_START = 0,
	DOZER_DOCK_POINT_ACTION = 1,
	DOZER_DOCK_POINT_END = 2,

	DOZER_NUM_DOCK_POINTS
};

enum DozerBuildSubTask
{
	DOZER_SELECT_BUILD_DOCK_LOCATION = 0
};

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x3E8 - 0x04 ];
};

class DozerAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	} m_task[ DOZER_NUM_TASKS ];																							///< 0x3E8
	Snapshot *m_dozerMachine;																									///< 0x400
	DozerTask m_currentTask;																									///< 0x404
	unsigned int m_bfmeAudio408;																			///< 0x408
	Bool m_bfmeFlag40C;																												///< 0x40C
	struct DozerDockPointInfo
	{
		Bool valid;
		Coord3DBase location;
	} m_dockPoint[ DOZER_NUM_TASKS ][ DOZER_NUM_DOCK_POINTS ];								///< 0x410
	DozerBuildSubTask m_buildSubTask;																					///< 0x4A0
	ObjectID m_bfmeObject4A4;																									///< 0x4A4
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void DozerAIUpdate::xfer( Xfer *xfer )
{

 // extend base class
	AIUpdateInterface::xfer(xfer);

	if( xfer->IsLightCRC() )
		return;

  // version
	Xfer::Version version( 1, 2 );
	*xfer == version;

	Int numTasks = DOZER_NUM_TASKS;
	*xfer == numTasks;
	if (numTasks != DOZER_NUM_TASKS) {
		throw XferException( 5, 0 );
	}
	Int i, j;
	for (i=0; i<DOZER_NUM_TASKS; i++) {
		XferObjectID( xfer, &m_task[i].m_targetObjectID );
		*xfer == m_task[i].m_taskOrderFrame;
	}
	*xfer == *m_dozerMachine;
	xfer->XferRawBytes( &m_currentTask, sizeof(m_currentTask) );

	Int dockPoints = DOZER_NUM_DOCK_POINTS;
	*xfer == dockPoints;
	if (dockPoints!=DOZER_NUM_DOCK_POINTS) {
		throw XferException( 5, 0 );
	}
	for (i=0; i<DOZER_NUM_TASKS; i++) {
		for (j=0; j<DOZER_NUM_DOCK_POINTS; j++) {
			*xfer == m_dockPoint[i][j].valid;
			*xfer == m_dockPoint[i][j].location;
		}
	}
	xfer->XferRawBytes( &m_buildSubTask, sizeof(m_buildSubTask) );

	if( TheAudio )
		TheAudio->xferAudioHandle( xfer, &m_bfmeAudio408 );

	*xfer == m_bfmeFlag40C;
	XferObjectID( xfer, &m_bfmeObject4A4 );

}  // end xfer
