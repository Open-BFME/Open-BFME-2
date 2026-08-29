// cl: /O1 /ICode/GameEngine/Source/Common

struct IRegion2D
{
    bool operator==(const IRegion2D &that) const;
    bool operator!=(const IRegion2D &that) const;
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

bool IRegion2D::operator==(const IRegion2D &that) const
{
    return x_min == that.x_min &&
        y_min == that.y_min &&
        x_max == that.x_max &&
        y_max == that.y_max;
}

bool IRegion2D::operator!=(const IRegion2D &that) const
{
    return !(*this == that);
}

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

int IRegion3D::depth() const
{
    return z_max - z_min;
}
