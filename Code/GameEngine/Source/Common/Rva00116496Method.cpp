// cl: /DNDEBUG /MD /EHsc
// ?rva00116496@Rva00116496@@QAEXXZ, retail 0x00116496 (20B).
// Evidence: unlock lane (unblocks 0x00111B9A plus 3); callers at 0x00102244
// 0x00102274 0x0010228D 0x00111BB8; flag at +4 with slot 0x0C then clear;
// siblings 0x00116482 0x001164AA share /O1 /G7 and layout.
class Rva00116496
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	void rva00116496();
private:
	bool m_flag;
};

void Rva00116496::rva00116496()
{
	if (m_flag)
	{
		s0C();
		m_flag = false;
	}
}
