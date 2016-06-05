#pragma once
#include <mupdf/pdf.h>
#include "Context.h"
#include "Device.h"
#include "Cookie.h"
using namespace MuPdf::Sharp::Fitz;
using namespace System;
using namespace System::Windows;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Pdf
		{
			public ref class PdfPage 
			{ 
/*			internal:
				Context^ m_pCtx;
				pdf_page* m_pPdfPage;
				PdfPage(pdf_page*, Context^);
			public:
				PdfPage();
				PdfPage(Context^);
				~PdfPage();
				void Run(Device^, Matrix^, Cookie^);
				property Rect PageBounds
				{
					Rect get()
					{
						fz_rect rect;
						fz_rect* bound = pdf_bound_page(m_pCtx->m_pCtx, m_pPdfPage, &rect);
						Rect result(bound->x0, bound->y0, bound->x1, bound->y1);
						return result;
					}
				}*/
			};
		}
	}
}
