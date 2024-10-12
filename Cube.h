#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"
#include <iostream>

class Cube : public Shape
{
public:
	Cube() {};
	~Cube() {};

	OBJ_TYPE getType()
	{
		return SHAPE_CUBE;
	}

	void draw()
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.5f);
		drawSquare();
		glPopMatrix();

		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(0.0f, 0.0f, 0.5f);
		drawSquare();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.0f, 0.0f, 0.5f);
		drawSquare();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(0.0f, 0.0f, 0.5f);
		drawSquare();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 0.5f);
		drawSquare();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 0.5f);
		drawSquare();
		glPopMatrix();
	}

void drawNormal()
    {
        float normalLength = 0.1f;
        float startX = -0.5f;
        float startY = -0.5f;
        float startZ = -0.5f;
        float endX = 0.5f;
        float endY = 0.5f;
        float endZ = 0.5f;
        float deltaX = 1.0f / m_segmentsX;
        float deltaY = 1.0f / m_segmentsY;
        float deltaZ = 1.0f / m_segmentsX;  

        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); 

        for (int i = 0; i <= m_segmentsX; ++i)
        {
            for (int j = 0; j <= m_segmentsY; ++j)
            {
                float x = startX + i * deltaX;
                float y = startY + j * deltaY;

                glVertex3f(x, y, endZ);
                glVertex3f(x, y, endZ + normalLength);

                glVertex3f(x, y, startZ);
                glVertex3f(x, y, startZ - normalLength);
            }
        }

        for (int j = 0; j <= m_segmentsY; ++j)
        {
            for (int k = 0; k <= m_segmentsX; ++k)
            {
                float y = startY + j * deltaY;
                float z = startZ + k * deltaZ;

                glVertex3f(endX, y, z);
                glVertex3f(endX + normalLength, y, z);

                glVertex3f(startX, y, z);
                glVertex3f(startX - normalLength, y, z);
            }
        }

        for (int i = 0; i <= m_segmentsX; ++i)
        {
            for (int k = 0; k <= m_segmentsX; ++k)
            {
                float x = startX + i * deltaX;
                float z = startZ + k * deltaZ;

                glVertex3f(x, endY, z);
                glVertex3f(x, endY + normalLength, z);

                glVertex3f(x, startY, z);
                glVertex3f(x, startY - normalLength, z);
            }
        }

        glEnd();
    }


void drawNormalHelper(float nx, float ny, float nz)
    {
        float startX = -0.5f;
        float startY = -0.5f;
        float deltaX = 1.0f / m_segmentsX;
        float deltaY = 1.0f / m_segmentsY;
        
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); 
        for (int i = 0; i <= m_segmentsX; ++i)
        {
            for (int j = 0; j <= m_segmentsY; ++j)
            {
                float x = startX + i * deltaX;
                float y = startY + j * deltaY;
                float z = 0.0f;

                glVertex3f(x, y, z);
                glVertex3f(x + nx * 0.1f, y + ny * 0.1f, z + nz * 0.1f);
            }
        }
        glEnd();
    }

private:
	void drawSquare()
	{
		int segmentsX = m_segmentsX;
		int segmentsY = m_segmentsY;
		float startX = -0.5f;
		float startY = -0.5f;
		float deltaX = 1.0f / segmentsX;
		float deltaY = 1.0f / segmentsY;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < segmentsX; ++i)
		{
			for (int j = 0; j < segmentsY; ++j)
			{
				float x0 = startX + i * deltaX;
				float x1 = startX + (i + 1) * deltaX;
				float y0 = startY + j * deltaY;
				float y1 = startY + (j + 1) * deltaY;
				float z = 0.0f;

				glNormal3f(0.0f, 0.0f, 1.0f);

				glVertex3f(x0, y0, z);
				glVertex3f(x1, y0, z);
				glVertex3f(x1, y1, z);

				glVertex3f(x0, y0, z);
				glVertex3f(x1, y1, z);
				glVertex3f(x0, y1, z);
			}
		}
		glEnd();
	}

};

#endif