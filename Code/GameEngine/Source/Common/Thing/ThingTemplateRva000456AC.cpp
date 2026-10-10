// cl: /MD
// ?rva000456AC@ThingTemplate@@QBEHH@Z @0x000456AC 21B: ThingTemplate kind-bit test via rowed helper.
// Evidence: caller Team countKind 0x0039DC05 passes Object+4 template with kind index; offset 0x108 is ThingTemplate kind bits per Handicap and Rva00290EFE and StatsCollector; helper rowed at 0x001E4426.
int __cdecl Rva001E4426Test(unsigned int *bits, int bit);

class ThingTemplate
{
public:
	int rva000456AC(int bit) const;

private:
	unsigned char m_pre[0x108];
	unsigned int m_kindBits[4];
};

int ThingTemplate::rva000456AC(int bit) const
{
	return Rva001E4426Test((unsigned int *)((const char *)this + 0x108), bit);
}

// ?rva000456C1@Rva000456C1Owner@@QAEHH@Z @0x000456C1 8B, directly after
// rva000456AC: forwards the kind-bit test to the ThingTemplate pointer held
// at +4 (mov ecx, [ecx+4]; tail jump). Owner and name are address-derived.
class Rva000456C1Owner
{
public:
	int rva000456C1(int bit);
private:
	void *m_00;
	const ThingTemplate *m_template04;
};

int Rva000456C1Owner::rva000456C1(int bit)
{
	return m_template04->rva000456AC(bit);
}
