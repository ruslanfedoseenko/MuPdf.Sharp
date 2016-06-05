#include "Context.h"
MuPdf::Sharp::Fitz::Context::Context(fz_context* ctx)
{
	m_pCtx = ctx;
	fz_register_document_handlers(m_pCtx);
}
MuPdf::Sharp::Fitz::Context::Context(int maxStore)
{
	m_pCtx = fz_new_context(NULL, NULL, maxStore);
	fz_register_document_handlers(m_pCtx);
}

MuPdf::Sharp::Fitz::Context::~Context()
{
	fz_drop_context(m_pCtx);
}

Object ^ MuPdf::Sharp::Fitz::Context::Clone()
{
	return gcnew Context(fz_clone_context(m_pCtx));
}

void MuPdf::Sharp::Fitz::Context::SetImageScaleTunner(TuneImageScale^ tuner, Object^ arg)
{
	fz_tune_image_scale(m_pCtx, ObjectHelper::DelegateToFunctionNativePtr<fz_tune_image_scale_fn*>(tuner), ObjectHelper::ObjectToNativePointer(arg));
}

void MuPdf::Sharp::Fitz::Context::SetImageDecodeTunner(TuneImageDecode ^ tuner, Object ^ arg)
{
	fz_tune_image_decode(m_pCtx, ObjectHelper::DelegateToFunctionNativePtr<fz_tune_image_decode_fn*>(tuner), ObjectHelper::ObjectToNativePointer(arg));
}

fz_matrix * MuPdf::Sharp::Fitz::Matrix::toNativeMatrix()
{
	fz_matrix* result = new fz_matrix;
	result->a = A;
	result->b = B;
	result->c = C;
	result->d = D;
	result->e = E;
	result->f = F;
	return result;
}

MuPdf::Sharp::Fitz::Matrix^ MuPdf::Sharp::Fitz::Matrix::fromNativeMatrix(fz_matrix* nativeMatrix)
{
	Matrix^ result = gcnew Matrix;
	result->A = nativeMatrix->a;
	result->B = nativeMatrix->b;
	result->C = nativeMatrix->c;
	result->D = nativeMatrix->d;
	result->E = nativeMatrix->e;
	result->F = nativeMatrix->f;
	return result;
}
