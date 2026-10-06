// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0053850B@Rva0053850B@@QAEXPAVDataChunkOutput@@@Z @0x0053850B 100B
// Vector Float4 save via rowed DataChunkOutput writeInt count then writeReal xyzw loop.
// Evidence: callee 0x00306CFF row writeReal writeInt folded; next uninit-copy Float4; prev Rva005382A6Getter /O1.
class DataChunkOutput
{
public:
	void writeInt(int v);
	void writeReal(float v);
};
struct BfmeFloat4Record00469C61
{
	float x, y, z, w;
};
class Rva0053850B
{
public:
	void rva0053850B(DataChunkOutput *out);
private:
	BfmeFloat4Record00469C61 *m_start;
	BfmeFloat4Record00469C61 *m_finish;
};
void Rva0053850B::rva0053850B(DataChunkOutput *out)
{
	int count = (int)(m_finish - m_start);
	out->writeInt(count);
	BfmeFloat4Record00469C61 *start = m_start;
	BfmeFloat4Record00469C61 *finish = m_finish;
	for (BfmeFloat4Record00469C61 *p = start; p != finish; ++p) {
		out->writeReal(p->x);
		out->writeReal(p->y);
		out->writeReal(p->z);
		out->writeReal(p->w);
	}
}
