#include "FzContext.h"
MuPdf::Sharp::Fitz::FzContext::FzContext(fz_context* ctx)
{
	m_pCtx = ctx;
}
MuPdf::Sharp::Fitz::FzContext::FzContext(int maxStore)
{
	m_pCtx = fz_new_context(NULL, NULL, maxStore);
}

MuPdf::Sharp::Fitz::FzContext::~FzContext()
{
	fz_drop_context(m_pCtx);
}

Object ^ MuPdf::Sharp::Fitz::FzContext::Clone()
{
	return gcnew FzContext(fz_clone_context(m_pCtx));
}

void MuPdf::Sharp::Fitz::FzContext::SetImageScaleTunner(TuneImageScale^ tuner, Object^ arg)
{
	fz_tune_image_scale(m_pCtx, ObjectHelper::DelegateToFunctionNativePtr<fz_tune_image_scale_fn*>(tuner), ObjectHelper::ObjectToNativePointer(arg));
}

void MuPdf::Sharp::Fitz::FzContext::SetImageDecodeTunner(TuneImageDecode ^ tuner, Object ^ arg)
{
	fz_tune_image_decode(m_pCtx, ObjectHelper::DelegateToFunctionNativePtr<fz_tune_image_decode_fn*>(tuner), ObjectHelper::ObjectToNativePointer(arg));
}
