// cl: /O1 /G7 /MD /EHsc
// WB10488D0 names LivingWorldBattle::BattleResults::DoXfer in
// GameLogic/System/LivingWorld/LivingWorldBattle.cpp. Native3F3FFE..3F4096
// proves a player pointer at0 and four transferred integers at4/8/C/10.
// The player's ID at14 is independently used by the rowed lookup2B51F8.
// Xfer's native vtable7BB910 proves Version10 and signed integer31.
// Original field labels and full player extent remain unresolved; these
// address-qualified views preserve the existing lookup's type and ABI.
// Typed player access closes the earlier saved-ID register mismatch.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char UnsignedByte;
class AsciiString;
#include "../../../../Include/Common/XferVersionFields.h"

union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};

class Snapshot;

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
#include "../../../../Include/Common/BfmeXfer.h"

void XferLivingWorldPlayerID(Xfer *, int *);
class Rva002E2903Player
{
public:
	int getID() const { return id; }
	char unknown00[0x14];
	int id;
};
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva003F3FFE
{
public:
	void rva003F3FFE(Xfer &);
private:
	Rva002E2903Player *player;
	int counts[4];
};

void Rva003F3FFE::rva003F3FFE(Xfer &xfer)
{
	XferVersion version;
	version.m_fields.m_version = 1;
	version.m_fields.m_currentVersion = 1;
	(xfer == reinterpret_cast<Xfer::Version &>(version));
	(xfer == counts[0]);
	(xfer == counts[1]);
	(xfer == counts[2]);
	(xfer == counts[3]);
	if (xfer.IsLoading()) {
		int id;
		XferLivingWorldPlayerID(&xfer, &id);
		player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(id, 0);
	} else {
		int id = player ? player->getID() : -1;
		XferLivingWorldPlayerID(&xfer, &id);
	}
}
