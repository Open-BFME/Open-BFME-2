// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva005F8F31@Rva005F8F31@@QAEXXZ @0x005F8F31 13B.
// Evidence: chain lane; callee 0x005CB260 ?rva005CB260@Rva005CB260@@QAEXXZ rowed;
// callers 0x005F96D4 loops load [edi]/[esi] as this with no args.

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva005F8F31
{
public:
	void rva005F8F31();
	char m_pad[0x2c];
	Rva005CB260 *m_ptr;
};

void Rva005F8F31::rva005F8F31()
{
	if (m_ptr)
		m_ptr->rva005CB260();
}
