// cl: /MD
// stlport
// ?rva00506AFA@Rva00506A52@@QAEXXZ @ 0x00506AFA 33B
// Chain from 0x00506A52: calls rowed filler with same this, then calls
// virtual slot 0 on each vector<ModuleData*> element from +4/+8.
// Evidence: call at 0x00506AFE to rowed 0x00506A52, loads at +4/+8,
// stride 4, indirect call [eax] slot 0, caller jmp at 0x002C67BD.
#include <vector>

class Player;
class ModuleData
{
public:
	virtual void v0() const;
};

class Rva00506A52
{
public:
	void rva00506A52();
	void rva00506AFA();
private:
	Player *m_00;
	_STL::vector<const ModuleData *> m_04;
};

void Rva00506A52::rva00506AFA()
{
	rva00506A52();
	_STL::vector<const ModuleData *>::iterator it = m_04.begin();
	_STL::vector<const ModuleData *>::iterator end = m_04.end();
	for (; it != end; ++it)
		(*it)->v0();
}
