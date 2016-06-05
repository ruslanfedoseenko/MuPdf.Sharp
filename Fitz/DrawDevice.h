#pragma once
#include <mupdf\fitz.h>
#include "Device.h"
#include "Pixmap.h"
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class DrawDevice : Device
			{
				Pixmap^ m_pPixmap;
			public:
				DrawDevice(Pixmap^);
				DrawDevice(Context^, Pixmap^ );
				~DrawDevice();
				!DrawDevice();
			protected:
				fz_device* initDevice(Context^ ctx) override;
			};
		}
	}
}
