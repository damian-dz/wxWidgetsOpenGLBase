#include "App.h"

extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

void openDebuggingWindow()
{
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
    printf("Debugging Window:\n");
}

bool OpenGLApp::OnInit()
{
    openDebuggingWindow();
    prepareMainFrame();
    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(OpenGLApp::OnIdle));
    return true;
}

void OpenGLApp::OnIdle(wxIdleEvent &evt)
{
    if (!m_pFrame->IsIconized()) {
        m_pFrame->updateGLPane();
        evt.RequestMore();
    }
}

void OpenGLApp::prepareMainFrame()
{   
    m_pFrame = new MainFrame(NULL, -1, wxT("OpenGL Test"));   
    m_pFrame->Show();
}

IMPLEMENT_APP(OpenGLApp);
