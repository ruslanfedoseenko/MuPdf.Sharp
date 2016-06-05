#pragma once
#include <mupdf\fitz.h>
#include "Context.h"
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class Device abstract
			{ 
			public:
				enum class DeviceType : int
				{
					Trace,
					Draw,
					List,
					Text,
					BoundBox
				};
			private:
				DeviceType m_deviceType;
			protected:
				virtual fz_device* initDevice(Context^) abstract;
			internal:
				fz_device* m_pDevice;
				Context^ m_pCtx;
			public: 
				Device(DeviceType type)
					: m_deviceType(type)
				{
					m_pCtx = gcnew Context(0);
					m_pDevice = initDevice(m_pCtx);
					
				}
				Device(DeviceType type, Context^ ctx)
					: m_deviceType(type)
					, m_pCtx(ctx)
				{
					m_pDevice = initDevice(m_pCtx);
				}
				virtual ~Device() {};
				!Device()
				{
					fz_drop_device(m_pCtx->m_pCtx, m_pDevice);
				}
			
			};
		}
	}
}
