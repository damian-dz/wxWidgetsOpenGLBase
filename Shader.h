#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glew.h>

#include <fstream> 
#include <iostream>
#include <map>
#include <string>

class Shader
{
public:
    Shader();
    Shader(const std::string &filename);
    ~Shader();

    void loadFromString(GLenum type, const std::string &source);
    void loadFromFile(GLenum type, const std::string &filename);
    void loadFromFile(const std::string &filename);
    void createAndLinkProgram();
    void bind();
    void unbind();
    void addAttribute(const std::string &attribute);
    void addUniform(const std::string &uniform);
    void setUniformMat4f(const std::string &name, float *data, bool transpose = false);
    GLuint getProgramID();
    void deleteProgram();

    GLuint operator[](const std::string &attribute);
    GLuint operator()(const std::string &uniform);

private:
    enum ShaderType { NONE = -1, VERTEX_SHADER = 0, FRAGMENT_SHADER = 1, GEOMETRY_SHADER = 2 };

    GLuint m_program;
    int m_totalShaders;
    GLuint m_shaders[3];
    std::map<std::string, GLuint> m_attributeList;
    std::map<std::string, GLuint> m_uniformLocationList;

    void initializeShader();
};

#endif // !SHADER_H