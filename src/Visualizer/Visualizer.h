/*
 * Visualizer.h
 *
 *  Created on: Jun 3, 2012
 *      Author: joe
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>

#include <iostream>

#include <SFML/Graphics.hpp>
#include <png.h>

#include "../mc/MarchingCubes.h"
#include "../MarchingCubesThread/MarchingCubesThread.h"

class Visualizer
{
	public:
		Visualizer(float, float);
		virtual ~Visualizer();

		//hud
		void updateHudStatus(std::string);

		void setMarchingCubesThread(MarchingCubesThread*);
		int saveScreenshot(char *file_name, unsigned int x, unsigned int y, unsigned long width, unsigned long height);

		void loop();

	private:
		void setup();
		void processInputEvents(const float);
		void processStackEvents(float);

		void setup3dLights();
		void draw3dScene();
		void draw3dAxis();
		void draw3dGrid();
		void draw3dPoints(int, int, int, int, int, int);
		void draw3dModel();

		//hud
		void drawHud();
		void drawHudStatus();

		std::string hud_status_string;
		sf::String* hud_status;

		//sfml primitives
		sf::VideoMode* video_mode;
		sf::Window* app;
		sf::Clock* clock;

		MarchingCubesThread* mc_thread;

		//array of triangles
		std::vector< GLfloat >* vertexes;
		GLfloat* vertexes_cache;

		float min_value;

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

		//flags
		bool flag_is_model_valid;
};

#endif /* VISUALIZER_H_ */
