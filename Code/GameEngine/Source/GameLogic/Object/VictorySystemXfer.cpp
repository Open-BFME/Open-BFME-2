// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// Semantic donor: BF1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/VictorySystemXfer.cpp.
// WB10771D0 names VictorySystem::DoXfer and VictorySystem.cpp. Native
// 4056ED..40596C proves twenty indices, 168-byte root cell, 24-byte faction
// records, grid transfer56C50E and the diagnostic string/return chain.
// This view starts at the Snapshot subobject, twelve bytes after the complete
// VictorySystem (independently proved by GameStateInit). It preserves the
// canonical Snapshot base and does not assert a complete subsystem layout.
// Primary slot38's original method name remains unresolved. Member labels
// follow the donor only where the target transfer sequence agrees.
// Native Xfer table7BB910 proves Version10, raw9, float28, uint30 and bool36.
// The record constructor is expanded at its sole use, as native instructions
// show; no imported constructor call or standalone constructor body is used.
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"
typedef bool Bool;
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

union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
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
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(Real *value);
	virtual void slot29();
	virtual void xferUnsignedInt(UnsignedInt *value);
 virtual void xferInt(Int *value);
 virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
 virtual void xferBool(Bool *value);
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
class VictoryPrimaryView {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot38();
};
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
class CellGrid
{
public:
	Bool rva0056C50E(Xfer *);
};
class VictorySystemSnapshotView : public Snapshot
{
public:
	void rva004056ED(Xfer *xfer);
private:
 Real m_cellSize;UnsignedInt m_field10;Real m_firstScale,m_secondScale,m_field1c,m_field20;
 Int m_playerParameterIndex[20];
 Rva00404AB1 m_rootCell;
 _STL::vector<BfmeStringRecord00404BF3> m_factionVictoryParameters;
 CellGrid *m_cellGrids[2];
 Bool m_initialized;unsigned char m_padding[3];UnsignedInt m_activeGrid,m_currentPlayer;
};
void VictorySystemSnapshotView::rva004056ED(Xfer *xfer)
{
	UnsignedInt gridCount;
	XferVersion version;
	version.m_fields.m_version = 1;
	version.m_fields.m_currentVersion = 1;
	xfer->xferVersion(&version);

	xfer->xferBool(&m_initialized);
	xfer->xferReal(&m_cellSize);
	xfer->xferUnsignedInt(&m_field10);
	xfer->xferReal(&m_firstScale);
	xfer->xferReal(&m_secondScale);
	xfer->xferReal(&m_field1c);
	xfer->xferReal(&m_field20);

	m_rootCell.rva00404AB1(xfer);
	xfer->xferUser(m_playerParameterIndex, 0x50);

	if (xfer->IsLightCRC())
		return;

	if (xfer->IsLoading())
	{
		_STL::vector<Rva0040538FElement> &parameters =
   *reinterpret_cast<_STL::vector<Rva0040538FElement> *>(&m_factionVictoryParameters);
  parameters.erase(parameters.begin(), parameters.end());

		UnsignedInt parameterCount = 0;
		xfer->xferUnsignedInt(&parameterCount);
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
		xfer->xferUnsignedInt(&parameterCount);
		for (UnsignedInt index = 0;
				index < m_factionVictoryParameters.size(); ++index)
		{
			BfmeStringRecord00404BF3 &parameters = m_factionVictoryParameters[index];
   reinterpret_cast<Rva0040471B *>(&parameters)->rva0040471B(reinterpret_cast<Rva0040471BXfer *>(xfer));
		}
	}

	gridCount = 2;
	xfer->xferUnsignedInt(&gridCount);
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
			reinterpret_cast<VictoryPrimaryView *>(reinterpret_cast<char *>(this)-12)->slot38();
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
