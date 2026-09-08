// BFME2 texture ownership used by particle emitter construction and serialization.
#ifndef BFME2_PARTICLE_TEXTURE_HANDLE_H
#define BFME2_PARTICLE_TEXTURE_HANDLE_H
#include "texture.h"
#include "wwstring.h"
class BFME2ParticleTextureHandle {
    TextureClass *Ptr;
public:
    BFME2ParticleTextureHandle(TextureClass *ptr = 0) : Ptr(ptr) {
        if (Ptr) Ptr->Add_Ref();
    }
    BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &other) : Ptr(other.Ptr) {
        if (Ptr) Ptr->Add_Ref();
    }
    ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
    BFME2ParticleTextureHandle &operator=(const BFME2ParticleTextureHandle &other) {
        if (other.Ptr) other.Ptr->Add_Ref();
        if (Ptr) Ptr->Release_Ref();
        Ptr = other.Ptr;
        return *this;
    }
    operator bool() const { return Ptr != 0; }
    StringClass Get_Texture_Name() const;
    // Descriptive conversion predicate; this retail build returns false.
    bool Use_Alpha_Shader() const;
};
#endif
