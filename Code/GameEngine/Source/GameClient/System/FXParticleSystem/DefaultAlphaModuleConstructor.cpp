// cl: /DNDEBUG /MD /EHsc /Ob2 /O1 /arch:SSE /G7

// Native 0x0055B5E9..0x0055B65D is the smart-handle/input constructor
// of the existing Rva003AEA42 owner: all four vtable destinations match
// its independently rowed 0x003AEA42 copy constructor. The native base
// call fixes the 0x1C head extent; the alpha-info constructor and eight
// 16-byte assignments fix the embedded info and source +0xC key array.
// Composition here is an ABI view of those two construction stages;
// their complete retail inheritance names remain unproven.

class RvaSmartPtr12;
class Rva0055B5BF
{
public:
    Rva0055B5BF(const RvaSmartPtr12 &, int);
    virtual ~Rva0055B5BF();
private:
    char storage[0x18];
};

namespace FXParticleSystem
{

struct FXCoord3D
{
	float x;
	float y;
	float z;
};

struct FXKeyframe
{
	FXCoord3D m_value;
	unsigned int m_frame;
};

struct AlphaKeys
{
	FXKeyframe m_keys[8];
};

class DefaultAlphaModuleInfo
{
public:
    DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();

private:
	FXKeyframe m_keys[8];
};

}

extern "C" char Rva003AEA42_v0b;
extern "C" char Rva003AEA42_v14b;
extern "C" char Rva003AEA42_v18b;
extern "C" char Rva003AEA42_vsub;

class Rva003AEA42
{
public:
    Rva003AEA42(const RvaSmartPtr12 &, int);

private:
    Rva0055B5BF m_base;
    FXParticleSystem::DefaultAlphaModuleInfo m_info;
};

// Native 55B5E9..55B65D: rowed smart base and default alpha info, then
// the owner's existing vtables and eight 16-byte source keys at input+C.
Rva003AEA42::Rva003AEA42(const RvaSmartPtr12 &smart, int input)
    : m_base(smart, input), m_info()
{
    *(void **)this = &Rva003AEA42_v0b;
    *(void **)((char *)this + 0x14) = &Rva003AEA42_v14b;
    *(void **)((char *)this + 0x18) = &Rva003AEA42_v18b;
    *(void **)((char *)this + 0x1C) = &Rva003AEA42_vsub;
    for (int i = 0; i < 8; ++i)
        ((FXParticleSystem::AlphaKeys *)((char *)this + 0x20))->m_keys[i] =
            ((const FXParticleSystem::AlphaKeys *)(input + 0xC))->m_keys[i];
}
