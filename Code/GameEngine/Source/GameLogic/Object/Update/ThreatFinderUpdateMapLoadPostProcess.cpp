// cl: /DNDEBUG /MD /EHsc
// ThreatFinderUpdate::mapLoadPostProcess at 0x003ECE33..0x003ECED5 (162B),
// named by WB 0x01028A50's identical constructor/register/property sequence.
// The ctor-installed +0x0C interface passes this: owner at -4, data at -8,
// heap at +0x14. Its radius is +0x560; default module radius is +8.
// Retail's lazy key object VA 0x00DBDE1C has key zero and the name pointer
// VA 0x00C0953C, the literal "objectThreatFinderRadius". This establishes the
// extern key's purpose; its descriptive name does not assert a donor spelling.
template <class T> class StringBase
{
public:
 StringBase(const StringBase &other);
private:
 void *m_data;
};
struct OwnerWithName
{
 unsigned char m_pad000[0x88];
 StringBase<char> m_name;
};
class Rva003ECDB7Object
{
public:
 void registerName();
};
class Rva003ECD60Object : public Rva003ECDB7Object
{
public:
 Rva003ECD60Object(const StringBase<char> &name, bool flag);
 unsigned char m_pad000[0x560];
 float m_radius;
 unsigned char m_pad564[8];
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Rva00148F5ECache
{
public:
 NameKeyType get();
private:
 NameKeyType m_key;
 const char *m_name;
};
extern Rva00148F5ECache g_objectThreatFinderRadiusKey;
class Dict
{
public:
 float getReal(int key, bool *exists) const;
};
struct ModuleData
{
 unsigned char m_pad000[8];
 float m_radius;
};
class Rva003ECE33Primary
{
public:
 virtual void primaryAnchor() = 0;
protected:
 const ModuleData *m_data;
 OwnerWithName *m_owner;
};
class Rva003ECE33MapLoad
{
public:
 virtual void mapLoadPostProcess(const Dict *properties) = 0;
};
class Rva003ECE33Secondary
{
public:
 virtual void secondaryAnchor() = 0;
private:
 unsigned char m_pad14[0x20 - 0x14];
};
class ThreatFinderUpdate : public Rva003ECE33Primary,
 public Rva003ECE33MapLoad, public Rva003ECE33Secondary
{
public:
 virtual void mapLoadPostProcess(const Dict *properties);
private:
 Rva003ECD60Object *m_heap;
};
void ThreatFinderUpdate::mapLoadPostProcess(const Dict *properties)
{
 if (properties)
 {
  Rva003ECD60Object *finder = new Rva003ECD60Object(m_owner->m_name, false);
  m_heap = finder;
  finder->registerName();
  bool exists = false;
  float radius = properties->getReal(g_objectThreatFinderRadiusKey.get(), &exists);
  if (exists)
   m_heap->m_radius = radius;
  else
   m_heap->m_radius = m_data->m_radius;
 }
}
