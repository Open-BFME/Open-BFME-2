// cl: /Os /MD /GX
// WorldBuilder 0x01157BB0 names MapPreviewTextureAssetFactory::PreLoad
// and asserts m_impl == NULL at MapPreviewTextureAsset.cpp:51. Retail's
// complete body is 0x002DB8BF..0x002DB93E. Its allocation and descriptor
// stores share the established TextureAsset::Factory::PreLoad pattern.
// Retail constructor 0x002DB882 installs vftable 0x00803E48; PreLoad is
// its slot 1 at 0x00803E4C, after the deleting-destructor entry.
// All offsets below are read from that retail body. The File byte at +0x0D
// is delete-on-close, consistent with the reference Common/File.h accessor.

typedef unsigned int size_t;
void *__cdecl operator new(size_t);

class File;
class FileSystem
{
public:
    File *openFile(const char *filename, int access, int bufferSize);
};
extern FileSystem *TheFileSystem;

struct MapPreviewFileFlags
{
    char m_pad00[0x0D];
    bool m_deleteOnClose;
};

class Rva0013107A
{
public:
    virtual ~Rva0013107A();
    Rva0013107A();
    char m_pad04[0x0C];
    File *m_file10;
    char m_pad14[0x30];
    int m_44;
    int m_48;
    int m_4C;
    char m_pad50[0x08];
};

class MapPreviewTextureAssetFactory
{
public:
    virtual ~MapPreviewTextureAssetFactory();
    virtual void PreLoad();
private:
    char m_pad04[0x10];
    Rva0013107A *m_impl;
    const char *m_name18;
    char m_pad1C[0x14];
    int m_30;
    int m_34;
    int m_38;
};

void MapPreviewTextureAssetFactory::PreLoad()
{
    m_impl = new Rva0013107A;
    m_impl->m_44 = m_30;
    m_impl->m_4C = m_34;
    m_impl->m_48 = m_38;
    const char *filename = m_name18;
    FileSystem *filesystem = TheFileSystem;
    m_impl->m_file10 = filesystem->openFile(filename, 0x41, 0);
    if (m_impl->m_file10)
        reinterpret_cast<MapPreviewFileFlags *>(m_impl->m_file10)->m_deleteOnClose = true;
}
