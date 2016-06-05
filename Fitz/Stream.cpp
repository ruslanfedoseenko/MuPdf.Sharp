#include "Stream.h"
#include "Helpers\ArrayHepler.h"
MuPdf::Sharp::Fitz::Stream^ MuPdf::Sharp::Fitz::Stream::OpenFile(String ^ fileName)
	
{
	MuPdf::Sharp::Fitz::Stream^ stream = gcnew MuPdf::Sharp::Fitz::Stream();
	stream->m_pCtx = gcnew Context(0);
	stream->isContextOwner = true;
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	stream->m_pStream = fz_open_file(stream->m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
	return stream;
}

MuPdf::Sharp::Fitz::Stream^ MuPdf::Sharp::Fitz::Stream::OpenMemory(array<Byte>^ data)
{
	unsigned char* dataPtr = ArrayHepler::toNativeArray(data);
	MuPdf::Sharp::Fitz::Stream^ stream = gcnew MuPdf::Sharp::Fitz::Stream();
	stream->m_pCtx = gcnew Context(0);
	stream->isContextOwner = true;
	stream->m_pStream = fz_open_memory(stream->m_pCtx->m_pCtx, dataPtr, data->Length);
	return stream;
}

MuPdf::Sharp::Fitz::Stream^ MuPdf::Sharp::Fitz::Stream::OpenMemory(Context^ ctx, array<Byte>^ data)
{
	unsigned char* dataPtr = ArrayHepler::toNativeArray(data);
	MuPdf::Sharp::Fitz::Stream^ stream = gcnew MuPdf::Sharp::Fitz::Stream();
	stream->m_pCtx = ctx;
	stream->isContextOwner = false;
	stream->m_pStream = fz_open_memory(stream->m_pCtx->m_pCtx, dataPtr, data->Length);
	return stream;
}

MuPdf::Sharp::Fitz::Stream^ MuPdf::Sharp::Fitz::Stream::OpenFile(Context^ ctx, String^ fileName)
{
	MuPdf::Sharp::Fitz::Stream^ stream = gcnew MuPdf::Sharp::Fitz::Stream();
	stream->m_pCtx = ctx;
	stream->isContextOwner = false;
	char* fileNameChars = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
	stream->m_pStream = fz_open_file(stream->m_pCtx->m_pCtx, fileNameChars);
	Marshal::FreeHGlobal((IntPtr)fileNameChars);
	return stream;
}


void MuPdf::Sharp::Fitz::Stream::Flush()
{}

long long MuPdf::Sharp::Fitz::Stream::Seek(long long offset, System::IO::SeekOrigin origin)
{
	if (offset > Int32::MaxValue)
	{
		throw gcnew NotSupportedException("Only values in range [0, Int32.MaxValue) shuld be suuplied.");
	}
	int whence = 0;
	switch (origin)
	{
	case System::IO::SeekOrigin::Begin:
		whence = SEEK_SET;
		break;
	case System::IO::SeekOrigin::Current:
		whence = SEEK_CUR;
		break;
	case System::IO::SeekOrigin::End:
		whence = SEEK_END;
		break;
	default:
		whence = (int)origin;
		break;
	}
	fz_seek(m_pCtx->m_pCtx, m_pStream, offset, whence);
	return Position;
}

void MuPdf::Sharp::Fitz::Stream::SetLength(long long value)
{
	throw gcnew System::NotImplementedException();
}

int MuPdf::Sharp::Fitz::Stream::Read(array<unsigned char, 1> ^buffer, int offset, int count)
{
	return 0;
}

void MuPdf::Sharp::Fitz::Stream::Write(array<unsigned char, 1> ^buffer, int offset, int count)
{
	throw gcnew System::NotImplementedException();
}

void MuPdf::Sharp::Fitz::Stream::Close()
{
	fz_drop_stream(m_pCtx->m_pCtx, m_pStream);
	m_pStream = nullptr;
	if (isContextOwner)
	{
		delete m_pCtx;
		m_pCtx = nullptr;
	}
}
