// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Native 0x0018C088..0x0018C09B (19 bytes, RET 0): 2 when the shared buffer
// at +0x34 exists, else whether the one at +0x30 does. Both callers sit in
// FXShaderGeometry::Init (0x0018C84E, WB fxshadergeometry.cpp): 0x0018C969
// calls it on the mesh it just passed to MeshGeometryClass::get_bone_links
// (0x0016A0C0) and scales the result by VertexCount (+0x28); 0x0018CB45
// uses it as the per-vertex count when skinning, 1 otherwise. +0x30/+0x34
// are two of the 12-byte-element buffers meshgeometry.cpp's layout records.
// The original method name is unknown, hence the address name. The 9-byte
// tail at 0x0018C092 (the je target here) is not a separate entry: nothing
// calls or references it.
class MeshGeometryClass
{
public:
	int rva0018C088() const;

private:
	unsigned char m_pad00[0x30];
	void *m_buffer30; // +0x30
	void *m_buffer34; // +0x34
};

int MeshGeometryClass::rva0018C088() const
{
	if (m_buffer34)
		return 2;
	return m_buffer30 != 0;
}
