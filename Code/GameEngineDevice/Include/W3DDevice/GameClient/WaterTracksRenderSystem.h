// Target facts: WaterTracksRenderSystem is a plain class with no bases or virtual functions.
// Addresses below are RVAs unless marked VA. Constructor 0x000FE90D (46 bytes)
// and destructor 0x000FF4D6 (55 bytes) store no vptr and call no base constructor or destructor;
// 0x0007FD0D allocates 0x2C bytes and 0x0007FD22 calls that constructor without a base adjustment.
// Constructor stores prove pointers at +0/+4/+8, lists +0x10/+0x14, strip counts +0x18/+0x1C,
// and batch +0x20. Its +0x0C constant 0x0010441B is ShaderClass's state word (ctor 0x00068FE6),
// below the image's VA 0x00400000 base. init 0x000FE93B copies the shader preset from
// VA 0x00DB6234 to +0x0C and clears its cull bit at +0x0E;
// it copies the water-level float to +0x24. ReAcquireResources 0x000FE065 proves buffer pointers
// +0/+4; shutdown 0x000FF448 proves material +8 and those resources' separate virtual dispatch.
// releaseTrack 0x000FE001 and bindTrack 0x000FDF4C prove the used/free lists at +0x10/+0x14;
// flush 0x0010004D uses the vertex buffer, material, shader, used list and batch at those offsets.
// Constructor zeroes +0x28; destructor calls StringBase<char>::releaseBuffer (0x00036410)
// on the owning AsciiString member at this+0x28.
// Other rowed methods: rva000FE188 0x000FE188, rva000FE1AC 0x000FE1AC, findTrack 0x000FE207,
// rva000FE8FC 0x000FE8FC. Scalar-deleting wrapper 0x0007E10A calls the nonvirtual destructor.
// Donor names through m_level: GeneralsMD W3DDevice/GameClient/W3DWaterTracks.h.
// Retail saveTracks 0x000FF50D and loadTracks 0x000FF5E6 use m_file at +0x28 as a path string;
// those bodies are rowed under other class names. All rowed methods remain out of line.

#pragma once
#ifndef __BFME2_WATERTRACKSRENDERSYSTEM_H_
#define __BFME2_WATERTRACKSRENDERSYSTEM_H_

#include "../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class DX8VertexBufferClass;
class DX8IndexBufferClass;
class VertexMaterialClass;
class WaterTracksObj;
class RenderInfoClass;
struct FeNode;
enum waveType;

class WaterTracksRenderSystem
{
public:
    WaterTracksRenderSystem();
    ~WaterTracksRenderSystem();
    void ReAcquireResources();
    void flush(RenderInfoClass &rinfo);
    void rva000FE1AC();
    void init();
    void shutdown();
    WaterTracksObj *bindTrack(waveType type);
    void releaseTrack(FeNode *track);
    void rva000FE188();
    void rva000FE8FC(FeNode *track);
    FeNode *findTrack(const float *start, const float *end, int type);

    DX8VertexBufferClass *m_vertexBuffer;
    DX8IndexBufferClass *m_indexBuffer;
    VertexMaterialClass *m_vertexMaterialClass;
    ShaderClass m_shaderClass;
    WaterTracksObj *m_usedModules;
    WaterTracksObj *m_freeModules;
    int m_stripSizeX;
    int m_stripSizeY;
    int m_batchStart;
    float m_level;
    AsciiString m_file;
};

#endif
