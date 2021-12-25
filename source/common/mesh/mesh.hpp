#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our
{

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            //DONE#TODO: Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc
            // store the number of elements to use with glDrawElements
            elementCount = elements.size();
            // Create a vertex array object
            // vertex array object stores all the "configurations" of the vertex buffer
            // stores things like how to read data inside the vertex buffer
            glGenVertexArrays(1, &VAO);

            // VAOs are bounded at setup time and when drawing the geometry
            // we create and bind the vao first, as any buffer or element array
            // created will be bound to this buffer which is what we want
            glBindVertexArray(VAO);
            
            // Create a vertex buffer object
            // vertex buffer is essentially just an array
            // its not that smart, it only has data with no clue what that data is
            glGenBuffers(1, &VBO);
            // Vertex and Element buffers are bound only when you need to update them
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
            
            // enable vertices (allows them to accept data)
            // then Specify the layout of the vertex data
            // if false data is already normalized
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, position));
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);

            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);

            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);

            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);

            // Create an element buffer object
            // element buffer contains data
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(elements[0]), elements.data(), GL_STATIC_DRAW);

            // since we are not using global VOAs
            // we don't need to call disableVertexAttribArray
            // as they are contained inside the voa

            // unbinding the buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        // this function should render the mesh
        void draw()
        {
            //DONE#TODO: Write this function
            // Bind the VAO
            // since the VAO is responsible for remembering which buffers (VBO & EBO) are bound
            // it has to be bounded here
            glBindVertexArray(VAO);

            // Draw the mesh
            // param 3 is type of data in element buffer
            // param 4 is the offset, we give it 0 and let OpenGL figure it out
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void *)0);
            // Unbind the VAO
            glBindVertexArray(0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {
            //DONE#TODO: Write this function

            // deleting buffers
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}