// cl: /O1 /DNDEBUG /MD
//
// BfmeResetTextureRef::clear, retail 0x0004D75B, 19 bytes.
// Dedicated TU so the assign unit cannot see this body. /O1 for and-zero
// of the holder after Release_Ref.

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

void BfmeResetTextureRef::clear()
{
	if (pointer)
	{
		pointer->Release_Ref();
		pointer = 0;
	}
}
