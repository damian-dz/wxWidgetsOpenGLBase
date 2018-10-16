#include "GLPane.h"

#include <iomanip>

enum IdxMode
{
    BL2TR = 0, TL2BR = 1, ALTER = 2
};

void generatePoints(Vertex *vertices, GLfloat xMin, GLfloat xMax, GLfloat yMin, GLfloat yMax, int resX, int resY)
{
    GLfloat stepX = (xMax - xMin) / (resX - 1);
    GLfloat stepY = (yMax - yMin) / (resY - 1);
    for (int i = 0, y = 0; y < resY; ++y) {
        for (int x = 0; x < resX; ++x) {
            int j = y * resX + x;
            vertices[j].positions.x = xMin + stepX * x;
            vertices[j].positions.y = yMin + stepY * y;
        }
    }
}

void generateIndices(Index3 *indices, int resX, int resY, IdxMode mode)
{
    if (mode == IdxMode::BL2TR) {
        for (int i = 0, y = 0; y < resY - 1; ++y) {
            for (int x = 0; x < resX - 1; ++x) {
                int j = y * resX + x;
                indices[i].frst = j;
                indices[i].scnd = j + resX + 1;
                indices[i].thrd = j + resX;
                indices[i + 1].frst = j;
                indices[i + 1].scnd = j + 1;
                indices[i + 1].thrd = j + resX + 1;
                i += 2;
            }
        }
    } else if (mode == IdxMode::TL2BR) {
        for (int i = 0, y = 0; y < resY - 1; ++y) {
            for (int x = 0; x < resX - 1; ++x) {
                int j = y * resX + x;
                indices[i].frst = j;
                indices[i].scnd = j + 1;
                indices[i].thrd = j + resX;
                indices[i + 1].frst = j + 1;
                indices[i + 1].scnd = j + resX + 1;
                indices[i + 1].thrd = j + resX;
                i += 2;
            }
        }
    } else if (mode == IdxMode::ALTER) {
        for (int i = 0, y = 0; y < resY - 1; ++y) {
            for (int x = 0; x < resX - 1; ++x) {
                int j = y * resX + x;
                if ((!(x % 2) && !(y % 2)) || (x % 2) && (y % 2)) {
                    indices[i].frst = j;
                    indices[i].scnd = j + resX + 1;
                    indices[i].thrd = j + resX;
                    indices[i + 1].frst = j;
                    indices[i + 1].scnd = j + 1;
                    indices[i + 1].thrd = j + resX + 1;
                } else {
                    indices[i].frst = j;
                    indices[i].scnd = j + 1;
                    indices[i].thrd = j + resX;
                    indices[i + 1].frst = j + 1;
                    indices[i + 1].scnd = j + resX + 1;
                    indices[i + 1].thrd = j + resX;
                }
                i += 2;
            }
        }
    }
}

double estimateFPS(std::chrono::time_point<std::chrono::system_clock> &start, int &cnt)
{
    auto tEnd = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = tEnd - start;
    if (elapsedSeconds.count() >= 1.0) {
        start = std::chrono::system_clock::now();
        cnt = 0;
    }
    return cnt / elapsedSeconds.count();
}

GLPane::GLPane(wxFrame *parent, int *args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
    m_frameCnt(0),
    m_tStart(std::chrono::system_clock::now())
{
    m_pContext = new wxGLContext(this);
    wxGLCanvas::SetCurrent(*m_pContext);
    glewInit();

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

    prepareGLObjects();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    std::cout << std::fixed << std::setprecision(2);
}

GLPane::~GLPane()
{
    delete m_pContext;
    delete m_pObj;
}

void GLPane::resized(wxSizeEvent &WXUNUSED(evt))
{
    glViewport(0, 0, (GLsizei)getWidth(), (GLsizei)getHeight());
    Refresh();
}

int GLPane::getWidth()
{
    return GetSize().x;
}

int GLPane::getHeight()
{
    return GetSize().y;
}

void GLPane::prepareGLObjects()
{
    constexpr int WIDTH = 30;
    constexpr int HEIGHT = 40;
    std::vector<Vertex> vertices(HEIGHT * WIDTH);
    std::vector<Index3> indices3((HEIGHT - 1) * (WIDTH - 1) * 2);
    generatePoints(vertices.data(), -0.9, 0.9, -0.9, 0.9, WIDTH, HEIGHT);
    generateIndices(indices3.data(), WIDTH, HEIGHT, IdxMode::BL2TR);

    m_pObj = new Object(vertices, indices3);
    m_pObj->addShaderSlot();
    m_pObj->loadShaderFromFile("Basic.glsl");
    m_pObj->createAndLinkShaderProgram();
    m_pObj->bindAll();
    m_pObj->fillBuffers();
    m_pObj->unbindAll();  
}

void GLPane::render(wxPaintEvent &evt)
{
    if (IsShown()) {
        wxPaintDC(this);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_pObj->bindAll();
        m_pObj->draw();
        m_pObj->unbindAll();
        glFlush();
        SwapBuffers();
        m_frameCnt++;
        std::cout << '\r' << estimateFPS(m_tStart, m_frameCnt) << " FPS";     
    }
}

// empty mouse and key events
void GLPane::mouseMoved(wxMouseEvent &evt) { }
void GLPane::mouseDown(wxMouseEvent &evt) { }
void GLPane::mouseWheelMoved(wxMouseEvent &evt) { }
void GLPane::mouseReleased(wxMouseEvent &evt) { }
void GLPane::rightClick(wxMouseEvent &evt) { }
void GLPane::mouseLeftWindow(wxMouseEvent &evt) { }
void GLPane::keyPressed(wxKeyEvent &evt) { }
void GLPane::keyReleased(wxKeyEvent &evt) { }

BEGIN_EVENT_TABLE(GLPane, wxGLCanvas)
EVT_MOTION(GLPane::mouseMoved)
EVT_LEFT_DOWN(GLPane::mouseDown)
EVT_LEFT_UP(GLPane::mouseReleased)
EVT_RIGHT_DOWN(GLPane::rightClick)
EVT_LEAVE_WINDOW(GLPane::mouseLeftWindow)
EVT_SIZE(GLPane::resized)
EVT_KEY_DOWN(GLPane::keyPressed)
EVT_KEY_UP(GLPane::keyReleased)
EVT_MOUSEWHEEL(GLPane::mouseWheelMoved)
EVT_PAINT(GLPane::render)
END_EVENT_TABLE()
