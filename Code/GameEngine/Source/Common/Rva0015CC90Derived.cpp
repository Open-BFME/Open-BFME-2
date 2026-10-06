// cl: /MD
//
// Opaque single-inheritance destructor tail-calling Rva0015CC90::~
// Rva0015CC90 at 0x0015CC90 (pinned opaque SEH base dtor; identity unproven).
// The class below stores its own vtable (0xBD3CF4, DIR32 auto-patch) and
// tail-calls the base destructor; the base itself is only declared here
// (defined nowhere -- it resolves via the pin), because a same-TU definition
// would capture the call locally instead of at the ledger address. Owner
// identity is unproven (opaque Rva name). One ledger row per destructor,
// landed one commit at a time.

class Rva0015CC90
{
public:
	virtual ~Rva0015CC90();
};

class Rva0015D0E0 : public Rva0015CC90
{
public:
	virtual ~Rva0015D0E0();
};

Rva0015D0E0::~Rva0015D0E0()
{
}
