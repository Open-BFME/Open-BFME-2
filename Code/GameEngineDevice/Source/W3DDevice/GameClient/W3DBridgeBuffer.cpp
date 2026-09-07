// cl: /DNDEBUG /DWIN32 /MD /O1 /GX
//
// BFME2 W3DBridge enabled-flag setter, transferred from the exact BFME1
// reconstruction
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp,
// which emits the out-of-line copy). Retail BFME2 keeps the flag at the
// same offset (+0x110).

class W3DBridge
{
public:
	void setEnabled(bool enabled);

private:
	unsigned char m_pre[0x110];
	bool m_enabled;	// +0x110
};

// ?setEnabled@W3DBridge@@QAEX_N@Z
void W3DBridge::setEnabled(bool enabled)
{
	m_enabled = enabled;
}
