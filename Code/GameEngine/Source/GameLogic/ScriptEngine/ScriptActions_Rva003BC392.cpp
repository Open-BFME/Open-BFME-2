// cl: /DNDEBUG /MD /EHsc
//
// ScriptActions bool setter over the TerrainLogic singleton, retail
// 0x003BC392 (19 bytes, ret 4): null-checked store of the argument byte to
// [TheTerrainLogic+0x1914]. Boundary by ret-scan; sole E8 caller is the
// script-action dispatcher case at 0x3CD094, which passes a setne-built 0/1
// (hence bool). True semantic identity unproven, so the row carries an
// address token (opaque-holder precedent).

struct TerrainLogicMirror
{
	unsigned char pad[0x1914];
	bool flag1914;
};

extern TerrainLogicMirror *TheTerrainLogic;

struct Rva003BC392Holder
{
	void set(bool enabled);
};

// ?set@Rva003BC392Holder@@QAEX_N@Z
void Rva003BC392Holder::set(bool enabled)
{
	if (TheTerrainLogic == 0)
		return;
	TheTerrainLogic->flag1914 = enabled;
}
// ?TheTerrainLogic@@3PAUTerrainLogicMirror@@A: the global at VA 0xdfec50 is ?TheTerrainLogic@@3PAVTerrainLogic@@A.
#pragma comment(linker, "/alternatename:?TheTerrainLogic@@3PAUTerrainLogicMirror@@A=?TheTerrainLogic@@3PAVTerrainLogic@@A")
