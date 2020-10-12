#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
	double x,y,z;
}Point;

bool drawAxes = true;
bool drawGrid = false;
bool drawRoad = false;
bool drawRay = true;
bool color = true;
bool drawLightRay = true;

int mousecounter = 0;
int unit=5;
int flag,check=0;

float quadAngle = 0;
float boxAngle = 0;
float lightAngle = 0;

float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;

float runcar = 0;
float tyreAngle = 0;

float x_boxScaleFactor = 1;
float y_boxScaleFactor = 1;
float z_boxScaleFactor = 1;
float x_boxScaleFactorwithtyre = 0;
float y_boxScaleFactorwithtyre = 0;
float z_boxScaleFactorwithtyre = 0;

float changecolor = 0;


Point pos, u, r, l;

void displayAxes()
{
	if(drawAxes)
	{
		glBegin(GL_LINES);
		{
		    glColor3f(1.0, 0, 0);

			glVertex3f( 700,0,0); // a point on pos x axis
			glVertex3f(-700,0,0); // a point on neg x axis

			glColor3f(0, 1.0, 0);

			glVertex3f(0,-700,0); // a point on pos y axis
			glVertex3f(0, 700,0); // a point on neg y axis

			glColor3f(0, 0, 1.0);

			glVertex3f(0,0, 700);  // a point on pos z axis
			glVertex3f(0,0,-700);   // a point on neg z axis
		}
		glEnd();
	}
}

void displayGrid()
{
	if(drawGrid)
	{
		glBegin(GL_LINES);
		{

            for(int i=-700; i<=700; i=i+50)
            {
                glColor3f(1.0, 0, 0);
                glVertex3f( 700,i,0); // a point on pos x axis
                glVertex3f(-700,i,0); // a point on neg x axis

                glColor3f(0, 1.0, 0);
                glVertex3f(i,-700,0); // a point on pos y axis
                glVertex3f(i, 700,0); // a point on neg y axis
            }
		}
		glEnd();
	}
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}

