// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00540F0B@Rva00540F0B@@QAEXPAVDataChunkOutput@@@Z, retail 0x00540F0B 66B.
// Array writer for 0x1C-stride keyframes (float plus Rva00540C59 0x18 body):
// count = (end-begin)/0x1C via push-imm/pop-ecx idiv, writeInt(count), then
// for each element writeInt(float bits at +0) and rowed Rva00540C59 at +4.
// Evidence: strides 0x1C in 0x00540F0B versus 0x14 sibling 0x00540F4D; inner
// call to rowed 0x00540C59; begin at +0x10 end at +0x14; caller at 0x005411B5.

class DataChunkOutput
{
public:
	void writeInt(int value);
	void writeReal(float value);
};

class Rva00540C59
{
public:
	void rva00540C59(DataChunkOutput *out);
};

class Rva00540F0B
{
public:
	void rva00540F0B(DataChunkOutput *out);
	char m_pad[0x10];
	char *m_begin;
	char *m_end;
};

void Rva00540F0B::rva00540F0B(DataChunkOutput *out)
{
	int count = (m_end - m_begin) / 0x1C;
	out->writeInt(count);
	for (char *p = m_begin; p != m_end; p += 0x1C)
	{
		out->writeInt(*reinterpret_cast<int *>(p));
		reinterpret_cast<Rva00540C59 *>(p + 4)->rva00540C59(out);
	}
}
