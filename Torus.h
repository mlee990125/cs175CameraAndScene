#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class Torus : public Shape {
public:
    Torus() {};
    ~Torus() {};

    OBJ_TYPE getType() {
        return SHAPE_SPECIAL1;  
    }

    void draw() {
        float outerRadius = 0.5f;  
        float innerRadius = 0.2f;  

        int segmentsX = m_segmentsX; 
        int segmentsY = m_segmentsY;  
        
        float thetaStep = 2.0f * glm::pi<float>() / segmentsY;
        float phiStep = 2.0f * glm::pi<float>() / segmentsX;    

     
        vertices.clear();
        normals.clear();

        
        for (int i = 0; i <= m_segmentsY; ++i) {
            float theta = i * thetaStep;
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);

            for (int j = 0; j <= m_segmentsX; ++j) {
                float phi = j * phiStep;
                float cosPhi = cos(phi);
                float sinPhi = sin(phi);

             
                float x = (outerRadius + innerRadius * cosPhi) * cosTheta;
                float y = (outerRadius + innerRadius * cosPhi) * sinTheta;
                float z = innerRadius * sinPhi;

                glm::vec3 vertex(x, y, z);

               
                glm::vec3 center(outerRadius * cosTheta, outerRadius * sinTheta, 0.0f); 
                glm::vec3 normal = glm::normalize(vertex - center); 
                vertices.push_back(vertex);
                normals.push_back(normal);
            }
        }

    
       
        for (int i = 0; i < segmentsY; ++i) {
    for (int j = 0; j < segmentsX; ++j) {
        int first = (i * (segmentsX + 1)) + j;
        int second = first + segmentsX + 1;

        glBegin(GL_TRIANGLES);

        // First triangle
        glNormal3f(normals[first].x, normals[first].y, normals[first].z);
        glVertex3f(vertices[first].x, vertices[first].y, vertices[first].z);

        glNormal3f(normals[second].x, normals[second].y, normals[second].z);
        glVertex3f(vertices[second].x, vertices[second].y, vertices[second].z);

        glNormal3f(normals[first + 1].x, normals[first + 1].y, normals[first + 1].z);
        glVertex3f(vertices[first + 1].x, vertices[first + 1].y, vertices[first + 1].z);

        // Second triangle
        glNormal3f(normals[second].x, normals[second].y, normals[second].z);
        glVertex3f(vertices[second].x, vertices[second].y, vertices[second].z);

        glNormal3f(normals[second + 1].x, normals[second + 1].y, normals[second + 1].z);
        glVertex3f(vertices[second + 1].x, vertices[second + 1].y, vertices[second + 1].z);

        glNormal3f(normals[first + 1].x, normals[first + 1].y, normals[first + 1].z);
        glVertex3f(vertices[first + 1].x, vertices[first + 1].y, vertices[first + 1].z);
        
        glEnd();
    }
}

    }

    void drawNormal() {
        float normalLength = 0.1f; 

        
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 0.0f, 0.0f); 

        for (size_t i = 0; i < vertices.size(); ++i) {
            glm::vec3 vertex = vertices[i];
            glm::vec3 normal = normals[i];

            
            glBegin(GL_LINES);
            
            glVertex3f(vertex.x, vertex.y, vertex.z);
           
            glVertex3f(vertex.x + normal.x * normalLength,
                       vertex.y + normal.y * normalLength,
                       vertex.z + normal.z * normalLength);
            glEnd();
        }

       
        glEnable(GL_LIGHTING);
    }



private:
    std::vector<glm::vec3> vertices;  
    std::vector<glm::vec3> normals;   
};

#endif