Point func_1(Point position, Point vec, int m)
{
    Point point;
    point.x = position.x + (m * vec.x);
    point.y = position.y + (m * vec.y);
    point.z = position.z + (m * vec.z);

    return point;
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '1': {
            Point l1 = func(l, r, -1);
            r = func(r, l, 1);
            l = l1;
            break;
		}
		case '2': {
            Point l1 = func(l, r, 1);
            r = func(r, l, -1);
            l = l1;
            break;
		}
		case '3': {
            Point u1 = func(u, l, -1);
            l = func(l, u, 1);
            u = u1;
            break;
        }
        case '4': {
            Point u1 = func(u, l, 1);
            l = func(l, u, -1);
            u = u1;
            break;
        }
        case '5': {
            Point r1 = func(r, u, -1);
            u = func(u, r, 1);
            r = r1;
            break;
        }
        case '6':{
            Point r1 = func(r, u, 1);
            u = func(u, r, -1);
            r = r1;
            break;
        }

        case '7':{
            if(runcar <=450)
            {
                runcar += 10;
                tyreAngle -= 10;
            }
            break;
        }
        case '8':{
            if(runcar >=-450)
            {
                runcar -= 10;
                tyreAngle += 10;
            }
            break;
        }
        case '9':{
            lightAngle += 10;
            break;
        }
        case '0':{
            lightAngle -= 10;
            break;
        }

        case 'a':{
            if(x_boxScaleFactor <= 2)
            {
                x_boxScaleFactor += 0.2;
                x_boxScaleFactorwithtyre += 10;
            }
            break;
        }
        case 'A':{
            if(x_boxScaleFactor <= 2)
            {
                x_boxScaleFactor += 0.2;
                x_boxScaleFactorwithtyre += 10;
            }
            break;
        }
        case 'b':{
            if(x_boxScaleFactor >= 0.1)
            {
                x_boxScaleFactor = x_boxScaleFactor - 0.2;
                x_boxScaleFactorwithtyre -= 10;
            }
            break;
        }
        case 'B':{
            if(x_boxScaleFactor >= 0.1)
            {
                x_boxScaleFactor = x_boxScaleFactor - 0.2;
                x_boxScaleFactorwithtyre -= 10;
            }
            break;
        }
        case 'c':{
            if(y_boxScaleFactor <= 2)
            {
                y_boxScaleFactor += 0.2;
                y_boxScaleFactorwithtyre += 30;
            }
            break;
        }
        case 'C':{
            if(y_boxScaleFactor <= 2)
            {
                y_boxScaleFactor += 0.2;
                y_boxScaleFactorwithtyre += 30;
            }
            break;
        }
        case 'd':{
            if(y_boxScaleFactor >= 0.1)
            {
                y_boxScaleFactor -= 0.2;
                y_boxScaleFactorwithtyre -= 30;
            }
            break;
        }
        case 'D':{
            if(y_boxScaleFactor >= 0)
            {
                y_boxScaleFactor -= 0.2;
                y_boxScaleFactorwithtyre -= 30;
            }
            break;
        }
        case 'e':{
            if(z_boxScaleFactor <= 2)
            {
                z_boxScaleFactor += 0.2;
                z_boxScaleFactorwithtyre += 4;
            }
            break;
        }
        case 'E':{
            if(z_boxScaleFactor <= 2)
            {
                z_boxScaleFactor += 0.2;
                z_boxScaleFactorwithtyre += 4;
            }
            break;
        }
        case 'f':{
            if(z_boxScaleFactor >= 0.1)
            {
                z_boxScaleFactor -= 0.2;
                z_boxScaleFactorwithtyre -= 4;
            }
            break;
        }
        case 'F':{
            if(z_boxScaleFactor >= 0.1)
            {
                z_boxScaleFactor -= 0.2;
                z_boxScaleFactorwithtyre -= 4;
            }
            break;
        }
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:
		    {
		        quadAngle += 5;
		        printf("Quad Angle %f\n", quadAngle);

		        pos= func_1(pos,l,-unit);

		        break;
		    }

		case GLUT_KEY_UP:
		    {
		        quadAngle -= 5;
		        printf("Quad Angle %f\n", quadAngle);

		        pos= func_1(pos,l,unit);

		        break;
		    }

		case GLUT_KEY_RIGHT:
		    {
		        boxAngle += 5;
		        printf("Box Angle %f\n", boxAngle);

		        pos= func_1(pos,r,unit);

		        break;
		    }

		case GLUT_KEY_LEFT:
		    {
		        boxAngle -= 5;
		        printf("Box Angle %f\n", boxAngle);

		        pos= func_1(pos,r,-unit);

		        break;
		    }

		case GLUT_KEY_PAGE_UP:
		    {
                pos= func_1(pos,u,unit);
                break;
		    }

		case GLUT_KEY_PAGE_DOWN:
		    {
		        pos= func_1(pos,u,-unit);
                break;
		    }

		case GLUT_KEY_HOME:
		    {
		        if(x_boxScaleFactor <= 2)
                {
                    x_boxScaleFactor += 0.2;
                    x_boxScaleFactorwithtyre += 10;
                }
                if(y_boxScaleFactor <= 2)
                {
                    y_boxScaleFactor += 0.2;
                    y_boxScaleFactorwithtyre += 30;
                }
                if(z_boxScaleFactor <= 2)
                {
                    z_boxScaleFactor += 0.2;
                    z_boxScaleFactorwithtyre += 4;
                }
		        break;
		    }

        case GLUT_KEY_END:
            {
                if(x_boxScaleFactor >= 0.1)
                {
                    x_boxScaleFactor = x_boxScaleFactor - 0.2;
                    x_boxScaleFactorwithtyre -= 10;
                }
                if(y_boxScaleFactor >= 0)
                {
                    y_boxScaleFactor -= 0.2;
                    y_boxScaleFactorwithtyre -= 30;
                }
                if(z_boxScaleFactor >= 0.1)
                {
                    z_boxScaleFactor -= 0.2;
                    z_boxScaleFactorwithtyre -= 4;
                }
                break;
            }

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
            {
                if(mousecounter%2 == 0)
                {
                    drawAxes = false;
                }
                else
                {
                    drawAxes = true;
                }

			}
			else if(state == GLUT_UP)
            {
                //drawAxes = true;
                mousecounter += 1;
            }
            break;
		default:
			break;
	}
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
        glVertex3f(0, -tyreRadius, 0);
        glVertex3f(0, tyreRadius, 0);


        glColor3f(1, 1, 1);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(0, -tyreRadius, 0);
        glVertex3f(0, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);
        glVertex3f(halfTyreWidth, 0, tyreRadius);
        glVertex3f(halfTyreWidth, 0, -tyreRadius);
        glVertex3f(0, 0, -tyreRadius);
        glVertex3f(0, 0, tyreRadius);

        glColor3f(1, 1, 1);
        glVertex3f(0, 0, -tyreRadius);
        glVertex3f(0, 0, tyreRadius);
        glVertex3f(-halfTyreWidth, 0, tyreRadius);
        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
    }
    glEnd();

    for(int i=0; i<tyreSlices; i++)
    {
        if(i%2 == 0){
            glColor3f(1, 1, 1);
        }else{
            glColor3f(1.0, 0, 0);
        }
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();
    }
}

