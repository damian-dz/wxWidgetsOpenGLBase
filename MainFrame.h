#pragma once

#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include "GLPane.h"

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow *parent, wxWindowID id, const wxString &title);
    ~MainFrame();

    void updateGLPane();

private:
    wxMenuBar *m_pMenuBar;
    wxMenu *m_pFileMenu;
    GLPane *m_pGlPane;;

    void prepareGLPane();
    void prepareMenus();
    void setFrameDimensions();

    void OnQuit(wxCommandEvent &evt);
};

#endif // !MAIN_FRAME_H
