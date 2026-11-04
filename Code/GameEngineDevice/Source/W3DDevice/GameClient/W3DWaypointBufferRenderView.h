// TU-scoped rendering view for the waypoint constructor, destructor and draw row.
// The existing rows establish reference count +4, transform +0x18 and virtual
// Render/Validate_Transform/Set_Position slots 12/20/22. Preserve those offsets
// while giving both donors the same inherited reference-count operations.
#ifndef W3D_WAYPOINT_BUFFER_RENDER_VIEW_H
#define W3D_WAYPOINT_BUFFER_RENDER_VIEW_H

class RenderInfoClass;
class Matrix3D;

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	Int NumRefs;
};

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class RenderObjClass : public RefCountClass
{
public:
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void Render(RenderInfoClass &rinfo);
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void Validate_Transform(void) const;
	virtual void slot21();
	virtual void Set_Position(const Vector3 &v);

	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *(const Matrix3D *)m_transform;
	}

	unsigned char m_unreconstructed_08[0x18 - 8];
	unsigned char m_transform[0x30];
};

class ShaderClass
{
public:
	ShaderClass() {}
	__declspec(dllimport) __forceinline ShaderClass(const ShaderClass &s) : m_bits(s.m_bits) {}
	void Set_Depth_Compare(int x) { m_bits = (m_bits & ~7) | x; }
	static ShaderClass _PresetAdditiveShader;
	unsigned int m_bits;
};

class SegLineRendererClass
{
public:
	enum TextureMapMode { UNIFORM_WIDTH_TEXTURE_MAP, UNIFORM_LENGTH_TEXTURE_MAP, TILED_TEXTURE_MAP };
};

class TextureClass;

class SegmentedLineClass : public RenderObjClass
{
public:
	virtual void Delete_This(void);
	SegmentedLineClass();
	void Set_Texture(TextureClass *);
	void Set_Shader(ShaderClass);
	void Set_Width(float);
	void Set_Color(const Vector3 &);
	void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode);
	void Set_Points(unsigned int num_points, Vector3 *locs);
	char m_rest[0x12c - 0x48];
};

#endif
