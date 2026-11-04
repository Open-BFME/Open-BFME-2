// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// stlport
// W3DScriptedModelDrawModuleData::parseAttachModel, retail 0x000C8748 (378B).
// Reference repair from Open-BFME/Open-BFME-1
// 34f59164f6d1efd413c5fd37f4894ec834c3c0fe:
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0077C390Parse.cpp.
// Target C8748/378 and WB926F20 establish parseAttachModel identity, full
// literals, eight-byte weighted model entries, masks +1C/+68 and owner+8.
// Existing record ctor C0D7A, dtor C0DA3, INIException and vector C8633
// names are preserved as provider ABI views, without new aliases or pins.
// All bytes except unresolved REL32 B62D4 match; the companion157B helper
// is banked at reverse/attempts/0x000b62d4.cpp. Proper Code destination:
// Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DScriptedModelDraw.cpp.
// The native FieldParse at VA BCA790 (Bone->INI::parseAsciiString offset0;
// Offset->INI::parseCoord3D offset4; Model->C3D00 offset0; null terminator)
// is defined below.
// Pass actual providers/consumers, full bytes, EH, strings and normal linking.
#include "ascii_string.h"
#include "../../../../../GameEngine/Include/Common/INI/FieldParse.h"
typedef int Int;
struct WeightedModel { AsciiString name; Int probability; };
struct WeightedModels { WeightedModel *m_start, *m_finish, *m_end; };
#include "../../../../../GameEngine/Include/Common/WeaponTemplateSetHead.h"
class BfmeStringTailRecord180 {
public:
    AsciiString bone;
    struct Offset { float x,y,z; } offset;
    WeightedModels models;
    WeaponTemplateSetHead all, positive;
    BfmeStringTailRecord180();
    ~BfmeStringTailRecord180();
};
struct BfmePod180;
namespace _STL {
template<class T> class allocator;
template<class T, class A=allocator<T> > class vector { public: void push_back(const T &); };
}
struct FieldParse;
extern const FieldParse AttachModelFieldParse[];
#include "../../../../../GameEngine/Include/Common/INI/INI.h"
void parseModelConditionFlags(INI *, WeaponTemplateSetHead *, WeaponTemplateSetHead *);
class W3DScriptedModelDrawModuleData {
public:
	static void parseAttachModel(INI *,void *,void *,const void *);
	struct AttachModelStruct { static void parseModel(INI *, void *, void *, const void *); };
};

// Zero Hour's FieldParse record (INI.h).

// Retail's table at VA 0x00BCA790 (RVA 0x007CA790): Bone and Offset fill the
// record's AsciiString (+0) and Coord3D (+4); Model goes to the rowed
// AttachModelStruct::parseModel 0x000C3D00; null terminator.
extern const FieldParse AttachModelFieldParse[] =
{
	{ "Bone", INI::parseAsciiString, 0, 0 },
	{ "Offset", INI::parseCoord3D, 0, 4 },
	{ "Model", W3DScriptedModelDrawModuleData::AttachModelStruct::parseModel, 0, 0 },
	{ 0, 0, 0, 0 }
};

void W3DScriptedModelDrawModuleData::parseAttachModel(INI *ini, void *instance, void *, const void *)
{
	if (instance == 0)
		return;

	BfmeStringTailRecord180 info;
	info.offset.x = 0;
	info.offset.y = 0;
	info.offset.z = 0;
	parseModelConditionFlags(ini, &info.all, &info.positive);
	ini->initFromINI(&info, AttachModelFieldParse);

	if (info.bone.isEmpty())
		throw INIException(3,
			"*** ASSET ERROR: you must specify then bone name");

	WeightedModel *first = info.models.m_start;
	if (first == info.models.m_finish)
		throw INIException(3,
			"*** ASSET ERROR: you must specify at least one model name");
	Int totalProbability = 0;
	Int unassignedCount = 0;
	for (WeightedModel *model = first; model != info.models.m_finish; ++model)
	{
		if (model->probability <= 0)
			++unassignedCount;
		else
			totalProbability += model->probability;
	}

	if (totalProbability > 100)
		throw INIException(3,
			"*** ASSET ERROR: combined probability may not be higher than 100 (it's %i)",
			totalProbability);

	if (totalProbability + unassignedCount > 100)
		throw INIException(3,
			"*** ASSET ERROR: can't auto-assign probabilities, specified probabilities must be %i or less",
			100 - unassignedCount);

	if (unassignedCount != 0)
	{
		Int remainder = 100 - totalProbability;
		Int share = remainder / unassignedCount;
		for (WeightedModel *model = first; model != info.models.m_finish; ++model)
		{
			if (model->probability <= 0)
			{
				--unassignedCount;
				if (unassignedCount == 0)
					model->probability = remainder;
				else
				{
					model->probability = share;
					remainder -= share;
				}
				totalProbability += model->probability;
			}
		}
	}

	if (totalProbability > 100)
		throw INIException(3,
			"*** ASSET ERROR: combined probability must be 100 (it's %i)",
			totalProbability);

	((_STL::vector<BfmePod180> *)((char *)instance + 8))->push_back(*(const BfmePod180 *)&info);
}
