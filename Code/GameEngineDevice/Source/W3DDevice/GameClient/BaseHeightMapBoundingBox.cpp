// cl: /O1 /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// Get_Obj_Space_Bounding_Box, with the original GeneralsMD body as semantic guide.
// Target: full native RVA 0x00069BCC..0x00069C5F, 147 bytes including RET4.
// Base terrain primary table VA 0x00BC5E5C slot25 points to VA 0x00469BCC.
// Retail and WB0x758A10 agree on map37C0, dimensions8/C, heights37D8/DC.
// Only this accessed prefix is modeled; the remainder of the class is open.
class Vector3
{
public:
    float X, Y, Z;
    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
    __forceinline Vector3 &operator=(const Vector3 &v) { X=v.X; Y=v.Y; Z=v.Z; return *this; }
    __forceinline Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};
__forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.X+b.X, a.Y+b.Y, a.Z+b.Z);
}
__forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
    return Vector3(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
}
__forceinline Vector3 operator*(const Vector3 &a, float k)
{
    return Vector3(a.X*k, a.Y*k, a.Z*k);
}
class MinMaxAABoxClass
{
public:
    Vector3 MinCorner, MaxCorner;
    __forceinline MinMaxAABoxClass(const Vector3 &minimum, const Vector3 &maximum)
        : MinCorner(minimum), MaxCorner(maximum) {}
};
class AABoxClass
{
public:
    Vector3 Center, Extent;
    __forceinline void Init(const MinMaxAABoxClass &bounds)
    {
        Center = (bounds.MaxCorner + bounds.MinCorner) * 0.5f;
        Extent = (bounds.MaxCorner - bounds.MinCorner) * 0.5f;
    }
};
class WorldHeightMap
{
public:
    int getXExtent() const { return m_xExtent; }
    int getYExtent() const { return m_yExtent; }
private:
    char m_unreconstructed[8];
    int m_xExtent, m_yExtent;
};
class BaseHeightMapRenderObjClass
{
public:
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
private:
    char m_unreconstructed004[0x37C0-4];
    WorldHeightMap *m_map;
    char m_unreconstructed37C4[0x37D8-0x37C4];
    float m_minHeight, m_maxHeight;
};
void BaseHeightMapRenderObjClass::Get_Obj_Space_Bounding_Box(AABoxClass &box) const
{
    int x=0, y=0;
    if (m_map)
    {
        x=m_map->getXExtent();
        y=m_map->getYExtent();
    }
    Vector3 minPt(0,0,m_minHeight);
    Vector3 maxPt((float)x*10.0f,(float)y*10.0f,m_maxHeight);
    MinMaxAABoxClass bounds(minPt,maxPt);
    box.Init(bounds);
}
