// ?rva00559DA0@Rva00559D0CRankWeights@@QBEHPBVRva00553E47StatsCore@@E@Z
// partial score=0.9 date=2026-10-09
// (class Rva00559D0CRankWeights also declares rva00559DA0(const Rva00553E47StatsCore*, unsigned char) const)
// Inline copy of the rowed byte-key lookup 0x005B808D.
static __forceinline Int Rva00559DA0Lookup(unsigned char key, Rva005B8053 *map)
{
	Int result = 0;
	void *node = map->rva005B8053(&key);
	if (node != *(void **)map)
		result = *(unsigned short *)((char *)node + 0x12);
	return result;
}

Int Rva00559D0CRankWeights::rva00559DA0(const Rva00553E47StatsCore *stats, unsigned char key) const
{
	if (stats->m_id == 0)
		return 0;
	Int winPoints = (Int)((float)Rva00559DA0Lookup(key, (Rva005B8053 *)&stats->m_maps04_0) * m_winWeight);
	Int rank = (Int)((float)Rva00559DA0Lookup(key, (Rva005B8053 *)&stats->m_maps04_1) * m_lossWeight + (float)winPoints);
	return _STL::max(rank, 0);
}

