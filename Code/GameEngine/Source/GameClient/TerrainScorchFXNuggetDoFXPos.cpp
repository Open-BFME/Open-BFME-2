// cl: /O1 /MD /DNDEBUG
// Semantic donor: Open-BFME-1 575ba2b04743 FXList.cpp and the ZH FXList.cpp
// it carries. WB 0x00AD60B0 names this method at FXList.cpp:1248; native
// 0x001E0915..0x001E0965 proves its four-argument const virtual ABI and
// configurable scorch range, absent in the donor's constant-range version.
// Vftable 0x007DD828 has this method in slot 1 at 0x007DD82C.

struct Coord3D;
class Matrix3D;
enum Scorches { SCORCH_1, SCORCH_2, SCORCH_3, SCORCH_4, SHADOW_SCORCH };

int GetGameClientRandomValue(int lo, int hi, char *file, int line);

class GameClient
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual void addScorch(const Coord3D *position, float radius, Scorches type);
};
extern GameClient *TheGameClient;

class TerrainScorchFXNugget
{
public:
    virtual void slot0();
    virtual void doFXPos(const Coord3D *primary, const Matrix3D *, float, const Coord3D *) const;
private:
    char m_pad04[0x144];
    int m_scorch;
    float m_radius;
    int m_minScorch;
    int m_maxScorch;
};

void TerrainScorchFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float, const Coord3D *) const
{
    if (primary)
    {
        int scorch = m_scorch;
        if (scorch < 0)
            scorch = GetGameClientRandomValue(m_minScorch, m_maxScorch,
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\FXList.cpp", 1248);
        TheGameClient->addScorch(primary, m_radius, (Scorches)scorch);
    }
}
