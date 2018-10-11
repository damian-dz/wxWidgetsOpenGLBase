#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "Vertex.h"

#include <vector>

class Object
{
public:
    Object();
    Object(const std::vector<Vertex> &vertices, const std::vector<Index3> &indices3);
    ~Object();

private:
    std::vector<Vertex> m_vertices;
    std::vector<Index3> m_indices3;
    uint32_t m_vertexID;
    uint32_t m_index3ID;
    uint32_t m_vaoID;

public:
    void addVertex(const Vertex &vtx);
    void addIndex3(const Index3 &idx);
    void bindAll();
    void bindBuffers();
    void draw();
    size_t getIndex3Count();
    size_t getVertexCount();
    size_t getByteSizeOfIndices3();
    size_t getByteSizeOfVertices();
    uint32_t getIndex3ID();
    uint32_t getVaoID();
    uint32_t getVertexID();
    void emptyAll();
    void emptyBuffers();
    void fillBuffers();
    void setIndices3(const std::vector<Index3> &indices3);
    void setVertices(const std::vector<Vertex> &vertices);
    void unbindAll();
    void unbindBuffers();

    Vertex *vertexData();
    Index3 *index3Data();
};

#endif // !OBJECT_H
