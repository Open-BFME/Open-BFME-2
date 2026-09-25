// cl: /DNDEBUG /MD /EHsc /O1 /Ob2

// GpuDrawModuleTemplate copy constructor.
//
// Retail 0x003A9EC7 (92B) copies the category base through the rowed
// CategoryModuleTemplate copy at 0x0004CB7B (the <6> spelling emits the
// $05 name rowed there), then the GpuDrawModuleInfo subobject at +8
// through the rowed info copy at 0x003A9D73 with the usual
// null-preserving source adjustment, then the sub vtable 0x00C1C208 and
// the template vtables 0x00C1C1F8/0x00C1C780 (gate-filled). Shape follows
// the landed RenderObjectDrawModuleTemplate copy 0x003A9C80 in this
// folder; the base model mirrors GpuDrawModuleTemplateCtorThunk.cpp and
// the info members mirror GpuDrawModuleInfoCopyCtor.cpp.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that)
		: StringBase<char>(that)
	{
	}
	~AsciiString();
};

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
	ModuleTemplate() {}
	virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
	CategoryModuleInfo() {}
	virtual ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplate : public ModuleTemplate,
	public CategoryModuleInfo<Category>
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
	virtual ~CategoryModuleTemplate() {}
};

class GpuDrawModuleInfo
{
public:
	GpuDrawModuleInfo(const GpuDrawModuleInfo &that);
	virtual ~GpuDrawModuleInfo();

private:
	int m_totalFrames;
	int m_framesPerRow;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

class GpuDrawModuleTemplate : public CategoryModuleTemplate<6>,
	public GpuDrawModuleInfo
{
public:
	GpuDrawModuleTemplate(const GpuDrawModuleTemplate &that);
	virtual ~GpuDrawModuleTemplate();
};

// ??0GpuDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z @0x3A9EC7
GpuDrawModuleTemplate::GpuDrawModuleTemplate(const GpuDrawModuleTemplate &that)
	: CategoryModuleTemplate<6>(that),
	  GpuDrawModuleInfo(that)
{
}

}
