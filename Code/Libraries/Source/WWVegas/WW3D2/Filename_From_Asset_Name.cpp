// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib
// Extracted from the BFME1 WW3D2 rendobj.cpp reference unit.  This keeps the
// reference helper body isolated while the surrounding RenderObj implementation
// remains queued behind its larger header dependency graph.
#include "winbase_shim.h"
#include "wwstring.h"
#include <string.h>

StringClass
Filename_From_Asset_Name (const char *asset_name)
{
    StringClass filename;
    if (asset_name != NULL) {
        ::lstrcpy (filename.Get_Buffer (::lstrlen (asset_name) + 5), asset_name);
        char *suffix = ::strchr (filename, '.');
        if (suffix != NULL) {
            suffix[0] = 0;
        }
        filename += ".w3d";
    }
    return filename;
}
