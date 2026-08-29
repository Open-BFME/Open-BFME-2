// cl: /ICode/GameEngine/Source/Common

struct IRegion2D
{
    int width() const;
    int height() const;

    int x_min;
    int y_min;
    int x_max;
    int y_max;
};

int IRegion2D::width() const
{
    return x_max - x_min;
}

int IRegion2D::height() const
{
    return y_max - y_min;
}
