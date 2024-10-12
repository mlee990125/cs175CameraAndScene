#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape {
public:
	Cylinder() {};
	~Cylinder() {};

	OBJ_TYPE getType() {
		return SHAPE_CYLINDER;
	}


	void draw() {
        float radius = 0.5f;
        float height = 1.0f;

		float halfHeight = height / 2.0f;
    float angleStep = 2.0f * glm::pi<float>() / m_segmentsX;
    float heightStep = height / m_segmentsY;

    // Tessellate the side surface
    for (int i = 0; i < m_segmentsX; i++) {
        float angle = i * angleStep;
        float next_angle = (i + 1) * angleStep;

        float x0 = radius * cos(angle);
        float z0 = radius * sin(angle);
        float x1 = radius * cos(next_angle);
        float z1 = radius * sin(next_angle);

       for (int j = 0; j < m_segmentsY; j++) {
    float y0 = -halfHeight + j * heightStep;
    float y1 = y0 + heightStep;

 

   
glBegin(GL_TRIANGLES);

// First triangle
glNormal3f(cos(angle), 0.0f, sin(angle));  
glVertex3f(x0, y0, z0);  
glNormal3f(cos(next_angle), 0.0f, sin(next_angle));  
glVertex3f(x1, y0, z1);  
glNormal3f(cos(angle), 0.0f, sin(angle));  
glVertex3f(x0, y1, z0);  
// Second triangle
glNormal3f(cos(next_angle), 0.0f, sin(next_angle));  
glVertex3f(x1, y0, z1);  // Bottom-right
glNormal3f(cos(next_angle), 0.0f, sin(next_angle));  
glVertex3f(x1, y1, z1);  
glNormal3f(cos(angle), 0.0f, sin(angle));  
glVertex3f(x0, y1, z0);  

glEnd();

}

    }

    
    glBegin(GL_TRIANGLE_FAN);
glNormal3f(0.0f, 1.0f, 0.0f); 
glVertex3f(0.0f, halfHeight, 0.0f); 
for (int i = 0; i <= m_segmentsX; i++) {
    float angle = i * angleStep;
    float x = radius * cos(angle);
    float z = radius * sin(angle);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x, halfHeight, z); 
}
glEnd();


    
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -halfHeight, 0.0f);
    for (int i = 0; i <= m_segmentsX; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(x, -halfHeight, z); 
    }
    glEnd();

	};

	void drawNormal() {
    float radius = 0.5f;
    float height = 1.0f;
    float halfHeight = height / 2.0f;

    float angleStep = 2.0f * glm::pi<float>() / m_segmentsX;
    float heightStep = height / m_segmentsY;

    float normalLength = 0.1f; 

    // normals on the sides of the cylinder
    for (int i = 0; i <= m_segmentsX; i++) { 
        float theta = i * angleStep;
        float cosTheta = cos(theta);
        float sinTheta = sin(theta);
        glm::vec3 normal(cosTheta, 0.0f, sinTheta);

        for (int j = 0; j <= m_segmentsY; j++) {
            float y = -halfHeight + j * heightStep;
            glm::vec3 position(radius * cosTheta, y, radius * sinTheta);

            
            glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f); 
            glVertex3f(position.x, position.y, position.z);
            glm::vec3 normalEnd = position + normal * normalLength;
            glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
            glEnd();
        }
    }
	 	{glm::vec3 position(0.0f, halfHeight, 0.0f);
        glm::vec3 normal(0.0f, 1.0f, 0.0f);

        
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(position.x, position.y, position.z);
        glm::vec3 normalEnd = position + normal * normalLength;
        glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
        glEnd();
		}
	 	{glm::vec3 position(0.0f, -halfHeight, 0.0f);
		glm::vec3 normal(0.0f, -1.0f, 0.0f);

        
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(position.x, position.y, position.z);
        glm::vec3 normalEnd = position + normal * normalLength;
        glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
        glEnd();
		}
    // bottom cap
    for (int i = 0; i <= m_segmentsX; i++) {
        float theta = i * angleStep;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glm::vec3 position(x, -halfHeight, z);
        glm::vec3 normal(0.0f, -1.0f, 0.0f);

        //normal
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(position.x, position.y, position.z);
        glm::vec3 normalEnd = position + normal * normalLength;
        glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
        glEnd();
    }

    // top cap
    for (int i = 0; i <= m_segmentsX; i++) {
        float theta = i * angleStep;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glm::vec3 position(x, halfHeight, z);
        glm::vec3 normal(0.0f, 1.0f, 0.0f);

 
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); 
        glVertex3f(position.x, position.y, position.z);
        glm::vec3 normalEnd = position + normal * normalLength;
        glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
        glEnd();
    }
}



private:
};

#endif