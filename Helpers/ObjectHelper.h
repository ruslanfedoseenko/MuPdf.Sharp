#pragma once
using namespace System;
using namespace System::Runtime::InteropServices;
namespace MuPdf
{
	namespace Sharp
	{
		namespace Helpers
		{
			class ObjectHelper
			{
			public:
				static Object^ NativePointerToObject(void* nativePtr);
				static void* ObjectToNativePointer(Object^ obj);
				template<typename TFunc>
				static TFunc DelegateToFunctionNativePtr(Delegate^ managedDelegate);
			};
			template<typename TFunc>
			inline TFunc ObjectHelper::DelegateToFunctionNativePtr(Delegate^ managedDelegate)
			{
				GCHandle gch = GCHandle::Alloc(managedDelegate);
				IntPtr ip = Marshal::GetFunctionPointerForDelegate(managedDelegate);
				TFunc nativeFunction = static_cast<TFunc>(ip.ToPointer());
				gch.Free();
				return nativeFunction;
			}
		}
	}
}

