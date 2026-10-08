// cl: /O1 /G6 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// BFME1 9cbfb551fe20 Rva0045A000ScalarField.cpp initialize algorithm, adapted
// using WB SmoothCameraHeightField::Initialize and retail 0x30E961/788.
// Retail samples and SSE float operations independently establish vector<float>.
// Target keys' eight-byte objects contain the string names used below; global
// spellings are descriptive TU-local caches, not recovered external linker names.
// MapObject::TheWorldDict is defined by WorldHeightMap.cpp; the three static
// NameKey caches contain zero keys and their exact retail name literals.
// Retail code proves GlobalData +0xDE4 and the 32-byte scalar-field layout.
// Target resize helper takes the value by value, adapted with a container
// subclass preserving the genuine STLport layout and erase/insert semantics.
// WB labels the initializer; the resize adapter name is descriptive.
// Signed sample conversion preserves its 0..65535 range and native SSE shape;
// shared output indices and direct destination indexing reproduce all homes.
#include <vector>
typedef unsigned short R3HeightSample;
enum NameKeyType {NAMEKEY_INVALID=0};
class StaticNameKey { public: NameKeyType key() const; mutable NameKeyType cached; const char*name; };
class Dict { public: float getReal(int,bool*) const; };
class MapObject { public: static Dict TheWorldDict; };
static StaticNameKey TheKey_cameraMapHeightSmoothnessScalar={NAMEKEY_INVALID,"cameraMapHeightSmoothnessScalar"};
static StaticNameKey TheKey_cameraGroundMinHeight={NAMEKEY_INVALID,"cameraGroundMinHeight"};
static StaticNameKey TheKey_cameraGroundMaxHeight={NAMEKEY_INVALID,"cameraGroundMaxHeight"};
class GlobalData { public: unsigned char pad[0xDE4];float m_cameraMapHeightSmoothnessScalar; };
extern GlobalData*TheWritableGlobalData;
template<class T> T clamp(T,T,T);
// Target 0x30E910 takes its fill value by value; vendored resize takes const&.
// This adapter preserves the genuine STLport container, exposing the target ABI.
class SmoothCameraHeightSamples:public _STL::vector<float>{public:__declspec(noinline) void resize(unsigned,float);};
class SmoothCameraHeightField {
public:
 void Initialize(const R3HeightSample*,int,int,int,int);
 SmoothCameraHeightSamples m_data;
 int m_width,m_height;float m_scale;int m_state;bool m_ready;
};
void SmoothCameraHeightField::Initialize( const R3HeightSample *source, int unused,
	int sourceWidth, int sourceHeight, int state )
{
	bool found;
	float setting = MapObject::TheWorldDict.getReal((int)TheKey_cameraMapHeightSmoothnessScalar.key(), &found);
	if( !found )
		setting = TheWritableGlobalData->m_cameraMapHeightSmoothnessScalar;
	if( setting == 0.0f )
		return;

	float low = MapObject::TheWorldDict.getReal((int)TheKey_cameraGroundMinHeight.key(), &found);
	if( !found )
		low = -9999999.0f;
	float high = MapObject::TheWorldDict.getReal((int)TheKey_cameraGroundMaxHeight.key(), &found);
	if( !found )
		high = 9999999.0f;
	if( high < low )
	{
		float temporary = high;
		high = low;
		low = temporary;
	}

	m_width = ( sourceWidth + 3 ) / 4;
	m_height = ( sourceHeight + 3 ) / 4;
	m_scale = 40.0f;
	m_data.resize( m_width * m_height, 0.0f );

	int outputX,outputY;
	for( outputX = 0; outputX < m_width; ++outputX )
	{
		for( outputY = 0; outputY < m_height; ++outputY )
		{
			float value = 0.0f;
			for( int x = outputX * 4; x < outputX * 4 + 4; ++x )
			{
				for( int y = outputY * 4; y < outputY * 4 + 4; ++y )
				{
					if( x < sourceWidth && y < sourceHeight )
					{
						float sample=clamp(low,(float)(int)source[y*sourceWidth+x]*0.0390625f,high);
						if( value < sample )
							value = sample;
					}
				}
			}
			m_data[ outputY * m_width + outputX ] = value;
		}
	}

	int x;
	int y;
	bool changed = false;
	int passes = m_width;
	if( m_height > passes )
		passes = m_height;
	do
	{
		changed = false;
		for( outputX = 0; outputX < m_width; ++outputX )
		{
			for( outputY = 0; outputY < m_height; ++outputY )
			{
				for( x = outputX - 1; x < outputX + 2; ++x )
				{
					if( x < 0 || x >= m_width )
						continue;
					for( y = outputY - 1; y < outputY + 2; ++y )
					{
						if( y >= 0 && y < m_height )
						{
							float delta = setting;
							delta *= m_scale;
							delta *= 0.6f;
							if( x != outputX && y != outputY )
								delta *= 1.4f;
							float candidate = m_data[ y * m_width + x ] - delta;
							if( candidate > m_data[outputY*m_width+outputX] )
							{
								m_data[outputY*m_width+outputX] = candidate;
								changed = true;
							}
						}
					}
					}
			}
		}
		--passes;
	}
	while( changed && passes > 0 );

	m_state = state;
	m_ready = true;
}

void SmoothCameraHeightSamples::resize(unsigned count,float value){
 if(count<size())erase(begin()+count,end());
 else insert(end(),count-size(),value);
}
