// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/shims/stringinline
//
// ??1Rva00735D80TreeType@@QAE@XZ, retail 0x000EC6E1, 124 bytes.
// Evidence: Rva00735D80TreeTypeCtor.cpp's destructor compiles to these bytes
// except the four string teardowns: retail calls the folded string dtor at
// 0x00036410, while ~AsciiString resolves to its rowed 5-byte copy at
// 0x0048BA39. The strings are spelled AsciiStringMember here, as other TUs
// do for call sites that read 0x00036410; it lives apart from the ctor so the
// rowed ctor keeps its AsciiString members.

#include "coord2d.h"

class AsciiStringMember
{
public:
	~AsciiStringMember();

private:
	void *m_data;
};

class Rva00735D80TreeType
{
public:
	~Rva00735D80TreeType();

private:
	unsigned char m_treeData[0x24];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
	unsigned char m_textureFlags[4];
	AsciiStringMember m_modelName;
	AsciiStringMember m_textureName;
	AsciiStringMember m_shadowName;
	AsciiStringMember m_animationName;
};

Rva00735D80TreeType::~Rva00735D80TreeType()
{
}

// ??1Rva000E86B8@@QAE@XZ, retail 0x000E86B8, 124 bytes: the same teardown for a
// sibling class of this layout; only the EH handler record differs from
// ~Rva00735D80TreeType's bytes. It directly follows the constructor rowed at
// 0x000E8656, as 0x000EC67F precedes the destructor rowed at 0x000EC6E1, so retail
// holds two such classes. Identity is not recovered.
class Rva000E86B8
{
public:
	~Rva000E86B8();
private:
	unsigned char m_treeData[0x24];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
	unsigned char m_textureFlags[4];
	AsciiStringMember m_modelName;
	AsciiStringMember m_textureName;
	AsciiStringMember m_shadowName;
	AsciiStringMember m_animationName;
};

Rva000E86B8::~Rva000E86B8()
{
}
