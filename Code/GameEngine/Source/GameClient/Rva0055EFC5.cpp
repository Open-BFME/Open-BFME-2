// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0055EFC5@Rva0055EFC5@@QAEXPAVXfer@@@Z 28B @0x0055EFC5: parent xfer
// that calls rowed Version1 on the Xfer arg then the just-landed sub-xfer
// 0x0055EF6E on the member at +0x0C. Chain of the 0x0055EF6E landing;
// caller is an unclaimed getClass thunk.

class Xfer
{
public:
	void Version1();
};

class Rva0055EF6E
{
public:
	void rva0055EF6E(Xfer *xfer);
};

class Rva0055EFC5
{
public:
	void rva0055EFC5(Xfer *xfer);
private:
	unsigned char m_pad00[0x0C];
	Rva0055EF6E m_0c;
};

void Rva0055EFC5::rva0055EFC5(Xfer *xfer)
{
	xfer->Version1();
	m_0c.rva0055EF6E(xfer);
}
