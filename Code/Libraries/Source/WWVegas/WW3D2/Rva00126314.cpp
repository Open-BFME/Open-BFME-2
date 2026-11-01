// ??0Rva00126314@@QAE@XZ
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native renderer settings36; donor SegLineRenderer initializer is semantic guide.
class TextureClass;
class ShaderClass {public: __declspec(dllimport) __forceinline ShaderClass(const ShaderClass &that):Bits(that.Bits){} unsigned Bits; static ShaderClass _PresetAdditiveSpriteShader;};
#include "../WWMath/Vector3Data.h"
struct Rva00126314 {Rva00126314();TextureClass *texture;ShaderClass shader;float width;Vector3 color;float opacity,scale;bool flag;};
Rva00126314::Rva00126314():texture(0),shader(ShaderClass::_PresetAdditiveSpriteShader),width(0.f),color(1.f,1.f,1.f),opacity(1.f),scale(1.f),flag(false){}
