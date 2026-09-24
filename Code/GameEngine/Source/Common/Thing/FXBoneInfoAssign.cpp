// cl: /O1 /DNDEBUG /MD

// FXBoneInfo::operator=, retail 0x001D9990 (27 bytes).
// Identity is call-proven: the EightByteVectorCopyLoop copy pair
// (copyEightByteRange at 0x00254D65 plus its forwarder at 0x00255CFA,
// both rowed) drives per-element `*dest = *first` over FXBoneInfo arrays,
// and the sole byte-true target of that call is this body.
// Layout is donor-backed (ZH StructureToppleUpdate.h): boneName first,
// particleSystemTemplate second; retail proves the sizes (string call at
// +0, plain copy at +4, 8-byte stride in the copy loop).
// The string call folds to the ledger's AsciiString assignment at
// 0x000366F0, so this TU needs zero new pins.

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_particleSystemTemplate;

	FXBoneInfo &operator=(const FXBoneInfo &other);
};

FXBoneInfo &FXBoneInfo::operator=(const FXBoneInfo &other)
{
	m_boneName = other.m_boneName;
	m_particleSystemTemplate = other.m_particleSystemTemplate;
	return *this;
}
