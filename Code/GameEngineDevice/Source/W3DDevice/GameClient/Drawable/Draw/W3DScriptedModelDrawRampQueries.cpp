// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// The byte-proven constructor C0DD8 installs primary table7CA090 and
// constructs a string at260 followed by two strings at264. Slots54/55
// point to B5FBE/B5FD5. This is the primary object, without an adjustment.
// WB948160 names SetRampMeshOverload and indexes the264 array. Its old
// vtable pairing to B5FD5 contradicts RET8 versus RET0: nativeB5FBE is
// the indexed setter. The query's original name and return spelling stay
// unknown; retain an address name and the observed full EAX integer ABI.
#include "ascii_string.h"
template<> void StringBase<char>::set(const char *);
template<> bool StringBase<char>::isEmpty() const;

class BridgeInfo;
class PolygonTrigger;
class RenderObjClass;

class W3DScriptedModelDraw
{
public:
#define SLOT(N) virtual void slot##N();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
 SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
 SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53)
#undef SLOT
 virtual void SetRampMeshOverload(const char *name, int index);
 virtual int rva000B5FD5();
 bool getRamp(BridgeInfo *, AsciiString, PolygonTrigger **, RenderObjClass **, bool);
private:
 char unknown04[0x260 - 4];
 StringBase<char> string260;
 StringBase<char> rampNames[2];
};

void W3DScriptedModelDraw::SetRampMeshOverload(const char *name, int index)
{
 rampNames[index].set(name);
}

int W3DScriptedModelDraw::rva000B5FD5()
{
 return !string260.isEmpty();
}

// NativeBBFD6..BC057 RET16. Secondary-table7CC588 slot43 is shared by
// ScriptedModelDraw/Truck/Tank interfaces; this is complete-object+0C.
// The recovered getRamp B9EC2 proves the forwarded pointer/output/flag ABI.
// ConstructorC0DD8 proves the override string at complete-object268. The
// fallback module-data string at118 is observed here; its original name
// and this callback's original name remain unresolved.
struct Rva000BBFD6ModuleDataView
{
 char unknown00[0x118];
 AsciiString string118;
};

class Rva000BBFD6DrawInterface
{
public:
 bool rva000BBFD6(BridgeInfo *, PolygonTrigger **, RenderObjClass **, bool);
private:
 char unknown00[0x25C];
 AsciiString string25C;
};

bool Rva000BBFD6DrawInterface::rva000BBFD6(BridgeInfo *info,
 PolygonTrigger **polygon, RenderObjClass **mesh, bool useObjectTransform)
{
 AsciiString name;
 if (!string25C.isEmpty())
  name = string25C;
 else
  name = (*reinterpret_cast<const Rva000BBFD6ModuleDataView *const *>(reinterpret_cast<const char *>(this) - 8))->string118;
 return reinterpret_cast<W3DScriptedModelDraw *>(reinterpret_cast<char *>(this) - 0xC)
  ->getRamp(info, name, polygon, mesh, useObjectTransform);
}
