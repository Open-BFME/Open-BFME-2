// cl: /O2 /Ireference/shims/bfme2htree /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// stlport
// ZH read_pivots adapted to the BFME 2 compact pivot ABI proven by
// WorldBuilder HTreeClass::read_pivots and retail RVA 0x001614F0 (526 bytes).
// BFME 1 donor revision: ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
#include "htree.h"
#include "chunkio.h"
#include <string.h>
#include <assert.h>

// BFME 2 WorldBuilder read_pivots and retail 0x001614F0 agree on the
// 0x58-byte pivot and quaternion/vector transform, unlike ZH's Matrix3D pivot.
struct Bfme2HTreeTransform {
    Quaternion Rotation;
    Vector3 Translation;
    // ?Bfme2HTreeTransform::Bfme2HTreeTransform absent-from-retail
    __forceinline Bfme2HTreeTransform(bool identity) {
        Rotation.Make_Identity();
        Translation.Set(0.0f, 0.0f, 0.0f);
    }
    // ?Bfme2HTreeTransform::operator= absent-from-retail
    __forceinline Bfme2HTreeTransform &operator=(const Bfme2HTreeTransform &source) {
        Rotation = source.Rotation;
        Translation = source.Translation;
        return *this;
    }
};
struct Bfme2HTreePivot {
    char Name[16];
    Bfme2HTreePivot *Parent;
    Bfme2HTreeTransform BaseTransform;
    Bfme2HTreeTransform Transform;
    int Index;
    bool IsVisible;
    float PivotFade;
};
typedef char Bfme2HTreePivotSize[(sizeof(Bfme2HTreePivot) == 88) ? 1 : -1];
bool HTreeClass::read_pivots(ChunkLoadClass &cload, bool pre30)
{
    W3dPivotStruct piv;
    int first_piv = 0;
    if (pre30) {
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Index = 0;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Parent = NULL;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].BaseTransform = Bfme2HTreeTransform(true);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Transform = Bfme2HTreeTransform(true);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].IsVisible = true;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].PivotFade = 1.0f;
        strcpy(reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Name, "RootTransform");
        first_piv++;
    }
    for (int pidx = first_piv; pidx < NumPivots; pidx++) {
        if (cload.Read(&piv, sizeof(W3dPivotStruct)) != sizeof(W3dPivotStruct))
            return false;
        memcpy(reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Name, piv.Name, W3D_NAME_LEN);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Index = pidx;
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].BaseTransform.Translation.Set(piv.Translation.X, piv.Translation.Y, piv.Translation.Z);
        reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].BaseTransform.Rotation.Set(piv.Rotation.Q[0], piv.Rotation.Q[1], piv.Rotation.Q[2], piv.Rotation.Q[3]);
        if (pre30) piv.ParentIdx += 1;
        if (piv.ParentIdx == -1) {
            reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Parent = NULL;
            assert(pidx == 0);
        } else {
            reinterpret_cast<Bfme2HTreePivot *>(Pivot)[pidx].Parent = &reinterpret_cast<Bfme2HTreePivot *>(Pivot)[piv.ParentIdx];
        }
    }
    reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].Transform = Bfme2HTreeTransform(true);
    reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].IsVisible = true;
    reinterpret_cast<Bfme2HTreePivot *>(Pivot)[0].PivotFade = 1.0f;
    return true;
}
