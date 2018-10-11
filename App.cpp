#include "App.h"
#include "MainFrame.h"

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
    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(OpenGLApp::onIdle));
    return true;
}

void OpenGLApp::onIdle(wxIdleEvent &evt)
{
    m_pFrame->updateGLPane();
    evt.RequestMore();
}

void OpenGLApp::prepareMainFrame()
{   
    m_pFrame = new MainFrame(NULL, -1, wxT("OpenGL Test"));   
    m_pFrame->Show();
}

IMPLEMENT_APP(OpenGLApp);
