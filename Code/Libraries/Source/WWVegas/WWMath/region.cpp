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

struct IRegion3D
{
    int width() const;
    int height() const;
    int depth() const;

    int x_min;
    int y_min;
    int z_min;
    int x_max;
    int y_max;
    int z_max;
};

int IRegion2D::width() const
{
    return x_max - x_min;
}

int IRegion2D::height() const
{
    return y_max - y_min;
}

int IRegion3D::width() const
{
    return x_max - x_min;
}

int IRegion3D::height() const
{
    return y_max - y_min;
}
