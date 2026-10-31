// cl: /Ob0

// ?EverSeenByPlayer@Data@ShroudManager@@QAEDH@Z @0x0073A0C0 28B: renamed
// from placeholder Rva008F7B00::get — the WorldBuilder twin names
// ShroudManager::Data::EverSeenByPlayer at EA's own shroudmanager_data.cpp;
// the class is corroborated by the landed KeepAsGhost / DoSmallFill /
// UpdateCellsTouched siblings.
class ShroudManager
{
public:
	class Data
	{
		char m_pad[0xC4];
		char m_slots[20];

	public:
		char EverSeenByPlayer(int index);
	};
};

char ShroudManager::Data::EverSeenByPlayer(int index)
{
	if (index < 0 || index >= 20)
		return 0;
	return m_slots[index];
}
