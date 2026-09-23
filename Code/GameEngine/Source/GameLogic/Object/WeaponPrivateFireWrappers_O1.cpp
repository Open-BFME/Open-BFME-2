// cl: /O1 /DNDEBUG /MD /EHs-c-
// Donor provenance: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Weapon_privateFireWeaponWrappers.cpp
// Target callers establish Weapon receivers; Object fields are position +0x38
// and ID +0x74. Address-based method names and control arguments remain neutral.
struct Coord3D { float x, y, z; };
class Object { public: char m_pad[0x38]; Coord3D m_position; char m_pad44[0x30]; int m_id; };
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
class GameLogic { public: Object *findObjectByID(ObjectID id); };
extern GameLogic *TheGameLogic;
extern GameLogic *TheGameLogic;
class Weapon {
public:
    bool privateFireWeapon(const Object *source, const Coord3D *sourcePos, const Object *target,
        int targetID, const Coord3D *targetPos, int arg6, int arg7, int arg8, int *projectileID);
    bool fireWeapon(const Object *source, const Coord3D *pos, int *projectileID);
    bool rva002CE6C5(const Object *source, int targetID, const Object *target, int *projectileID);
    Object *forceFireWeapon(const Object *source, const Coord3D *pos);
};
bool Weapon::fireWeapon(const Object *source, const Coord3D *pos, int *projectileID)
{
	return privateFireWeapon(source, &source->m_position, 0, 0, pos, 0, 0, 0, projectileID);
}

bool Weapon::rva002CE6C5(const Object *source, int targetID, const Object *target, int *projectileID)
{
	return privateFireWeapon(source, &source->m_position, target, targetID, 0, 0, 0, 0, projectileID);
}

Object *Weapon::forceFireWeapon(const Object *source, const Coord3D *pos)
{
	int id = 0;
	privateFireWeapon(source, &source->m_position, 0, 0, pos, 1, 0, 0, &id);
	return TheGameLogic->findObjectByID((ObjectID)id);
}
