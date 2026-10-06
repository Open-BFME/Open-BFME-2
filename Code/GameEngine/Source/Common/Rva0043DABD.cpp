// cl: /DNDEBUG /MD
// ??1Rva0043DABD@@UAE@XZ @0x0043DABD 11B
// Evidence: chain dtor stores vtable 0x0083D954 then tail-jmps to rowed base 0x0057EE5C. Callers 0x0043DAEE plus unwind funclets. Prev 0x0043DA65 next 0x0043DAE0.
// ??0Rva0043DABD@@QAE@PAUTargetRef00217D4C@@@Z @0x0043DAA5 24B: the
// constructor, base 0x0057EDB2 (unrowed, pinned) then vtable 0x00C3D954;
// the MpGameSetup panel ctor 0x00441F35 builds its +0xD0 member with it from
// the owner's holder 1 (rowed 0x0043F103).
struct TargetRef00217D4C;

class Rva0057EE5C
{
public:
	Rva0057EE5C(TargetRef00217D4C *ref);
	virtual ~Rva0057EE5C();
};

class Rva0043DABD : public Rva0057EE5C
{
public:
	Rva0043DABD(TargetRef00217D4C *ref);
	virtual ~Rva0043DABD();
};

Rva0043DABD::Rva0043DABD(TargetRef00217D4C *ref) : Rva0057EE5C(ref)
{
}

Rva0043DABD::~Rva0043DABD()
{
}
