// ?rva0030E67C@Rva0030E961@@QAEMMM@Z
// partial score=0.9922045575 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy-
// BFME1 Rva0045A000ScalarField.cpp clean source at2f243e26d supplies the
// flat-grid sampler. Native30E67C..30E7D0 340B independently proves layout
// vector0, widthC, height10, scale14, state18, ready1C; WB EAD110 agrees.
// Native uses FISTP after floor rather than the truncating SSE cast. The
// two-instruction donor x87 conversion is confined to that codegen blocker.
extern "C" __declspec(dllimport) double __cdecl floor(double);
__forceinline int CameraFieldFloatToInt(float value){int result;__asm{fld value
 fistp result}return result;}
class Rva0030E961 {public:float rva0030E67C(float,float);float*m_data;float*finish,*end;int m_width,m_height;float m_scale;int m_state;bool m_ready;};
float Rva0030E961::rva0030E67C( float x, float y )
{
	if( !m_ready )
		return 0.0f;

	float scale = 1.0f / m_scale;
	float offset = (float)m_state * 10.0f;
	register float scaledX = (x + offset) * scale;
	register float scaledY = (y + offset) * scale;
	float xFloor = (float)floor( (double)scaledX );
	register int xIndex = CameraFieldFloatToInt( xFloor );
	float yFloor = (float)floor( (double)scaledY );
	register int yIndex = CameraFieldFloatToInt( yFloor );
	float xFraction = scaledX - (float)xIndex;
	float yFraction = scaledY - (float)yIndex;

	if( xIndex < 0 )
		xIndex = 0;
	if( yIndex < 0 )
		yIndex = 0;

	if( xIndex > m_width - 1 )
		xIndex = m_width - 1;
	if( yIndex > m_height - 1 )
		yIndex = m_height - 1;
	if( xIndex > m_width - 2 || yIndex > m_height - 2 )
		return m_data[ yIndex * m_width + xIndex ];

	int index = yIndex * m_width + xIndex;
	float p0 = m_data[ index ];
	float p2 = m_data[ index + m_width + 1 ];
	if( yFraction > xFraction )
	{
		float p3 = m_data[ index + m_width ];
		float height = (1.0f - yFraction) * (p0 - p3) +
			xFraction * (p2 - p3);
		height = height + p3;
		volatile float result=height;return result;
	}
	{
		float p1 = m_data[ index + 1 ];
		float height = (1.0f - xFraction) * (p0 - p1) +
			yFraction * (p2 - p1);
		height = height + p1;
		volatile float result=height;return result;
	}
}
