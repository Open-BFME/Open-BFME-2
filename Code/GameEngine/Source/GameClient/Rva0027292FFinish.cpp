// cl: /DNDEBUG /MD /EHsc
// Native27292F..27294522B forwards position/normal coordinate pointers
// to first draw module14C vslot64. Target275C79..275D95 passes addresses
// of native twelve-byte position and normal locals; the former donor
// setTerrainDecalSize(float,float) attribution is refuted by this caller.
// Original BFME2 method spelling remains unresolved.
#include "../../../Libraries/Include/Lib/Coord3D.h"
class DrawableDecalPositionModule
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void rva0027292F(const Coord3D *position, const Coord3D *normal) = 0;
};

class Drawable
{
public:
	void rva0027292F(const Coord3D *position, const Coord3D *normal);
private:
	char m_pad[0x14C];
	DrawableDecalPositionModule **m_drawModules;
};

// ?rva0027292F@Drawable@@QAEXPBUCoord3D@@0@Z
void Drawable::rva0027292F(const Coord3D *position, const Coord3D *normal)
{
	DrawableDecalPositionModule **p = m_drawModules;
	if (*p)
		(*p)->rva0027292F(position, normal);
}
