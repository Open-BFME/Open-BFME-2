// platformsdk
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
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// W3DTerrainVisual::load, native 9213F..92512 (979B), primary BC80A0 slot4.
// ZH W3DTerrainVisual::load is the semantic reference (also BFME1 verified
// pointer23b143233b5a8664a3bdf8572df6d905c310a5a1). Target adds an already-open
// stream and three typed area sets, a stream rewind, water subscription
// rebuild, two timing reads, and a final water-name load. Every direct callee
// uses an existing verified owner. Primary/member offsets agree with the
// independently matched terrain destructor and water-list builders.
// Map flags are observed bit1/bit3; accessors preserve native bool lowering.
// RGBColor and Vector3 are layout-compatible three-float color views; target
// copies each component directly rather than materializing scalar arguments.
// Attenuation setters take doubles, as the original light.h declares.
// The seven StaticNameKey globals have retail zero caches and full matching
// key strings at DBDC3C/44/4C/54/5C and DBDD7C/94, independently inspected.

#include <new>
#include <windows.h>
#include "Lib/Coord3D.h"
#include "Lib/RGBColor.h"
#include "ascii_string.h"
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
class ChunkInputStream
{
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void seek(int);
};
class WorldHeightMap
{
  public:
    WorldHeightMap(ChunkInputStream *);
    virtual void Delete_This();
    int refs;
    char pad[0x120e8 - 8];
    int width, height;
    __declspec(dllimport) __forceinline int getDrawWidth()
    {
        return width;
    }
    __declspec(dllimport) __forceinline int getDrawHeight()
    {
        return height;
    }
};
class RenderObjClass
{
  public:
    virtual void Delete_This();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void Set_Position(const Vector3 &);
    int refs;
    char pad[0xC4 - 8];
};
class LightClass : public RenderObjClass
{
  public:
    enum LightType
    {
        POINT = 0
    };
    LightClass(LightType);
    int type;
    unsigned flags;
    bool isLight() const
    {
        return (flags & 2) != 0;
    }
    bool isScorch() const
    {
        return (flags & 8) != 0;
    }
    bool shadows;
    char padCC[3];
    float intensity;
    Vector3 ambient, diffuse, specular;
    float nearStart, nearEnd, farStart, farEnd, angle, cosangle, exponent;
    Vector3 direction;
    void Set_Ambient(const Vector3 &vec)
    {
        ambient = vec;
    }
    void Set_Diffuse(const Vector3 &vec)
    {
        diffuse = vec;
    }
    void Set_Far_Attenuation_Range(double start, double end)
    {
        farStart = start;
        farEnd = end;
    }
};
enum Scorches
{
    SCORCH_UNKNOWN
};
template <class T> class RefMultiListIterator;
class BaseHeightMapRenderObjClass
{
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void initHeightData(int, int, WorldHeightMap *, RefMultiListIterator<RenderObjClass> *);
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142();
    virtual void slot143();
    virtual void slot144();
    virtual float getHeightMapHeight(float, float, void *);
    void addScorch(Vector3, float, Scorches);
};
#include "../../../Include/W3DDevice/GameClient/RTS3DScene.h"
class W3DDisplay
{
  public:
    static RTS3DScene *m_3DScene;
};
class Rva0006ED29
{
  public:
    void rva0006ED29(void *);
};
class Dict
{
  public:
    float getReal(int, bool * = 0) const;
    int getInt(int, bool * = 0) const;
};
enum NameKeyType
{
    KEY_UNKNOWN
};
class StaticNameKey
{
  public:
    NameKeyType key() const;
    operator NameKeyType() const
    {
        return key();
    }
    int cached;
    const char *name;
};
extern const StaticNameKey TheKey_lightHeightAboveTerrain, TheKey_lightAmbientColor, TheKey_lightDiffuseColor,
    TheKey_lightInnerRadius, TheKey_lightOuterRadius, TheKey_objectRadius, TheKey_scorchType;
