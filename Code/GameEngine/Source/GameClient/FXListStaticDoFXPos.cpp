// cl: /Oy- /DNDEBUG /MD /GX-
//
// ?doFXPos@FXList@@SAXPBV1@PBUCoord3D@@PBVMatrix3D@@M1@Z
// retail 0x00094C29 47 bytes. Static FXList::doFXPos wrapper.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h,
// FXList::doFXPos static inline null-guard): BFME2 materializes the inline as
// a 47B out-of-line body with an extra gate through the pinned 0x1E2EF1
// predicate before forwarding to the rowed member doFXPos 0x1E296E. Callers at
// 0x9575C 0xB1C12 0xB586F 0xB58C1 pass FXList plus pos plus mtx plus speed
// plus secondary and clean 0x14 (cdecl).

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
	float m[12];
};

class FXList
{
public:
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) const;
	bool rva001E2EF1() const;
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

void FXList::doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary)
{
	if (fx && !fx->rva001E2EF1())
		fx->doFXPos(primary, mtx, speed, secondary);
}
