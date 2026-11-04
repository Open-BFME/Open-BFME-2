// cl: /MD /EHsc /DNDEBUG

#include "../../../../Libraries/Include/Lib/Coord2DCtorView.h"

class AnimateWindow
{
public:
	Coord2D getVel();

private:
	unsigned char m_previousFields[0x2C];
	Coord2D m_velocity;
};

Coord2D AnimateWindow::getVel()
{
	return m_velocity;
}
