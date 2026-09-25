// ?getVel@AnimateWindow@@QAE?AUCoord2D@@XZ
// partial score=0.75 date=2026-09-25
// cl: /O1 /MD
struct Coord2D
{
    Coord2D(float xValue, unsigned int yBitsValue) : x(xValue), yBits(yBitsValue) {}
    float x;
    union { float y; unsigned int yBits; };
};

class AnimateWindow
{
public:
    Coord2D getVel();

private:
    char m_prefix[0x2c];
    Coord2D m_velocity;
};

Coord2D AnimateWindow::getVel()
{
    Coord2D velocity(m_velocity.x, 0);
    velocity.yBits = m_velocity.yBits;
    return velocity;
}
