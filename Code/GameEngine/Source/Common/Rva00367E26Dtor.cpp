// cl: /DNDEBUG /MD
// ??1Rva00367E26@@UAE@XZ @0x00367E26 11B
// Virtual dtor stores vtable 0x00C17600 then tail-jmps to the rowed base dtor
// ~AIStateMachine 0x003516F3. Evidence: deleting dtor 0x00367E0A calls this
// address with vtable 0x00C17600 slot 0; the constructor that installs
// 0x00C17600 (0x0036792F, Rva0036792FMachineCtor.cpp) first runs the rowed
// AIStateMachine constructor 0x00351C48.
class AIStateMachine
{
public:
	virtual ~AIStateMachine();
};
class Rva00367E26 : public AIStateMachine
{
public:
	virtual ~Rva00367E26();
};
Rva00367E26::~Rva00367E26()
{
}
