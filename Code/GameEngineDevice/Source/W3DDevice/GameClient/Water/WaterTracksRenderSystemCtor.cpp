// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD
// BF1 WaterTracksRenderSystem source and native new(0x2c) at 7FD0D
// followed by FE90D prove this is the WaterTracksRenderSystem constructor.
// Target member offsets agree with the separately verified init FE93B.
#include "ascii_string.h"
class ShaderClass {
public:
 ShaderClass() : bits(0x10441b) {}
 unsigned int bits;
};
class WaterTracksRenderSystem {
public:
 WaterTracksRenderSystem();
 void *vertexBuffer, *indexBuffer, *material;
 ShaderClass shader;
 void *used, *free;
 int stripX, stripY, batch;
 float level;
 AsciiString filename;
};
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;
WaterTracksRenderSystem::WaterTracksRenderSystem() {
 used=0;
 free=0;
 indexBuffer=0;
 material=0;
 vertexBuffer=0;
 stripX=2;
 stripY=2;
 batch=0;
 TheWaterTracksRenderSystem=this;
}
