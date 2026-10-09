// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native00412111..004121B2 RET0 is the complete161B callback: the next
// independent31B constructor starts004121B2. The recovered registry4121D1
// binds this address under ColorPicker; the existing88B factory419F3 creates
// the identified80B ColorPicker and the owned getter411112 looks it up.
// The shared draw interface is the virtual slot2 used by the adjacent94B
// View3D callback. The native truncations and four caller arguments prove
// the ABI; the callback's original free-function name remains unknown.
// Reference neighbour4120B3 supplies the registration/draw pattern; the
// ColorPicker-specific key and level/factory behavior are target facts.
// The factory keeps its existing erased level/parameters word ABI;
// these casts preserve the native32-bit representations.
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "ascii_string.h"

const char *bfmePathLeafAfterMarker(const char *path);
void *Rva004110DCGet(const char *key);
void *Rva004118B4(const char *path, const char *parameters);
void Rva004107CDParse(void *asset, const char *parameters);
class Rva004120B3Asset
{
public:
    virtual ~Rva004120B3Asset();
    virtual void slot01();
    virtual void draw(int x, int y, int width, int height);
};


bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
void *Rva00411112Get(const AsciiString*);
void *Rva004119F3Get(void*,const AsciiString*,int);
namespace AptUtils {int LevelIndexFromTarget(const char*);}
void Rva00412111(const Coord2D*origin,const Coord2D*size,const char*path,const char*params) {
 AsciiString name;
 if(!Rva004128F0GetParam(params,"_componentId",name))return;
 Rva004120B3Asset *asset=(Rva004120B3Asset*)Rva00411112Get(&name);
 if(!asset)asset=(Rva004120B3Asset*)Rva004119F3Get(reinterpret_cast<void*>(AptUtils::LevelIndexFromTarget(path)),&name,reinterpret_cast<int>(params));
 if(!asset)return;
 asset->draw((int)origin->x,(int)origin->y,(int)size->x,(int)size->y);
}
