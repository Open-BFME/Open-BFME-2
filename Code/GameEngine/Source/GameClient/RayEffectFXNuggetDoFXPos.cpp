// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?doFXPos@RayEffectFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z, retail
// 0x001E022D (212 bytes, RET 16), slot 1 of the RayEffect nugget's vtable
// 0x00BDD77C: Zero Hour's RayEffectFXNugget::doFXPos (FXList.cpp) with BFME 2's
// four-argument doFXPos (no override radius): look up the template named at
// +0x148 and, given a primary, a secondary and the template, offset both
// positions by the nugget's offsets (+0x14C primary, +0x158 secondary) and ask
// TheGameClient (slot 21, 0x54) to create the ray effect between them.
// The position copy is the per-field helper (a struct copy would use movs and spill EBX/EDI);
// the offsets are added field by field straight from the nugget.
// Evidence: BFME1 FXList.cpp donor 575ba2b semantic shape; field offsets from the
// retail ctor 0x001E01B2 and the parse table 0x00BDCB58; the same name lookup
// 0x002D06CA the laser nugget uses.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"

static inline void coordCopy(Coord3D *to, const Coord3D *from) {
 to->x = from->x; to->y = from->y; to->z = from->z;
}
class Matrix3D;
class ThingTemplate;

#include "../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

class GameClient
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void createRayEffectByTemplate(const Coord3D *start, const Coord3D *end, const ThingTemplate *tmpl);	// +0x54
};
extern GameClient *TheGameClient;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
};

class RayEffectFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;

private:
	unsigned char m_pad04[0x148 - 4];
	AsciiString m_templateName;	// +0x148
	Coord3D m_primaryOffset;	// +0x14C
	Coord3D m_secondaryOffset;	// +0x158
};

void RayEffectFXNugget::doFXPos(const Coord3D *primary, const Matrix3D * /*primaryMtx*/, float /*primarySpeed*/, const Coord3D *secondary) const
{
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(m_templateName);
	if (primary && secondary && thingTemplate)
	{
		Coord3D sourcePos;
		coordCopy(&sourcePos, primary);
		sourcePos.x += m_primaryOffset.x;
		sourcePos.y += m_primaryOffset.y;
		sourcePos.z += m_primaryOffset.z;

		Coord3D targetPos;
		coordCopy(&targetPos, secondary);
		targetPos.x += m_secondaryOffset.x;
		targetPos.y += m_secondaryOffset.y;
		targetPos.z += m_secondaryOffset.z;

		TheGameClient->createRayEffectByTemplate(&sourcePos, &targetPos, thingTemplate);
	}
}
