#pragma once
#include <mupdf\fitz.h>
using namespace System;
using namespace System::Threading;
using namespace System::ComponentModel;
using namespace System::Windows::Threading;
namespace MuPdf
{
	namespace Sharp
	{

		namespace Fitz
		{
			public ref class Cookie : public INotifyPropertyChanged
			{
			internal:
				fz_cookie* m_pCookie;


			public:
				Cookie(CancellationToken token);
				Cookie(CancellationToken token, bool isIncopleteOk);
				~Cookie();
				!Cookie();
				event ProgressChangedEventHandler^ ProgressChanged 
				{
					void add(ProgressChangedEventHandler^ value)
					{
						m_progressChangedHandler = static_cast<ProgressChangedEventHandler^>(Delegate::Combine(m_progressChangedHandler, value));
					}
					void remove(ProgressChangedEventHandler^ value)
					{
						m_progressChangedHandler = static_cast<ProgressChangedEventHandler^>(Delegate::Remove(m_progressChangedHandler, value));
					}
					void raise(Object^ sender, ProgressChangedEventArgs^ e)
					{
						if (m_progressChangedHandler != nullptr)
						{
							m_progressChangedHandler->Invoke(sender, e);
						}
					}
				}
				virtual event PropertyChangedEventHandler^ PropertyChanged
				{
					void add(PropertyChangedEventHandler^ value)
					{
						m_propChangedHandler = static_cast<PropertyChangedEventHandler^>(Delegate::Combine(m_propChangedHandler, value));
					}
					void remove(PropertyChangedEventHandler^ value)
					{
						m_propChangedHandler = static_cast<PropertyChangedEventHandler^> (Delegate::Remove(m_propChangedHandler, value));
					}
					void raise(Object^ sender, PropertyChangedEventArgs^ e)
					{
						if (m_propChangedHandler != nullptr)
						{
							m_propChangedHandler->Invoke(sender, e);
						}
					}
				}
				property int ProgressMax
				{
					int get()
					{
						return m_progressMax;
					}
					void set(int value)
					{
						if (m_progressMax == value)
							return;
						m_progressMax = value;
						OnPropertyChanged(gcnew String("ProgressMax"));
					}
				}
				property int Progress
				{
					int get()
					{
						return m_progress;
					}
				private:
					void set(int value)
					{
						if (m_progress == value)
							return;
						m_progress = value;
						OnProggresChanged();
						OnPropertyChanged(gcnew String("Progress"));
					}
				}
				property bool IsIncopliteOk
				{
					bool get()
					{
						return m_pCookie->incomplete_ok > 0;
					}
				private:
					void set(bool value)
					{
						if ((m_pCookie->incomplete_ok > 0) == value)
							return;
						m_pCookie->incomplete_ok = value ? 1 : 0;
						OnPropertyChanged(gcnew String("IsIncopliteOk"));
					}
				}

				property bool IsIncoplite
				{
					bool get()
					{
						return m_incomplete;
					}
				private:
					void set(bool value)
					{
						if (m_incomplete == value)
							return;
						m_incomplete = value;
						OnPropertyChanged(gcnew String("IsIncoplite"));
					}
				}

				
			private:
				void OnPropertyChanged(String^ info)
				{
					PropertyChanged(this, gcnew PropertyChangedEventArgs(info));
				}
				void OnProggresChanged()
				{
					if (m_progressMax != 0 && m_progressMax!= -1)
					{
						ProgressChanged(this, gcnew ProgressChangedEventArgs(m_progress * 100 / m_progressMax, nullptr));
					}
					else
					{
						ProgressChanged(this, gcnew ProgressChangedEventArgs(m_progress, nullptr));
					}
					
				}
				ProgressChangedEventHandler^ m_progressChangedHandler;
				PropertyChangedEventHandler^ m_propChangedHandler;
				CancellationToken m_pCancelationToken;
				DispatcherTimer^ m_pTickTimer;
				int m_progress;
				int m_progressMax; /* -1 for unknown */
				int m_errors;
				bool m_incompleteOk;
				bool m_incomplete;
				void OnTick(System::Object ^sender, System::EventArgs ^e);
			};
		}
	}
}
