#include "DrawDevice.h"


MuPdf::Sharp::Fitz::DrawDevice::DrawDevice(Pixmap^ pPixmap)
	: Device(Device::DeviceType::Draw, pPixmap->m_pCtx)
	, m_pPixmap(pPixmap)
{
	
}

MuPdf::Sharp::Fitz::DrawDevice::DrawDevice(Context^ ctx, Pixmap^ pixmap)
	: Device(Device::DeviceType::Draw, pixmap->m_pCtx)
	, m_pPixmap(pixmap)
{
	
}

MuPdf::Sharp::Fitz::DrawDevice::~DrawDevice()
{
	
}

MuPdf::Sharp::Fitz::DrawDevice::!DrawDevice()
{
	
}

fz_device * MuPdf::Sharp::Fitz::DrawDevice::initDevice(Context ^ ctx)
{
	return fz_new_draw_device(ctx->m_pCtx, m_pPixmap->m_pPixmap);
}
