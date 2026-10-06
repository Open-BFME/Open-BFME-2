// cl: /DNDEBUG /MD
// ?rva0030E09A@Rva0030E09A@@QAEXXZ @0x0030E09A 16B: wrapper calls rowed rva0030D606 then tail-jmps pinned bfmeRunEYE on same this
// Evidence: callee row 0x0030D606 ?rva0030D606@Rva0030D606@@QAEXXZ plus pin 0x0030DEAE ?bfmeRunEYE@BfmeNodeEYE@@QAEXXZ caller 0x0030E266
class Rva0030D606
{
public:
	void rva0030D606();
};

struct BfmeNodeEYE
{
	void bfmeRunEYE();
};

class Rva0030E09A
{
public:
	void rva0030E09A();
};

void Rva0030E09A::rva0030E09A()
{
	((Rva0030D606 *)this)->rva0030D606();
	((BfmeNodeEYE *)this)->bfmeRunEYE();
}
