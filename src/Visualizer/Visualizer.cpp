/*
 * Visualizer.cpp
 *
 *  Created on: Jun 3, 2012
 *      Author: joe
 */

#include "Visualizer.h"

Visualizer::Visualizer(
	unsigned int percentual_width = 75,
	unsigned int percentual_height = 75
)
{
	this->res_x = sf::VideoMode::GetMode(0).Width * percentual_width;
	this->res_y = sf::VideoMode::GetMode(0).Width * percentual_height;

	this->setup();
	this->loop();
}

Visualizer::~Visualizer() {
	// TODO Auto-generated destructor stub
}

void Visualizer::setup()
{
//	//video mode
//	this->video_mode = new sf::VideoMode(this->res_x, this->res_y, 32);
//
//	//window
//	this->app = new sf::Window(
//		this->video_mode,
//		"OpenGL xbox cam [Joe]",
//		sf::Style::Titlebar | sf::Style::Close// | sf::Style::Fullscreen
//	);
//	this->app.SetFramerateLimit(60);
//
//	// Set color and depth clear value
//	//glClearDepth(1.f);
//	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
//
//	//clock
//	this->clock = new sf::Clock();
}

void Visualizer::loop()
{
	float elapsed_time = 0;

	while (this->app.IsOpened())
	{
		elapsed_time = this->clock.GetElapsedTime();
		this->clock.Reset();

		this->processInputEvents();
		this->processStackEvents();

		// Set the active window before using OpenGL commands
		// It's useless here because active window is always the same,
		// but don't forget it if you use multiple windows or controls
		this->app.SetActive();

		//modelview
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

void Visualizer::processInputEvents()
{
	//input reference for real time events
	const sf::Input& Input = this->app.GetInput();

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

//	camera_angle_velocity = axis_u * 0.01f * 270;
//
//	//calculo velocidad angular
//	camera_azimut = axis_v * 0.01f * 90.f;
//	camera_angle = camera_angle + camera_angle_velocity * elapsed_time;
//
//	//calculo velocidad
//	// v_x = v_x0 +a_xt
//	camera_velocity[0] = axis_y * 0.01f * sin(camera_angle * 3.14159265/180);
//	camera_velocity[1] = axis_y * -0.01f * cos(camera_angle * 3.14159265/180);
//	camera_velocity[2] = axis_y * -0.01f * sin(camera_azimut * 3.14159265/180);
//
//	//strafe
//	camera_velocity_strafe[0] = axis_x * -0.01f * cos(camera_angle * 3.14159265/180);
//	camera_velocity_strafe[1] = axis_x * -0.01f * sin(camera_angle * 3.14159265/180);
//	camera_velocity_strafe[2] = axis_r * -0.01f - axis_z * -0.01f;
//
//	//calculo posicion
//	//p_x = p_x + v_x * t + 1/2 a_x*t^2
//	camera_position[0] = camera_position[0] + camera_velocity[0] * 5.f * elapsed_time;
//	camera_position[1] = camera_position[1] + camera_velocity[1] * 5.f * elapsed_time;
//	camera_position[2] = camera_position[2] + camera_velocity[2] * 5.f * elapsed_time;
//	//strafe
//	camera_position[0] = camera_position[0] + camera_velocity_strafe[0] * 5.f * elapsed_time;
//	camera_position[1] = camera_position[1] + camera_velocity_strafe[1] * 5.f * elapsed_time;
//	camera_position[2] = camera_position[2] + camera_velocity_strafe[2] * 5.f * elapsed_time;
}

void Visualizer::processStackEvents()
{
	sf::Event Event;
	while (this->app.GetEvent(Event))
	{
		switch(Event.Type)
		{
			case sf::Event::Closed:
				this->app.Close();
				break;

			case sf::Event::KeyPressed:
				if(Event.Key.Code == sf::Key::Escape)
					this->app.Close();
				break;

			case sf::Event::Resized:
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
				break;

			default:
				break;
		}
	}
}
