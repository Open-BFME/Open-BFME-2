// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0039D40F@Rva0039D40F@@QBE_NPAPAV1@@Z @0x0039D40F (26B).
// List-membership test over the +0x3C/+0x40 pair: true when the head slot
// holds this or either link is set, false only for an isolated node whose
// head differs. Retail shape is head compare plus prev test plus next test
// plus two single-byte returns. Sibling of the 0x0039D429 prepend sharing
// the same link layout; callers at 0x0039D4AD 0x0039D4C1 0x0039D4E4 pass a
// +0x334 head. Owner unproven so the name keeps the address token.

typedef bool Bool;

class Rva0039D40F
{
public:
	Bool rva0039D40F(Rva0039D40F **head) const;

private:
	char m_pad00[0x3C];
	Rva0039D40F *m_prev3C; // +0x3C
	Rva0039D40F *m_next40; // +0x40
};

Bool Rva0039D40F::rva0039D40F(Rva0039D40F **head) const
{
	return *head == this || m_prev3C != 0 || m_next40 != 0;
}
