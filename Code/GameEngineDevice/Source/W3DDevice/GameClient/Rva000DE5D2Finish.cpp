// cl: /MD /EHsc /DNDEBUG
//
// ?Rva000DE5D2Copy@@YGHPAGHGPAX@Z 0x000DE5D2 118B.
// Authentic donor body: reference/open-bfme-1/game/GameEngineDevice/Source/
// W3DDevice/GameClient/W3DBridgeBuffer.cpp W3DBridge::getModelIndices
// (maxBridgeIndex 16000), the mesh index copier. BFME2 keeps the same body as
// a free __stdcall (unsigned short*, int, unsigned short, void*) whose third
// argument is the vertex offset; the source clamps curIndex+3*numPoly+6
// against 16000 and copies three unsigned shorts per polygon with the offset
// added. Struct offsets below are the inlined Peek_Model()/Get_Polygon_Count()/
// Get_Polygon_Array() chain observed in the retail bytes: pMesh+0xC4 -> model,
// model+0x24 -> polygon count, model+0x2C -> polygon-array holder whose data
// pointer is +0xC. The exact match uses the for-loop spelling (not the banked
// do-while) with pPoly[i].I/J/K.
struct De5d2Inner
{
	int _pad[3];
	unsigned short *m_buf;
};
struct De5d2Mid
{
	char _pad0[0x24];
	int m_count;
	char _pad1[4];
	De5d2Inner *m_inner;
};
struct De5d2Outer
{
	char _pad[0xC4];
	De5d2Mid *m_mid;
};
struct TriIndex { unsigned short I, J, K; };

int __stdcall Rva000DE5D2Copy(unsigned short *destination_ib, int curIndex, unsigned short vertexOffset, void *pMeshRaw)
{
	if (pMeshRaw == 0)
		return 0;
	De5d2Outer *pMesh = (De5d2Outer *)pMeshRaw;
	De5d2Mid *model = pMesh->m_mid;
	int numPoly = model->m_count;
	De5d2Inner *inner = model->m_inner;
	const TriIndex *pPoly = (const TriIndex *)inner->m_buf;
	const int maxBridgeIndex = 16000;
	if (curIndex + 3 * numPoly + 6 >= maxBridgeIndex)
		return 0;
	unsigned short *curIb = destination_ib + curIndex;
	for (int i = 0; i < numPoly; i++)
	{
		*curIb++ = vertexOffset + pPoly[i].I;
		*curIb++ = vertexOffset + pPoly[i].J;
		*curIb++ = vertexOffset + pPoly[i].K;
	}
	return numPoly * 3;
}
