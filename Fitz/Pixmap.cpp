#include "Pixmap.h"
#include "Helpers\ArrayHepler.h"
using namespace MuPdf::Sharp::Helpers;

MuPdf::Sharp::Fitz::Pixmap::Pixmap(int width, int height)
	: m_pCtx(gcnew Context(0))
	, isContextOwner(true)
	, m_pPixmap(fz_new_pixmap(m_pCtx->m_pCtx, fz_device_rgb(m_pCtx->m_pCtx), width, height))
{
	
}

MuPdf::Sharp::Fitz::Pixmap::Pixmap(Context^ ctx, int width, int height)
	: m_pCtx(ctx)
	, isContextOwner(false)
	
{
	if (ctx == nullptr)
	{
		throw gcnew System::ArgumentNullException(gcnew String("ctx"));
	}
	m_pPixmap = fz_new_pixmap(m_pCtx->m_pCtx, fz_lookup_device_colorspace(m_pCtx->m_pCtx, "DeviceBGR"), width, height);
	fz_clear_pixmap_with_value(m_pCtx->m_pCtx, m_pPixmap, 0xFF);
}

MuPdf::Sharp::Fitz::Pixmap::~Pixmap()
{
	fz_drop_pixmap(m_pCtx->m_pCtx, m_pPixmap);
	if (isContextOwner)
		delete m_pCtx;
}

MuPdf::Sharp::Fitz::Pixmap::!Pixmap()
{
	
}

array<Byte>^ MuPdf::Sharp::Fitz::Pixmap::GetSamples()
{
	return ArrayHepler::toByteArray(fz_pixmap_samples(m_pCtx->m_pCtx, m_pPixmap), Width * Height * Components);
}
