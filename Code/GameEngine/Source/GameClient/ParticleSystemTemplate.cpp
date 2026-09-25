// cl: /O1 /EHsc

// The template's string accessors. Each returns an AsciiString by value, so the
// copy constructor runs into the caller's slot inside an unwind region - the
// `and dword ptr [ebp-4], 0` ahead of it is the EH state store - which is why
// these cannot sit in FXParticleSystem.cpp with its /GX-.
//
// The static parse() below builds its 22-entry FieldParse table as a local
// aggregate; MSVC hoists the repeated parse verbs into registers (eax holds
// parseIndexList then parseAsciiString then parseGameClientRandomVariable,
// ecx holds parseBool, esi the bounded-unsigned verb, edx NULL) and stores
// single-use tokens, name tables, and offsets inline in entry order.

#include <stddef.h>

class INI;

template <typename T>
class StringBase
{
private:
    friend class AsciiString;

    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString
{
public:
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }

    // Declared, never defined: the return object needs cleanup for MSVC to open
    // an unwind region at all, and that state store is the first thing retail
    // does after the frame.
    ~AsciiString();

    // Declared, never defined: setTextureFilename tail-jumps to it, and the
    // call resolves through its own ledger row.
    AsciiString &operator=(const AsciiString &that);

private:
    char *m_text;
};

struct Region2D
{
    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

struct Coord3D
{
    float x;
    float y;
    float z;
};

// BFME1 ClientRandomValue.h layout (DistributionType first, then the range):
// 12 bytes, no constructor or destructor by design (used within unions).
class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT,
        UNIFORM,
        GAUSSIAN,
        TRIANGULAR,
        LOW_BIAS,
        HIGH_BIAS
    };

protected:
    DistributionType m_type;
    float m_low;
    float m_high;
};

struct FieldParse
{
    const char *token;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    int offset;
};

class INI
{
public:
    void initFromINI(void *instance, const FieldParse *table);
    static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
    static void parseBool(INI *ini, void *instance, void *store, const void *userData);
    static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
    static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
    static void dup_002EF72(INI *ini, void *instance, void *store, const void *userData);
    static void parseGameClientRandomVariable(INI *ini, void *instance, void *store, const void *userData);
};

