// cl: /O1
// ?rva004E7B0C@Rva004E7B0CHolder@@QAEXXZ, RVA 0x004E7B0C size 7.
// Leaf lane with LINK BONUS (1 file 64B waits only for this body).
// Evidence: LINK BONUS names this exact mangling; callee row 0x004E7A85;
// callers at 0x004CC60F and 0x004CC59A; neighbours share /O1.
class Rva004E7A85
{
public:
	void rva004E7A85();
};
class Rva004E7B0CHolder
{
public:
	void rva004E7B0C();
private:
	Rva004E7A85 *m_ptr;
};
void Rva004E7B0CHolder::rva004E7B0C()
{
	m_ptr->rva004E7A85();
}
