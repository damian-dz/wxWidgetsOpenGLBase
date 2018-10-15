#include "Object.h"

#include <glew.h>

#include <iostream>

Object::Object() : m_pShader(new Shader)
{
    glGenVertexArrays(1, &m_vaoID);
    glGenBuffers(1, &m_vertexID);
    glGenBuffers(1, &m_index3ID);
}

Object::Object(const std::vector<Vertex> &vertices, const std::vector<Index3> &indices3)
    : m_vertices(vertices), m_indices3(indices3), m_pShader(new Shader)
{
    glGenBuffers(1, &m_vertexID);
    glGenBuffers(1, &m_index3ID);
}

Object::~Object()
{
    this->unbindAll();
    this->emptyAll();
    m_vertices.clear();
    m_indices3.clear();
    m_pShader->unbind();
    m_pShader->deleteProgram();
    delete m_pShader;
}

void Object::addVertex(const Vertex &vtx)
{
    m_vertices.push_back(vtx);
}

void Object::addIndex3(const Index3 &idx)
{
    m_indices3.push_back(idx);
}

void Object::bindAll()
{
    glBindVertexArray(m_vaoID);
    this->bindBuffers();
    m_pShader->bind();
}

void Object::bindBuffers()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index3ID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
}

void Object::draw()
{
    glDrawElements(GL_TRIANGLES, getByteSizeOfIndices3(), GL_UNSIGNED_INT, 0);
}

void Object::emptyAll()
{
    this->emptyBuffers();
    glDeleteVertexArrays(1, &m_vaoID);
}

void Object::emptyBuffers()
{
    glDeleteBuffers(1, &m_vertexID);
    glDeleteBuffers(1, &m_index3ID);
}

void Object::fillBuffers()
{
    glBufferData(GL_ARRAY_BUFFER, getByteSizeOfVertices(), m_vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getByteSizeOfIndices3(), m_indices3.data(), GL_STATIC_DRAW);
}

size_t Object::getIndex3Count()
{
    return m_indices3.size();
}

size_t Object::getVertexCount()
{
    return m_vertices.size();
}

size_t Object::getByteSizeOfIndices3()
{
    return m_indices3.size() * sizeof(Index3);
}

size_t Object::getByteSizeOfVertices()
{
    return m_vertices.size() * sizeof(Vertex);
}

uint32_t Object::getIndex3ID()
{
    return m_index3ID;
}

uint32_t Object::getVaoID()
{
    return m_vaoID;
}

uint32_t Object::getVertexID()
{
    return m_vertexID;
}

void Object::loadShaderFromFile(GLenum type, const std::string &filename)
{
    m_pShader->loadFromFile(type, filename);
}

void Object::createAndLinkShaderProgram()
{
    m_pShader->createAndLinkProgram();
}

void Object::setIndices3(const std::vector<Index3> &indices3)
{
    m_indices3.clear();
    m_indices3 = std::vector<Index3>(indices3);
}

void Object::setVertices(const std::vector<Vertex> &vertices)
{
    m_vertices.clear();
    m_vertices = std::vector<Vertex>(vertices);
}

void Object::unbindAll()
{
    this->unbindBuffers();
    glBindVertexArray(0);
    m_pShader->unbind();
}

void Object::unbindBuffers()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
