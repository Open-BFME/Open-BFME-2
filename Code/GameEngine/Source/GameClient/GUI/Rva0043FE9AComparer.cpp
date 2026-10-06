// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0043FE9A, 309 bytes.
// ?rva0043FE9A@Rva0043FE9A@@QAE_NPAVMapMetaData@@0@Z is the MapMetaData sort
// comparator used by the STL sort helpers 0x00440AB0 0x00440B1B 0x00440B64
// 0x00440B93 via 0x0044192F 0x00441999 up to 0x00443538. Offsets 0x20
// (playerCount) and 0xF4 (wordF4) from MapMetaDataCopy 256B layout and the
// bfme_getDisplayName sibling TU; display-name compare via rowed
// StringBase compareNoCase with throw; two sort keys 0=name asc 1=name desc
// 2=players asc 3=players desc 4=F4 asc 5=F4 desc plus ascending tie break.
typedef unsigned short WideChar;
template <typename T> class StringBase
{
	friend class UnicodeString;
	friend class MapMetaData;
	friend class Rva0043FE9A;
public:
	int compareNoCase(const StringBase<T> &other) const throw();
private:
	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	void *m_data;
};
class UnicodeString : private StringBase<unsigned short>
{
	friend class MapMetaData;
	friend class Rva0043FE9A;
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};
class MapMetaData
{
	friend class Rva0043FE9A;
public:
	UnicodeString bfme_getDisplayName(bool includePlayerCount);
private:
	UnicodeString m_displayNameLabel;
	char m_pad04[0x20 - 0x04];
	int m_playerCount;
	char m_pad24[0xF4 - 0x24];
	int m_wordF4;
};
class Rva0043FE9A
{
	int m_sort0;
	int m_sort1;
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
};
bool Rva0043FE9A::rva0043FE9A(MapMetaData *a, MapMetaData *b)
{
	if (!a)
		return false;
	if (!b)
		return true;
	int playerDiff = a->m_playerCount - b->m_playerCount;
	int nameCmp = ((StringBase<unsigned short> &)a->bfme_getDisplayName(true)).compareNoCase((StringBase<unsigned short> &)b->bfme_getDisplayName(true));
	int f4Diff = a->m_wordF4 - b->m_wordF4;
	int key = m_sort0;
	for (int i = 0; i < 2; ++i)
	{
		switch (key)
		{
		case 0:
			if (nameCmp == 0)
				break;
			return nameCmp < 0;
		case 1:
			if (nameCmp == 0)
				break;
			return nameCmp >= 0;
		case 2:
			if (playerDiff == 0)
				break;
			return playerDiff < 0;
		case 3:
			if (playerDiff == 0)
				break;
			return playerDiff >= 0;
		case 4:
			if (f4Diff == 0)
				break;
			return f4Diff < 0;
		case 5:
			if (f4Diff == 0)
				break;
			return f4Diff >= 0;
		}
		key = m_sort1;
	}
	if (nameCmp != 0)
		return nameCmp < 0;
	if (playerDiff != 0)
		return playerDiff < 0;
	if (f4Diff != 0)
		return f4Diff < 0;
	return a < b;
}
