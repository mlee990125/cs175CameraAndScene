#ifndef CONE_H
#define CONE_H

#include "Shape.h"

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};

	OBJ_TYPE getType() {
		return SHAPE_CONE;
	}

	void draw() {
    float radius = 0.5f;
    float height = 1.0f;
    float halfHeight = height / 2.0f;
    float angleStep = 2.0f * glm::pi<float>() / m_segmentsX;
    float heightStep = height / m_segmentsY;

    //  constants for normals
    float slantHeight = sqrt(radius * radius + height * height);
    float nx_const = height / slantHeight;
    float ny_const = radius / slantHeight;

    // side surface
    for (int i = 0; i < m_segmentsX; i++) {
        float theta = i * angleStep;
        float nextTheta = ((i + 1) % m_segmentsX) * angleStep;

        float cosTheta = cos(theta);
        float sinTheta = sin(theta);
        float cosNextTheta = cos(nextTheta);
        float sinNextTheta = sin(nextTheta);

        for (int j = 0; j < m_segmentsY; j++) {
     
            float y0 = -halfHeight + (j * heightStep);
            float y1 = y0 + heightStep;

            
            float r0 = radius * (1.0f - (float)j / m_segmentsY);
            float r1 = radius * (1.0f - (float)(j + 1) / m_segmentsY);

            
            float x0y0 = r0 * cosTheta;
            float z0y0 = r0 * sinTheta;
            float x1y0 = r0 * cosNextTheta;
            float z1y0 = r0 * sinNextTheta;

			
            float x0y1 = r1 * cosTheta;
            float z0y1 = r1 * sinTheta;
            float x1y1 = r1 * cosNextTheta;
            float z1y1 = r1 * sinNextTheta;

            // normals at current and next heights
            glm::vec3 normal0(nx_const * cosTheta, ny_const, nx_const * sinTheta);
            glm::vec3 normal1(nx_const * cosNextTheta, ny_const, nx_const * sinNextTheta);

            glBegin(GL_TRIANGLES);

            // First triangle
            glNormal3f(normal0.x, normal0.y, normal0.z);
            glVertex3f(x0y0, y0, z0y0);

            glNormal3f(normal0.x, normal0.y, normal0.z);
            glVertex3f(x0y1, y1, z0y1);

            glNormal3f(normal1.x, normal1.y, normal1.z);
            glVertex3f(x1y0, y0, z1y0);

            // Second triangle
            glNormal3f(normal0.x, normal0.y, normal0.z);
            glVertex3f(x0y1, y1, z0y1);

            glNormal3f(normal1.x, normal1.y, normal1.z);
            glVertex3f(x1y1, y1, z1y1);

            glNormal3f(normal1.x, normal1.y, normal1.z);
            glVertex3f(x1y0, y0, z1y0);

            glEnd();
        }
    }

    // Draw the base cap
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f); // Normal pointing down
    glVertex3f(0.0f, -halfHeight, 0.0f); // Center of the base
    for (int i = 0; i <= m_segmentsX; i++) {
        float theta = (i % m_segmentsX) * angleStep;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glNormal3f(0.0f, -1.0f, 0.0f); 
        glVertex3f(x, -halfHeight, z);
    }
    glEnd();
}


	void drawNormal() {
    float radius = 0.5f;
    float height = 1.0f;
    float halfHeight = height / 2.0f;
    float angleStep = 2.0f * glm::pi<float>() / m_segmentsX;
    float heightStep = height / m_segmentsY;
    float normalLength = 0.1f;

    // contants for the normals
    float slantHeight = sqrt(radius * radius + height * height);
    float nx_const = height / slantHeight;
    float ny_const = radius / slantHeight;

    // side normals
    for (int i = 0; i < m_segmentsX; i++) {
        float theta = i * angleStep;
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);

        for (int j = 0; j < m_segmentsY; j++) {
            
            float y = -halfHeight + (j * heightStep);

            
            float r = radius * (1.0f - (float)j / m_segmentsY);

            float x = r * cosTheta;
            float z = r * sinTheta;

            // Normal at this position
            glm::vec3 normal(nx_const * cosTheta, ny_const, nx_const * sinTheta);

           
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f); 
            glVertex3f(x, y, z);
            glm::vec3 normalEnd = glm::vec3(x, y, z) + normal * normalLength;
            glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
            glEnd();
        }
    }
	}
private:
};

#endif