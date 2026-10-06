// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0053FBFE@Rva0053FBFE@@QAEXPAVDataChunkOutput@@@Z @0x0053FBFE 131B
// Eight-float keyframe writer: interp tag at +0 via rowed Rva005C706A writer,
// then eight floats at +4 +8 +0xC +0x10 +0x14 +0x18 +0x1C +0x20 via
// DataChunkOutput::writeReal. Writer twin of the reader in Rva0053FB91Read.cpp
// (same layout). Evidence: calls 0x005C706A then eight writeReal fld/fstp
// sequences; base file Rva005C706AWrite.cpp names 0x53FC07 as a caller passing
// the same this plus DataChunkOutput; caller at 0x0053FF4C.
class DataChunkOutput
{
public:
	void writeReal(float value);
};
class Rva005C706A
{
public:
	void rva005C706A(DataChunkOutput *out);
	int m_key;
};
class Rva0053FBFE
{
public:
	void rva0053FBFE(DataChunkOutput *out);
	Rva005C706A m_interp;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};
void Rva0053FBFE::rva0053FBFE(DataChunkOutput *out)
{
	m_interp.rva005C706A(out);
	out->writeReal(m_04);
	out->writeReal(m_08);
	out->writeReal(m_0c);
	out->writeReal(m_10);
	out->writeReal(m_14);
	out->writeReal(m_18);
	out->writeReal(m_1c);
	out->writeReal(m_20);
}
