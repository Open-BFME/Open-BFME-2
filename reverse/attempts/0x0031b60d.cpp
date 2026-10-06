// ?rva0031B60D@Rva0031B60D@@QAE?AVRva0035AEC2@@XZ
// partial score=0.94 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva0031B60D@Rva0031B60D@@QAE?AVRva0035AEC2@@XZ retail 0x0031B60D 52B
// Evidence: caller at 0x0053D3FD and rowed Rva0035AEC2 constructor at 0x0035AEC2.
// The caller class and vector element meaning remain unresolved. Retail compares
// pointers at +0x2a8/+0x2ac and copies the final 8-byte element when nonempty.

class Rva0035AEC2
{
public:
	Rva0035AEC2();
	int m_first;
	int m_second;
};

class Rva0031B60D
{
public:
	Rva0035AEC2 rva0031B60D();

private:
	struct Vector
	{
		Rva0035AEC2 * volatile m_begin;
		Rva0035AEC2 * volatile m_end;
		Rva0035AEC2 *m_capacity;
	};
	char m_pad[0x2a8];
	Vector m_vector;
};

Rva0035AEC2 Rva0031B60D::rva0031B60D()
{
	Rva0035AEC2 *begin = m_vector.m_begin;
	if (begin == m_vector.m_end)
		return Rva0035AEC2();
	return *(m_vector.m_end - 1);
}
