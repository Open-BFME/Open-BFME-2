// cl: /MD /EHsc /DNDEBUG
// ?rva002B4D41@Rva002B4D41@@QAEXXZ @0x002B4D41 128B: Rva002B4D41 countdown with sound.
// Evidence: caller 0x002BD9B4 passes this in ecx; callee 0x002B35F7 rowed Rva002BA8F1Logic::rva002B35F7;
// callee 0x0020E3EF rowed get; callee 0x00412A51 rowed PlaySound; globals TheLivingWorldManager and g_Rva0107301CEmptyString.
class Rva002BA8F1Logic
{
public:
	void rva002B35F7();
};

class Rva0020E3EFNullAdjustGlobalField
{
public:
	int get() const;
};

class Rva0021294A
{
public:
	char m_pad[0x2C0];
	unsigned char m_flag2C0;
};
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
void __cdecl PlaySound(const char *eventName);

class Rva002B4D41
{
public:
	void rva002B4D41();
private:
	char m_pad00[0xB0];
	Rva0020E3EFNullAdjustGlobalField *m_b0;
	char m_padB4[0xE4 - 0xB4];
	int m_e4;
	unsigned char m_e8;
	char m_padE9[0x169 - 0xE9];
	unsigned char m_169;
	char m_pad16A[0x16C - 0x16A];
	int m_16c;
};

void Rva002B4D41::rva002B4D41()
{
	if (!m_e8)
		return;
	if (m_169) {
		if (((Rva0021294A *)TheLivingWorldManager)->m_flag2C0 != 0)
			return;
		m_169 = 0;
		((Rva002BA8F1Logic *)this)->rva002B35F7();
	}
	if (m_e4 > 0) {
		if (--m_e4 > 0)
			return;
		int p = m_b0->get();
		int v = *(int *)p;
		const char *s = v ? (const char *)(v + 8) : "";
		PlaySound(s);
	}
	if (m_16c != 0)
		--m_16c;
	if (m_16c != 0)
		return;
	m_e8 = 0;
}
