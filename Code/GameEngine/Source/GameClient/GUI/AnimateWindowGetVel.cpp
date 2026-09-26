// cl: /O1 /G7 /MD /EHsc /DNDEBUG

struct Coord2D
{
	Coord2D() {}
	Coord2D(const Coord2D &other) : x(other.x), y(other.y) {}
	float x;
	float y;
};

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
