// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva00145000::~
// Rva00145000 at 0x00145000 (pinned opaque SEH base dtor; identity unproven).
// The class below stores its own vtable (0xBD3544, DIR32 auto-patch) and
// tail-calls the base destructor; the base itself is only declared here
// (defined nowhere -- it resolves via the pin), because a same-TU definition
// would capture the call locally instead of at the ledger address. Owner
// identity is unproven (opaque Rva name). One ledger row per destructor,
// landed one commit at a time.

class Rva00145000
{
public:
	virtual ~Rva00145000();
};

class Rva00145610 : public Rva00145000
{
public:
	virtual ~Rva00145610();
};

Rva00145610::~Rva00145610()
{
}
