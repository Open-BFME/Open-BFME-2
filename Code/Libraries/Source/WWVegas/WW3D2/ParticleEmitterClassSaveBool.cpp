// cl: /G7 /EHsc /arch:SSE /DNDEBUG /MD
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Adapted from the Open-BFME-1 ParticleEmitterClass::Save donor.  BFME2's
// retail entry point has a bool ABI, so the declaration below is a local ABI
// view and does not alter the later vendored WW3DErrorType declaration.
class ChunkLoadClass;
class ChunkSaveClass;

// The retail definition vtable has a destructor, Load_W3D, then Save_W3D;
// retaining those slots makes the virtual save call land at vtable + 0x8.
class ParticleEmitterDefClass
{
public:
    virtual ~ParticleEmitterDefClass();
    virtual bool Load_W3D(ChunkLoadClass &chunk_load);
    virtual bool Save_W3D(ChunkSaveClass &chunk_save);
};

class ParticleEmitterClass
{
public:
    ParticleEmitterDefClass *Build_Definition(void) const;
    bool Save(ChunkSaveClass &chunk_save) const;
};

bool ParticleEmitterClass::Save(ChunkSaveClass &chunk_save) const
{
    bool ret_val = false;
    ParticleEmitterDefClass *pdefinition = Build_Definition();
    if (pdefinition != 0) {
        ret_val = pdefinition->Save_W3D(chunk_save);
    }
    return ret_val;
}
