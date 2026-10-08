// cl: /MD
// m_cellsOnFire's insert (0x00287B2A): FireLogicSystem::update calls it
// with ecx = the set at +0x84 and a hidden pair<iterator,bool> result, and
// it forwards ecx untouched to the tree's insert_unique (0x00286E33), then
// rebuilds the pair from that call's result (iterator dword, bool byte).
class Rva00285672;
struct Rva00286214Node;
struct Rva00287B2AResult
{
	Rva00287B2AResult(Rva00286214Node *node, bool inserted) : m_node(node), m_inserted(inserted) {}
	Rva00286214Node *m_node;
	bool m_inserted;
};
class Rva00286214
{
public:
	Rva00287B2AResult rva00286E33(const Rva00285672 *key);
	Rva00287B2AResult rva00287B2A(const Rva00285672 *key);
};
Rva00287B2AResult Rva00286214::rva00287B2A(const Rva00285672 *key)
{
	Rva00287B2AResult p = rva00286E33(key);
	return Rva00287B2AResult(p.m_node, p.m_inserted);
}
