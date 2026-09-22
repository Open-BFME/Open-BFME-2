// cl: /O1 /DNDEBUG /MD /EHsc
// BFME 1 ScoreKeeper_totalDestroyed.cpp semantics with BFME 2's measured
// twenty-player arrays at +0x20 and +0x78. The retail getters call distinct
// out-of-line sum workers, which remain declarations in this unit.

class ScoreKeeper
{
public:
    int getTotalUnitsDestroyed();
    int getTotalBuildingsDestroyed();

private:
    int bfmeSumUnitsDestroyed20(const int *values);
    int bfmeSumBuildingsDestroyed20(const int *values);
    char m_pad00[0x20];
    int m_unitsDestroyed[20];
    char m_pad70[0x08];
    int m_buildingsDestroyed[20];
};

int ScoreKeeper::getTotalUnitsDestroyed()
{
    return bfmeSumUnitsDestroyed20(m_unitsDestroyed);
}

int ScoreKeeper::getTotalBuildingsDestroyed()
{
    return bfmeSumBuildingsDestroyed20(m_buildingsDestroyed);
}
