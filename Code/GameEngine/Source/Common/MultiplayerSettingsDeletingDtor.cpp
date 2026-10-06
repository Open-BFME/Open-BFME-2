// cl: /MD
// MultiplayerSettings scalar deleting destructor (retail 0x00381277,
// 28B): calls the rowed non-virtual destructor 0x00381293, then frees
// through 0x002FD60 when the deleting flag is set. Same shell as the
// famgen gdtor family; the complete-destructor call resolves through
// the dtor row.

// ??_GMultiplayerSettings@@QAEPAXI@Z @0x381277
class MultiplayerSettings
{
public:
	__declspec(noinline) ~MultiplayerSettings();

private:
	int m_famgen;
};

// MultiplayerSettings::~MultiplayerSettings: defined in MultiplayerSettingsDtor.cpp (its row's unit).

void deleteMultiplayerSettings(MultiplayerSettings *p)
{
	delete p;
}
