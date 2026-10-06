// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00540F4D@Rva00540F4D@@QAEXPAVDataChunkOutput@@@Z, retail 0x00540F4D 66B.
// Array writer for 0x14-stride keyframes (time plus Rva00540CED 0x10 body):
// count = (end-begin)/0x14 via push-imm/pop-ecx idiv, writeInt(count), then
// for each element writeInt(time at +0) and rowed Rva00540CED at +4.
// Evidence: strides 0x14 in 0x00540F4D versus 0x1C/0x28 siblings; inner call
// to rowed 0x00540CED; begin at +0x10 end at +0x14; caller at 0x005411BE.

class DataChunkOutput
{
public:
	void writeInt(int value);
	void writeReal(float value);
};

class Rva00540CED
{
public:
	void rva00540CED(DataChunkOutput *out);
};

class Rva00540F4D
{
public:
	void rva00540F4D(DataChunkOutput *out);
	char m_pad[0x10];
	char *m_begin;
	char *m_end;
};

void Rva00540F4D::rva00540F4D(DataChunkOutput *out)
{
	int count = (m_end - m_begin) / 0x14;
	out->writeInt(count);
	for (char *p = m_begin; p != m_end; p += 0x14)
	{
		out->writeInt(*reinterpret_cast<int *>(p));
		reinterpret_cast<Rva00540CED *>(p + 4)->rva00540CED(out);
	}
}
