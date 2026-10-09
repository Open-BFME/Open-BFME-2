// ?Draw_Sentence@Render2DSentenceClass@@QAEXKKKK@Z
// partial score=0.85 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR (helper draft; target Code/Libraries/Source/WWVegas/WW3D2/, the existing
// render2dsentence.cpp holds the Zero Hour Draw_Sentence as present-unmatched):
// compiles to 2061 of 2187 bytes. Same blocks and calls, but cl gives `this`
// EDI (retail ESI), pushes EBX up front (retail pushes it only at the main
// loop, after the scale prepass), resets DrawExtents through a lea'd pointer
// and allocates the renderer bookkeeping temps differently. Layout, field
// meanings and every callee are established from retail; needs the pin
// ??1SurfaceClass@@QAE@XZ=0x00176CB0 (the ICF body rowed as
// ??1W3DRadarResetSurface@@QAE@XZ; BFME2's SurfaceClass is the one-pointer
// handle that ctor 0x001165D0 builds).
//
// ?Draw_Sentence@Render2DSentenceClass@@QAEXKKKK@Z, retail 0x00155B00 (2187 bytes),
// thiscall RET 0x10; callers 0x00104D9F (one colour four times), 0x001052A8,
// 0x001052DE, 0x001064A9, 0x001064ED, 0x00106548.
//
// Zero Hour's Render2DSentenceClass::Draw_Sentence (WW3D2 render2dsentence.cpp)
// in its BFME 2 form: four corner colours go to the rowed four-colour
// Render2DClass::Add_Quad 0x00042719; when a target size (+0xBC/+0xC0) is
// set the draw extents of the unscaled chunks first give the scale (default
// +0xB4/+0xB8); each chunk is scaled about its own left/top, moved by the
// location (+0x58) and rounded with floor(x + 0.5); the uv rectangle is
// normalised by the surface's width and height separately. New renderers
// cover the DX8 resolution (DX8Wrapper ResolutionWidth/Height read unsigned).
// BFME 2's SurfaceClass is a one-pointer D3D surface handle (ctor 0x001165D0
// stores the created surface at +0); copies AddRef/Release it and its
// destructor is the ICF body 0x00176CB0. Other names follow Zero Hour.

typedef unsigned long uint32;

extern "C" double __cdecl floor(double x);

class D3DSurfaceView
{
public:
	virtual long __stdcall QueryInterface(const void *iid, void **object);
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
};

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		int Format;
		unsigned int Width;
		unsigned int Height;
	};

	SurfaceClass() : D3DSurface(0) {}
	~SurfaceClass();
	SurfaceClass &operator=(const SurfaceClass &that)
	{
		if (that.D3DSurface)
			that.D3DSurface->AddRef();
		if (D3DSurface)
			D3DSurface->Release();
		D3DSurface = that.D3DSurface;
		return *this;
	}
	bool operator==(const SurfaceClass &that) const { return D3DSurface == that.D3DSurface; }
	bool operator!=(const SurfaceClass &that) const { return D3DSurface != that.D3DSurface; }
	void Get_Description(SurfaceDescription &desc);

	D3DSurfaceView *D3DSurface;
};

class Vector2
{
public:
	float X;
	float Y;
};

class RectClass
{
public:
	RectClass() {}
	RectClass(float left, float top, float right, float bottom) : Left(left), Top(top), Right(right), Bottom(bottom) {}
	float Width() const { return Right - Left; }
	float Height() const { return Bottom - Top; }
	void Set(float left, float top, float right, float bottom) { Left = left; Top = top; Right = right; Bottom = bottom; }
	RectClass &operator+=(const RectClass &r)
	{
		Left = (Left < r.Left) ? Left : r.Left;
		Top = (Top < r.Top) ? Top : r.Top;
		Right = (Right > r.Right) ? Right : r.Right;
		Bottom = (Bottom > r.Bottom) ? Bottom : r.Bottom;
		return *this;
	}
	RectClass &operator+=(const Vector2 &o)
	{
		Left += o.X;
		Right += o.X;
		Top += o.Y;
		Bottom += o.Y;
		return *this;
	}

