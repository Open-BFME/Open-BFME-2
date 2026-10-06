// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000683DC@Rva000683DC@@QAEXXZ 0x000683DC 35B
// If +0x3858 calls rowed notifyShroudChanged, if +0x3854 tail-jmps rowed
// rva000E73CE. Same +0x3854 member and flags as Rva000682B8/Rva000683FF
// neighbours; caller at 0x00045048.
// Evidence: callees rowed; count/dirty layout from Common neighbours.
class W3DPropBuffer
{
public:
	void notifyShroudChanged();
};

class Rva000E73CE
{
public:
	void rva000E73CE();
};

class Rva000683DC
{
public:
	void rva000683DC();
private:
	unsigned char m_pad[0x3854];
	Rva000E73CE *m_3854;
	W3DPropBuffer *m_3858;
};

void Rva000683DC::rva000683DC()
{
	if (m_3858)
		m_3858->notifyShroudChanged();
	if (m_3854)
		m_3854->rva000E73CE();
}
