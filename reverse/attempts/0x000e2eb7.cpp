// ?Rva000E2EB7@@YAXPAUID3DXEffect@@PBD@Z
// partial score=0.85 date=2026-10-05
// ?Rva000E2EB7@@YAXPAUID3DXEffect@@PBD@Z present-unmatched
void Rva000E2EB7(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (TheTerrainRenderObject)
	{
		if (*(BfmeTerrain37C0Target **)((char *)TheTerrainRenderObject + 0x37C0))
		{
			BfmeTerrain37C0Target *t = *(BfmeTerrain37C0Target **)((char *)TheTerrainRenderObject + 0x37C0);
			value.x = (float)t->m_08 * BfmeGlobalBC2428;
			value.y = (float)t->m_0C * BfmeGlobalBC2428;
		}
	}
	effect->SetVector(handle, &value);
}
