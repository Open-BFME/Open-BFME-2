// cl: -DNDEBUG -MD -EHsc- -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Contain/HordeContain

// Refresh0023FA80Primary::scheduleNullable is an inline in the donor
// FormationRefresh0023FA80.cpp:
//     void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj)
//     { if (ai && obj) schedule(ai,obj); }
// Retail 0x002B388D null-checks both and tail-jumps to the out-of-line schedule
// at 0x002B37B4; that callee has no proven name, so it is pinned under the
// address-derived name rva002B37B4. Donor's other bodies omitted.
class Refresh0023FA80AI;
class Refresh0023FA80Object;

class Rva002B37B4
{
public:
	void rva002B37B4( Refresh0023FA80AI *ai, Refresh0023FA80Object *obj );
};

class Refresh0023FA80Primary
{
public:
	void scheduleNullable( Refresh0023FA80AI *ai, Refresh0023FA80Object *obj );
};

void Refresh0023FA80Primary::scheduleNullable( Refresh0023FA80AI *ai, Refresh0023FA80Object *obj )
{
	if (ai && obj)
		((Rva002B37B4 *)this)->rva002B37B4(ai, obj);
}
