// cl: /EHsc /MD
//
// ?rva00405AA7@Rva00405AA7@@QAEXXZ @0x00405AA7 (34B):
// Clears +0x2A4 via rowed Rva000AD6F4::clear then notifies
// theRadarWindowOverrideSource via rowed rva002D370A.
// Evidence: caller 0x003BBB26 passes g_bfmeWorldRV in ecx with no stack args;
// same +0x2A4 as neighbour 0x00405A50; callees rowed; jmp tail to 0x002D370A.

class Rva000AD6F4
{
public:
	void clear();
};

class RadarWindowOverrideSource
{
public:
	void rva002D370A();
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Rva00405AA7
{
public:
	void rva00405AA7();
private:
	char m_pad[0x214];
	unsigned char m_214;
	char m_pad2[0x2a4 - 0x214 - 1];
	Rva000AD6F4 m_2a4;
};

void Rva00405AA7::rva00405AA7()
{
	m_214 = 0;
	m_2a4.clear();
	if (theRadarWindowOverrideSource)
		theRadarWindowOverrideSource->rva002D370A();
}
