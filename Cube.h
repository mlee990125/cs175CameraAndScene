#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape {
public:
	Cube() {};
	~Cube() {};

	OBJ_TYPE getType() {
		return SHAPE_CUBE;
	}

	void draw() {
    float halfSize = 0.5f;
    float stepX = 1.0f / m_segmentsX;
    float stepY = 1.0f / m_segmentsY;

 

    for (int face = 0; face < 6; face++) {

   
        
        for (int i = 0; i < m_segmentsX; i++) {
            float x0 = -halfSize + i * stepX;
            float x1 = x0 + stepX;

            for (int j = 0; j < m_segmentsY; j++) {
                float y0 = -halfSize + j * stepY;
                float y1 = y0 + stepY;

                glBegin(GL_TRIANGLES);

             
                if (face == 0) { // Front face (+Z)
                    float z = halfSize;
                    // First bottom-left, bottom-right, top-right)
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glVertex3f(x0, y0, z);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glVertex3f(x1, y0, z);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glVertex3f(x1, y1, z);
                    // Second bottom-left, top-right, top-left)
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glVertex3f(x0, y0, z);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glVertex3f(x1, y1, z);
                    glNormal3f(0.0f, 0.0f, 1.0f);
                    glVertex3f(x0, y1, z);
                } else if (face == 1) { // Back face (-Z)
                    float z = -halfSize;
                   glNormal3f(0.0f, 0.0f, -1.0f);
                    glVertex3f(x1, y0, z);
                   glNormal3f(0.0f, 0.0f, -1.0f);
                    glVertex3f(x0, y0, z);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glVertex3f(x0, y1, z);
                   
                   glNormal3f(0.0f, 0.0f, -1.0f);
                    glVertex3f(x1, y0, z);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glVertex3f(x0, y1, z);
                    glNormal3f(0.0f, 0.0f, -1.0f);
                    glVertex3f(x1, y1, z);
                } else if (face == 2 || face == 3) {
                    glNormal3f(0.0f, (face == 2) ? 1.0f : -1.0f, 0.0f);
                    float y = (face == 2) ? halfSize : -halfSize;
               
                    glVertex3f(x0, y, y0);
                    glNormal3f(0.0f, (face == 2) ? 1.0f : -1.0f, 0.0f);
                    glVertex3f(x1, y, y0);
                    glNormal3f(0.0f, (face == 2) ? 1.0f : -1.0f, 0.0f);
                    glVertex3f(x1, y, y1);
                    glNormal3f(0.0f, (face == 2) ? 1.0f : -1.0f, 0.0f);
                    glVertex3f(x0, y, y0);
                    glNormal3f(0.0f, (face == 2) ? 1.0f : -1.0f, 0.0f);
                    glVertex3f(x1, y, y1);
                    glNormal3f(0.0f, (face == 2) ? 1.0f : -1.0f, 0.0f);
                    glVertex3f(x0, y, y1);
                } else if (face == 4 || face == 5) { 
                    glNormal3f((face == 4) ? 1.0f : -1.0f, 0.0f, 0.0f);
                    float x = (face == 4) ? halfSize : -halfSize;
                    // First triangle
                    glVertex3f(x, y0, x0);
                    glNormal3f((face == 4) ? 1.0f : -1.0f, 0.0f, 0.0f);
                    glVertex3f(x, y0, x1);
                    glNormal3f((face == 4) ? 1.0f : -1.0f, 0.0f, 0.0f);
                    glVertex3f(x, y1, x1);
                    // Second triangle
                    glNormal3f((face == 4) ? 1.0f : -1.0f, 0.0f, 0.0f);
                    glVertex3f(x, y0, x0);
                    glNormal3f((face == 4) ? 1.0f : -1.0f, 0.0f, 0.0f);
                    glVertex3f(x, y1, x1);
                    glNormal3f((face == 4) ? 1.0f : -1.0f, 0.0f, 0.0f);
                    glVertex3f(x, y1, x0);
                }

                glEnd();
            }
        }
    }
}




	void drawNormal() {
		float halfSize = 0.5f;
		float stepX = 1.0f / m_segmentsX;
		float stepY = 1.0f / m_segmentsY;

		glm::vec3 normals[6] = {
        {0.0f, 0.0f, 1.0f},  // Front
        {0.0f, 0.0f, -1.0f}, // Back
        {0.0f, 1.0f, 0.0f},  // Top
        {0.0f, -1.0f, 0.0f}, // Bottom
        {1.0f, 0.0f, 0.0f},  // Right
        {-1.0f, 0.0f, 0.0f}  // Left
    };

		for(int face = 0; face <6; face++){
			glm::vec3 normal = normals[face];

			for(int i = 0; i<= m_segmentsX; i++){
				float s  = i / static_cast<float>(m_segmentsX);
				float x  = -halfSize + s;

				for(int j = 0; j <= m_segmentsY; j++){
					float t = j / static_cast<float>(m_segmentsY);
					float y = -halfSize + t;
				
				glm::vec3 position;
				
				if (face ==0 ){
					position = glm :: vec3(x,y,halfSize);

				} else if (face == 1){
					position = glm::vec3(x,y,-halfSize);


				}else if (face ==2){
					position = glm::vec3(x,halfSize,y);

					
				}else if (face==3){
					position = glm::vec3(x,-halfSize,y);
				}else if (face ==4){
					position = glm::vec3(halfSize,y,x);
				}
				else if (face == 5) { 
                    position = glm::vec3(-halfSize, y, x);
                }
				glBegin(GL_LINES);
                glColor3f(1.0f, 0.0f, 0.0f); 
                glVertex3f(position.x, position.y, position.z);
                glm::vec3 normalEnd = position + (normal * 0.1f); 
                glVertex3f(normalEnd.x, normalEnd.y, normalEnd.z);
                glEnd();

				}

			}		

	}

	}

	

private:
};

#endif