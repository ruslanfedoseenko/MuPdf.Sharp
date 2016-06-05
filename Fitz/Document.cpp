#include "Document.h"
#include <mupdf\fitz.h>

MuPdf::Sharp::Fitz::Document::Document(fz_document* pDocument, Context ^ ctx)
	: m_bContextInternalyCreated(false)
{
	m_pDocument = pDocument;
	m_pCtx = ctx;
}
MuPdf::Sharp::Fitz::Document::Document()
	: m_pCtx(gcnew Context(0))
	, m_bContextInternalyCreated(true)
{
	m_pDocument = static_cast<fz_document*>(fz_new_document_of_size(m_pCtx->m_pCtx, sizeof(fz_document)));
}

MuPdf::Sharp::Fitz::Document::Document(String ^ fileName)
	: m_pCtx(gcnew Context(0))
	, m_bContextInternalyCreated(true)
{
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	m_pDocument = fz_open_document(m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
}

MuPdf::Sharp::Fitz::Document::Document(Context ^ ctx, String ^ fileName)
	: m_bContextInternalyCreated(false)
	, m_pCtx(ctx)
{
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	m_pDocument = fz_open_document(m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
}

MuPdf::Sharp::Fitz::Document::Document(IO::Stream ^ documentStream, String ^ magic)
	: m_pCtx(gcnew Context(0))
	, m_bContextInternalyCreated(true)
{
	char* magicChars = (char*)Marshal::StringToHGlobalAnsi(magic).ToPointer();
	if (Fitz::Stream^ internalStream = dynamic_cast<Fitz::Stream^>(documentStream))
	{
		m_pDocument = fz_open_document_with_stream(m_pCtx->m_pCtx, magicChars, internalStream->m_pStream);
	}
	else
	{
		documentStream->Position = 0;
		array<System::Byte>^ buffer = gcnew array<System::Byte>(documentStream->Length);
		for (int totalBytesCopied = 0; totalBytesCopied < documentStream->Length; )
			totalBytesCopied += documentStream->Read(buffer, totalBytesCopied, Convert::ToInt32(documentStream->Length) - totalBytesCopied);
		
		internalStream = Fitz::Stream::OpenMemory(m_pCtx, buffer);
		m_pDocument = fz_open_document_with_stream(m_pCtx->m_pCtx, magicChars, internalStream->m_pStream);
		m_pInternalyCreatedStream = internalStream;
	}
	Marshal::FreeHGlobal((IntPtr)magicChars);
}

MuPdf::Sharp::Fitz::Document::Document(Context ^ ctx, IO::Stream ^ documentStream, String ^ magic)
	: m_pCtx(ctx)
	, m_bContextInternalyCreated(false)
{
	char* magicChars = (char*)Marshal::StringToHGlobalAnsi(magic).ToPointer();
	if (Fitz::Stream^ internalStream = dynamic_cast<Fitz::Stream^>(documentStream))
	{
		m_pDocument = fz_open_document_with_stream(m_pCtx->m_pCtx, magicChars, internalStream->m_pStream);
	}
	else
	{
		documentStream->Position = 0;
		array<System::Byte>^ buffer = gcnew array<System::Byte>(documentStream->Length);
		for (int totalBytesCopied = 0; totalBytesCopied < documentStream->Length; )
			totalBytesCopied += documentStream->Read(buffer, totalBytesCopied, Convert::ToInt32(documentStream->Length) - totalBytesCopied);

		internalStream = Fitz::Stream::OpenMemory(m_pCtx, buffer);
		m_pDocument = fz_open_document_with_stream(m_pCtx->m_pCtx, magicChars, internalStream->m_pStream);
		m_pInternalyCreatedStream = internalStream;
	}
	Marshal::FreeHGlobal((IntPtr)magicChars);
}

MuPdf::Sharp::Fitz::Document::~Document()
{
	fz_drop_document(m_pCtx->m_pCtx, m_pDocument);
	if (m_bContextInternalyCreated)
	{
		delete m_pCtx;
	}
	if (m_pInternalyCreatedStream != nullptr)
	{
		delete m_pInternalyCreatedStream;
	}
}

void MuPdf::Sharp::Fitz::Document::UsePassword(String ^ passowrd)
{
	char* passwordChars = (char*)Marshal::StringToHGlobalAnsi(passowrd).ToPointer();
	int res = fz_authenticate_password(m_pCtx->m_pCtx, m_pDocument, passwordChars);
	Marshal::FreeHGlobal((IntPtr)passwordChars);
	if (res != 0)
	{
		throw gcnew ArgumentException("Invalid Password");
	}

}


MuPdf::Sharp::Fitz::Page^ MuPdf::Sharp::Fitz::Document::LoadPage(int index)
{
	return gcnew MuPdf::Sharp::Fitz::Page(fz_load_page(m_pCtx->m_pCtx, m_pDocument, index), m_pCtx);
	
}