void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    if(drawRoad)
    {
        float halfQuadWidth = quadWidth-20, halfQuadLength = quadLength;

        glBegin(GL_QUADS);
        {
            /**Main Road **/

            glColor3f(0.44, 0.44, 0.44);

            glVertex3f(halfQuadWidth, halfQuadLength, 0);
            glVertex3f(halfQuadWidth, -halfQuadLength, 0);
            glVertex3f(-halfQuadWidth, -halfQuadLength, 0);
            glVertex3f(-halfQuadWidth, halfQuadLength, 0);

            /** Side Road **/
            glColor3f(1, 1, 1);

            glVertex3f(quadWidth, quadLength, 0);
            glVertex3f(halfQuadWidth, halfQuadLength, 0);
            glVertex3f(halfQuadWidth, -halfQuadLength, 0);
            glVertex3f(quadWidth, -quadLength, 0);

            glColor3f(1, 1, 1);

            glVertex3f(-quadWidth, quadLength, 0);
            glVertex3f(-quadWidth, -quadLength, 0);
            glVertex3f(-halfQuadWidth, -halfQuadLength, 0);
            glVertex3f(-halfQuadWidth, halfQuadLength, 0);
        }
        glEnd();
    }

}

void displayheadlight(float quadLength, float quadWidth) // width along x axis, length along z axis
{
        float headlightWidth = quadWidth/10, headlightLength = quadLength/100;

        glBegin(GL_QUADS);
        {

            glColor3f(1, 1, 1);
            glVertex3f(headlightWidth, 0, headlightLength);
            glVertex3f(-headlightWidth, 0, headlightLength);
            glColor3f(1, 0, 0);
            glVertex3f(-headlightWidth, 0, -headlightLength);
            glVertex3f(headlightWidth, 0, -headlightLength);
        }
        glEnd();
}

