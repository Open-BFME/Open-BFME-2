// cl: /DNDEBUG /MD
//
// ?_bfme_mapper_v8@TextureMapperClass@@UAE_NH@Z, retail 0x00182150, 5 bytes.
// BFME2 adds a one-argument bool virtual to TextureMapperClass between the donor's
// Needs_Normals (slot 7) and Calculate_Texture_Matrix (slot 9); the base default
// returns false (XOR AL,AL / RET 4). Evidence: slot 8 of ??_7ClassicEnvironmentMapperClass
// (0x00BD3170) and ten other mapper tables point at this body; BFME1/ZH mapper.h has
// no such slot, so the name is slot-derived and the argument type is unknown (int).

class TextureMapperClass
{
public:
	virtual bool _bfme_mapper_v8(int unk);
};

bool TextureMapperClass::_bfme_mapper_v8(int unk)
{
	return false;
}
