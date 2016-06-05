#include "PdfDocument.h"
#include "Stream.h"
MuPdf::Sharp::Pdf::PdfDocument::PdfDocument(Context^ ctx, fz_document* fzDoc)
	: isDocumentOwner(false)
	, m_pCtx(ctx)
	, isContextOwner(false)
{

	m_pDocument = pdf_specifics(m_pCtx->m_pCtx, fzDoc);
}

MuPdf::Sharp::Pdf::PdfDocument^ MuPdf::Sharp::Pdf::PdfDocument::FromDocument(Document^ doc)
{
	PdfDocument^ result = gcnew PdfDocument(doc->m_pCtx , doc->m_pDocument);
	return result;
}

MuPdf::Sharp::Pdf::PdfDocument::PdfDocument()
	: m_pCtx(gcnew Context(0))
	, isContextOwner(true)
	, isDocumentOwner(true)
{
	m_pDocument = pdf_create_document(m_pCtx->m_pCtx);
}

MuPdf::Sharp::Pdf::PdfDocument::PdfDocument(Context^ ctx)
	: m_pCtx(ctx)
	, isContextOwner(false)
	, isDocumentOwner(true)
{
	m_pDocument = pdf_create_document(m_pCtx->m_pCtx);
}
MuPdf::Sharp::Pdf::PdfDocument::PdfDocument(String^ fileName)
	: m_pCtx(gcnew Context(0))
	, isContextOwner(true)
	, isDocumentOwner(true)
{
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	m_pDocument = pdf_open_document(m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
}
MuPdf::Sharp::Pdf::PdfDocument::PdfDocument(Context^ ctx, String^ fileName)
	: m_pCtx(ctx)
	, isContextOwner(false)
	, isDocumentOwner(true)
{
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	m_pDocument = pdf_open_document(m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
}
MuPdf::Sharp::Pdf::PdfDocument::PdfDocument(IO::Stream^ documentStream)
	: m_pCtx(gcnew Context(0))
	, isContextOwner(true)
	, isDocumentOwner(true)
{
	if (Fitz::Stream^ internalStream = dynamic_cast<Fitz::Stream^>(documentStream))
	{
		m_pDocument = pdf_open_document_with_stream(m_pCtx->m_pCtx, internalStream->m_pStream);
	}
	else
	{
		documentStream->Position = 0;
		array<System::Byte>^ buffer = gcnew array<System::Byte>(documentStream->Length);
		for (int totalBytesCopied = 0; totalBytesCopied < documentStream->Length; )
			totalBytesCopied += documentStream->Read(buffer, totalBytesCopied, Convert::ToInt32(documentStream->Length) - totalBytesCopied);

		internalStream = Fitz::Stream::OpenMemory(m_pCtx, buffer);
		m_pDocument = pdf_open_document_with_stream(m_pCtx->m_pCtx, internalStream->m_pStream);
		m_pInternalyCreatedStream = internalStream;
	}
}
MuPdf::Sharp::Pdf::PdfDocument::PdfDocument(Context^ ctx, IO::Stream^ documentStream)
	: m_pCtx(ctx)
	, isContextOwner(false)
	, isDocumentOwner(true)
{
	if (Fitz::Stream^ internalStream = dynamic_cast<Fitz::Stream^>(documentStream))
	{
		m_pDocument = pdf_open_document_with_stream(m_pCtx->m_pCtx, internalStream->m_pStream);
	}
	else
	{
		documentStream->Position = 0;
		array<System::Byte>^ buffer = gcnew array<System::Byte>(documentStream->Length);
		for (int totalBytesCopied = 0; totalBytesCopied < documentStream->Length; )
			totalBytesCopied += documentStream->Read(buffer, totalBytesCopied, Convert::ToInt32(documentStream->Length) - totalBytesCopied);

		internalStream = Fitz::Stream::OpenMemory(m_pCtx, buffer);
		m_pDocument = pdf_open_document_with_stream(m_pCtx->m_pCtx, internalStream->m_pStream);
		m_pInternalyCreatedStream = internalStream;
	}
}
MuPdf::Sharp::Pdf::PdfDocument::~PdfDocument()
{
	if (isDocumentOwner)
	{
		pdf_drop_document(m_pCtx->m_pCtx, m_pDocument);
	}
	if (isContextOwner)
	{
		delete m_pCtx;
	}
	if (m_pInternalyCreatedStream != nullptr)
	{
		delete m_pInternalyCreatedStream;
	}
}
void MuPdf::Sharp::Pdf::PdfDocument::UsePassword(String^ passowrd)
{
	char* passwordChars = (char*)Marshal::StringToHGlobalAnsi(passowrd).ToPointer();
	int res = pdf_authenticate_password(m_pCtx->m_pCtx, m_pDocument, passwordChars);
	Marshal::FreeHGlobal((IntPtr)passwordChars);
	if (res != 0)
	{
		throw gcnew ArgumentException("Invalid Password");
	}
}
MuPdf::Sharp::Pdf::PdfPage^ MuPdf::Sharp::Pdf::PdfDocument::LoadPage(int index)
{
	return gcnew PdfPage();
}

