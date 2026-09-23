// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ibuild/toolchains/dx81/include /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME MaterialInfoClass::Get_Texture_Index: RVA 0x00930680, full 96 bytes.
// GeneralsMD matinfo.cpp supplies the name, signature and search semantics.
// The matched BFME default/copy constructors establish the texture vector at
// +0x20 (array +0x24, active count +0x30); elements are owning 4-byte handles.
// Retail calls BFME2ParticleTextureHandle::Get_Texture_Name at 0x008FF5B0, compares via
// the _strcmpi import at VA 0x0135933C, then frees the temporary StringClass
// through 0x009DB7A0. Both RET 4 paths end within this complete span; the
// next distinct function starts immediately at 0x009306E0.
#include "wwstring.h"
#include "vector.h"
#include <string.h>
class TextureClass;
class BFME2ParticleTextureHandle {
public:
    TextureClass *p;
    StringClass Get_Texture_Name() const;
    bool operator==(const BFME2ParticleTextureHandle &other) const { return p == other.p; }
    bool operator!=(const BFME2ParticleTextureHandle &other) const { return p != other.p; }
};

class MaterialInfoClass {
public:
    int Get_Texture_Index(const char *name);
private:
    char prefix[0x20];
    DynamicVectorClass<BFME2ParticleTextureHandle> Textures;
};

int MaterialInfoClass::Get_Texture_Index(const char *name)
{
    for (int i = 0; i < Textures.Count(); i++) {
        if (_strcmpi(name, Textures[i].Get_Texture_Name()) == 0) return i;
    }
    return -1;
}
