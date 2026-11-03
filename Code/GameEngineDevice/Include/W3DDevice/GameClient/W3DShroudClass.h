// Target facts (game.dat RVAs): constructor 0x00073320 initializes counts at +0/+4/+8/+0xC, floats at +0x10/+0x14 and +0x2C/+0x30, pointers at +0x18/+0x1C/+0x38/+0x3C, dimensions at +0x20/+0x24, filter at +0x28 and bytes at +0x34/+0x35/+0x36/+0x48. Allocation 0x0006CD18..0x0006CD67 passes 0x58 to new and calls this constructor. There is no base or vptr: W3DShroud has no virtual functions. Destructor 0x0007311B (ledger Rva0007311B), called on the same terrain member at 0x0006D246, also installs no table.
// Target facts: the ten-entry table 0x00BC6568 stored at 0x000733A5 belongs to the separately allocated 0x10-byte object stored at +0x40, whose +0xC points back to this shroud. Its base teardown 0x00072AED restores 0x00BC650C at 0x00072B15; neither table belongs to W3DShroud. Getter 0x0006F1FE copies the counted RenderingMethod pointer at +0x40; +0x44 is zeroed at 0x000733BC. The tree constructed at +0x4C through 0x000D3A71 has a header at +0x4C and count at +0x50 (0x000734CE/0x000734AD); its remaining four bytes and ownership-wrapper types stay opaque. Getter 0x00072988 reads two-byte cells at +0x18, masks the low nibble and scales it by 17.
// Target facts: out-of-line rows name construction 0x00073320, ReAcquireResources 0x000728F0, init 0x00072B72, getShroudLevel 0x00072988, setShroudLevel 0x000731F4, interpolateFogLevels 0x00073426, rva00073628 0x00073628 and rva0006F1FE 0x0006F1FE. Zero Hour's W3DShroud.h supplies the matching count, cell-size, texture-size, filter, origin and fog-buffer names; its surface members and raw texture getter do not describe this target layout. Unidentified storage uses neutral names. No method body is emitted here.
#pragma once
#ifndef BFME2_W3DSHROUD_CLASS_H
#define BFME2_W3DSHROUD_CLASS_H

class WorldHeightMap;
template <class T> class RefCountPtr;
namespace FXShader { class RenderingMethod; }
struct tagRECT;

class W3DShroud
{
public:
    W3DShroud();
    ~W3DShroud();
    bool ReAcquireResources();
    void init(WorldHeightMap *map, float worldCellSizeX, float worldCellSizeY);
    unsigned char getShroudLevel(int x, int y);
    void setShroudLevel(int x, int y, unsigned char level, bool textureOnly);
    void rva00073628(void *argument);
    RefCountPtr<FXShader::RenderingMethod> rva0006F1FE();

protected:
    void interpolateFogLevels(tagRECT *rect);

private:
    int m_numCellsX;
    int m_numCellsY;
    int m_numMaxVisibleCellsX;
    int m_numMaxVisibleCellsY;
    float m_cellWidth;
    float m_cellHeight;
    unsigned short *m_shroudData;
    unsigned char m_1C[4];
    int m_dstTextureWidth;
    int m_dstTextureHeight;
    int m_shroudFilter;
    float m_drawOriginX;
    float m_drawOriginY;
    unsigned char m_drawFogOfWar;
    unsigned char m_clearDstTexture;
    unsigned char m_borderShroudLevel;
    unsigned char *m_finalFogData;
    unsigned char *m_currentFogData;
    FXShader::RenderingMethod *m_renderingMethod;
    unsigned int m_44;
    unsigned char m_48;
    unsigned char m_pad49[3];
    unsigned char m_4C[12];
};

typedef char W3DShroudRetailSize[(sizeof(W3DShroud) == 0x58) ? 1 : -1];

#endif
