// cl: /DNDEBUG /MD
//
// ?rva0039AF9B@Rva0039AF9B@@QAEMM@Z, retail 0x0039AF9B (45 bytes).
// Identity: float scale by +0x2C pointee +8 unless game state +0x114 is 3 or
// +0x4 pointee flag 0x80 at +0x108 is set; callers in Object and behavior
// units. Layout from retail offsets; TheGameLogic via rowed name.
class GameLogic
{
public:
	unsigned char m_pad[0x114];
	int m_i114;
};
extern GameLogic *TheGameLogic;
struct Rva0039AF9B_P04
{
	unsigned char m_pad[0x108];
	unsigned char m_b108;
};
struct Rva0039AF9B_P2C
{
	unsigned char m_pad[8];
	float m_f08;
};
class Rva0039AF9B
{
public:
	float rva0039AF9B(float v);
private:
	unsigned char m_pad00[4];
	Rva0039AF9B_P04 *m_p04; // +0x04
	unsigned char m_pad08[0x2C - 0x08];
	Rva0039AF9B_P2C *m_p2C; // +0x2C
};
float Rva0039AF9B::rva0039AF9B(float v)
{
	if (TheGameLogic->m_i114 == 3)
		return v;
	if ((m_p04->m_b108 & 0x80) == 0)
		return v * m_p2C->m_f08;
	return v;
}
