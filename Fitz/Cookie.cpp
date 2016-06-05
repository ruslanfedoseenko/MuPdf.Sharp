#include "Cookie.h"

MuPdf::Sharp::Fitz::Cookie::Cookie(CancellationToken token)
	: m_pCancelationToken(token)
	, m_pTickTimer(gcnew DispatcherTimer())
{
	m_pCookie = new fz_cookie;
	m_pTickTimer->Tick += gcnew System::EventHandler(this, &MuPdf::Sharp::Fitz::Cookie::OnTick);
	m_pTickTimer->Interval = TimeSpan::FromMilliseconds(700);
	m_pTickTimer->Start();
	
}

MuPdf::Sharp::Fitz::Cookie::Cookie(CancellationToken token, bool isIncopleteOk)
	: m_pCancelationToken(token)
	, m_pTickTimer(gcnew DispatcherTimer())
{
	m_pCookie = new fz_cookie;
	IsIncopliteOk = isIncopleteOk;
	m_pTickTimer->Tick += gcnew System::EventHandler(this, &MuPdf::Sharp::Fitz::Cookie::OnTick);
	m_pTickTimer->Interval = TimeSpan::FromMilliseconds(700);
	m_pTickTimer->Start();
	
}

MuPdf::Sharp::Fitz::Cookie::~Cookie()
{
	m_pTickTimer->Stop();
}

MuPdf::Sharp::Fitz::Cookie::!Cookie()
{
	delete m_pCookie;
}


void MuPdf::Sharp::Fitz::Cookie::OnTick(System::Object ^sender, System::EventArgs ^e)
{
	if (m_pCancelationToken.IsCancellationRequested && m_pCookie->abort != 1)
	{
		m_pCookie->abort = 1;
	}
	Progress = m_pCookie->progress;
	ProgressMax = m_pCookie->progress_max;
	IsIncoplite = m_pCookie->incomplete > 0;
}
