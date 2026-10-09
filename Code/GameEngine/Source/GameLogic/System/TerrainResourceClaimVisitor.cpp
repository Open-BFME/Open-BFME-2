// cl: /O1 /G7 /arch:SSE /MD
// Native ctor3598D3 installs one callback slot, table8153DC, not a destructor.
// WB E5F810 / E5F870 prove the same nonvirtual-base destructor and cell visitor
// relation as query visitor35986C. Complete layout28B; original names unknown.
#include "TerrainResourceVisitorView.h"
#include "../../Common/GameLogicObjectLookupView.h"
class TerrainResourceManager {
public:
    void tryToClaimCell(int,int,int,ObjectID,bool,int*,int*);
};
Rva003598D3::Rva003598D3(int a1, int a2, int a3, bool a4)
{
	m_10 = 0;
	m_14 = 0;
	m_04 = a1;
	m_08 = a2;
	m_0C = a3;
	m_18 = a4;
}

// ?Rva003598D3::slot00 present-unmatched
void Rva003598D3::slot00(int x,int y)
{
    reinterpret_cast<TerrainResourceManager*>(m_04)->tryToClaimCell(
        x,y,m_08,(ObjectID)m_0C,m_18,&m_10,&m_14);
}
