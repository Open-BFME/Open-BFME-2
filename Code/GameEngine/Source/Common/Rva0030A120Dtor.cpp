// cl: /DNDEBUG /MD
// ??1Rva0030A120@@UAE@XZ @0x0030A120 13B.
//
// Unknown-class virtual dtor. Stores vtable 0x008086E0 and decrements
// global 0x009FF4A8. Called from deleting dtor 0x0030A243 plus large dtors
// 0x002793F0 and 0x00299CE4 which restore Snapshot base 0x00BBB554 at +0x60
// before the call. Honest Rva name pending class recovery.
class Rva0030A120
{
public:
	virtual ~Rva0030A120();
};
int g_Rva0030A120Count;
Rva0030A120::~Rva0030A120()
{
	--g_Rva0030A120Count;
}
