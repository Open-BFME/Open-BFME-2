// cl: /MD
// ?rva000B4E23@Rva000B4E23@@QAEMXZ 0x000B4E23 32B evidence: stride-64 float at +0x14 via mid+0x50 with null and index-negative fallback to BfmeZeroRange VA 0x00BBAEAC; caller at 0x000B708C in 0x000B7074; neighbours 0x000B4CBE/0x000B6253 same flags
// The data ledger identifies the shared read-only operand as float +0.0.

struct Rva000B4E23Elem
{
	char _pad[0x14];
	float m_val;
	char _rest[64 - 0x14 - 4];
};

struct Rva000B4E23Mid
{
	char _pad[0x50];
	Rva000B4E23Elem *m_arr;
};

class Rva000B4E23
{
	char _pad[0x18];
	Rva000B4E23Mid *m_mid;
	char _midpad[0x44 - 0x18 - 4];
	int m_idx;
public:
	float rva000B4E23();
};

float Rva000B4E23::rva000B4E23()
{
	Rva000B4E23Mid *mid = m_mid;
	if (mid != 0)
	{
		int idx = m_idx;
		if (idx >= 0)
			return mid->m_arr[idx].m_val;
	}
	return 0.0f;
}
