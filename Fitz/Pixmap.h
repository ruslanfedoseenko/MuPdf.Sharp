#pragma once
#include <mupdf\fitz.h>
#include "Context.h"
using namespace System;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class Pixmap
			{
				
				bool isContextOwner;
			internal:
				Context^ m_pCtx;
				fz_pixmap* m_pPixmap;
			public:
				Pixmap(int width, int height);
				Pixmap(Context^, int width, int height);
				~Pixmap();
				!Pixmap();
				property int Width
				{
					int get()
					{
						return fz_pixmap_width(m_pCtx->m_pCtx, m_pPixmap);
					}
				}
				property int Height
				{
					int get()
					{
						return fz_pixmap_height(m_pCtx->m_pCtx, m_pPixmap);
					}
				}
				property int Components
				{
					int get()
					{
						return fz_pixmap_components(m_pCtx->m_pCtx, m_pPixmap);
					}
				}
				array<Byte>^ GetSamples();
			};
		}
	}
}
