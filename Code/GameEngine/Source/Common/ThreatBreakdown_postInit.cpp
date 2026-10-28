// cl: /MD
// ?postInit@ThreatBreakdown@@QAEXPBX@Z @0x0033A920 49B
// Lazy enum setter: if this int is not -1 return; else if the arg byte at
// +0x108 has 0x80 set this to 6, else this to 10 when the arg dword at +0x110
// has 0x4000000 else 0 (neg/sbb/and shape). Caller at 0x002CF666 passes
// esi with this at esi+0x520 and arg esi: this is the ThingTemplate's
// ThreatBreakdown member, at the +0x520 offset of its "ThreatBreakdown"
// FieldParse entry, and the arg is that template.
class ThreatBreakdown
{
public:
	void postInit(const void *thingTemplate);

private:
	int m_val;
};

struct Rva0033A920Arg
{
	unsigned char m_pad00[0x108];
	unsigned char m_108;
	unsigned char m_pad109[0x110 - 0x108 - 1];
	unsigned int m_110;
};

void ThreatBreakdown::postInit(const void *thingTemplate)
{
	if (m_val != -1)
		return;
	const Rva0033A920Arg *objectTemplate = (const Rva0033A920Arg *)thingTemplate;
	if (objectTemplate->m_108 & 0x80)
		m_val = 6;
	else
		m_val = (objectTemplate->m_110 & 0x4000000) ? 10 : 0;
}
