// cl: /DNDEBUG /MD /EHs-c-
// Donor provenance: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Weapon_privateFireWeaponWrappers.cpp
// Target callers establish Weapon receivers; Object fields are position +0x38
// and ID +0x74. Address-based method names and control arguments remain neutral.
struct Coord3D { float x, y, z; };
class Object { public: char m_pad[0x38]; Coord3D m_position; char m_pad44[0x30]; int m_id; };
class Weapon {
public:
    bool privateFireWeapon(const Object *source, const Coord3D *sourcePos, const Object *target,
        int targetID, const Coord3D *targetPos, int arg6, int arg7, int arg8, int *projectileID);
    bool rva002CE74B(const Object *source, const Object *target);
};
bool Weapon::rva002CE74B(const Object *source, const Object *target)
{
    return privateFireWeapon(source, &source->m_position, target, target->m_id, 0, 1, 1, 0, 0);
}
