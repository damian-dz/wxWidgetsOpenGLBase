#include "Shader.h"

Shader::Shader() : m_totalShaders(0)
{
    for (int i = 0; i < 3; ++i) {
        m_shaders[i] = 0;
    }
    m_attributeList.clear();
    m_uniformLocationList.clear();
}

Shader::~Shader()
{
    m_attributeList.clear();
    m_uniformLocationList.clear();
}

void Shader::loadFromString(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char *pSource = source.c_str();
    glShaderSource(shader, 1, &pSource, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        std::cerr << "Compile log: " << infoLog << std::endl;
        delete[] infoLog;
    }
    m_shaders[m_totalShaders++] = shader;
}

void Shader::loadFromFile(GLenum type, const std::string &filename)
{
    std::ifstream file;
    file.open(filename.c_str(), std::ios_base::in);
    if (file) {
        std::string line, buffer;
        while (getline(file, line)) {
            buffer += line;
            buffer += "\r\n";
        }
        loadFromString(type, buffer);
    } else {
        std::cerr << "Error loading the shader: " << filename << std::endl;
    }
}

void Shader::createAndLinkProgram()
{
    m_program = glCreateProgram();
    for (int i = 0; i < 3; ++i) {
        if (m_shaders[i] != 0) {
            glAttachShader(m_program, m_shaders[i]);
        }
    }
    glLinkProgram(m_program);
    GLint status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(m_program, infoLogLength, NULL, infoLog);
        std::cerr << "Link log: " << infoLog << std::endl;
        delete[] infoLog;
    }
    for (int i = 0; i < 3; ++i) {
        glDeleteShader(m_shaders[i]);
    }
}

void Shader::bind()
{
    glUseProgram(m_program);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::addAttribute(const std::string &attribute)
{
    m_attributeList[attribute] = glGetAttribLocation(m_program, attribute.c_str());
}

void Shader::addUniform(const std::string &uniform)
{
    m_uniformLocationList[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

void Shader::deleteProgram()
{
    glDeleteProgram(m_program);
}

GLuint Shader::operator[](const std::string &attribute)
{
    return m_attributeList[attribute];
}

GLuint Shader::operator()(const std::string &uniform)
{
    return m_uniformLocationList[uniform];
}