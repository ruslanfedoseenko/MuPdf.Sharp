#include "Page.h"

MuPdf::Sharp::Fitz::Page::Page(fz_page* pPage, Context^ pCtx)
{
	m_pCtx = pCtx;
	m_pPage = pPage;
}

MuPdf::Sharp::Fitz::Page::Page()
	: m_pCtx(gcnew Context(0))
{
	m_pPage = static_cast<fz_page*>(fz_new_page(m_pCtx->m_pCtx, sizeof(fz_page)));
}

MuPdf::Sharp::Fitz::Page::Page(Context ^ ctx)
	: m_pCtx(ctx)
{
	m_pPage = static_cast<fz_page*>(fz_new_page(m_pCtx->m_pCtx, sizeof(fz_page)));
}

MuPdf::Sharp::Fitz::Page::~Page()
{
	fz_drop_page(m_pCtx->m_pCtx, m_pPage);
}

void MuPdf::Sharp::Fitz::Page::Run(Device^ device, Matrix^ matrix, Cookie^ cookie)
{
	if (device == nullptr)
	{
		throw gcnew ArgumentNullException(gcnew String("device"));
	}
	if (matrix == nullptr)
	{
		throw gcnew ArgumentNullException(gcnew String("matrix"));
	}
	fz_run_page(m_pCtx->m_pCtx, m_pPage, device->m_pDevice, 
		matrix->toNativeMatrix(),
		cookie == nullptr ? nullptr : cookie->m_pCookie);
}
