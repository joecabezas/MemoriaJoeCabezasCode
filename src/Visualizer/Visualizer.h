/*
 * Visualizer.h
 *
 *  Created on: Jun 3, 2012
 *      Author: joe
 */

#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include <SFML/Window.hpp>

class Visualizer
{
	public:
		Visualizer(unsigned int, unsigned int);
		virtual ~Visualizer();

		sf::Window app;

	private:
		void setup();
		void loop();
		void processInputEvents();
		void processStackEvents();

		sf::VideoMode video_mode;
		sf::Clock clock;
		unsigned int res_x;
		unsigned int res_y;

		int axis_x = 0;
		int axis_y = 0;
		int axis_u = 0;
		int axis_v = 0;
		int axis_r = 0;
		int axis_z = 0;
};

#endif /* VISUALIZER_H_ */
