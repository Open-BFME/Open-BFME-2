// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// DOTManager::rva0043B725 (class named by WorldBuilder's DOTManager::update,
// 0x0043B73D, which calls 0x0043B72D on the same this), retail 0x0043B725, 8 bytes.
// Forwards this+4 to Rva0043B2E2 clear 0x0043B334.
// Evidence: jmp target row ?rva0043B334@Rva0043B2E2@@QAEXXZ caller 0x002442A4.
class Rva0043B2E2
{
public:
	void rva0043B334();
	unsigned int rva0043B4EC(const int &x);
private:
	void *m_00Head;
	int m_04Flag;
};

class DOTManager
{
public:
	void rva0043B725();
	unsigned int rva0043B72D(int x);
private:
	char m_pad[4];
	Rva0043B2E2 m_tree;
};

void DOTManager::rva0043B725()
{
	m_tree.rva0043B334();
}

unsigned int DOTManager::rva0043B72D(int x)
{
	return m_tree.rva0043B4EC(x);
}
