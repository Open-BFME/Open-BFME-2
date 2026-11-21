#ifndef CANONICAL_W3DBUFFBUFFER_H
#define CANONICAL_W3DBUFFBUFFER_H

#include <set>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct BuffInfoView;
class Drawable;
class DX8IndexBufferClass;
class MeshClass;
class RenderInfoClass;
class RenderObjClass;
class TBuff;

struct BuffTypeView
{
	RenderObjClass *render;
	AsciiString name;
	bool flag;
};

typedef _STL::set<TBuff *> TBuffSet;

class W3DBuffBuffer
{
public:
	enum
	{
		MAX_BUFF_VERTEX = 30000,
		MAX_BUFF_INDEX = 60000
	};
	TBuff *addBuff(Drawable *, const BuffInfoView *);
	int addBuffType(const AsciiString &, const BuffInfoView *);
	void allocateBuffBuffers();
	void rva000D2301(MeshClass *mesh, RenderObjClass *target, int type, TBuffSet::iterator *it);
	void rva000D28FA(RenderInfoClass &rinfo, bool flag);

private:
	void *m_vertexBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	int m_curNumBuffVertices;
	int m_curNumBuffIndices;
	int m_vertexOffset;
	int m_indexOffset;
	BuffTypeView types[10];
	int count;
	TBuffSet buffs[10];
	bool enabled;
};

typedef char W3DBuffBufferSizeCheck[(sizeof(W3DBuffBuffer) == 0x110) ? 1 : -1];

#endif // CANONICAL_W3DBUFFBUFFER_H
