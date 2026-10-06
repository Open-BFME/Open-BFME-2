// cl: /MD
// Target evidence: Ghidra starts 0x0046AA69 at 28 bytes. Retail saves this,
// calls the matched anonymous destructor at 0x00469DCE, tests delete flag bit 0,
// conditionally calls operator delete at 0x0002FD60, returns this, and ret 4.
// The target object's class identity is unresolved, so keep the type address-derived.
extern void __cdecl dup_00469dce();

class Rva0046AA69 {
public:
	~Rva0046AA69() { dup_00469dce(); }
};

void Rva0046AA69_Delete(Rva0046AA69 *p) { delete p; }
