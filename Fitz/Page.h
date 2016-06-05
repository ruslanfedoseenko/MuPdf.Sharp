#pragma once
#include <mupdf\fitz.h>
#include "Context.h"
#include "Cookie.h"
#include "Device.h"
using namespace System;
using namespace System::Windows;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class Page
			{
				fz_page* m_pPage;
				Context^ m_pCtx;
			internal:
				Page(fz_page* pPage, Context^ pCtx);
			public:
				Page();
				Page(Context^ ctx);
				~Page();
				void Run(Device^,Matrix^, Cookie^);
				property Rect PageBounds
				{
					Rect get()
					{
						fz_rect rect;
						fz_rect* bound = fz_bound_page(m_pCtx->m_pCtx, m_pPage, &rect);
						Rect result(bound->x0, bound->y0, bound->x1, bound->y1);
						return result;
					}
				}
			};
		}
	}
}
