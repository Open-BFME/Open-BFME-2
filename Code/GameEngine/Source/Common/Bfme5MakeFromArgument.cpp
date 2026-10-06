// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class BfmeMade_009CB5F0
{
public:
	BfmeMade_009CB5F0(void *owner);			// retail 0x009CB4E0

private:
	int m_bfmeFields[0xA];
};

// ?bfmeMake_009CB5F0@@YAPAVBfmeMade_009CB5F0@@PAX@Z
BfmeMade_009CB5F0 * __cdecl bfmeMake_009CB5F0(void *owner)
{
	return new BfmeMade_009CB5F0(owner);
}
