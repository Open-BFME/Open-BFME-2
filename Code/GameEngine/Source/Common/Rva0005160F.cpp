// cl: /Oy- /MD
//
// ?Rva0005160FGet@@YG?AUBfmeEventPositionView@@PAVAudioEventRTS@@AA_N@Z @0x0005160F 64B
// Returns owner position view and validity: non-positional events get zeros
// and false, positional forward to rowed BfmeAudioEventPrefix136::rva002DA1CC
// at 0x002DA1CC via rowed AudioEventRTS::isPositionalAudio at 0x002D9C37.
// Evidence: packet EBP-frame 3-arg shape with xorps+movss zeros, ret 0xc,
// callers at 0x00055CEB 0x0005632D 0x0005C4FF 0x0005E276 0x00060DCB.
struct BfmeEventPositionView
{
	float x, y, z;
	BfmeEventPositionView() {}
	BfmeEventPositionView(float a, float b, float c) : x(a), y(b), z(c) {}
};

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;
};

class BfmeAudioEventPrefix136
{
public:
	BfmeEventPositionView rva002DA1CC(bool &valid);
};

BfmeEventPositionView __stdcall Rva0005160FGet(AudioEventRTS *event, bool &valid)
{
	if (!event->isPositionalAudio())
	{
		valid = false;
		return BfmeEventPositionView(0.0f, 0.0f, 0.0f);
	}
	return ((BfmeAudioEventPrefix136 *)event)->rva002DA1CC(valid);
}
