#pragma once

#ifndef GL_PANE_H
#define GL_PANE_H

#include "Shader.h"
#include "Object.h"

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <chrono>

class GLPane : public wxGLCanvas
{
public:
    GLPane(wxFrame *parent, int *args);
    virtual ~GLPane();

    int getWidth();
    int getHeight();

private:
    wxGLContext *m_pContext;
    Object *m_pObj;
    Shader *m_pShader;
    int m_frameCnt;
    std::chrono::time_point<std::chrono::system_clock> m_tStart;

    void prepareGLObjects();

    void render(wxPaintEvent &evt);
    void resized(wxSizeEvent &evt);

    void mouseMoved(wxMouseEvent &evt);
    void mouseDown(wxMouseEvent &evt);
    void mouseWheelMoved(wxMouseEvent &evt);
    void mouseReleased(wxMouseEvent &evt);
    void rightClick(wxMouseEvent &evt);
    void mouseLeftWindow(wxMouseEvent &evt);
    void keyPressed(wxKeyEvent &evt);
    void keyReleased(wxKeyEvent &evt);

    DECLARE_EVENT_TABLE()
};

#endif // !GL_PANE_H
