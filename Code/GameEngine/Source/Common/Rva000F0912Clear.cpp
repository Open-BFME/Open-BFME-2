// cl: /MD
// ?rva000F0912@Rva000F0912@@QAEXXZ @0x000F0912 68B: clear 160 slots per node over +0x68 list with zero 12B triple. Evidence: caller 0x000F09C6 in 0x000F0972 plus LINK BONUS via 0x000F0972 plus callee 0x000EFB68 row.
class Rva000EFB68
{
public:
	void rva000EFB68(int a, int b, void *src);
	char _pad[0x68];
	Rva000EFB68 *m_next;
};
class Rva000F0912
{
public:
	void rva000F0912();
private:
	Rva000EFB68 *m_head;
};
struct Rva000F0912Zero
{
	float x;
	float y;
	float z;
};
void Rva000F0912::rva000F0912()
{
	Rva000EFB68 *node = m_head;
	if (node == 0)
		return;
	Rva000F0912Zero zero;
	zero.x = 0.0f;
	zero.y = 0.0f;
	zero.z = 0.0f;
	do
	{
		for (int i = 0; i < 160; ++i)
			node->rva000EFB68(0, i, &zero);
		node = node->m_next;
	} while (node != 0);
}
