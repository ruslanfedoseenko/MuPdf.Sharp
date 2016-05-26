#include "ObjectHelper.h"
Object ^ MuPdf::Sharp::Helpers::ObjectHelper::NativePointerToObject(void * nativePtr)
{
	GCHandle h = GCHandle::FromIntPtr(IntPtr(nativePtr));
	Object^ result = h.Target;
	h.Free();
	return result;
}

void * MuPdf::Sharp::Helpers::ObjectHelper::ObjectToNativePointer(Object ^ obj)
{
	return  GCHandle::ToIntPtr(GCHandle::Alloc(obj)).ToPointer();;
}
