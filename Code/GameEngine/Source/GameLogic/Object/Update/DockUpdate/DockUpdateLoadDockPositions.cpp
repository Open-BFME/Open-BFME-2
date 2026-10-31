// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/bfme2_dockupdate /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/dockupdate /Ireference/open-bfme-1/inputs/reference/shims/moduledata /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /Ireference/shims/sweep -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Update/DockUpdate
// stlport
//
// ?loadDockPositions@DockUpdate@@IAEXXZ, retail 0x005897FB, 270 bytes.
// Dock bone strings DockStart/DockAction/DockEnd/DockWaiting plus eight callers
// (0x589909 loadPostProcess wrapper tail-jumping to UpdateModule::loadPostProcess,
// 0x589972/0x58A1A1 with -0x20 this-adjustment) prove DockUpdate identity.
// Donor is BFME1 DockUpdate::loadDockPositions
// (BFME1 revision 9cbfb551fe20dae985f91f2319d8997287b6a705, game engine DockUpdate.cpp:524,
// protected IAEXXZ) via ZH DockUpdate.cpp:491. BFME2 drops the KINDOF_IGNORE_DOCKING_BONES
// patch branch. Layout is the rowed DockUpdateCtor TU (UpdateModule base 0x20 plus
// DockUpdateInterface vptr at +0x20, enter/dock/exit at +0x24/+0x30/+0x3C,
// number/bones/loaded at +0x48/+0x4C/+0x50, approach vector at +0x54).
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Debug.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/DockUpdate.h"

// This array's construction/destruction is witnessed in the native unwind
// graph; the data view uses the canonical Coord3D layout. The lifetime-only
// adapter callbacks are byte-and-relocation twins of the folded native
// constructor at 0x0047A6A9 (8b c1 c3) and destructor at 0x000B3FD0 (c3).
// These offsets prove lifetime machinery, not an independent class identity.
struct Rva005897FBCoordLifetime : Coord3D
{
    Rva005897FBCoordLifetime() {}
    ~Rva005897FBCoordLifetime() {}
};

// ?loadDockPositions@DockUpdate@@IAEXXZ
void DockUpdate::loadDockPositions()
{
	Object *obj = getObject();
	Drawable *myDrawable = obj->Thing::getDrawable();

	if (myDrawable != NULL)
	{
		myDrawable->getPristineBonePositions("DockStart", 0, &m_enterPosition, NULL, 1, 0);
		myDrawable->getPristineBonePositions("DockAction", 0, &m_dockPosition, NULL, 1, 0);
		myDrawable->getPristineBonePositions("DockEnd", 0, &m_exitPosition, NULL, 1, 0);
		if (m_numberApproachPositions != DYNAMIC_APPROACH_VECTOR_FLAG)
		{
			Rva005897FBCoordLifetime approachBones[DEFAULT_APPROACH_VECTOR_SIZE];
			m_numberApproachPositionBones = myDrawable->getPristineBonePositions("DockWaiting", 1, approachBones, NULL, m_numberApproachPositions, 0);
			if (m_numberApproachPositions == m_approachPositions.size())
			{
				for (Int copyIndex = 0; copyIndex < m_numberApproachPositions; ++copyIndex)
				{
					m_approachPositions[copyIndex] = approachBones[copyIndex];
				}
			}
		}
		else
		{
			m_numberApproachPositionBones = 0;
		}

		m_positionsLoaded = TRUE;
	}
}
