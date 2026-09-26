// ??1ImageCollection@@MAE@XZ
// partial score=0.93 date=2026-09-26
// cl: /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <map>
class AsciiString { void *m_data; };
class NameKeyGenerator { public: int Rva002D91AF(const AsciiString &n); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Image { public: virtual ~Image(); };
typedef _STL::map<unsigned int, Image *> ImageNameMap;
class SubsystemInterface {
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
private:
	unsigned char m_bfmeBasePad[8];
};
class ImageCollection : public SubsystemInterface {
public:
	~ImageCollection();
private:
	ImageNameMap m_imageMap;
};
ImageCollection::~ImageCollection(void)
{
  for (ImageNameMap::iterator i=m_imageMap.begin();i!=m_imageMap.end();++i)
  {
    Image *img = i->second;
    if (img)
      img->~Image();
    ::operator delete(img);
  }
}
