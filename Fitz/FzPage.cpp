#include "FzPage.h"

MuPdf::Sharp::Fitz::FzPage::FzPage(fz_page* pPage, FzContext^ pCtx)
{
	m_pCtx = pCtx;
	m_pPage = pPage;
}

MuPdf::Sharp::Fitz::FzPage::FzPage()
	: m_pCtx(gcnew FzContext(0))
{
	m_pPage = static_cast<fz_page*>(fz_new_page(m_pCtx->m_pCtx, sizeof(fz_page)));
}

MuPdf::Sharp::Fitz::FzPage::FzPage(FzContext ^ ctx)
	: m_pCtx(ctx)
{
	m_pPage = static_cast<fz_page*>(fz_new_page(m_pCtx->m_pCtx, sizeof(fz_page)));
}

MuPdf::Sharp::Fitz::FzPage::~FzPage()
{
	fz_drop_page(m_pCtx->m_pCtx, m_pPage);
}
