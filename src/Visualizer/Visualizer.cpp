/*
 * Visualizer.cpp
 *
 *  Created on: Jun 3, 2012
 *      Author: joe
 */

#include "Visualizer.h"

Visualizer::Visualizer(
	float percentual_width,
	float percentual_height
)
{
	this->res_x = sf::VideoMode::GetMode(0).Width * percentual_width;
	this->res_y = sf::VideoMode::GetMode(0).Height * percentual_height;

	this->setup();
}

//void Visualizer::Run()
//{
//	this->loop();
//}

Visualizer::~Visualizer() {
	// TODO Auto-generated destructor stub
}

void Visualizer::setup()
{
	//initial camera values
	camera_position[0] = 0.f;
	camera_position[1] = 0.f;
	camera_position[2] = 0.f;

	camera_velocity[0] = 0.f;
	camera_velocity[1] = 0.f;
	camera_velocity[2] = 0.f;

	camera_angle = 0.f;
	camera_angle_velocity = 0.f;
	camera_azimut = 0.f;

	camera_velocity_strafe[0] = 0.f;
	camera_velocity_strafe[1] = 0.f;
	camera_velocity_strafe[2] = 0.f;

	// Set color and depth clear value
	//glClearDepth(1.f);
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	//clock
	this->clock = new sf::Clock();

	//hud
	this->hud_status_string = "";
	this->hud_status = new sf::String();

	//video mode
	this->video_mode = new sf::VideoMode(this->res_x, this->res_y, 32);

	//window
	this->app = new sf::RenderWindow(
		*(this->video_mode),
		"OpenGL xbox cam [Joe]",
		sf::Style::Titlebar | sf::Style::Close// | sf::Style::Fullscreen
	);

	this->app->SetFramerateLimit(60);
}

static GLint vertices[] =
			{
				0,0,0,
				0,0,1,
				0,1,0,
				0,1,1,
				1,0,0,
				1,0,1,
				1,1,0,
				1,1,1,
			};

void Visualizer::loop()
{
	float elapsed_time = 0;

	std::cout << "exc 2" << std::endl;
	while (this->app->IsOpened())
	{
		elapsed_time = this->clock->GetElapsedTime();
		this->clock->Reset();

		std::cout << "exc 0" << std::endl;
		this->processInputEvents(elapsed_time);
		std::cout << "exc 1" << std::endl;
		this->processStackEvents(elapsed_time);

		// Set the active window before using OpenGL commands
		// It's useless here because active window is always the same,
		// but don't forget it if you use multiple windows or controls
		this->app->SetActive();

		//clear 2d graphics
		//this->app->Clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//modelview
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//draw using vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_INT, 0, vertices);
			glBegin(GL_QUAD_STRIP);
				for (unsigned int i = 0; i < 8; i++)
				{
					glArrayElement(i);
				}
			glEnd();
		glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays

		//draw 3d Scene
		this->draw3dScene();

		//draw 3d model
		this->draw3dModel();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(-50, 50, -50, 50, -50, 50);
		gluPerspective(
			90.f,
			float(sf::VideoMode::GetMode(0).Width)/float(sf::VideoMode::GetMode(0).Height),
			0.f, -500.f
		);
		//set camera
		glRotatef(camera_azimut, 1.f, 0.f, 0.f);
		glRotatef(camera_angle, 0.f, 1.f, 0.f);
		glTranslatef(camera_position[0], camera_position[2], camera_position[1]);

		//printf("caz: %f | ca: %f | cp: %f\n", camera_azimut, camera_angle, camera_position[0]);

		//draw Hud (User Interface)
		//this->drawHud();

		// Finally, display rendered frame on screen
		this->app->Display();
	}
}

