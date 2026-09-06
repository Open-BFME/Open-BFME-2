// cl: /O1 /arch:SSE2 /DNDEBUG /MD /EHsc
// BFME 2 map-picture loader at RVA 0x0057CDC3, 328 bytes.
// The bfme names describe recovered behavior, not original source spellings.
// Caller 0x0057D10F passes MapMetaData+0x50, owns the returned Image at
// preview+0x5C (flag +0x60), and selects MissingMap when it is unavailable.
// The full body ends at 0x0057CF0B; the inventory stops after its EH prologue.

class AsciiString;
template <typename T> class StringBase
{
    friend class AsciiString;
public:
    void removeLastChar();
    void concat(const T *text);
    void set(const StringBase<T> &other);
private:
    StringBase(const StringBase<T> &other);
    ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    struct Header
    {
        int refCount;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };
    Header *m_data;
};
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    void removeLastChar() { StringBase<char>::removeLastChar(); }
    void concat(const char *text) { StringBase<char>::concat(text); }
    AsciiString &operator=(const AsciiString &other) { StringBase<char>::set(other); return *this; }
    const char *str() const { return m_data ? m_data->text : ""; }
};

typedef unsigned int size_t;
void *__cdecl operator new(size_t);
void __cdecl operator delete(void *);

class GlobalData;
extern GlobalData *TheWritableGlobalData;
class FileSystem
{
public:
    bool doesFileExist(const char *) const;
};
extern FileSystem *TheFileSystem;

class TextureBaseClass
{
public:
    void Release_Ref();
};
// One owning pointer. Image+0x2C points to a separately allocated holder.
class BfmeMapPictureTexture
{
public:
    BfmeMapPictureTexture(const char *filename);
    ~BfmeMapPictureTexture() { if (m_texture) m_texture->Release_Ref(); }
private:
    TextureBaseClass *m_texture;
};
struct Coord2D { float x, y; };
struct Region2D { Coord2D lo, hi; };
class Image
{
public:
    Image();
    virtual ~Image();
    void bfmeSetName(const AsciiString &name) { m_name = name; }
    void bfmeSetFilename(const AsciiString &name) { m_filename = name; }
    void bfmeSetTexture(const BfmeMapPictureTexture &texture);
    unsigned int setStatus(unsigned int bit);
    void setUV(Region2D *uv) { if (uv) m_uv = *uv; }
    void setTextureHeight(int height) { m_textureHeight = height; }
    void setTextureWidth(int width) { m_textureWidth = width; }
private:
    AsciiString m_name;
    AsciiString m_filename;
    int m_textureWidth;
    int m_textureHeight;
    Region2D m_uv;
    int m_imageWidth;
    int m_imageHeight;
    BfmeMapPictureTexture *m_texture;
    unsigned int m_status;
};

Image *bfmeCreateMapPictureImage(const AsciiString &mapName)
{
    if (!TheWritableGlobalData)
        return 0;
    AsciiString pictureName = mapName;
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.removeLastChar();
    pictureName.concat("_pic.tga");

    Image *image = 0;
    if (TheFileSystem->doesFileExist(pictureName.str()))
    {
        image = new Image;
        image->bfmeSetName(pictureName);
        image->bfmeSetFilename(pictureName);
        image->bfmeSetTexture(BfmeMapPictureTexture(pictureName.str()));
        image->setStatus(2);
        Region2D uv;
        uv.hi.x = 1.0f;
        uv.hi.y = 1.0f;
        uv.lo.x = 0.0f;
        uv.lo.y = 0.0f;
        image->setUV(&uv);
        image->setTextureHeight(128);
        image->setTextureWidth(128);
    }
    return image;
}
