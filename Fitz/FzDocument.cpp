#include "FzDocument.h"
#include <mupdf\fitz.h>

MuPdf::Sharp::Fitz::FzDocument::FzDocument(fz_document* pDocument, FzContext ^ ctx)
	: m_bContextInternalyCreated(false)
{
	m_pDocument = pDocument;
	m_pCtx = ctx;
}
MuPdf::Sharp::Fitz::FzDocument::FzDocument()
	: m_pCtx(gcnew FzContext(0))
	, m_bContextInternalyCreated(true)
{
	m_pDocument = static_cast<fz_document*>(fz_new_document_of_size(m_pCtx->m_pCtx, sizeof(fz_document)));
}

MuPdf::Sharp::Fitz::FzDocument::FzDocument(String ^ fileName)
	: m_pCtx(gcnew FzContext(0))
	, m_bContextInternalyCreated(true)
{
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	m_pDocument = fz_open_document(m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
}

MuPdf::Sharp::Fitz::FzDocument::FzDocument(FzContext ^ ctx, String ^ fileName)
	: m_bContextInternalyCreated(false)
	, m_pCtx(ctx)
{
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	m_pDocument = fz_open_document(m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
}

MuPdf::Sharp::Fitz::FzDocument::FzDocument(Stream ^ documentStream, String ^ magic)
	: m_pCtx(gcnew FzContext(0))
	, m_bContextInternalyCreated(true)
{
	//ToDo: Implement FzStream as .Net Stream
	throw gcnew System::NotImplementedException();
}

MuPdf::Sharp::Fitz::FzDocument::FzDocument(FzContext ^ ctx, Stream ^ documentStream, String ^ magic)
{
	//ToDo: Implement FzStream as .Net Stream
	throw gcnew System::NotImplementedException();
}

MuPdf::Sharp::Fitz::FzDocument::~FzDocument()
{
	fz_drop_document(m_pCtx->m_pCtx, m_pDocument);
	if (m_bContextInternalyCreated)
	{
		delete m_pCtx;
	}
}

void MuPdf::Sharp::Fitz::FzDocument::UsePassword(String ^ passowrd)
{
	char* passwordChars = (char*)Marshal::StringToHGlobalAnsi(passowrd).ToPointer();
	fz_authenticate_password(m_pCtx->m_pCtx, m_pDocument, passwordChars);
	Marshal::FreeHGlobal((IntPtr)passwordChars);

}
