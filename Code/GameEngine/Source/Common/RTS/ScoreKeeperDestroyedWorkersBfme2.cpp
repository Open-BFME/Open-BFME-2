// cl: /O1 /DNDEBUG /MD /EHsc
// The two twenty-player sum workers called by ScoreKeeper's total getters.
// The building worker reads its pointer argument; the units worker uses this
// plus the target-measured array offset while keeping the ABI's pointer slot.

class ScoreKeeper
{
private:
    int bfmeSumUnitsDestroyed20(const int *values);
    int bfmeSumBuildingsDestroyed20(const int *values);

private:
    char m_pad00[0x20];
    int m_unitsDestroyed[20];
};

int ScoreKeeper::bfmeSumBuildingsDestroyed20(const int *values)
{
    int total = 0;
    for (int i = 0; i < 20; ++i)
        total += values[i];
    return total;
}

int ScoreKeeper::bfmeSumUnitsDestroyed20(const int * /* values */)
{
    int total = 0;
    for (int i = 0; i < 20; ++i)
        total += m_unitsDestroyed[i];
    return total;
}
