/*
 * Visualizer.h
 *
 *  Created on: Jun 3, 2012
 *      Author: joe
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include <SFML/Graphics.hpp>

class Visualizer : public sf::Thread
{
	public:
		Visualizer(float, float);
		virtual ~Visualizer();

		//hud
		void updateHudStatus(std::string);

	private:
		void setup();
		void loop();
		void processInputEvents();
		void processStackEvents();

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

		//overrides
		virtual void Run();
};

#endif /* VISUALIZER_H_ */
