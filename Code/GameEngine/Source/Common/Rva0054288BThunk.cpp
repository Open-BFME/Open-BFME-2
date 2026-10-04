// cl: /O1 /MD /Oi-
// ?rva0054288B@Rva0054288B@@QAEXXZ, retail 0x0054288B, 5 bytes.
// Tail-jmp to rowed 0x005427F1 ?rva005427F1@Rva005427F1@@QAEXXZ.
// Evidence: packet disassembly (jmp 0x005427F1), callees all rowed,
// callers 0x00338301 and unwind, prev/next flags.
class Rva005427F1
{
public:
	void rva005427F1();
};

class Rva0054288B
{
public:
	void rva0054288B();
};

void Rva0054288B::rva0054288B()
{
	((Rva005427F1 *)this)->rva005427F1();
}
