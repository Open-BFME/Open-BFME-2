// cl: /MD
// ?rva0042094D@Rva0042094D@@QAEHH@Z, retail 0x0042094D, 24 bytes.
// Bounded array getter: returns m_data[index] for 0 <= index < 8 else 0.
// Array at +4 (8 ints). Evidence: ret 4 plus scale-4 load plus jl/jge to xor;
// callers at 0x0059D761 and 0x0059D792; unblocks 0x0059D74B.
class Rva0042094D
{
public:
	int rva0042094D(int index);
private:
	int m_pad00;
	int m_data[8];
};

int Rva0042094D::rva0042094D(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return m_data[index];
}
