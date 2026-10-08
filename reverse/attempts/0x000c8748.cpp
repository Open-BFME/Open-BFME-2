// ?parseAttachModel@W3DScriptedModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// stlport
// Banked reference repair, not a matched row. Donor Open-BFME/Open-BFME-1
// 34f59164f6d1efd413c5fd37f4894ec834c3c0fe:
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0077C390Parse.cpp.
// Target C8748/378 and WB926F20 establish parseAttachModel identity, full
// literals, eight-byte weighted model entries, masks +1C/+68 and owner+8.
// Existing record ctor C0D7A, dtor C0DA3, INIException and vector C8633
// names are preserved as provider ABI views, without new aliases or pins.
// All bytes except unresolved REL32 B62D4 match; the companion157B helper
// is banked at reverse/attempts/0x000b62d4.cpp. Proper Code destination:
// Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DScriptedModelDraw.cpp.
// Before landing: recover B3FA5/43, C3D00/218 model callback; define the
// native FieldParse at VA BCA790 (Bone->INI::parseAsciiString offset0;
// Offset->INI::parseCoord3D offset4; Model->C3D00 offset0; null terminator).
// Pass actual providers/consumers, full bytes, EH, strings and normal linking.
#include "ascii_string.h"
#include "Common/INIException.h"
typedef int Int;
struct WeightedModel { AsciiString name; Int probability; };
struct WeightedModels { WeightedModel *m_start, *m_finish, *m_end; };
class WeaponTemplateSetHead { public: unsigned words[19]; void rva000B3FA5(int, int); };
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
class INI { public: void initFromINI(void *,const FieldParse *); };
void parseModelConditionFlags(INI *, WeaponTemplateSetHead *, WeaponTemplateSetHead *);
class W3DScriptedModelDrawModuleData { public: static void parseAttachModel(INI *,void *,void *,const void *); };

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
