// cl: /MD
// Target evidence: Ghidra boundary 0x0046E7C2, 33 bytes. It reads this+8,
// then module+0x258, and calls the adjacent Ghidra function 0x0046E740 with
// zero when both tests pass. Type names stay address-derived.
struct Rva0046E7C2Module {
	char opaque00[0x258];
	void *field258;
};

class Rva0046E740 {
public:
	void rva0046E740(int value);
};

class Rva0046E7C2 {
public:
	char opaque00[8];
	Rva0046E7C2Module *module;
	void rva0046E7C2();
};

void Rva0046E7C2::rva0046E7C2()
{
	Rva0046E7C2Module *module = this->module;
	if (module ? module->field258 : 0) {
		if (module) {
			((Rva0046E740 *)this)->rva0046E740(0);
		}
	}
}
