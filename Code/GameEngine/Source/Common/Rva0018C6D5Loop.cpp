// cl: /O1 /G7 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: short-key insert loop at 0x18C6D5 (48B). For each 2-byte
// element in [first,last), copies it through a short local homed in the dead
// first-param slot (mov ax with a full-eax store and no xor under the P4
// scheduler) and calls 0x18C4A9(&result, &w) with this passed through in edi.
// The 8-byte result (ptr + inserted-flag per 0x18C4A9's own writes at the
// end of its body) is never read back. /G7 is what drops the blend-schedule
// xor; the STLport tree TUs use the same scheduler. Address-derived names;
// callee types unproven (short* pin: it reads a word key).

class Rva0018C4A9
{
public:
	void rva0018C4A9(void *out, short *key);
};
struct Rva0018C6D5Result
{
	void *pos;
	bool inserted;
};
class Rva0018C6D5
{
public:
	void rva0018C6D5(const unsigned short *first, const unsigned short *last);
};

// ?rva0018C6D5@Rva0018C6D5@@QAEXPBG0@Z
void Rva0018C6D5::rva0018C6D5(const unsigned short *first, const unsigned short *last)
{
	Rva0018C6D5Result ignored;
	for (const unsigned short *p = first; p != last; ++p) {
		short w = (short)*p;
		((Rva0018C4A9 *)this)->rva0018C4A9(&ignored, &w);
	}
}
