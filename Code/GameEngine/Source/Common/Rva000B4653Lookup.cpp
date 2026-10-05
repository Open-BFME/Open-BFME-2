// cl: /O1 /MD /EHsc /DNDEBUG
//
// ?rva000B4653@Rva000B4653@@QAEPAXH@Z @0x000B4653 29B: masked-index read.
// When the unsigned argument is below (m_0 & 7), resolves the pinned
// 0x000B2361 slot dispatcher on this and returns the slot's pointer;
// otherwise returns null. Honest address-derived names; boundary
// verified (frameless at 0xB4653, ret 4 at end).

struct Rva000B2361Slot
{
	void *ptr;
};

class Rva000B4653
{
public:
	Rva000B2361Slot *rva000B2361(int a);
	void *rva000B4653(int a);

private:
	int m_0;
};

// ?rva000B4653@Rva000B4653@@QAEPAXH@Z
void *Rva000B4653::rva000B4653(int a)
{
	if ((unsigned int)a < (unsigned int)(m_0 & 7))
		return rva000B2361(a)->ptr;
	return 0;
}
