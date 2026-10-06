// cl: /MD
// ?rva0059D74B@Rva0059D74B@@QAEXPAVRva0042094D@@@Z, retail 0x0059D74B, 102 bytes.
// Normalizes 7 ints from Rva0042094D getter into 7 floats: sum loop then scale by 1.0f/total.
// Evidence: callee row ?rva0042094D@Rva0042094D@@QAEHH@Z at 0x0042094D; caller at 0x004FB249 (this+0x8C, ret 8); 1.0f global VA 0x00BBB8D8.

class Rva0042094D
{
public:
	int rva0042094D(int index);
};

class Rva0059D74B
{
public:
	void rva0059D74B(Rva0042094D *src);
private:
	float m_vals[7];
};

void Rva0059D74B::rva0059D74B(Rva0042094D *src)
{
	float total = 0.0f;
	int i;
	for (i = 0; i < 7; ++i)
		total += (float)src->rva0042094D(i);
	int j = 0;
	float scale = 1.0f / total;
	for (; j < 7; ++j)
		m_vals[j] = (float)src->rva0042094D(j) * scale;
}
