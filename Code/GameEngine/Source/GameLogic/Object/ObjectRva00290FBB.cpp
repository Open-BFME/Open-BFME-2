// cl: /EHs-c-
// ?rva00290FBB@Object@@QBEEXZ retail 0x00290FBB 14B.
// Object status-byte bit4 inverted test: reads unsigned byte at +0x1C8, shr 4, not, and 1.
// Evidence: Object+0x1C8 statusByte per Object_isAbleToAttack.cpp; this is Object* from
// findObjectByID callers at 0x0046BEF4 0x0046C038 with Object+0x38 position use; abuts
// ?getGhostObject@Rva00290EFE (0x00290EFE+189); shape ((m_b>>4)&1)==0 yields retail
// shr-al not-al and-al-1 under /O1; uchar return per sbb-tip (mangled E not _N).
class Object
{
public:
	unsigned char rva00290FBB() const;

private:
	char m_pad[0x1C8];
	unsigned char m_status1C8;
};

unsigned char Object::rva00290FBB() const
{
	return ((m_status1C8 >> 4) & 1) == 0;
}
