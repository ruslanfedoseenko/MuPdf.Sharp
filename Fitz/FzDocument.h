#pragma once
#include <mupdf\fitz.h>
#include "FzContext.h"
#include "FzPage.h"
using namespace System;
using namespace System::IO;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			
			public ref class FzDocument 
			{
				bool m_bContextInternalyCreated;
				fz_document* m_pDocument;
				FzContext^ m_pCtx;
				FzDocument(fz_document* pDocument, FzContext ^ ctx);
			public: 
				FzDocument();
				FzDocument(String^ fileName);
				FzDocument(FzContext^ ctx, String^ fileName);
				FzDocument(Stream^ documentStream, String^ magic);
				FzDocument(FzContext^ ctx, Stream^ documentStream, String^ magic);
				~FzDocument();
				property bool IsPasswordrequired
				{
					bool get()
					{
						return fz_needs_password(m_pCtx->m_pCtx, m_pDocument);
					}
				}

				void UsePassword(String^ passowrd);

				property int PageCount
				{
					int get()
					{
						return fz_count_pages(m_pCtx->m_pCtx, m_pDocument);
					}
				}

				property FzPage^ Page[int]
				{
					FzPage^ get(int index)
					{
						return gcnew FzPage(fz_load_page(m_pCtx->m_pCtx, m_pDocument, index), m_pCtx);
					}
				}
			};
		}
	}
}