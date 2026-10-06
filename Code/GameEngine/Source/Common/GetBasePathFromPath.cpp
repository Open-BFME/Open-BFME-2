// cl: /MD
// ?GetBasePathFromPath@@YA?AVAsciiString@@V1@@Z @0x0044C872 (194B):
// GetBasePathFromPath, BFME1 donor FileTransfer_GetBasePathFromPath.cpp
// (reverseFind '\\' then prefix copy via getBufferForRead plus memcpy,
// empty returns AsciiString::TheEmptyString at 0x9E0878). Callers at
// 0x44CAFE 0x44CBE2 0x44CCC6 0x44CD7D 0x44CE1C 0x44CEBB 0x44CF5A 0x44CFF9.
class AsciiString;
AsciiString GetBasePathFromPath(AsciiString path);
class AsciiString;
AsciiString GetINIFromMap(AsciiString path);
class AsciiString;
AsciiString GetStrFileFromMap(AsciiString path);
class AsciiString;
AsciiString GetSoloINIFromMap(AsciiString path);
class AsciiString;
AsciiString GetAssetUsageFromMap(AsciiString path);
class AsciiString;
AsciiString GetReadmeFromMap(AsciiString path);
class AsciiString;
AsciiString GetFileFromPath(AsciiString path);
class AsciiString;
AsciiString GetBaseFileFromFile(AsciiString fname);
class AsciiString;
AsciiString GetPreviewFromMap(AsciiString path);
class AsciiString;
AsciiString GetArtPreviewFromMap(AsciiString path);
class AsciiString;
AsciiString GetPicPreviewFromMap(AsciiString path);
class AsciiString;
AsciiString GetExtensionFromFile(AsciiString fname);

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend AsciiString GetBasePathFromPath(AsciiString path);

	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &other);
	StringBase(const T *str);
	~StringBase() { releaseBuffer(); }

public:
	const T *reverseFind(T c) const;
	T *getBufferForRead(int length);
	const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }

private:
	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	const char *str() const { return StringBase<char>::str(); }
	const char *reverseFind(char match) const;
	char *getBufferForRead(int length) { return StringBase<char>::getBufferForRead(length); }
	void __cdecl format(const char *format, ...);

	static const AsciiString TheEmptyString;
	friend AsciiString GetBasePathFromPath(AsciiString path);
};

AsciiString GetBasePathFromPath(AsciiString path)
{
	const char *separator = ((const StringBase<char> &)path).reverseFind('\\');
	if (separator) {
		int prefixLength = (int)(separator - path.str());
		AsciiString base;
		char *buffer = base.getBufferForRead(prefixLength);
		memcpy(buffer, path.str(), prefixLength);
		buffer[prefixLength] = 0;
		return buffer;
	}
	return AsciiString::TheEmptyString;
}

AsciiString GetINIFromMap(AsciiString path)
{
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\map.ini", base.str());
	return out;
}

AsciiString GetStrFileFromMap(AsciiString path)
{
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\map.str", base.str());
	return out;
}

AsciiString GetSoloINIFromMap(AsciiString path)
{
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\solo.ini", base.str());
	return out;
}

AsciiString GetAssetUsageFromMap(AsciiString path)
{
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\assetusage.txt", base.str());
	return out;
}

AsciiString GetReadmeFromMap(AsciiString path)
{
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\readme.txt", base.str());
	return out;
}

AsciiString GetFileFromPath(AsciiString path)
{
	const char *separator = ((const StringBase<char> &)path).reverseFind('\\');
	if (separator) {
		return separator + 1;
	}
	return path;
}

AsciiString GetBaseFileFromFile(AsciiString fname)
{
	const char *separator = ((const StringBase<char> &)fname).reverseFind('.');
	if (separator) {
		int prefixLength = (int)(separator - fname.str());
		AsciiString base;
		char *buffer = base.getBufferForRead(prefixLength);
		memcpy(buffer, fname.str(), prefixLength);
		buffer[prefixLength] = 0;
		return buffer;
	}
	return AsciiString::TheEmptyString;
}

AsciiString GetPreviewFromMap(AsciiString path)
{
	AsciiString fname = GetBaseFileFromFile(GetFileFromPath(path));
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\%s.tga", base.str(), fname.str());
	return out;
}

AsciiString GetArtPreviewFromMap(AsciiString path)
{
	AsciiString fname = GetBaseFileFromFile(GetFileFromPath(path));
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\%s_art.tga", base.str(), fname.str());
	return out;
}

AsciiString GetPicPreviewFromMap(AsciiString path)
{
	AsciiString fname = GetBaseFileFromFile(GetFileFromPath(path));
	AsciiString base = GetBasePathFromPath(path);
	AsciiString out;
	out.format("%s\\%s_pic.tga", base.str(), fname.str());
	return out;
}

AsciiString GetExtensionFromFile(AsciiString fname)
{
	const char *separator = ((const StringBase<char> &)fname).reverseFind('.');
	if (separator) {
		return separator + 1;
	}
	return fname;
}
