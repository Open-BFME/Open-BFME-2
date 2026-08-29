// cl: /ICode/GameEngine/Source/Common

struct IRegion2D
{
    int width() const;

    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

int IRegion2D::width() const
{
    return x_max - x_min;
}
