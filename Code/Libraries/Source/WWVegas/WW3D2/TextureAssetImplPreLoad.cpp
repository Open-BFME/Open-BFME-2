// cl: /O1 /MD /EHsc /DNDEBUG
#include <cstring>

#include "../../../../GameEngine/Include/Common/File.h"

File *GetGameFile(const char *);

namespace TextureAsset {
class Impl {
public:
    char m_pad10[0x10];
    File *m_file;
    char m_pad1c[0x08];
    File *m_fileAlpha;
    void PreLoad(const char *name);
};
}

void TextureAsset::Impl::PreLoad(const char *name)
{
    char buffer[0x104];
    std::strcpy(buffer, name);
    char *dot = std::strrchr(buffer, '.');
    if (dot) {
        std::strcpy(dot, ".dds");
        m_file = GetGameFile(buffer);
        if (!m_file) {
            std::strcpy(dot, ".tga");
            m_file = GetGameFile(buffer);
            if (!m_file) {
                std::strcpy(dot, ".jpg");
                m_file = GetGameFile(buffer);
                if (m_file) {
                    std::strcpy(dot, ".png");
                    m_fileAlpha = GetGameFile(buffer);
                }
            }
        }
    }
    if (m_file)
        m_file->deleteOnClose();
    if (m_fileAlpha)
        m_fileAlpha->deleteOnClose();
}
