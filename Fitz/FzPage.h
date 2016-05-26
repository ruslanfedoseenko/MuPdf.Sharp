#pragma once
#include <mupdf\fitz.h>
#include "FzContext.h"
using namespace System;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class FzPage 
			{ 
				fz_page* m_pPage;
				FzContext^ m_pCtx;
			internal:
				FzPage(fz_page* pPage, FzContext^ pCtx);
			public: 
				FzPage();
				FzPage(FzContext^ ctx);
				~FzPage();
			};
		}
	}
}
