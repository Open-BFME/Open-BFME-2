// cl: /DNDEBUG /MD /EHsc
//
// ?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z,
// retail 0x005C9886, 58 bytes. Dedicated TU.
//
// BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/LocomotorStore_newLocomotor.cpp):
// one line `return new Locomotor(tmpl)` with plain global operator new.
// BFME2 adaptations (all retail-measured): sizeof(Locomotor) is 0x26C
// (retail pushes 0x26C; BFME1 pushes 0xA8), ctor is the unclaimed 0x5C96EB
// (pinned); /O1 selects the outlined __EH_prolog head
// (mov eax,scope + call 0x629188; pool-key law).

typedef int Int;
typedef bool Bool;

class LocomotorTemplate;

// ?0Locomotor@@QAE@PBVLocomotorTemplate@@@Z placeholder: real class is 0x26C;
// only the size and ctor matter here.
class Locomotor
{
public:
	Locomotor(const LocomotorTemplate *tmpl);

private:
	char m_bfme_body[0x26C];
};

class LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl) const;
};

// ?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z
inline Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl) const
{
	return new Locomotor(tmpl);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
Locomotor * (LocomotorStore::*_bfmeInlineAnchor_LocomotorStore_newLocomotor_0)(const LocomotorTemplate *tmpl) const = &LocomotorStore::newLocomotor;
