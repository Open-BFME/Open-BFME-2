// cl: /O1
// ?Rva003E4E6AGet@@YG_NPAVParameter@@@Z @0x003E4E6A 59B leaf single-param unit-mesh check via rowed ScriptEngine::getUnitNamed and rowed MeshGeometryClass::get_polys. Evidence: caller 0x003EBEA1; prev 0x003E4C77 next 0x003E4EA5 same // cl: /O1.
class Parameter;
class Vector3i16;
class MeshGeometryClass
{
protected:
    Vector3i16 *get_polys();
public:
    char m_pad00[0x24];
    int m_24;
    friend bool __stdcall Rva003E4E6AGet(Parameter *);
};
class Object
{
public:
    char m_pad00[0x264];
    MeshGeometryClass *m_mesh264;
};
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *);
};
extern class ScriptEngine *TheScriptEngine;
bool __stdcall Rva003E4E6AGet(Parameter *p)
{
    if (p) {
        Object *obj = TheScriptEngine->getUnitNamed(p);
        if (obj) {
            MeshGeometryClass *mesh = obj->m_mesh264;
            if (mesh) {
                int n = mesh->m_24;
                Vector3i16 *polys = mesh->get_polys();
                if (n > (int)polys)
                    return true;
            }
        }
    }
    return false;
}
