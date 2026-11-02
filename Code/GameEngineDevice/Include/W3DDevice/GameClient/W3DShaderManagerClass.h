// Target facts (code addresses are RVAs; static storage addresses are VAs):
//  - Constructor 0x00075480..0x000754DE only initializes absolute-address statics;
//    ECX is used solely to return this. There is no base call or vtable store.
//    W3DShaderManager has no virtual functions, bases or instance fields. No
//    destructor or allocation-size witness is rowed; the empty C++ class is size 1.
//  - Constructor stores: m_currentShader (int) at 0x00DE1F54, m_currentFilter
//    (int) at 0x00DE1F5C, m_renderingToTexture (byte) at 0x00DE1F60,
//    m_oldRenderSurface at 0x00DE1F64 and m_renderTexture at 0x00DE1F68.
//    The DWORD glow handles at 0x00DE1F74/78 are passed by init 0x00077F80
//    to loaders 0x00077D0F/0x00077C19 and read by performGlow 0x00077392.
//  - Rowed static methods: init 0x00077F80, shutdown 0x0007684A,
//    getShaderPasses(ShaderTypes) 0x00075649, setShroudTex(int) 0x00076C14,
//    setTexture(int, const TextureHandle &) 0x00072B25, drawViewport(int, bool,
//    const Vector2 *) 0x00075746, performGlow 0x00077392, createGaussianVector
//    0x000780BC and testMinimumRequirements 0x00076629 (64-bit RAM output).
//  - canRenderToTexture 0x000F630C tests surfaces at 0x00DE1F64/6C;
//    startRenderToTexture 0x00075BD8, endRenderToTexture 0x00075D52 and
//    getRenderTexture 0x00075E36 use the flag and texture statics above.
//    isRenderingToTexture 0x000A60EA reads the byte at 0x00DE1F60; retail
//    inlines that read at 0x000A64C7 and 0x000A6EF6 in the smudge methods.
//  - BfmeValidatedHandle::setValue 0x00085F2C calls filterSetup 0x00075725,
//    already pinned under that spelling; its rowed owner is Rva00075725Check.
// Names: the verified ledger spellings and Zero Hour W3DShaderManager.h.

#pragma once

#ifndef __BFME2_W3DSHADERMANAGERCLASS_H_
#define __BFME2_W3DSHADERMANAGERCLASS_H_

enum ChipsetType;
enum CpuType;
enum FilterTypes;
enum FilterModes;
class TextureHandle;
class Vector2;
struct BfmeGaussianParams;
struct GlowSampleVector;
struct IDirect3DSurface8;
struct IDirect3DTexture8;

class W3DShaderManager
{
    friend class Rva00075655;
    friend void Rva00075695Notify(int index);
    friend bool __cdecl Rva000756BFSelect(int index, int a1, int a2);
    friend bool __cdecl Rva000756F1Dispatch(int index, int a1, int a2, int a3, int a4);

public:
    enum ShaderTypes { ST_INVALID };

    W3DShaderManager();
    static void init();
    static void shutdown();
    static int getShaderPasses(ShaderTypes shader);
    static int setShroudTex(int stage);
    static void setTexture(int stage, const TextureHandle &texture);
    static bool filterSetup(FilterTypes filter, FilterModes mode);
    static bool canRenderToTexture();
    static void startRenderToTexture();
    static IDirect3DTexture8 *endRenderToTexture();
    static IDirect3DTexture8 *getRenderTexture();
    static bool isRenderingToTexture() { return m_renderingToTexture; }
    static void drawViewport(int color, bool useExplicitDimensions, const Vector2 *dimensions);
    static bool testMinimumRequirements(ChipsetType *videoChipType, CpuType *cpuType,
        int *cpuFreq, unsigned __int64 *numRAM, float *intBenchIndex,
        float *floatBenchIndex, float *memBenchIndex);
    static void performGlow(float weightScale, const GlowSampleVector *samples,
        int textureSize, IDirect3DTexture8 *sourceTexture, IDirect3DSurface8 *tempSurface,
        IDirect3DTexture8 *tempTexture, IDirect3DSurface8 *destSurface);
    static void createGaussianVector(void *kernel, BfmeGaussianParams *params);

    static IDirect3DSurface8 *m_oldRenderSurface;
    static IDirect3DTexture8 *m_renderTexture;

protected:
    static int m_currentShader;
    static int m_currentFilter;
    static bool m_renderingToTexture;
    static unsigned long m_dwGlowPixelShader;
    static unsigned long m_dwGlowVertexShader;
};

#endif