void Visualizer::processInputEvents(const float elapsed_time)
{
	std::cout << "exc 3" << std::endl;
	//input reference for real time events
	const sf::Input& Input = this->app->GetInput();

	std::cout << "exc 4" << std::endl;

	//axis and dead zones
	axis_u = Input.GetJoystickAxis(0, sf::Joy::AxisU); if(abs(axis_u) < 15) axis_u = 0;
	axis_v = Input.GetJoystickAxis(0, sf::Joy::AxisV); if(abs(axis_v) < 15) axis_v = 0;
	axis_x = Input.GetJoystickAxis(0, sf::Joy::AxisX); if(abs(axis_x) < 15) axis_x = 0;
	axis_y = Input.GetJoystickAxis(0, sf::Joy::AxisY); if(abs(axis_y) < 15) axis_y = 0;
	axis_r = Input.GetJoystickAxis(0, sf::Joy::AxisR); if(abs(axis_r) < 15) axis_r = 0;
	axis_z = Input.GetJoystickAxis(0, sf::Joy::AxisZ); if(abs(axis_z) < 15) axis_z = 0;

	//escala a eje R y Z
	axis_r = (axis_r + 100) * 0.5f;
	axis_z = (axis_z + 100) * 0.5f;

	camera_angle_velocity = axis_u * 0.01f * 270;

	//calculo velocidad angular
	camera_azimut = axis_v * 0.01f * 90.f;
	camera_angle = camera_angle + camera_angle_velocity * elapsed_time;

	//calculo velocidad
	// v_x = v_x0 +a_xt

	std::cout << "exc 5" << std::endl;
	std::cout << camera_velocity[0] << std::endl;
	camera_velocity[0] = 0.1f;

	camera_velocity[0] = axis_y * 0.01f * sin(camera_angle * 3.14159265/180);
	camera_velocity[1] = axis_y * -0.01f * cos(camera_angle * 3.14159265/180);
	camera_velocity[2] = axis_y * -0.01f * sin(camera_azimut * 3.14159265/180);

	std::cout << "exc 5" << std::endl;

	//strafe
	camera_velocity_strafe[0] = axis_x * -0.01f * cos(camera_angle * 3.14159265/180);
	camera_velocity_strafe[1] = axis_x * -0.01f * sin(camera_angle * 3.14159265/180);
	camera_velocity_strafe[2] = axis_r * -0.01f - axis_z * -0.01f;

	//calculo posicion
	//p_x = p_x + v_x * t + 1/2 a_x*t^2
	camera_position[0] = camera_position[0] + camera_velocity[0] * 5.f * elapsed_time;
	camera_position[1] = camera_position[1] + camera_velocity[1] * 5.f * elapsed_time;
	camera_position[2] = camera_position[2] + camera_velocity[2] * 5.f * elapsed_time;
	//strafe
	camera_position[0] = camera_position[0] + camera_velocity_strafe[0] * 5.f * elapsed_time;
	camera_position[1] = camera_position[1] + camera_velocity_strafe[1] * 5.f * elapsed_time;
	camera_position[2] = camera_position[2] + camera_velocity_strafe[2] * 5.f * elapsed_time;
}

void Visualizer::processStackEvents(float elapsed_time)
{
	std::cout << "exc 7" << std::endl;

	sf::Event Event;
	while (this->app->GetEvent(Event))
	{
		switch(Event.Type)
		{
			case sf::Event::Closed:
				this->app->Close();
				break;

			case sf::Event::KeyPressed:
				if(Event.Key.Code == sf::Key::Escape)
					this->app->Close();
				break;

			case sf::Event::Resized:
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
				break;

			default:
				break;
		}
	}
}

void Visualizer::draw3dModel()
{
}

void Visualizer::draw3dScene()
{
	this->draw3dAxis();
	this->draw3dGrid(-3,3,-3,3,-3,3);
}

#define AXIS_SCALE 100000
void Visualizer::draw3dAxis(void)
{
	glPushMatrix ();

		//glTranslatef (-2.4, -1.5, -5);
		//glRotatef (0 , 1,0,0);
		//glRotatef (0, 0,1,0);
		glScalef (AXIS_SCALE,AXIS_SCALE,AXIS_SCALE);

		glLineWidth (1.0);

		glBegin (GL_LINES);
			glColor3f (1,0,0); // X axis is red.
			glVertex3f(0,0,0);
			glVertex3f(1,0,0);

			glColor3f(0,1,0); // Y axis is green.
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);

			glColor3f (0,0,1); // z axis is blue.
			glVertex3f(0,0,0);
			glVertex3f(0,0,1);
		glEnd();

	glPopMatrix ();
}

void Visualizer::draw3dGrid(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax)
{
	glPushMatrix ();

		//glScalef (AXIS_SCALE,AXIS_SCALE,AXIS_SCALE);

		glLineWidth (1.0);
		glPointSize(1.5);
		glColor3f(1,1,1);

		for(int i=xmin; i<=xmax; i++)
		{
			for(int j=ymin; j<=ymax; j++)
			{
				for(int k=zmin; k<=zmax; k++)
				{
					glBegin (GL_POINTS);
						//glColor3f (i,j,k);
						glVertex3i(i,j,k);
					glEnd();
				}
			}
		}

	glPopMatrix ();
}

void Visualizer::drawHud()
{
	this->drawHudStatus();
}

void Visualizer::updateHudStatus(std::string status)
{
	this->hud_status_string = status;
}

void Visualizer::drawHudStatus()
{
	this->hud_status->SetText(this->hud_status_string);
	this->hud_status->SetFont(sf::Font::GetDefaultFont());
	this->hud_status->SetSize(20);

	this->app->Draw(*(this->hud_status));
}

void Visualizer::setTriangles(vector_triangles)
{

}
