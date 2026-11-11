// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// Semantic donor: BF1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/VictorySystemXfer.cpp.
// WB10771D0 names VictorySystem::DoXfer and VictorySystem.cpp. Native
// 4056ED..40596C proves twenty indices, 168-byte root cell, 24-byte faction
// records, grid transfer56C50E and the diagnostic string/return chain.
// xfer runs on the Snapshot subobject, twelve bytes after the complete
// VictorySystem (independently proved by GameStateInit). After loading a
// grid it calls primary slot 14 (+0x38), newMap (0x00404DE5). Member labels
// follow the donor only where the target transfer sequence agrees.
// Native Xfer table7BB910 proves Version10, raw9, float28, uint30 and bool36.
// The record constructor is expanded at its sole use, as native instructions
// show; no imported constructor call or standalone constructor body is used.
#include <vector>
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"
typedef bool Bool;
#include "../../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char UnsignedByte;
class Debug;
struct XferVersionFields
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};


class Snapshot;

class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	union {
		XferVersionFields m_fields;
		UnsignedInt m_value;
	};
};
extern Debug *theDebug;
class VictoryTransferStreamView {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
 virtual void s30();virtual void s34();virtual VictoryTransferStreamView &Put_String(const char *);
 virtual void s3C();virtual void s40();virtual void s44();virtual void s48();
 virtual void Finish(int);
};
class VictoryTransferDiagnosticView {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
 virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
 virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
 virtual void s30();virtual void s34();virtual void s38();virtual void s3C();
 virtual void s40();virtual void s44();virtual void s48();virtual void s4C();
 virtual void s50();virtual void s54();virtual void s58();virtual void s5C();
 virtual void Begin_Report();virtual void s64();virtual void s68();
 virtual VictoryTransferStreamView *Get_Stream(int,int,int);
};
void _bfme_debugRecordCallsite(int);
struct BfmeStringRecord00404BF3 {
 __declspec(dllimport) __forceinline BfmeStringRecord00404BF3() : name()
 {
  allyScale = 0.0f;
  enemyScale = 0.0f;
  cellRatio = 0.0f;
  threshold = 0.0f;
  majorValue = 0.0f;
 }
 AsciiString name;
 Real allyScale,enemyScale,cellRatio,threshold,majorValue;
};
struct Rva0040538FElement {char bytes[24];};
namespace _STL {
 template<>void vector<BfmeStringRecord00404BF3>::push_back(const BfmeStringRecord00404BF3&);
 template<>Rva0040538FElement *vector<Rva0040538FElement>::erase(Rva0040538FElement*,Rva0040538FElement*);
}
class Rva0040471BXfer;
class Rva0040471B
{
public:
	void rva0040471B(Rva0040471BXfer *);
};
class Rva00404AB1
{
public:
	void rva00404AB1(Xfer *);
private:
	char bytes[168];
};
#include "../../../Include/Common/CellGrid.h"
// xfer is slot 3 of the Snapshot vftable 0x008388C4; its this is the
// Snapshot subobject (+0x0C), so member offsets come out twelve less.
class VictorySystem : public SubsystemInterface, public Snapshot
{
public:
	VictorySystem();
	virtual ~VictorySystem();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void LoadPostProcess() {}
	virtual const char *GetSnapshotName() const { return "VictorySystem"; }
	virtual void DoXfer(Xfer *xfer);
	virtual void newMap();
private:
 Real m_cellSize;UnsignedInt m_field10;Real m_firstScale,m_secondScale,m_field1c,m_field20;
 Int m_playerParameterIndex[20];
 Rva00404AB1 m_rootCell;
 _STL::vector<BfmeStringRecord00404BF3> m_factionVictoryParameters;
 CellGrid *m_cellGrids[2];
 Bool m_initialized;unsigned char m_padding[3];UnsignedInt m_activeGrid,m_currentPlayer;
};
void VictorySystem::DoXfer(Xfer *xfer)
{
	UnsignedInt gridCount;
	Xfer::Version version;
	version.m_fields.m_version = 1;
	version.m_fields.m_currentVersion = 1;
	xfer->operator==(version);

	xfer->operator==(m_initialized);
	xfer->operator==(m_cellSize);
	xfer->operator==(m_field10);
	xfer->operator==(m_firstScale);
	xfer->operator==(m_secondScale);
	xfer->operator==(m_field1c);
	xfer->operator==(m_field20);

	m_rootCell.rva00404AB1(xfer);
	xfer->XferRawBytes(m_playerParameterIndex, 0x50);

	if (xfer->IsLightCRC())
		return;

	if (xfer->IsLoading())
	{
		_STL::vector<Rva0040538FElement> &parameters =
   *reinterpret_cast<_STL::vector<Rva0040538FElement> *>(&m_factionVictoryParameters);
  parameters.erase(parameters.begin(), parameters.end());

		UnsignedInt parameterCount = 0;
		xfer->operator==(parameterCount);
		for (UnsignedInt index = 0; index < parameterCount; ++index)
		{
			BfmeStringRecord00404BF3 parameters;
   reinterpret_cast<Rva0040471B *>(&parameters)->rva0040471B(reinterpret_cast<Rva0040471BXfer *>(xfer));
			m_factionVictoryParameters.push_back(parameters);
		}
	}

	else if (xfer->IsStoring())
	{
		UnsignedInt parameterCount = m_factionVictoryParameters.size();
		xfer->operator==(parameterCount);
		for (UnsignedInt index = 0;
				index < m_factionVictoryParameters.size(); ++index)
		{
			BfmeStringRecord00404BF3 &parameters = m_factionVictoryParameters[index];
   reinterpret_cast<Rva0040471B *>(&parameters)->rva0040471B(reinterpret_cast<Rva0040471BXfer *>(xfer));
		}
	}

	gridCount = 2;
	xfer->operator==(gridCount);
	if (gridCount != 2)
	{
		_bfme_debugRecordCallsite(1);
		((VictoryTransferDiagnosticView *)theDebug)->Begin_Report();
		((VictoryTransferDiagnosticView *)theDebug)->Get_Stream(0, 0, 0)
   ->Put_String("Cell Grid count != VS_CELL_GRID_COUNT, DoXFer failed!").Finish(1);
	}

	if (xfer->IsLoading())
	{
		Bool anyGrid = false;
		for (UnsignedInt index = 0; index < gridCount; ++index)
		{
			if (m_cellGrids[index] != 0)
				anyGrid |= m_cellGrids[index]->rva0056C50E(xfer);
		}

		if (anyGrid)
			newMap();
	}
	else if (xfer->IsStoring())
	{
		for (UnsignedInt index = 0; index < gridCount; ++index)
		{
			if (m_cellGrids[index] != 0)
				m_cellGrids[index]->rva0056C50E(xfer);
		}
	}
}
