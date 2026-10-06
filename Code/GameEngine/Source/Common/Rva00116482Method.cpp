// cl: /DNDEBUG /MD /EHsc
// ?rva00116482@Rva00116482@@QAEXXZ, retail 0x00116482 (20B).
// Evidence: unlock lane; callers at 0x0010227B and 0x00102310 in unclaimed;
// flag at +4 with virtual slot 0x08 then set flag; sibling of 0x001164AA
// (/O1 /G7 for cmp-mem and small frameless shape).
class Rva00116482
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	void rva00116482();
private:
	bool m_flag;
};

void Rva00116482::rva00116482()
{
	if (!m_flag)
	{
		s08();
		m_flag = true;
	}
}
