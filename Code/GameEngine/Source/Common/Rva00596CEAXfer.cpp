// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva00596CEA@Rva00596CDF@@UAEXPAVXfer@@PAX@Z @0x00596CEA 147B
// Xfer slot 12 (0x30) of Rva00596CDF (vtable 0x00870AF0, derived of Rva00573B23):
// Version(1,1), base Rva00573B23::Rva00573A35 first, Coord +0x40 via 0x60,
// ObjectID +0x4c via XferObjectID, uint +0x50 via 0x78, int +0x54 via 0x7c,
// bool +0x58 via 0x90, then IsLoading tail: m_58!=0 m_10==0 arg2!=0 calls
// Slot6(arg2,1) via slot 0x18. Chain from 0x00573A35. Unblocks 0x004EB092.
// Evidence: call [eax+28] bytes 1,1; call 0x573A35; virtuals 0x60 XferObjectID
// 0x78 0x7c 0x90; call [eax+4] test je xor cmp je cmp jne cmp je call [eax+18].
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase;
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
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/Common/XferVersion.h"
#include "GameLogicObjectLookupView.h"
void XferObjectID(Xfer *xfer, ObjectID *objectID);
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3DBase.h"

// Rva00573B23 (vftable 0x00C6E270) and its derived Rva00596CDF (vftable
// 0x00C70AF0, installed by 0x00596C85 and 0x00596CDF), one view for every
// body of this TU. Target facts: 0x00C70AF0 holds registerWithBuilder
// 0x00596C7C in slot 6 and the transfer 0x00596CEA in slot 12, and the
// transfer calls the base's slot-12 transfer 0x00573A35 directly. Slots with
// no rowed spelling in this hierarchy stay pure, so the table this TU emits
// names nothing the link cannot resolve; it is not retail's table.
class Rva00573B23
{
public:
	Rva00573B23();									// 0x00573A9B
	virtual ~Rva00573B23();							// slot 0, 0x00573B23
	virtual void vslot01() = 0;
	virtual void vslot02() = 0;
	virtual void vslot03() = 0;
	virtual void vslot04() = 0;
	virtual void vslot05() = 0;
	virtual void registerWithBuilder(void *builder, bool flag) = 0;	// slot 6
	virtual void vslot07() = 0;
	virtual void vslot08() = 0;
	virtual void vslot09() = 0;
	virtual void vslot10() = 0;
	virtual void vslot11() = 0;
	virtual void Rva00573A35(Xfer *xfer, void *arg2);	// slot 12, 0x00573A35
	float rva00573DCD(int player);					// 0x00573DCD
protected:
	char m_unknown04[0x10 - 0x04];
	unsigned int m_10;
	char m_unknown14[0x40 - 0x14];
};

struct WallOrderPosition : Coord3DBase
{
    __forceinline WallOrderPosition() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

class Rva00596CDF : public Rva00573B23
{
public:
	Rva00596CDF(unsigned int key);					// 0x00596C85
	virtual ~Rva00596CDF();							// 0x00596CDF
	virtual void registerWithBuilder(void *builder, bool flag);	// 0x00596C7C
	virtual void Rva00596CEA(Xfer *xfer, void *arg2);	// 0x00596CEA
private:
	WallOrderPosition position40;
	ObjectID objectID4c;
	unsigned int key50;
	int value54;
	bool value58;
};

void Rva00596CDF::Rva00596CEA(Xfer *xfer, void *arg2)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	Rva00573B23::Rva00573A35(xfer, arg2);
	*xfer == position40;
	XferObjectID(xfer, &objectID4c);
	*xfer == key50;
	*xfer == value54;
	*xfer == value58;
	if (xfer->IsLoading() && value58 && m_10 == 0 && arg2 != 0) {
		registerWithBuilder(arg2, true);
	}
}
