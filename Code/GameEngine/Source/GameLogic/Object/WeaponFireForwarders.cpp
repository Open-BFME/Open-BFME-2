// cl: -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	unsigned char m_bfmeHeadYB[0x74];
	int m_id;
};

#include "../../../Include/GameLogic/Weapon.h"

bool Weapon::bfmeFireYC(const Object *src, const Coord3D *pos, const Object *tgt, int n)
{
	return privateFireWeapon(src, pos, tgt, tgt->m_id, 0, 1, 0, n, 0);
}
