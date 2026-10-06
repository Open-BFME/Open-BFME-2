// cl: /MD
//
// ?rva00444462@Rva00444462@@QAEXXZ, retail 0x00444462, 11 bytes.
// Tail jmp to enable at this+0x288 via rowed 0x0043DB56.
// Evidence: add ecx 0x288 plus jmp, prev GameEngine 0x004443E7.

class Rva0043DB56ByteOneSetter
{
public:
	void enable();
};

class Rva00444462
{
public:
	void rva00444462();

private:
	unsigned char m_pad00[0x288];
	Rva0043DB56ByteOneSetter m_field;
};

void Rva00444462::rva00444462()
{
	return m_field.enable();
}
