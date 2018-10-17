#include "MainFrame.h"

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title) : 
    wxFrame(parent, id, title)
{
    setFrameDimensions();
    prepareGLPane();
    prepareMenus();
}

MainFrame::~MainFrame()
{
    delete m_pGlPane;
}

void MainFrame::prepareGLPane()
{
    int args[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0 };
    m_pGlPane = new GLPane((wxFrame *)this, args);
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_pGlPane, 1, wxEXPAND);
    SetSizer(sizer);
    SetAutoLayout(true);
}

void MainFrame::prepareMenus()
{
    m_pMenuBar = new wxMenuBar();
    m_pFileMenu = new wxMenu();
    m_pFileMenu->Append(wxID_EXIT, wxT("&Exit"));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnQuit));
    m_pMenuBar->Append(m_pFileMenu, wxT("&File"));
    SetMenuBar(m_pMenuBar);
}

void MainFrame::setFrameDimensions()
{
    int scrWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    int scrHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
    constexpr int frmWidth = 640;
    constexpr int frmHeight = 480 + 59;
    SetSize((scrWidth - frmWidth) / 2, (scrHeight - frmHeight) / 2, frmWidth, frmHeight);
}

void MainFrame::OnQuit(wxCommandEvent &evt)
{
    Close(true);
}

void MainFrame::updateGLPane()
{
    m_pGlPane->Refresh();
}
