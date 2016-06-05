#pragma once
#include <mupdf\fitz.h>
#include "Context.h"
#include "Page.h"
#include "Stream.h"
using namespace System;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			
			public ref class Document 
			{
				bool m_bContextInternalyCreated;
				
				
				Stream^ m_pInternalyCreatedStream;
			internal:
				Context^ m_pCtx;
				fz_document* m_pDocument;
				Document(fz_document* pDocument, Context ^ ctx);
			public: 
				Document();
				Document(String^ fileName);
				Document(Context^ ctx, String^ fileName);
				Document(IO::Stream^ documentStream, String^ magic);
				Document(Context^ ctx, IO::Stream^ documentStream, String^ magic);
				~Document();
				property bool IsPasswordRequired
				{
					bool get()
					{
						return fz_needs_password(m_pCtx->m_pCtx, m_pDocument) > 0;
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

				Page^ LoadPage(int index);
				
			};
		}
	}
}