	float Left;
	float Top;
	float Right;
	float Bottom;
};

class Render2DClass
{
public:
	Render2DClass();
	void Set_Coordinate_Range(const RectClass &range);
	void Add_Quad(const RectClass &screen, const RectClass &uv, unsigned long color1, unsigned long color2, unsigned long color3, unsigned long color4);

private:
	unsigned char m_pad[0x4C];
};

class DX8Wrapper
{
public:
	static unsigned int Get_Resolution_Width() { return ResolutionWidth; }
	static unsigned int Get_Resolution_Height() { return ResolutionHeight; }

protected:
	static int ResolutionWidth;
	static int ResolutionHeight;
};

template <class T> class VectorClass
{
public:
	virtual ~VectorClass();
	virtual bool operator==(const VectorClass<T> &other) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);

	T &operator[](int index) { return Vector[index]; }
	int Length() const { return VectorMax; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};

template <class T> class DynamicVectorClass : public VectorClass<T>
{
public:
	int Count() const { return ActiveCount; }
	__forceinline bool Add(T const &object)
	{
		if (ActiveCount >= this->Length())
		{
			if ((this->IsAllocated || !this->VectorMax) && GrowthStep > 0)
			{
				if (!this->Resize(this->Length() + GrowthStep))
					return false;
			}
			else
			{
				return false;
			}
		}
		(*this)[ActiveCount++] = object;
		return true;
	}

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DSentenceClass
{
public:
	void Draw_Sentence(uint32 color1, uint32 color2, uint32 color3, uint32 color4);

private:
	struct SentenceDataStruct
	{
		SurfaceClass Surface;
		RectClass ScreenRect;
		RectClass UVRect;
	};

	struct PendingSurfaceStruct
	{
		SurfaceClass Surface;
		DynamicVectorClass<Render2DClass *> Renderers;
	};

	struct RendererDataStruct
	{
		Render2DClass *Renderer;
		SurfaceClass Surface;
	};

	void *m_vtable;
	DynamicVectorClass<SentenceDataStruct> SentenceData; // +0x04
	DynamicVectorClass<PendingSurfaceStruct> PendingSurfaces; // +0x1C
	DynamicVectorClass<RendererDataStruct> Renderers; // +0x34
	unsigned char m_pad4C[0x58 - 0x4C];
	Vector2 Location; // +0x58
	unsigned char m_pad60[0x8C - 0x60];
	RectClass ClipRect; // +0x8C
	RectClass DrawExtents; // +0x9C
	bool IsClippedEnabled; // +0xAC
	unsigned char m_padAD[0xB4 - 0xAD];
	float DefaultScaleX; // +0xB4
	float DefaultScaleY; // +0xB8
	float TargetWidth; // +0xBC
	float TargetHeight; // +0xC0
};

void Render2DSentenceClass::Draw_Sentence(uint32 color1, uint32 color2, uint32 color3, uint32 color4)
{
	Render2DClass *curr_renderer = 0;
	SurfaceClass curr_surface;

	float scaleX = DefaultScaleX;
	float scaleY = DefaultScaleY;
	DrawExtents.Set(0, 0, 0, 0);

	int index;
	if (TargetWidth > 0 && TargetHeight > 0)
	{
		for (index = 0; index < SentenceData.Count(); index++)
		{
			SentenceDataStruct &data = SentenceData[index];
			if (DrawExtents.Width() == 0)
				DrawExtents = data.ScreenRect;
			else
				DrawExtents += data.ScreenRect;
		}
		if (DrawExtents.Width() != 0)
			scaleX = TargetWidth / DrawExtents.Width();
		if (DrawExtents.Height() != 0)
			scaleY = TargetHeight / DrawExtents.Height();
		DrawExtents.Set(0, 0, 0, 0);
	}

	for (index = 0; index < SentenceData.Count(); index++)
	{
		SentenceDataStruct &data = SentenceData[index];

		if (data.Surface != curr_surface)
		{
			curr_surface = data.Surface;

			bool found = false;
			for (int renderer_index = 0; renderer_index < Renderers.Count(); renderer_index++)
			{
				if (Renderers[renderer_index].Surface == curr_surface)
				{
					found = true;
					curr_renderer = Renderers[renderer_index].Renderer;
					break;
				}
			}

			if (found == false)
			{
				curr_renderer = new Render2DClass;
				curr_renderer->Set_Coordinate_Range(RectClass(0, 0, (float)DX8Wrapper::Get_Resolution_Width(), (float)DX8Wrapper::Get_Resolution_Height()));

				RendererDataStruct render_info;
				render_info.Renderer = curr_renderer;
				render_info.Surface = curr_surface;
				Renderers.Add(render_info);

				for (int surface_index = 0; surface_index < PendingSurfaces.Count(); surface_index++)
				{
					PendingSurfaceStruct &surface_info = PendingSurfaces[surface_index];
					if (surface_info.Surface == curr_surface)
						surface_info.Renderers.Add(curr_renderer);
				}
			}
		}

		RectClass uv_rect = data.UVRect;
		RectClass screen_rect;
		screen_rect.Left = data.ScreenRect.Left * scaleX;
		screen_rect.Top = data.ScreenRect.Top * scaleY;
		screen_rect.Right = data.ScreenRect.Width() * scaleX + screen_rect.Left;
		screen_rect.Bottom = data.ScreenRect.Height() * scaleY + screen_rect.Top;
		screen_rect += Location;
		screen_rect.Left = floor(screen_rect.Left + 0.5f);
		screen_rect.Top = floor(screen_rect.Top + 0.5f);
		screen_rect.Right = floor(screen_rect.Right + 0.5f);
		screen_rect.Bottom = floor(screen_rect.Bottom + 0.5f);

		if (IsClippedEnabled)
		{
			if (screen_rect.Right <= ClipRect.Left || screen_rect.Bottom <= ClipRect.Top)
				continue;

			RectClass clipped_rect;
			clipped_rect.Left = (screen_rect.Left > ClipRect.Left) ? screen_rect.Left : ClipRect.Left;
			clipped_rect.Right = (screen_rect.Right < ClipRect.Right) ? screen_rect.Right : ClipRect.Right;
			clipped_rect.Top = (screen_rect.Top > ClipRect.Top) ? screen_rect.Top : ClipRect.Top;
			clipped_rect.Bottom = (screen_rect.Bottom < ClipRect.Bottom) ? screen_rect.Bottom : ClipRect.Bottom;

			RectClass clipped_uv_rect;
			float percent = ((clipped_rect.Left - screen_rect.Left) / screen_rect.Width());
			clipped_uv_rect.Left = uv_rect.Left + (uv_rect.Width() * percent);

			percent = ((clipped_rect.Right - screen_rect.Left) / screen_rect.Width());
			clipped_uv_rect.Right = uv_rect.Left + (uv_rect.Width() * percent);

			percent = ((clipped_rect.Top - screen_rect.Top) / screen_rect.Height());
			clipped_uv_rect.Top = uv_rect.Top + (uv_rect.Height() * percent);

			percent = ((clipped_rect.Bottom - screen_rect.Top) / screen_rect.Height());
			clipped_uv_rect.Bottom = uv_rect.Top + (uv_rect.Height() * percent);

			screen_rect = clipped_rect;
			uv_rect = clipped_uv_rect;

			if (screen_rect.Right <= screen_rect.Left || screen_rect.Bottom <= screen_rect.Top)
				continue;
		}

		SurfaceClass::SurfaceDescription desc;
		curr_surface.Get_Description(desc);

		float inv_width = 1.0f / (float)desc.Width;
		uv_rect.Left *= inv_width;
		uv_rect.Right *= inv_width;
		float inv_height = 1.0f / (float)desc.Height;
		uv_rect.Top *= inv_height;
		uv_rect.Bottom *= inv_height;

		curr_renderer->Add_Quad(screen_rect, uv_rect, color1, color2, color3, color4);

		if (DrawExtents.Width() == 0)
			DrawExtents = screen_rect;
		else
			DrawExtents += screen_rect;
	}
}
