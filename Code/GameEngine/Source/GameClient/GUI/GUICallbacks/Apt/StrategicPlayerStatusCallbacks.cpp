// cl: /O1 /DNDEBUG /MD
//
// BFME2's strategic (War of the Ring) player status screen Apt callbacks,
// "StrategicPlayerStatus::OnCloseWindow" (0x00523481) and two Apt queries,
// bound by those names as member pointers by the screen's registration
// 0x00523900; that binding is their only reference. The class is named for
// the strings' prefix.

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

// Rva0052340DEnable.cpp's 0x0052340D.
void Rva0052340DEnable();

// The screen's color list at +0x288 (a vector of 0x00RRGGBB values).
struct StrategicPlayerColors
{
	unsigned int size() const { return m_end - m_begin; }
	unsigned int operator[](unsigned int index) const { return m_begin[index]; }

	unsigned int *m_begin;
	unsigned int *m_end;
};

class StrategicPlayerStatus
{
public:
	void OnCloseWindow(const char *unused);
	// Bound as "StrategicPlayerStatus::PlayerIndex" (query 0),
	// "...::NumAlliedPlayers" (1) and "...::NumEnemyPlayers" (2), so it
	// keeps its address.
	void rva00523438(int query, char *result, bool skip);
	// Bound as "StrategicPlayerStatus::EnemyColor_%d" and
	// "StrategicPlayerStatus::%sColor_%d" for each index, so it keeps its
	// address.
	void rva0052373A(int query, char *result, bool skip);

private:
	unsigned char m_pad000[0x27C];
	int m_playerIndex; // +0x27C
	int m_numAllied; // +0x280
	int m_numEnemies; // +0x284
	StrategicPlayerColors m_colors; // +0x288
};

// Retail 0x00523438, 73 bytes: bound as "StrategicPlayerStatus::PlayerIndex",
// "NumAlliedPlayers" and "NumEnemyPlayers", an Apt query answering the
// count the query selects ("0" otherwise).
void StrategicPlayerStatus::rva00523438(int query, char *result, bool skip)
{
	if (skip)
		return;
	result[0] = '0';
	result[1] = 0;
	switch (query)
	{
	case 0:
		sprintf(result, "%d", m_playerIndex);
		break;
	case 1:
		sprintf(result, "%d", m_numAllied);
		break;
	case 2:
		sprintf(result, "%d", m_numEnemies);
		break;
	}
}

// Retail 0x0052373A, 59 bytes: bound as the indexed color queries, an Apt
// query answering the color as 0xRRGGBB.
void StrategicPlayerStatus::rva0052373A(int query, char *result, bool skip)
{
	if ((unsigned int)query < m_colors.size())
		_snprintf(result, 0xFF, "0x%x", m_colors[query] & 0xFFFFFF);
}

// Retail 0x00523481, 8 bytes: "StrategicPlayerStatus::OnCloseWindow".
void StrategicPlayerStatus::OnCloseWindow(const char *unused)
{
	Rva0052340DEnable();
}
