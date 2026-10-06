// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0053FF1D@Rva0053FF1D@@QAEXPAVDataChunkOutput@@@Z @0x0053FF1D 66B
// Keyframe-track writer: count at +0x10/+0x14 via rowed writeInt then for each
// 0x28-byte key writes int at +0 via writeInt and the 8-float keyframe at +4
// via rowed 0x0053FBFE. Chain on 0x0053FBFE landed this session. Evidence:
// (end-begin)/0x28 idiv count; loop push [esi] plus lea ecx [esi+4] call
// 0x53FBFE plus add esi 0x28; caller at 0x00540144.
class DataChunkOutput
{
public:
	void writeInt(int value);
};
struct Rva0053FBFE
{
	void rva0053FBFE(DataChunkOutput *out);
	char m_pad[0x24];
};
struct Key40
{
	int m_00;
	Rva0053FBFE m_04;
};
class Rva0053FF1D
{
public:
	void rva0053FF1D(DataChunkOutput *out);
	char m_00[0x10];
	Key40 *m_begin;
	Key40 *m_end;
};
void Rva0053FF1D::rva0053FF1D(DataChunkOutput *out)
{
	int count = m_end - m_begin;
	out->writeInt(count);
	for (Key40 *p = m_begin; p != m_end; ++p)
	{
		out->writeInt(p->m_00);
		p->m_04.rva0053FBFE(out);
	}
}
