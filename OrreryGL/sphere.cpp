#include "sphere.h"

SolidSphere::SolidSphere()
{

}

SolidSphere::SolidSphere(float radius, unsigned int rings, unsigned int sectors)		//Create the planet spheare with normals.
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	vertices.resize(rings * sectors * 3);
	normals.resize(rings * sectors * 3);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		float const y = sin(-M_PI_2 + M_PI * r * R);
		float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

		*v++ = x * radius;
		*v++ = y * radius;
		*v++ = z * radius;

		*n++ = x;
		*n++ = y;
		*n++ = z;
	}

	indices.resize(rings * sectors * 4);
	std::vector<GLushort>::iterator i = indices.begin();
	for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s + 1);
		*i++ = (r + 1) * sectors + (s + 1);
		*i++ = (r + 1) * sectors + s;
	}
}

SolidSphere::~SolidSphere()
{

}

void SolidSphere::Draw(GLfloat x, GLfloat y, GLfloat z, GLfloat ax, GLfloat ay, GLfloat az, GLfloat colour[], GLfloat theta, GLfloat scale)
{

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(colour[0], colour[1], colour [2]);
	glTranslatef(x, y, z);
	glRotatef(ax, 1.0, 0.0, 0.0);
	AxisRotation(theta);							//Compute rotation on planet axis
	glScalef(scale, scale, scale);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);

	glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glPopMatrix();
}

void SolidSphere::AxisRotation(GLfloat theta)
{
	GLfloat x = 0.0f;				//Set the 'up' vector.
	GLfloat y = 1.0f;
	GLfloat z = 0.0f;

	GLfloat n = sqrt(x*x + y*y + z*z);	//normalise vector so that x^2 + y^2 + z^2 = 1
	if (n != 1) {
		GLfloat nN = 1 / n;
		x *= nN;
		y *= nN;
		z *= nN;
	}


	GLfloat mat[4][4]					//Create the rotation matrix using the upvector and theta.
		=
	{
		{ pow(x, 2) + ((pow(y, 2) + pow(z, 2)) * cos(theta)), ((x * y) * (1.0f - cos(theta))) - (z * sin(theta)), ((x * z) * (1.0f - cos(theta))) + (y * sin(theta)), 0 },
		{ ((x * y) * (1.0f - cos(theta))) + (z * sin(theta)), pow(y, 2) + ((pow(x, 2) + pow(z, 2)) * cos(theta)), ((y * z) * (1.0f - cos(theta))) - (x * sin(theta)), 0 },
		{ ((x * z) * (1.0f - cos(theta))) - (y * sin(theta)), ((y * z) * (1.0f - cos(theta))) + (x * sin(theta)), pow(z, 2) + ((pow(x, 2) + pow(y, 2)) * cos(theta)), 0 },
		{ 0, 0, 0, 1 }
	};
	glMultMatrixf(*mat);				//Times by the current matrix.
}