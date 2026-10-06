// cl: /MD
// ?regainFocusThunk@AudioManager@@QAEXXZ, retail 0x0035D326, 5B.
// Thunk to AudioManager::regainFocus at 0x0035D2F7.
class AudioManager
{
public:
	void regainFocus();
	void regainFocusThunk();
};

void AudioManager::regainFocusThunk()
{
	regainFocus();
}