namespace FXParticleSystem
{

enum ParticleType
{
    PARTICLE_TYPE_DEFAULT
};

// Name tables live in retail .rdata (exports 0x81B6A4/0x81B610/0x81B640); the
// references are DIR32 relocations, which the gate fills from retail, so they
// stay declared without a definition here.
extern const char *ParticlePriorityNames[];
extern const char *ParticleShaderTypeNames[];
extern const char *ParticleTypeNames[];

// Offsets recovered from the accessors themselves: the texture filename is the
// second word of the object and the name sits past the UV rectangle. The
// parse table below pins the rest: the random-variable fields are 12 bytes
// each (Lifetime 0x14, Size 0x28, StartSizeRate 0x34, BurstDelay 0x44,
// BurstCount 0x50, InitialDelay 0x5c), SlavePosOffset is a Coord3D at 0x6c,
// Priority sits at 0x7c, and five bool flags pack 0x80-0x84 ahead of the UV
// rectangle at 0x88. BFME1 names this 0x10 slot m_particleTypeName.
class ParticleSystemTemplate
{
public:
    AsciiString getName() const;
    AsciiString getTextureFilename() const;
    ParticleType getParticleType() const;
    void setTextureFilename(const AsciiString &name);
    static void parse(INI *ini, void *instance, void *store, const void *userData);

private:
    char m_unknown00[0x04];
    bool m_isOneShot;
    char m_pad05[0x03];
    int m_shaderType;
    ParticleType m_particleType;
    AsciiString m_textureFilename;
    GameClientRandomVariable m_lifetime;
    unsigned int m_systemLifetime;
    int m_sortLevel;
    GameClientRandomVariable m_startSize;
    GameClientRandomVariable m_startSizeRate;
    char m_unknown40[0x04];
    GameClientRandomVariable m_burstDelay;
    GameClientRandomVariable m_burstCount;
    GameClientRandomVariable m_initialDelay;
    AsciiString m_slaveSystemName;
    Coord3D m_slavePosOffset;
    AsciiString m_attachedSystemName;
    int m_priority;
    bool m_isGroundAligned;
    bool m_isEmitAboveGroundOnly;
    bool m_isParticleUpTowardsEmitter;
    bool m_useMaximumHeight;
    bool m_shroudEmitter;
    char m_pad85[0x03];
    Region2D m_uv;
    char m_unknown98[4];
    AsciiString m_name;
};

AsciiString ParticleSystemTemplate::getName() const
{
    return m_name;
}

AsciiString ParticleSystemTemplate::getTextureFilename() const
{
    return m_textureFilename;
}

ParticleType ParticleSystemTemplate::getParticleType() const
{
    return m_particleType;
}

// ?setTextureFilename@ParticleSystemTemplate@FXParticleSystem@@QAEXABVAsciiString@@@Z
void ParticleSystemTemplate::setTextureFilename(const AsciiString &name)
{
    m_textureFilename = name;
}

// ?parse@ParticleSystemTemplate@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
void ParticleSystemTemplate::parse(INI *ini, void *instance, void *, const void *)
{
    FieldParse table[] =
    {
        { "Priority", INI::parseIndexList, ParticlePriorityNames, offsetof(ParticleSystemTemplate, m_priority) },
        { "IsOneShot", INI::parseBool, NULL, offsetof(ParticleSystemTemplate, m_isOneShot) },
        { "Shader", INI::parseIndexList, ParticleShaderTypeNames, offsetof(ParticleSystemTemplate, m_shaderType) },
        { "Type", INI::parseIndexList, ParticleTypeNames, offsetof(ParticleSystemTemplate, m_particleType) },
        { "ParticleName", INI::parseAsciiString, NULL, offsetof(ParticleSystemTemplate, m_textureFilename) },
        { "SlaveSystem", INI::parseAsciiString, NULL, offsetof(ParticleSystemTemplate, m_slaveSystemName) },
        { "SlavePosOffset", INI::parseCoord3D, NULL, offsetof(ParticleSystemTemplate, m_slavePosOffset) },
        { "PerParticleAttachedSystem", INI::parseAsciiString, NULL, offsetof(ParticleSystemTemplate, m_attachedSystemName) },
        { "Lifetime", INI::parseGameClientRandomVariable, NULL, offsetof(ParticleSystemTemplate, m_lifetime) },
        { "SystemLifetime", INI::dup_002EF72, NULL, offsetof(ParticleSystemTemplate, m_systemLifetime) },
        { "SortLevel", INI::dup_002EF72, NULL, offsetof(ParticleSystemTemplate, m_sortLevel) },
        { "Size", INI::parseGameClientRandomVariable, NULL, offsetof(ParticleSystemTemplate, m_startSize) },
        { "StartSizeRate", INI::parseGameClientRandomVariable, NULL, offsetof(ParticleSystemTemplate, m_startSizeRate) },
        { "BurstDelay", INI::parseGameClientRandomVariable, NULL, offsetof(ParticleSystemTemplate, m_burstDelay) },
        { "BurstCount", INI::parseGameClientRandomVariable, NULL, offsetof(ParticleSystemTemplate, m_burstCount) },
        { "InitialDelay", INI::parseGameClientRandomVariable, NULL, offsetof(ParticleSystemTemplate, m_initialDelay) },
        { "IsGroundAligned", INI::parseBool, NULL, offsetof(ParticleSystemTemplate, m_isGroundAligned) },
        { "IsEmitAboveGroundOnly", INI::parseBool, NULL, offsetof(ParticleSystemTemplate, m_isEmitAboveGroundOnly) },
        { "IsParticleUpTowardsEmitter", INI::parseBool, NULL, offsetof(ParticleSystemTemplate, m_isParticleUpTowardsEmitter) },
        { "UseMaximumHeight", INI::parseBool, NULL, offsetof(ParticleSystemTemplate, m_useMaximumHeight) },
        { "ShroudEmitter", INI::parseBool, NULL, offsetof(ParticleSystemTemplate, m_shroudEmitter) },
        { NULL, NULL, NULL, 0 }
    };
    ini->initFromINI(instance, table);
}

}
