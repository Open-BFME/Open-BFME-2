// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?selectArmy@Rva0057709A@@QAEXH@Z, retail 0x005775C1 (115 bytes, EH, ret 4):
// slot 15 of the PlanRetreatsPhaseBehavior table 0x00C6E8A8 (owner built by the
// rowed 0x0057709A, the Impl at +0x08). When the Impl's +0x14 selection holder
// already holds the army with this id (+0x0C) it refreshes that selection
// (rowed 0x00576FBA); otherwise it clears the holder (rowed 0x0057702E) and
// installs a new 0x1C-byte selection for the id, built by the rowed constructor
// 0x005774E3 and stored through the rowed 0x0057704C. The method name is a
// placeholder for the vtable slot.
//
// Codegen: the compared id field is read into a named int before the compare
// (retail keeps the id argument in memory and the new-expression temp in its
// own EH slot; compare-in-condition caches the id in EDI instead).

struct Rva0057702EBase
{
	char m_pad00[0x0C];
	int m_0C;	// the selected army id
};
class Rva0057702E
{
public:
	void rva0057702E();
	Rva0057702EBase *m_ptr;
};
class Rva0057704C
{
public:
	void rva0057704C(Rva0057702EBase *selection);
};
class Rva00576FBA
{
public:
	void rva00576FBA();
};
struct Rva00577634Owner;
class Rva00576F48
{
public:
	Rva00576F48(Rva00577634Owner *owner, int id);
private:
	char m_data[0x1C];
};
struct Rva005775C1Impl
{
	char m_pad00[0x14];
	Rva0057702E m_selection;	// the current selection holder
};
class Rva0057709A
{
public:
	void selectArmy(int id);
private:
	char m_pad00[0x08];
	Rva005775C1Impl *m_08;
};

void Rva0057709A::selectArmy(int id)
{
	Rva0057702E *holder = &m_08->m_selection;
	Rva0057702EBase *current = holder->m_ptr;
	if (current)
	{
		int cur = current->m_0C;
		if (cur == id)
		{
			((Rva00576FBA *)current)->rva00576FBA();
			return;
		}
	}
	holder->rva0057702E();
	Rva00576F48 *selection = new Rva00576F48((Rva00577634Owner *)m_08, id);
	((Rva0057704C *)&m_08->m_selection)->rva0057704C((Rva0057702EBase *)selection);
}
