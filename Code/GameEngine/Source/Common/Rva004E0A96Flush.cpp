// cl: /DNDEBUG /MD /EHsc
// ?rva004E0A96@Rva004E0A96@@QAEXXZ @0x004E0A96 69B flush pending pointer at +0x2c via dword clearer then add Upgrades pair with amount 1 through global holder at +0x264
class Rva0023D2D8DwordClearer
{
public:
	void clear();
};

class Rva003FA681
{
public:
	void rva003FA681(int science, const int &amount);
};

class Rva0021294A
{
public:
	char m_pad[0x264];
	Rva003FA681 *m_264;
};

class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Rva004E0A96
{
public:
	void rva004E0A96();
private:
	char m_pad00[0x2c];
	Rva0023D2D8DwordClearer *m_2c;
};

void Rva004E0A96::rva004E0A96()
{
	if (!m_2c)
		return;
	m_2c->clear();
	int val;
	ji_006291ae(&val, 0, 4);
	val |= 1;
	((Rva0021294A *)TheLivingWorldManager)->m_264->rva003FA681((int)m_2c, val);
	m_2c = 0;
}