class BfmeRetBWF
{
  public:
    float x, y, z;
};
class Rva0030D631
{
  public:
    BfmeRetBWF *rva0030D631();
};
struct TerrainMapObject
{
    void *unused;
    TerrainMapObject *next;
    char pad8[0x24 - 8];
    Dict props;
    char pad25[0x44 - 0x25];
    unsigned flags;
    bool isLight() const
    {
        return (flags & 2) != 0;
    }
    bool isScorch() const
    {
        return (flags & 8) != 0;
    }
    const Coord3D *getLocation()
    {
        return (const Coord3D *)((Rva0030D631 *)this)->rva0030D631();
    }
};
class BfmeMapObjectListHolder
{
  public:
    TerrainMapObject *head;
};
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
class Rva002DAAF2
{
  public:
    bool rva002DAAF2(const AsciiString &, int, int, int, int);
};
class StandingWaveArea;
class RiverArea;
class WaterWaveArea;
template <class T> class AreaSet;
class WaterRenderObjClass
{
  public:
    void rva00083A7A(AreaSet<StandingWaveArea> *, AreaSet<RiverArea> *, AreaSet<WaterWaveArea> *);
    void rva000B3FD0();
};
struct TerrainWaterRenderView
{
    int before;
    RenderObjClass render;
};
extern unsigned char g_00DFE7A8;
class Rva0007E90EHost
{
  public:
    void rva0007E90E(int);
    void loadName(const AsciiString &name)
    {
        rva0007E90E((int)&name);
    }
};
#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
#include "../../../Include/W3DDevice/GameClient/W3DTerrainVisualClass.h"

bool W3DTerrainVisual::load(const AsciiString &filename, ChunkInputStream *stream,
                            AreaSet<StandingWaveArea> *standing, AreaSet<RiverArea> *rivers,
                            AreaSet<WaterWaveArea> *waves)
{
    if (!((Rva002DAAF2 *)this)->rva002DAAF2(filename, (int)stream, (int)standing, (int)rivers, (int)waves))
        return false;
    if (!m_terrainRenderObject)
        return false;
    if (m_logicHeightMap)
    {
        WorldHeightMap *old = m_logicHeightMap;
        if (--old->refs == 0)
            old->Delete_This();
        m_logicHeightMap = 0;
    }
    stream->seek(0);
    m_logicHeightMap = new WorldHeightMap(stream);
    if (m_waterRenderObject)
        m_waterRenderObject->rva00083A7A(standing, rivers, waves);
    TerrainMapObject *node = BfmeTheMapObjectListHolder->head;
    while (node)
    {
        Dict *dict = &node->props;
        if (node->isLight())
        {
            const Coord3D *location = node->getLocation();
            Coord3D loc;
            loc.x = location->x;
            loc.y = location->y;
            loc.z = location->z;
            if (loc.z < 0)
            {
                loc.z = m_terrainRenderObject->getHeightMapHeight(loc.x, loc.y, 0);
                loc.z += dict->getReal(TheKey_lightHeightAboveTerrain);
            }
            LightClass *light = new LightClass(LightClass::POINT);
            RGBColor color;
            color.setFromInt(dict->getInt(TheKey_lightAmbientColor));
            light->Set_Ambient(*reinterpret_cast<const Vector3 *>(&color));
            color.setFromInt(dict->getInt(TheKey_lightDiffuseColor));
            light->Set_Diffuse(*reinterpret_cast<const Vector3 *>(&color));
            light->Set_Position(Vector3(loc.x, loc.y, loc.z));
            light->Set_Far_Attenuation_Range(dict->getReal(TheKey_lightInnerRadius),
                                             dict->getReal(TheKey_lightOuterRadius));
            W3DDisplay::m_3DScene->Add_Render_Object(light);
            if (--light->refs == 0)
                light->Delete_This();
        }
        node = node->next;
    }
    RefMultiListIterator<RenderObjClass> *it = W3DDisplay::m_3DScene->createLightsIterator();
    m_terrainRenderObject->initHeightData(m_logicHeightMap->getDrawWidth(),
        m_logicHeightMap->getDrawHeight(), m_logicHeightMap, it);
    if (it)
        ((Rva0006ED29 *)W3DDisplay::m_3DScene)->rva0006ED29(it);
    timeGetTime();
    timeGetTime();
    W3DDisplay::m_3DScene->Add_Render_Object((RenderObjClass *)m_terrainRenderObject);
    if (m_waterRenderObject && !g_00DFE7A8)
    {
        W3DDisplay::m_3DScene->Add_Render_Object(&((TerrainWaterRenderView *)m_waterRenderObject)->render);
        m_waterRenderObject->rva000B3FD0();
    }
    node = BfmeTheMapObjectListHolder->head;
    while (node)
    {
        Dict *dict = &node->props;
        if (node->isScorch())
        {
            const Coord3D *pos = node->getLocation();
            Vector3 loc(pos->x, pos->y, pos->z);
            float radius = dict->getReal(TheKey_objectRadius);
            Scorches type = (Scorches)dict->getInt(TheKey_scorchType);
            m_terrainRenderObject->addScorch(loc, radius, type);
        }
        node = node->next;
    }
    if (m_waterRenderObject && TheTerrainLogic)
    {
        ((Rva0007E90EHost *)m_waterRenderObject)->loadName(TheTerrainLogic->getSourceFilename());
    }
    return true;
}
