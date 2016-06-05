#pragma once
#include <mupdf\fitz.h>
#include "Context.h"
using namespace System;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class Stream : public IO::Stream
			{
				Stream() {};
				bool isContextOwner;
			internal:
				Context^ m_pCtx;
				fz_stream* m_pStream;
			public:
				static MuPdf::Sharp::Fitz::Stream^ OpenFile(String^ filename);
				static MuPdf::Sharp::Fitz::Stream^ OpenFile(Context^ ctx, String^ filename);
				static MuPdf::Sharp::Fitz::Stream^ OpenMemory(array<System::Byte>^ data);
				static MuPdf::Sharp::Fitz::Stream^ OpenMemory(Context^ ctx, array<System::Byte>^ data);

				// Inherited via Stream
				virtual property bool CanRead
				{
					bool get() override
					{
						return m_pStream != nullptr;
					}
				}
				virtual property bool CanSeek
				{
					bool get() override
					{
						return m_pStream != nullptr;
					}
				}

				virtual property bool CanWrite
				{
					bool get() override
					{
						return m_pStream != nullptr;
					}
				}

				virtual property long long Length
				{
					long long get() override
					{
						if (m_pStream != nullptr)
						{
							return fz_available(m_pCtx->m_pCtx, m_pStream, 1);
						}
						return 0ll;
					}
				}
				virtual property long long Position
				{
					long long get() override
					{
						if (m_pStream != nullptr)
						{
							return fz_tell(m_pCtx->m_pCtx, m_pStream);
						}
						return 0ll;
					}
					void set(long long val) override
					{
						if (m_pStream != nullptr)
						{
							throw gcnew System::InvalidOperationException("Stream not properly inited.");
						}
						fz_seek(m_pCtx->m_pCtx, m_pStream, val, SEEK_SET);
					}
				}
				virtual void Close() override;
				virtual void Flush() override;
				virtual long long Seek(long long offset, System::IO::SeekOrigin origin) override;
				virtual void SetLength(long long value) override;
				virtual int Read(array<unsigned char, 1> ^buffer, int offset, int count) override;
				virtual void Write(array<unsigned char, 1> ^buffer, int offset, int count) override;
				
			};
		}
	}
}
