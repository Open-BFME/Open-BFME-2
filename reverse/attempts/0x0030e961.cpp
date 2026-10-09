// ?rva0030E961@Rva0030E961@@QAEXPBGHHHH@Z
// partial score=0.8684935219 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
// Native30E961..30EC75, 788B; BF1 clean scalar-field donor2f243e26d.
// Target constrains source samples then propagates a slope envelope across
// a quarter-resolution grid. Owner identity unknown; retain existingRva.
template<class T>__declspec(noinline)T clamp(T low,T value,T high){return low>value?low:(value>high?high:value);}
enum NameKeyType{NAMEKEY_INVALID=0};
class Rva00148F5ECache{public:NameKeyType get();int key;const char*name;};
extern Rva00148F5ECache g_Va00DBDEFC,g_Va00DBDF0C,g_Va00DBDF14;
class Dict{void*data;public:float getReal(int,bool*)const;};extern Dict g_Va00E00944;
class GlobalData{public:char gap[0xde4];float m_default;};extern GlobalData*TheWritableGlobalData;
class RvaVector{public:void rva0030E910(unsigned int,float);};
class Rva0030E961{public:void rva0030E961(const unsigned short*,int,int,int,int);float*m_data,*finish,*end;int m_width,m_height;float m_scale;int m_state;bool m_ready;};
void Rva0030E961::rva0030E961( const unsigned short *source, int unused,
	int sourceWidth, int sourceHeight, int state )
{
	int outputX,outputY;
	bool found;
	float setting=g_Va00E00944.getReal(g_Va00DBDEFC.get(),&found);
	if( !found )
		setting = TheWritableGlobalData->m_default;
	if( setting == 0.0f )
		return;

	float low=g_Va00E00944.getReal(g_Va00DBDF0C.get(),&found);
	if( !found )
		low = -9999999.0f;
	float high=g_Va00E00944.getReal(g_Va00DBDF14.get(),&found);
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
	reinterpret_cast<RvaVector*>(&m_data)->rva0030E910(m_width*m_height,0.0f);

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
						float sample = source[ y * sourceWidth + x ] *
							0.0390625f;
						sample=clamp<float>(low,sample,high);
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
							float *current = &m_data[ outputY * m_width + outputX ];
							if( candidate > *current )
							{
								*current = candidate;
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

