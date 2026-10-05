// cl: /O1 /DNDEBUG /MD
//
// BFME2's strategic (War of the Ring) player status screen Apt callback
// "StrategicPlayerStatus::OnCloseWindow", 0x00523481, bound by that name as
// a member pointer by the screen's registration; that binding is its only
// reference. The class is named for the string's prefix.

// Rva0052340DEnable.cpp's 0x0052340D.
void Rva0052340DEnable();

class StrategicPlayerStatus
{
public:
	void OnCloseWindow(const char *unused);
};

// Retail 0x00523481, 8 bytes: "StrategicPlayerStatus::OnCloseWindow".
void StrategicPlayerStatus::OnCloseWindow(const char *unused)
{
	Rva0052340DEnable();
}
