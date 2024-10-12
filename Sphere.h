#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere() {};
	~Sphere() {};

	OBJ_TYPE getType() {
		return SHAPE_SPHERE;
	}

		void draw() {
    float radius = 0.5f;
    
    float thetaStep = 2.0f * glm::pi<float>() / m_segmentsX;
    float phiStep = glm::pi<float>() / m_segmentsY;

    vertices.clear();
	normals.clear();

    // generate vertiecs and normals
    for (int i = 0; i <= m_segmentsY; i++) {
        float phi = i * phiStep;
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);

        for (int j = 0; j <= m_segmentsX; j++) {
            float theta = j * thetaStep;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            float x = radius * sinPhi * cosTheta;
            float y = radius * cosPhi;
            float z = radius * sinPhi * sinTheta;

            glm::vec3 vertex(x, y, z);
            glm::vec3 normal = glm::normalize(vertex);

            vertices.push_back(vertex);
            normals.push_back(normal);
        }
    }

    // Draw triangles
    for (int i = 0; i < m_segmentsY; i++) {
        for (int j = 0; j < m_segmentsX; j++) {
            int first = (i * (m_segmentsX + 1)) + j;
            int second = first + m_segmentsX + 1;

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

 
   
    glColor3f(1.0f, 0.0f, 0.0f); 

    for (size_t i = 0; i < vertices.size(); i++) {
        glm::vec3 vertex = vertices[i];
        glm::vec3 normal = normals[i];

      
        glBegin(GL_LINES);
        glVertex3f(vertex.x, vertex.y, vertex.z);
        glVertex3f(vertex.x + normal.x * normalLength,
                   vertex.y + normal.y * normalLength,
                   vertex.z + normal.z * normalLength);
        glEnd();
    }


   
}


private:
	std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};

#endif