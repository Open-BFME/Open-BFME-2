// cl: /O2 /G7 /MD
// Retail forwarding wrapper: the grid object is at offset 0x1c.
class Matrix3D;

class WaterGrid
{
public:
    virtual void reset();
    virtual void update();
    virtual void setGridTransform(const Matrix3D *transform);
};

class WaterRenderObjClass
{
public:
    void setGridTransform(const Matrix3D *transform);

private:
    char m_prefix[0x1c];
    WaterGrid * volatile m_grid;
};

void WaterRenderObjClass::setGridTransform(const Matrix3D *transform)
{
    WaterGrid *grid = m_grid;
    if (grid)
        grid->setGridTransform(transform);
}
