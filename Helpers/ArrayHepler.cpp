#include "ArrayHepler.h"
using namespace  System::Runtime::InteropServices;
array<Byte>^ MuPdf::Sharp::Helpers::ArrayHepler::toByteArray(unsigned char * arr, long length)
{
	array<Byte>^ result = gcnew array<Byte>(length);
	Marshal::Copy((IntPtr)arr, result, 0, length);
	return result;
}

unsigned char * MuPdf::Sharp::Helpers::ArrayHepler::toNativeArray(array<Byte>^ arr)
{
	unsigned char * res = new unsigned char[arr->Length];
	Marshal::Copy(arr, 0, (IntPtr)res, arr->Length);
	return res;
}
