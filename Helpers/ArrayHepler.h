#pragma once
using namespace System;
namespace MuPdf
{
	namespace Sharp
	{
		namespace Helpers
		{
			class ArrayHepler
			{
			public:
				static array<Byte>^ toByteArray(unsigned char* arr, long lenth);
				static unsigned char* toNativeArray(array<Byte>^ arr);
			};
		}
	}
}
