// ?rva00278190@Drawable@@QAE?AVPlayingAudioRef@@XZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00278190@Drawable@@QAE?AVPlayingAudioRef@@XZ, retail 0x00278190..
// 0x002781DA (74 bytes, EH, RET 4): returns a copy (pinned PlayingAudioRef
// copy constructor 0x000A8C7C) of the reference at +0x04 of the record the
// keyed lookup for key 0x25 builds (rowed Drawable::rva0027682F); the
// record's own reference is released (rowed Release_Ref 0x00050ED3) when the
// temporary dies. Nothing references the body directly.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class PlayingAudioRef
{
public:
	PlayingAudioRef(const PlayingAudioRef &other);
	~PlayingAudioRef() { if (m_ref) m_ref->Release_Ref(); }
private:
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	int m_00;
	PlayingAudioRef m_ref04;				// +0x04
};

class Drawable
{
public:
	Rva002390CB rva0027682F();				// key 0x25
	PlayingAudioRef rva00278190();
};

PlayingAudioRef Drawable::rva00278190()
{
	return rva0027682F().m_ref04;
}
