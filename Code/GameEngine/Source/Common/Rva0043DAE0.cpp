// cl: /O1 /DNDEBUG /MD
// ??1Rva0043DAE0@@UAE@XZ @0x0043DAE0 11B
// Evidence: chain from 0x0057F2DE, stores vtable 0x00C3D95C then jmp to ??1Rva0057F2DE@@UAE@XZ; callers 0x0043DB0A 0x00788C09 0x00788CA7.
// ??0Rva0043DAE0@@QAE@PAUTargetRef00217D4C@@@Z @0x0043DAC8 24B: the
// constructor, base 0x0057F486 (unrowed, pinned) then vtable 0x00C3D95C; the
// MpGameSetup panel ctor 0x00441F4E builds its +0x190 member with it from the
// owner's holder 1 (rowed 0x0043F103).
struct TargetRef00217D4C;

class Rva0057F2DE
{
public:
	Rva0057F2DE(TargetRef00217D4C *ref);
	virtual ~Rva0057F2DE();
};

class Rva0043DAE0 : public Rva0057F2DE
{
public:
	Rva0043DAE0(TargetRef00217D4C *ref);
	virtual ~Rva0043DAE0();
};

Rva0043DAE0::Rva0043DAE0(TargetRef00217D4C *ref) : Rva0057F2DE(ref)
{
}

Rva0043DAE0::~Rva0043DAE0()
{
}