void displayLightRay(float rayLength, float rayWidth, float rayhight) // width along x axis, length along z axis
{
    if(drawLightRay)
    {
        float halfrayLength = rayLength/2, halfrayWidth = rayWidth/2, halfrayhight= rayhight/2;

        float pointrayLength = rayLength * 4, pointrayWidth = halfrayWidth * 30, pointrayhight= halfrayhight-5;

        glBegin(GL_QUADS);
        {
            /** light Ground **/

            glColor3f(1, 0, 0);

            glVertex3f(halfrayLength, halfrayWidth, halfrayhight);
            glVertex3f(-halfrayLength, halfrayWidth, halfrayhight);
            glVertex3f(-halfrayLength, halfrayWidth, -halfrayhight);
            glVertex3f(halfrayLength, halfrayWidth, -halfrayhight);



            /**LIGHT RAY LEFT**/

            glColor3f(0.70, 0, 0);

            glVertex3f(halfrayLength, halfrayWidth, halfrayhight);
            glVertex3f(halfrayLength, halfrayWidth, pointrayhight);
            glVertex3f(pointrayLength, pointrayWidth, pointrayhight);
            glVertex3f(pointrayLength, pointrayWidth, halfrayhight);

            glVertex3f(halfrayLength, halfrayWidth, -2.5);
            glVertex3f(halfrayLength, halfrayWidth, 2.5);
            glVertex3f(pointrayLength, pointrayWidth, 2.5);
            glVertex3f(pointrayLength, pointrayWidth, -2.5);

            glVertex3f(halfrayLength, halfrayWidth, -pointrayhight);
            glVertex3f(halfrayLength, halfrayWidth, -halfrayhight);
            glVertex3f(pointrayLength, pointrayWidth, -halfrayhight);
            glVertex3f(pointrayLength, pointrayWidth, -pointrayhight);

            /** LIGHT RAY RIGHT **/

            glVertex3f(-halfrayLength, halfrayWidth, halfrayhight);
            glVertex3f(-halfrayLength, halfrayWidth, pointrayhight);
            glVertex3f(-pointrayLength, pointrayWidth, halfrayhight);
            glVertex3f(-pointrayLength, pointrayWidth, pointrayhight);

            glVertex3f(-halfrayLength, halfrayWidth, -2.5);
            glVertex3f(-halfrayLength, halfrayWidth, 2.5);
            glVertex3f(-pointrayLength, pointrayWidth, 2.5);
            glVertex3f(-pointrayLength, pointrayWidth, -2.5);

            glVertex3f(-halfrayLength, halfrayWidth, -pointrayhight);
            glVertex3f(-halfrayLength, halfrayWidth, -halfrayhight);
            glVertex3f(-pointrayLength, pointrayWidth, -halfrayhight);
            glVertex3f(-pointrayLength, pointrayWidth, -pointrayhight);

            /**LIGHT RAY UP**/

            glVertex3f(halfrayLength, halfrayWidth, halfrayhight);
            glVertex3f(pointrayhight, halfrayWidth, halfrayhight);
            glVertex3f(pointrayhight, pointrayWidth, pointrayLength);
            glVertex3f(halfrayLength, pointrayWidth, pointrayLength);

            glVertex3f(2.5, halfrayWidth, halfrayhight);
            glVertex3f(-2.5, halfrayWidth, halfrayhight);
            glVertex3f(-2.5, pointrayWidth, pointrayLength);
            glVertex3f(2.5, pointrayWidth, pointrayLength);

            glVertex3f(-halfrayLength, halfrayWidth, halfrayhight);
            glVertex3f(-pointrayhight, halfrayWidth, halfrayhight);
            glVertex3f(-pointrayhight, pointrayWidth, pointrayLength);
            glVertex3f(-halfrayLength, pointrayWidth, pointrayLength);

            /**LIGHT RAY BOTTOM**/

            glVertex3f(halfrayLength, halfrayWidth, -halfrayhight);
            glVertex3f(pointrayhight, halfrayWidth, -halfrayhight);
            glVertex3f(pointrayhight, pointrayWidth, -pointrayLength);
            glVertex3f(halfrayLength, pointrayWidth, -pointrayLength);

            glVertex3f(2.5, halfrayWidth, -halfrayhight);
            glVertex3f(-2.5, halfrayWidth, -halfrayhight);
            glVertex3f(-2.5, pointrayWidth, -pointrayLength);
            glVertex3f(2.5, pointrayWidth, -pointrayLength);

            glVertex3f(-halfrayLength, halfrayWidth, -halfrayhight);
            glVertex3f(-pointrayhight, halfrayWidth, -halfrayhight);
            glVertex3f(-pointrayhight, pointrayWidth, -pointrayLength);
            glVertex3f(-halfrayLength, pointrayWidth, -pointrayLength);


        }
        glEnd();
    }

}

void displayLightBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);



        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        // FONT & BACK
        glColor3f(0.24, 0.82, 0.98);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glColor3f(0, 0, 1);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        // LEFT & RIGHT
        glColor3f(0.03, 0.53, 0.66);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.66, 0.31, 0.60);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        // UP & DOWN
        glColor3f(0.45, 0.14, 0.086);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glColor3f(0.086, 0.66, 0.31);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.93, 0.8, 0.22);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displaysmallBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    float  halfBoxWidth1 = (boxWidth / 2)-45;

    glBegin(GL_QUADS);
    {
        // FONT & BACK
        glColor3f(1, 1, 1);
        glVertex3f(halfBoxLength, halfBoxWidth1, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth1, halfBoxHeight);
        glColor3f(0, 0, 1);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glColor3f(0.90, 0.45, 0.45);
        glVertex3f(halfBoxLength, -halfBoxWidth1, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth1, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        // LEFT & RIGHT
        glColor3f(0.24, 0.82, 0.98);
        glVertex3f(halfBoxLength, halfBoxWidth1, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth1, halfBoxHeight);

        glColor3f(1, 1, 0.11);
        glVertex3f(-halfBoxLength, halfBoxWidth1, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth1, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth1, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth1, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth1, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth1, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayholderBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        // FONT & BACK
        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        // LEFT & RIGHT
        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.66, 0.31, 0.60);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);


        // UP & DOWN
        glColor3f(1, 0, 0);
        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glColor3f(0.086, 0.66, 0.31);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.93, 0.8, 0.22);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayScene()
{
    //Primitive Object dimensions
    /** Road Length & Width**/
    float quadLength = 700, quadWidth = 120;

    float largeBoxLength = 100, largeBoxWidth = 450, largeBoxHeight = 20;
    float smallBoxLength = 100, smallBoxWidth = 300, smallBoxHeight = 60;
    float lightBoxLength = 10, lightBoxWidth = 10, lightBoxHeight = 70;
    float lightLength = 30, lightWidth = 30, lightHeight = 30;
    // Light Ray
    float lightrayLength = 32, lightrayWidth = 32, lightrayHeight = 30;

    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float tyreRadius = 20, tyreWidth = 10;

    float marginheight1 = largeBoxHeight/2, marginheight2 = smallBoxHeight/2, marginheight3 = lightBoxHeight/2;


    /** Principal Axes **/

    displayAxes();
    displayGrid();

    /**/

    /** Road **/
    displayQuad(quadLength, quadWidth);

    /** Headlight Left **/
    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(30, 226, 50);
    displayheadlight(quadLength, quadWidth);
    glPopMatrix();

    /** Headlight Right **/
    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(-30, 226, 50);
    displayheadlight(quadLength, quadWidth);
    glPopMatrix();


    /** Animate Function **/

    /** Bottom Box **/

    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(0, 0, 50);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    /** Uper Box**/

    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(0, 0, 50);
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displaysmallBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();

    /**Tyre 1**/
    glPushMatrix();
    glTranslatef(50+x_boxScaleFactorwithtyre, 150+y_boxScaleFactorwithtyre+runcar, 20+z_boxScaleFactorwithtyre); // places the tyre on top of both boxes
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    /**Tyre 2**/
    glPushMatrix();
    glTranslatef(50+x_boxScaleFactorwithtyre, -150-y_boxScaleFactorwithtyre+runcar, 20+z_boxScaleFactorwithtyre); // places the tyre on top of both boxes
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    /**Tyre 3**/
    glPushMatrix();
    glTranslatef(-50-x_boxScaleFactorwithtyre, 150+y_boxScaleFactorwithtyre+runcar, 20+z_boxScaleFactorwithtyre); // places the tyre on top of both boxes
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    /**Tyre 4**/
    glPushMatrix();
    glTranslatef(-50-x_boxScaleFactorwithtyre, -150-y_boxScaleFactorwithtyre+runcar, 20+z_boxScaleFactorwithtyre); // places the tyre on top of both boxes
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glRotatef(tyreAngle, 1, 0, 0);
    displayTyre(tyreRadius, tyreWidth); // tyre
    glPopMatrix();

    /** light holder **/
    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(0, 0, 80);
    glTranslatef(0, 0, marginheight1+marginheight2+marginheight3);
    displayholderBox(lightBoxLength, lightBoxWidth, lightBoxHeight); // large box
    glPopMatrix();

    /** light **/
    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(0, 0, 100);
    glTranslatef(0, 0, marginheight1+marginheight2+marginheight3+(lightHeight/2));
    glRotatef(lightAngle, 0, 0, 1);
    displayLightBox(lightLength, lightWidth, lightHeight); // large box
    glPopMatrix();

    /** light ray **/
    glPushMatrix();
    glTranslatef(0, runcar, 0);
    glScalef(x_boxScaleFactor, y_boxScaleFactor, z_boxScaleFactor);
    glTranslatef(0, 0, 100);
    glTranslatef(0, 0, marginheight1+marginheight2+marginheight3+(lightHeight/2));
    glRotatef(lightAngle, 0, 0, 1);
    displayLightRay(lightrayLength, lightrayWidth, lightrayHeight); // large box
    glPopMatrix();
}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(background, background, background, 0);	//sets background color

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

	glutSwapBuffers();
}

