// cl: /MD /Oy-
// Native Ghidra 004120B3..00412111 RET. Resolve the path leaf in the
// existing Apt registry, create the missing entry using 004118B4, parse
// its parameters, then pass four integer-truncated coordinates to slot 8.
// The registry and parser are rowed providers. The concrete asset class
// and the original callback name remain unknown.
#include "../../../../Libraries/Include/Lib/Coord2D.h"

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

void Rva004120B3(const Coord2D *origin, const Coord2D *size,
                 const char *path, const char *parameters)
{
    Rva004120B3Asset *asset = static_cast<Rva004120B3Asset *>(
        Rva004110DCGet(bfmePathLeafAfterMarker(path)));
    if (!asset)
        asset = static_cast<Rva004120B3Asset *>(Rva004118B4(path, parameters));
    if (asset)
    {
        Rva004107CDParse(asset, parameters);
        asset->draw((int)origin->x, (int)origin->y, (int)size->x, (int)size->y);
    }
}
