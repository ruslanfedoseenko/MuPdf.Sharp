#pragma once
#include <mupdf/pdf.h>
#include "Context.h"
#include "Document.h"
#include "PdfPage.h"
using namespace System;
using namespace MuPdf::Sharp::Fitz;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Pdf
		{
			public ref class PdfDocument
			{ 
				bool isContextOwner;
				bool isDocumentOwner;
				Stream^ m_pInternalyCreatedStream;
			internal:
				pdf_document* m_pDocument;
				Context^ m_pCtx;
				PdfDocument(Context^, fz_document*);
			public: 
				static PdfDocument^ FromDocument(Document^);
				PdfDocument();
				PdfDocument(Context^);
				PdfDocument(String^);
				PdfDocument(Context^, String^);
				PdfDocument(IO::Stream^);
				PdfDocument(Context^, IO::Stream^);
				~PdfDocument();
				property bool IsPasswordRequired
				{
					bool get()
					{
						return pdf_needs_password(m_pCtx->m_pCtx, m_pDocument) > 0;
					}
				}

				void UsePassword(String^ passowrd);

				property int PageCount
				{
					int get()
					{
						return pdf_count_pages(m_pCtx->m_pCtx, m_pDocument);
					}
				}

				PdfPage^ LoadPage(int index);

			};
		}
	}
}
