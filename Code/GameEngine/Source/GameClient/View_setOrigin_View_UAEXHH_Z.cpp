// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport

// View::setOrigin is an inline in GameClient/View.h:
//     virtual void setOrigin( Int x, Int y) { m_originX=x; m_originY=y;}
// The BFME1 donor View.cpp only emits it through the class vtable, so there is
// no donor .cpp definition to copy. Retail 0x000851A6 stores x at this+0x20 and
// y at this+0x24, which fixes both offsets; the header body is emitted
// out-of-line here.
class View
{
public:
	virtual void setOrigin( int x, int y );

private:
	char m_pad[0x1c];		// after the vptr
	int m_originX;		// this+0x20
	int m_originY;		// this+0x24
};

void View::setOrigin( int x, int y )
{
	m_originX = x;
	m_originY = y;
}
