// cl: /DNDEBUG /MD /EHsc
// Native27292F..27294522B forwards position/normal coordinate pointers
// to first draw module14C vslot64. Target275C79..275D95 passes addresses
// of native twelve-byte position and normal locals; the former donor
// setTerrainDecalSize(float,float) attribution is refuted by this caller.
// Original BFME2 method spelling remains unresolved.
#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"


// ?rva0027292F@Drawable@@QAEXPBUCoord3D@@0@Z
void Drawable::rva0027292F(const Coord3D *position, const Coord3D *normal)
{
	DrawModule **drawableDecalPositionModule = ((DrawModule **)m_modules[0]);
	if (*drawableDecalPositionModule)
		(*drawableDecalPositionModule)->rva0027292F(position, normal);
}
