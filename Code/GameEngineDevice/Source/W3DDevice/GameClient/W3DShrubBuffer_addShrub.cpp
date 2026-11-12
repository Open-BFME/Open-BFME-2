// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// W3DShrubBuffer::addShrub, retail 0x000E91CE (1254 bytes, ret 0x2C). Donor: Open-BFME-1
// W3DShrubBufferRva00720D10.cpp (BFME1 0x00720D10). BFME2 layout read from retail.
#include "ascii_string.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// Retail's global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData, defined
// once in Common/GlobalData.cpp. Only the field this body reads is described on a
// TU-local view; the real class is never redeclared.
class GlobalData;
struct Rva000E91CEGlobalData
{
	unsigned char m_pad00[0x1c];
	bool m_flag1c;
};

extern GlobalData *TheWritableGlobalData;




extern float GetGameClientRandomValueReal(float, float, char *, int);
extern int GetGameClientRandomValue(int, int, char *, int);

static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
	// Preserve the observed x87 load order for this alias-sensitive aggregate update.
	const volatile float &x = position.X;
	center.X += x;
	center.Y = position.Y + center.Y;
	center.Z = position.Z + center.Z;
}

#include "../../../../GameEngine/Include/Common/FloatPair.h"

#include "../../../Include/W3DDevice/GameClient/W3DShrubBuffer.h"

// ?addShrub@W3DShrubBuffer@@QAEXIUCoord3D@@MPBVMatrix3D@@MPBURva000E91CEData@@HABVAsciiString@@3@Z
void W3DShrubBuffer::addShrub(unsigned int id, Coord3D location, float scale, const Matrix3D *transform,
	float randomScaleAmount, const Rva000E91CEData *data, int shadowKind, const AsciiString &textureName,
	const AsciiString &nameD)
{
	if (!((const Rva000E91CEGlobalData *)TheWritableGlobalData)->m_flag1c) return;
	if (m_numTrees >= 2000) return;
	if (!m_initialized) return;
	int type = -2;
	for (int i = 0; i < m_numTypes; ++i) {
		if (((const StringBase<char> *)&m_treeTypes[i].m_data->m_modelName)->compareNoCase(*(const StringBase<char> *)&data->m_modelName) == 0 &&
			((const StringBase<char> *)&m_treeTypes[i].m_data->m_textureName)->compareNoCase(*(const StringBase<char> *)&data->m_textureName) == 0) { type = i; break; }
	}
	if (type < 0) {
		type = addTreeType(data->m_modelName, data->m_textureName, data, shadowKind, textureName, nameD);
		if (type < 0) return;
		m_flag4fb6e = true;
	}
	m_treeTypes[type].m_field58 = rva000E8F9D(data->m_name48, shadowKind, textureName);
	if (data->m_framesToMoveOutward > 0 || data->m_doTopple) {
		short bucket = getPartitionBucket((const FloatPair *)&location);
		m_trees[m_numTrees].nextInPartition = m_areaPartition[bucket];
		m_areaPartition[bucket] = m_numTrees;
	} else {
		m_trees[m_numTrees].nextInPartition = -1;
	}
	float randomScale = GetGameClientRandomValueReal(1.0f - randomScaleAmount, 1.0f + randomScaleAmount,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DShrubBuffer.cpp", 0x32d);
	m_trees[m_numTrees].transform = *transform;
	if (randomScaleAmount > 0.0f) m_trees[m_numTrees].scale = scale * randomScale;
	else m_trees[m_numTrees].scale = scale;
	m_trees[m_numTrees].location = (const Vector3 &)location;
	m_trees[m_numTrees].treeType = type;
	m_trees[m_numTrees].m_field88 = type;
	m_trees[m_numTrees].m_field8c = m_treeTypes[type].m_field58;
	m_trees[m_numTrees].m_field9c = 1;
	m_trees[m_numTrees].bounds = m_treeTypes[type].m_bounds;
	{ float sc = m_trees[m_numTrees].scale; Vector3 &c = m_trees[m_numTrees].bounds.Center; c.X = sc * c.X; c.Y *= sc; c.Z *= sc; }
	m_trees[m_numTrees].bounds.Radius *= m_trees[m_numTrees].scale;
	translateBounds(m_trees[m_numTrees].bounds.Center, m_trees[m_numTrees].location);
	m_trees[m_numTrees].visible = false;
	m_trees[m_numTrees].drawableID = id;
	m_trees[m_numTrees].firstIndex = 0;
	m_trees[m_numTrees].bufferNdx = -1;
	m_trees[m_numTrees].swayType = data->m_noSway ? 0 : GetGameClientRandomValue(1, 10,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DShrubBuffer.cpp", 0x348);
	m_trees[m_numTrees].pushAside = 0;
	m_trees[m_numTrees].lastFrameUpdated = 0;
	m_trees[m_numTrees].pushAsideSource = 0;
	m_trees[m_numTrees].pushAsideDelta = 0;
	m_trees[m_numTrees].pushAsideCos = 1;
	m_trees[m_numTrees].pushAsideSin = 1;
	m_trees[m_numTrees].m_toppleState = 0;
	m_trees[m_numTrees].m_field94 = 0;
	m_trees[m_numTrees].m_field98 = 0;
	m_trees[m_numTrees].m_flag45 = false;
	m_trees[m_numTrees].m_flag46 = false;
	m_trees[m_numTrees].m_field90 = 0;
	++m_numTrees;
	m_flag4fb5e = true;
}

