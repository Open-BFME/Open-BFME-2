// cl: /O1 /DNDEBUG /MD
// ?rva00318F64@Rva00318F64@@QAEXXZ @0x00318F64 39B. Sync dwords at +0x34/+0x38
// from +0x44/+0x48 then refresh cached value at +0x2C via rowed
// Rva00318C79Owner::rva00318C79 0x00318C79 on the same object; on match bump
// count at +0x30 else clear it and store the new value. Evidence: callers
// 0x003193D4 and 0x0031A564; callees rowed; neighbours Rva00318E8CGet and
// Rva00318FBEGet give TU and flags.
class Rva00318C79Owner
{
public:
	int rva00318C79();
};

class Rva00318F64
{
public:
	void rva00318F64();
private:
	char m_pad00[0x2C];
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	char m_pad3C[0x8];
	int m_44;
	int m_48;
};

void Rva00318F64::rva00318F64()
{
	m_34 = m_44;
	m_38 = m_48;
	int v = ((Rva00318C79Owner *)this)->rva00318C79();
	if (m_2C == v)
		++m_30;
	else {
		m_30 = 0;
		m_2C = v;
	}
}
