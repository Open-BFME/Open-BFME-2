// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0Made002CCB04@@QAE@XZ retail 0x0050B59B 43B
// Evidence: leaf lane; pin ??0Made002CCB04; callee base Rva00507823 0x0050775B; caller parseEmotionWeaponNugget 0x002CCB29; prev Made002CCB04Parse same /O1 DNDEBUG MD; vtable 0x00864D10 plus members 0x128 -1 plus 0x12C float0 plus 0x130 0.
class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
private:
	char m_pad[0x128 - 4];
};
class Made002CCB04 : public Rva00507823
{
public:
	Made002CCB04();
private:
	int m_128;
	float m_12C;
	int m_130;
};
Made002CCB04::Made002CCB04()
{
	m_128 = -1;
	m_130 = 0;
	m_12C = 0.0f;
}
