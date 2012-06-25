/*
 * Visualizer.h
 *
 *  Created on: Jun 3, 2012
 *      Author: joe
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include <iostream>

#include <SFML/Graphics.hpp>

#include "../mc/MarchingCubes.h"

class Visualizer
{
	public:
		Visualizer(float, float);
		virtual ~Visualizer();

		//hud
		void updateHudStatus(std::string);

		//model
		void setTriangles(vector_triangles);

		void loop();

	private:
		void setup();
		void processInputEvents(const float);
		void processStackEvents(float);

		void draw3dScene();
		void draw3dAxis();
		void draw3dGrid(int, int, int, int, int, int);
		void draw3dModel();

		//hud
		void drawHud();
		void drawHudStatus();

		std::string hud_status_string;
		sf::String* hud_status;

		//sfml primitives
		sf::VideoMode* video_mode;
		sf::RenderWindow* app;
		sf::Clock* clock;

		//sf::Thread* thread_window;
		//sf::Thread* thread_marching_cubes;

		unsigned int res_x;
		unsigned int res_y;

		int axis_x;
		int axis_y;
		int axis_u;
		int axis_v;
		int axis_r;
		int axis_z;

		GLfloat camera_position[3];
		GLfloat camera_velocity[3];
		GLfloat camera_angle;
		GLfloat camera_angle_velocity;
		GLfloat camera_azimut;
		GLfloat camera_velocity_strafe[3];

		//overrides
		//virtual void Run();
};

#endif /* VISUALIZER_H_ */