void animate()
{
    glutPostRedisplay();

}

void animate_t()
{
    if (check==1)
    {
        if (background <= 0)
            flag=0;
        else if (background >= 1)
            flag=1;

        if (background < 1 && flag != 1)
            background += 0.0002;

        else if (background > 0 && flag != 0)
            background -= 0.0002;
    }
	glutPostRedisplay();

}

void init(){
    //glClearColor(background, background, background, 0.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

	// to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu(int id)
{
    if(id == 6)
    {
        drawRoad = 1;
    }
    else if(id == 7)
    {
        drawRoad = 0;
    }
    else if(id == 8)
    {
        drawLightRay = 1;
    }
    else if(id == 9)
    {
        drawLightRay = 0;
    }
    else if(id == 10)
    {
        check=0;
    }
    else if(id == 11)
    {
        check=1;
        glutIdleFunc(animate_t);

    }
    else if(id == 12)
    {
        background = 1;
    }
    else if(id == 13)
    {
        background = 0;
    }
}

void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
    else if(id == 3)
    {
        drawGrid = true;
    }
    else if(id == 4)
    {
        drawGrid = false;
    }
    else if(id == 5)
    {
        x_boxScaleFactor = 1;
        y_boxScaleFactor = 1;
        z_boxScaleFactor = 1;
        x_boxScaleFactorwithtyre = 0;
        y_boxScaleFactorwithtyre = 0;
        z_boxScaleFactorwithtyre = 0;
    }
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	int subMenuNo1 = glutCreateMenu(subMenu);
    glutAddMenuEntry("Show", 6);
	glutAddMenuEntry("Hide", 7);

	int subMenuNo2 = glutCreateMenu(subMenu);
    glutAddMenuEntry("Turn On", 8);
	glutAddMenuEntry("Turn Off", 9);

	int subMenuNo3 = glutCreateMenu(subMenu);
	glutAddMenuEntry("Auto Transition off", 10);
	glutAddMenuEntry("Auto Transition On", 11);
    glutAddMenuEntry("White", 12);
	glutAddMenuEntry("Black", 13);

    glutCreateMenu(mainMenu);
	glutAddMenuEntry("Axes On", 1);
	glutAddMenuEntry("Axes Off", 2);

	glutAddMenuEntry("Grid On", 3);
	glutAddMenuEntry("Grid Off", 4);

	glutAddMenuEntry("Standard Dimension", 5);

	glutAddSubMenu("Road", subMenuNo1);
	glutAddSubMenu("Light", subMenuNo2);
	glutAddSubMenu("Background", subMenuNo3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();		//The main loop of OpenGL, this function never returns

	return 0;
}
