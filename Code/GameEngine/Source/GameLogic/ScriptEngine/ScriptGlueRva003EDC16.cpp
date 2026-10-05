// cl: /O1 /DNDEBUG /MD
//
// ?rva003EDC16@Rva003EDC16@@QAEXXZ @0x003EDC16 27B (dump range 18).
// Pointer-array walk: calls the pinned 0x00569AA8 member on each element
// of the [this+0x1C, this+0x20) pointer array.
class Rva00569AA8
{
public:
	void rva00569AA8();
};

class Rva003EDC16
{
public:
	void rva003EDC16();
private:
	char m_pad[0x1C];
	void **m_begin; // +0x1C
	void **m_end; // +0x20
};

void Rva003EDC16::rva003EDC16()
{
	for (void **it = m_begin; it != m_end; ++it)
		((Rva00569AA8 *)*it)->rva00569AA8();
}
