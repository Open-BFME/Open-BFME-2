// cl: /O1
// ?rva0006840A@Rva0006840A@@QAEXQAVVector3@@W4DrawableID@@_N@Z retail 0x0006840A 11B,
// ?rva00068415@Rva00068415@@QAEXXZ retail 0x00068415 11B,
// ?rva00068420@Rva00068420@@QAEXXZ retail 0x00068420 11B.
// Three 11B tail-jmp forwarders via the +0x385C W3DBibBuffer member, same offset
// as neighbour 0x000683FF (Rva000683FF.cpp). Evidence: each body is
// mov ecx,[ecx+0x385C] then jmp to a rowed W3DBibBuffer method
// (0x000D415B addBibDrawable, 0x000D3D44 removeHighlighting, 0x000D3D35 clearAllBibs);
// caller of 0x0006840A at 0x00092DB3 pushes corners[4] + int id + outer bool.
class Vector3
{
public:
	float x, y, z;
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};

class W3DBibBuffer
{
public:
	void addBibDrawable(Vector3 corners[4], DrawableID id, bool highlight);
	void removeHighlighting();
	void clearAllBibs();
};

class Rva0006840A
{
public:
	void rva0006840A(Vector3 corners[4], DrawableID id, bool highlight);
private:
	unsigned char m_pad[0x385C];
	W3DBibBuffer *m_bib;
};

void Rva0006840A::rva0006840A(Vector3 corners[4], DrawableID id, bool highlight)
{
	return m_bib->addBibDrawable(corners, id, highlight);
}

class Rva00068415
{
public:
	void rva00068415();
private:
	unsigned char m_pad[0x385C];
	W3DBibBuffer *m_bib;
};

void Rva00068415::rva00068415()
{
	m_bib->removeHighlighting();
}

class Rva00068420
{
public:
	void rva00068420();
private:
	unsigned char m_pad[0x385C];
	W3DBibBuffer *m_bib;
};

void Rva00068420::rva00068420()
{
	m_bib->clearAllBibs();
}
