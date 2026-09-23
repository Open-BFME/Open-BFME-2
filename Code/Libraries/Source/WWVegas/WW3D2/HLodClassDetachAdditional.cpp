// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Target HLodClass primary-vtable slot 41 at RVA 0x0019CEA0 (168 bytes).
// The target public method name is unresolved. The BFME1 donor is
// HLodClass::_bfme_ro_v40 in
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/HLodClass_BFME_Detach_Additional.cpp;
// its detach/release behavior and target-adjusted ABI view reproduce retail.
// Accessed offsets and virtual slots are target-backed; unused fields retain donor order.

class SceneClass;

class RenderObjClass
{
public:
	virtual void Delete_This(); // table slot 0
#define RENDER_SLOT(n) virtual void slot##n();
	RENDER_SLOT(001) RENDER_SLOT(002) RENDER_SLOT(003) RENDER_SLOT(004)
	RENDER_SLOT(005) RENDER_SLOT(006) RENDER_SLOT(007) RENDER_SLOT(008)
	RENDER_SLOT(009) RENDER_SLOT(010) RENDER_SLOT(011) RENDER_SLOT(012)
	RENDER_SLOT(013) RENDER_SLOT(014) RENDER_SLOT(015) RENDER_SLOT(016)
	RENDER_SLOT(017) RENDER_SLOT(018)
	virtual void Set_Container(void *container); // slot 19
	RENDER_SLOT(020) RENDER_SLOT(021) RENDER_SLOT(022) RENDER_SLOT(023)
	RENDER_SLOT(024) RENDER_SLOT(025)
	virtual void Notify_Added(SceneClass *scene); // target slot 26
	virtual void Notify_Removed(SceneClass *scene); // target slot 27
#undef RENDER_SLOT

	int m_refs; // target refcount word at +4
	void Release_Ref(void)
	{
		if (--m_refs == 0) Delete_This();
	}
};

// Opaque inherited virtuals retain target primary-table indices. Names are
// placeholders except where a target-verified call in this body needs a method.
class BfmeRenderObjSlots : public RenderObjClass
{
public:
#define RENDER_SLOT(n) virtual void slot##n();
	RENDER_SLOT(028) RENDER_SLOT(029) RENDER_SLOT(030) RENDER_SLOT(031)
	RENDER_SLOT(032) RENDER_SLOT(033) RENDER_SLOT(034) RENDER_SLOT(035)
	RENDER_SLOT(036) RENDER_SLOT(037) RENDER_SLOT(038) RENDER_SLOT(039)
	RENDER_SLOT(040)
	virtual void _bfme_ro_v41(); // target slot 41; donor semantic analogue is _bfme_ro_v40
	RENDER_SLOT(042) RENDER_SLOT(043) RENDER_SLOT(044) RENDER_SLOT(045)
	RENDER_SLOT(046) RENDER_SLOT(047) RENDER_SLOT(048) RENDER_SLOT(049)
	RENDER_SLOT(050) RENDER_SLOT(051) RENDER_SLOT(052) RENDER_SLOT(053)
	RENDER_SLOT(054) RENDER_SLOT(055) RENDER_SLOT(056) RENDER_SLOT(057)
	RENDER_SLOT(058) RENDER_SLOT(059) RENDER_SLOT(060) RENDER_SLOT(061)
	RENDER_SLOT(062) RENDER_SLOT(063) RENDER_SLOT(064) RENDER_SLOT(065)
	RENDER_SLOT(066) RENDER_SLOT(067) RENDER_SLOT(068)
	virtual void Update_Obj_Space_Bounding_Volumes(); // donor name, target slot 69
	RENDER_SLOT(070) RENDER_SLOT(071) RENDER_SLOT(072) RENDER_SLOT(073)
	RENDER_SLOT(074) RENDER_SLOT(075) RENDER_SLOT(076) RENDER_SLOT(077)
	RENDER_SLOT(078) RENDER_SLOT(079) RENDER_SLOT(080) RENDER_SLOT(081)
	RENDER_SLOT(082) RENDER_SLOT(083) RENDER_SLOT(084) RENDER_SLOT(085)
	RENDER_SLOT(086) RENDER_SLOT(087) RENDER_SLOT(088) RENDER_SLOT(089)
	RENDER_SLOT(090) RENDER_SLOT(091) RENDER_SLOT(092) RENDER_SLOT(093)
	RENDER_SLOT(094) RENDER_SLOT(095) RENDER_SLOT(096) RENDER_SLOT(097)
	RENDER_SLOT(098) RENDER_SLOT(099) RENDER_SLOT(100) RENDER_SLOT(101)
	RENDER_SLOT(102) RENDER_SLOT(103) RENDER_SLOT(104) RENDER_SLOT(105)
	RENDER_SLOT(106) RENDER_SLOT(107) RENDER_SLOT(108) RENDER_SLOT(109)
	RENDER_SLOT(110) RENDER_SLOT(111) RENDER_SLOT(112) RENDER_SLOT(113)
	RENDER_SLOT(114) RENDER_SLOT(115) RENDER_SLOT(116) RENDER_SLOT(117)
	RENDER_SLOT(118) RENDER_SLOT(119) RENDER_SLOT(120) RENDER_SLOT(121)
	RENDER_SLOT(122)
	virtual bool Is_In_Scene(); // target slot 123
	RENDER_SLOT(124) RENDER_SLOT(125) RENDER_SLOT(126) RENDER_SLOT(127)
	virtual void Update_Sub_Object_Bits(); // target slot 128
#undef RENDER_SLOT
};

struct BfmeModelNode
{
	RenderObjClass *Model;
	int BoneIndex;
	char Offset[12];
};

// Target DynamicVectorClass<ModelNodeClass> subobject begins at +0x138 and count
// at +0x148. The two intervening flags and metric fields retain donor order.
class BfmeModelArray
{
public:
	virtual ~BfmeModelArray();
	virtual bool operator == (const BfmeModelArray &) const;
	virtual bool Resize(int newsize, BfmeModelNode const *array = 0);
	virtual void Clear(void);
	virtual int ID(BfmeModelNode const *ptr);
	virtual int ID(BfmeModelNode const &ptr);

	BfmeModelNode *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	char VectorClassPad[2];
	int ActiveCount;
	int GrowthStep;
	float MaxScreenSize;
	float NonPixelCost;
	float PixelCostPerArea;
	float BenefitFactor;

	int Count(void) const { return ActiveCount; }
	BfmeModelNode &operator [] (int index) { return Vector[index]; }
	void Delete_All(void)
	{
		int len = VectorMax;
		Clear();
		Resize(len);
	}
};

class HLodClass : public BfmeRenderObjSlots
{
public:
	virtual void _bfme_ro_v41();
	virtual void Update_Obj_Space_Bounding_Volumes();
	char RenderObjFields[0x70];
	SceneClass *Scene; // target +0x78
	char HlodFields[0xBC];
	BfmeModelArray AdditionalModels; // target +0x138
};

void HLodClass::_bfme_ro_v41(void)
{
	int additional_count = AdditionalModels.Count();
	if (additional_count == 0) {
		return;
	}

	for (int i = 0; i < AdditionalModels.Count(); i++) {
		RenderObjClass * model = AdditionalModels[i].Model;
		AdditionalModels[i].Model = 0;
		model->Set_Container(0);

		if (Is_In_Scene()) {
			model->Notify_Removed(Scene);
		}

		model->Release_Ref();
	}

	AdditionalModels.Delete_All();
	Update_Sub_Object_Bits();
	Update_Obj_Space_Bounding_Volumes();
}