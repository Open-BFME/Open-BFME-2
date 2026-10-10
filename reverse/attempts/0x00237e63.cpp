// ?rva00237E63@Version@@QAEHPBX_N@Z
// partial score=0.98 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O2 /EHsc
//
// ?rva00237E63@Version@@QAEHPBX_N@Z @0x00237E63 (94B).
// Version-block colour for the games list box (caller: AptOnlineCustomMatch
// rebuild 0x004457BC via REL32 at 0x00445944): compares the four version
// words at +0x00 (m_major/m_minor/m_buildNum/m_localBuildNum, the same
// layout VersionDestructor.cpp establishes) against the room's 16-byte
// version block unless the caller already flagged a version/build mismatch,
// then selects the entry colour by the block's leading word: 1 and 2 pick
// between the match/mismatch colours, anything else is 0xFF646464.
// Shard (not a graft into VersionDestructor.cpp) so that TU's shape stays
// green; the method spelling is a reconstruction, the address is pinned.
class Version
{
public:
	int rva00237E63(const void *block, bool mismatch);
private:
	int m_major, m_minor, m_buildNum, m_localBuildNum;
};

int Version::rva00237E63(const void *block, bool mismatch)
{
	const int *words = (const int *)block;
	bool same = false;
	if (!mismatch)
		same = m_major == words[0] && m_minor == words[1] && m_buildNum == words[2] && m_localBuildNum == words[3];
	switch (words[0]) {
	case 1:
		return same ? 0xFF7AAB44 : 0xFF3D5522;
	case 2:
		return same ? 0xFF747BCE : 0xFF3A3D67;
	default:
		return 0xFF646464;
	}
}
