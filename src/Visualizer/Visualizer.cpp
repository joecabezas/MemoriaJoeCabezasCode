/*
 * Visualizer.cpp
 *
 *  Created on: Jun 3, 2012
 *	  Author: joe
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

Visualizer::~Visualizer()
{
}

void Visualizer::setMarchingCubesThread(MarchingCubesThread* mc_thread)
{
	this->mc_thread = mc_thread;
}

void Visualizer::setup()
{
	min_value = 0.4f;

	//initial camera values
	camera_position[0] = -5.f;
	camera_position[1] = -5.f;
	camera_position[2] = -2.f;

	camera_velocity[0] = 0.f;
	camera_velocity[1] = 0.f;
	camera_velocity[2] = 0.f;

	camera_angle = -45.f;
	camera_angle_velocity = 0.f;
	camera_azimut = 0.f;

	camera_velocity_strafe[0] = 0.f;
	camera_velocity_strafe[1] = 0.f;
	camera_velocity_strafe[2] = 0.f;

	model_rotation[0] = 0.f;
	model_rotation[1] = 0.f;
	model_rotation[2] = 0.f;

	//set initial flags
	this->flag_is_model_valid = false;

	//hud
	this->hud_status_string = "";
	this->hud_status = new sf::String();

	//video mode
	this->video_mode = new sf::VideoMode(this->res_x, this->res_y, 32);

	//title
	this->window_title = "OpenGL xbox cam [Joe]";

	//style
	this->window_style =
			//sf::Style::Fullscreen |
			sf::Style::Titlebar |
			sf::Style::Close;

	//window
	this->app = new sf::Window(
		*(this->video_mode),
		this->window_title, this->window_style
	);
	this->app->SetFramerateLimit(60);

	//clock
	this->clock = new sf::Clock();

	this->setupOpenGL();
}

void Visualizer::loop()
{
	float elapsed_time;

	while(this->app->IsOpened())
	{
		//MarchingCubesThread process
		if(!this->flag_is_model_valid)
		{
			this->updateHudStatus("Generating Marching Cubes...");
			this->vertexes = this->mc_thread->getTriangles(min_value);
			this->updateHudStatus("Marching Cubes Done");

//			for(unsigned int i=0; i < 3; i++)
//			{
//				printf("vertice %d: %f\n", i, *(this->vertexes)[i]);
//			}

			//this->vertexes_cache = this->vertexes->data();
			std::cout << "this->vertexes->size() = " << this->vertexes->size() << std::endl;
			//make model valid again
			this->flag_is_model_valid = true;
		}

		//Drawing process
		elapsed_time = this->clock->GetElapsedTime();
		this->clock->Reset();

		this->processInputEvents(elapsed_time);
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

		//draw 3d Scene
		this->draw3dScene();

		//draw 3d model
		this->draw3dModel();

//		glPushMatrix();
//			glTranslatef(5,5,5);
//			glutSolidSphere(2.0, 10, 10);
//		glPopMatrix();

//			glBegin(GL_TRIANGLES);
//
//				glColor3f(1.f, 1.f, 1.f);
//
//				//Right
//				glNormal3f(1.0f, 1.0f, 0.0f);
//				glVertex3f(0.0f, 1.0f, 0.0f);
//
//				glNormal3f(1.0f, 1.0f, 0.0f);
//				glVertex3f(0.0f, 1.0f, 1.0f);
//
//				glNormal3f(1.0f, 1.0f, 0.0f);
//				glVertex3f(1.0f, 0.0f, 0.0f);
//
//				//Front
//				glNormal3f(0.0f, 0.0f, 1.0f);
//				glVertex3f(0.0f, 0.0f, 0.0f);
//
//				glNormal3f(0.0f, 0.0f, 1.0f);
//				glVertex3f(0.0f, 1.0f, 0.0f);
//
//				glNormal3f(0.0f, 0.0f, 1.0f);
//				glVertex3f(1.0f, 0.0f, 0.0f);
//
//			glEnd();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(
			60.f,
			float(sf::VideoMode::GetMode(0).Width)/float(sf::VideoMode::GetMode(0).Height),
			0.1f, -500.f
		);
		//set camera
		glRotatef(camera_azimut, 1.f, 0.f, 0.f);
		glRotatef(camera_angle, 0.f, 1.f, 0.f);
		glTranslatef(camera_position[0], camera_position[2], camera_position[1]);

		//printf("caz: %f | ca: %f | cp: %f\n", camera_azimut, camera_angle, camera_position[0]);

		//draw Hud (User Interface)
		this->showInfo();

		// Finally, display rendered frame on screen
		this->app->Display();
	}
}

void Visualizer::processInputEvents(const float elapsed_time)
{
	//input reference for real time events
	const sf::Input& Input = this->app->GetInput();

	//axis and dead zones
	axis_u = Input.GetJoystickAxis(0, sf::Joy::AxisU); if(abs(axis_u) < 15) axis_u = 0;
	axis_v = Input.GetJoystickAxis(0, sf::Joy::AxisV); if(abs(axis_v) < 15) axis_v = 0;
	axis_x = Input.GetJoystickAxis(0, sf::Joy::AxisX); if(abs(axis_x) < 15) axis_x = 0;
	axis_y = Input.GetJoystickAxis(0, sf::Joy::AxisY); if(abs(axis_y) < 15) axis_y = 0;
	axis_r = Input.GetJoystickAxis(0, sf::Joy::AxisR); if(abs(axis_r) < 15) axis_r = 0;
	axis_z = Input.GetJoystickAxis(0, sf::Joy::AxisZ); if(abs(axis_z) < 15) axis_z = 0;

//	for(unsigned int i=0; i < 20; i++)
//		if(Input.IsJoystickButtonDown(0, i))
//			std::cout << i << std::endl;

	//BACK BUTTON (SELECT)
	if(Input.IsJoystickButtonDown(0, 6))
	{
		min_value -= 0.01f;
		std::cout << "min_value = " << min_value << std::endl;
	}

	//START BUTTON
	if(Input.IsJoystickButtonDown(0, 7))
	{
		min_value += 0.01f;
		std::cout << "min_value = " << min_value << std::endl;
	}

	//A BUTTON
	if(Input.IsJoystickButtonDown(0, 0)) this->flag_is_model_valid = false;

	if(Input.IsKeyDown(sf::Key::A)) axis_x = -100;
	if(Input.IsKeyDown(sf::Key::D)) axis_x = 100;

	if(Input.IsKeyDown(sf::Key::W)) axis_y = -100;
	if(Input.IsKeyDown(sf::Key::S)) axis_y = 100;

	if(Input.IsKeyDown(sf::Key::Left)) axis_u = -60;
	if(Input.IsKeyDown(sf::Key::Right)) axis_u = 60;

	if(Input.IsKeyDown(sf::Key::Up)) axis_r = 100;
	if(Input.IsKeyDown(sf::Key::Down)) axis_z = 100;

	//minvalue
	if(Input.IsKeyDown(sf::Key::Add) || Input.IsKeyDown(sf::Key::F2))
	{
		min_value += 0.01f;
		std::cout << "min_value = " << min_value << std::endl;
	}

	if(Input.IsKeyDown(sf::Key::Subtract) || Input.IsKeyDown(sf::Key::Dash) || Input.IsKeyDown(sf::Key::F1))
	{
		min_value -= 0.01f;
		std::cout << "min_value = " << min_value << std::endl;
	}

	//limit min_value to a valid percentual value
	if(min_value < 0.0f) min_value = 0.0f;
	if(min_value > 1.0f) min_value = 1.0f;


	//clear vertices vector
	if(Input.IsKeyDown(sf::Key::N))
	{
		std::cout << "A: this->vertexes->size() = " << this->vertexes->size() << std::endl;
		this->vertexes->clear();
		std::cout << "B: this->vertexes->size() = " << this->vertexes->size() << std::endl;
	}

	//generate off file
	if(Input.IsKeyDown(sf::Key::O))
	{
		std::cout << "Generating Off file" << std::endl;
		this->mc_thread->createOffFile();
	}

	//take screenshot
	if(Input.IsKeyDown(sf::Key::P))
	{
		std::cout << "Taking Screenshot" << std::endl;
		std::cout << this->saveScreenshot((char*)"screenshot.png", 0, 0, this->res_x, this->res_y) << std::endl;
	}

	//rotate model
	if(Input.IsKeyDown(sf::Key::R)) this->model_rotation[0] += 1.f;
	if(Input.IsKeyDown(sf::Key::F)) this->model_rotation[0] -= 1.f;
	if(Input.IsKeyDown(sf::Key::T)) this->model_rotation[1] += 1.f;
	if(Input.IsKeyDown(sf::Key::G)) this->model_rotation[1] -= 1.f;

	//escala a eje R y Z
	axis_r = (axis_r + 100) * 0.5f;
	axis_z = (axis_z + 100) * 0.5f;

	camera_angle_velocity = axis_u * 0.01f * 90;

	//calculo velocidad angular
	camera_azimut = axis_v * 0.01f * 90.f;
	camera_angle = camera_angle + camera_angle_velocity * elapsed_time;

	//calculo velocidad
	// v_x = v_x0 +a_xt
	camera_velocity[0] = axis_y * 0.01f * sin(camera_angle * 3.14159265/180);
	camera_velocity[1] = axis_y * -0.01f * cos(camera_angle * 3.14159265/180);
	camera_velocity[2] = axis_y * -0.01f * sin(camera_azimut * 3.14159265/180);

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
	sf::Event Event;
	while (this->app->GetEvent(Event))
	{
		switch(Event.Type)
		{
			case sf::Event::Closed:
				this->app->Close();
				break;

			case sf::Event::KeyPressed:

				switch(Event.Key.Code)
				{
					case sf::Key::Escape:
						this->app->Close();
						break;

					case sf::Key::F11:
						if(this->window_style & sf::Style::Fullscreen)
							this->window_style =
								sf::Style::Titlebar |
								sf::Style::Close;
						else
							this->window_style =
									sf::Style::Fullscreen;

						this->app->Create(*this->video_mode, this->window_title, this->window_style);
						this->setupOpenGL();
						break;

					case sf::Key::Return:
						this->flag_is_model_valid = false;
						break;

					default:
						break;
				}

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
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), this->vertexes->data() + 3);
	//glColorPointer(3, GL_FLOAT, 0, colors1);
	glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), this->vertexes->data());

//	std::cout << "this->vertexes->size()" << this->vertexes->size() << std::endl;
//	std::cout << "this->vertexes->size() / 6" << this->vertexes->size() / 6 << std::endl;

	glPushMatrix();

		glScalef(0.05f, 0.05f, 0.05f);
		glColor3f(1,1,1);
		glRotatef(this->model_rotation[0], 1.f, 0.f, 0.f);
		glRotatef(this->model_rotation[1], 0.f, 1.f, 0.f);

		glDrawArrays(GL_TRIANGLES, 0, this->vertexes->size() / 6);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Visualizer::setupOpenGL()
{
	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);

	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	//Set material properties which will be assigned by glColor
//	GLfloat mat_ambient_cubo[] = {0.5, 0.5, 0.5, 0.5f};
//	GLfloat mat_diffuse_cubo[] = {1.0, 1.0, 1.0, 0.7f};
//	GLfloat mat_specular_cubo[] = {1.0, 1.0, 1.0, 0.3f};
//	glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_cubo);
//	glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_cubo);
//	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_cubo);
//	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Create light components
	GLfloat ambientLight0[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat diffuseLight0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat specularLight0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat position0[] = { 0.0f, 1.0f, 0.0f, 0.0f };

	GLfloat ambientLight1[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat diffuseLight1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat specularLight1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position1[] = { 0.0f, -1.0f, 0.0f, 0.0f };

//	GLfloat position1[] = {
//			camera_position[0],
//			camera_position[2],
//			camera_position[1]
//	};

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);

//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
}

void Visualizer::draw3dScene()
{
	this->draw3dAxis();
	this->draw3dGrid();
	//this->draw3dPoints(-3,3,-3,3,-3,3);
}

#define AXIS_SCALE 100000
void Visualizer::draw3dAxis(void)
{
	glPushMatrix ();

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

//parametros para construir la grilla
#define DEF_floorGridScale	1.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0
void Visualizer::draw3dGrid()
{
	//Dibujo la Grilla
	GLfloat zExtent, xExtent, xLocal, zLocal;
	int loopX, loopZ;

	glPushMatrix();
		//glPushAttrib( GL_LIGHTING_BIT );
			//glDisable( GL_LIGHTING );
			//glColor3f( 0.0, 0.7, 0.7 );
			glBegin( GL_LINES );

				zExtent = DEF_floorGridScale * DEF_floorGridZSteps;

				for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
				{
					xLocal = DEF_floorGridScale * loopX;
					glVertex3f( xLocal, 0.0, -zExtent );
					glVertex3f( xLocal, 0.0,  zExtent );
				}

				xExtent = DEF_floorGridScale * DEF_floorGridXSteps;

				for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
				{
					zLocal = DEF_floorGridScale * loopZ;
					glVertex3f( -xExtent, 0.0, zLocal );
					glVertex3f(  xExtent, 0.0, zLocal );
				}

			glEnd();
		//glPopAttrib();
	glPopMatrix();
}

void Visualizer::draw3dPoints(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax)
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
						glVertex3i(i,j,k);
					glEnd();
				}
			}
		}

	glPopMatrix ();
}

void Visualizer::drawHud()
{
	this->showInfo();
	//this->drawHudStatus();
}

void Visualizer::updateHudStatus(std::string status)
{
	std::cout << status << std::endl;
	this->hud_status_string = status;
}

void Visualizer::drawHudStatus()
{
	this->hud_status->SetText(this->hud_status_string);
	this->hud_status->SetFont(sf::Font::GetDefaultFont());
	this->hud_status->SetSize(20);

	//this->app->Draw(*(this->hud_status));
}

int Visualizer::saveScreenshot(char *file_name, unsigned int x, unsigned int y, unsigned long width, unsigned long height)
{
	FILE *fp;
	unsigned long i;
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette;
	png_byte *image;
	png_bytep *row_pointers;

	fp = fopen(file_name, "wb");
	if (fp == NULL)
		return -1;

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		fclose(fp);
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, png_infopp_NULL);
		return -1;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return -1;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof (png_color));
	png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);

	png_write_info(png_ptr, info_ptr);

	png_set_packing(png_ptr);

	image = (png_byte *)malloc(width * height * 3 * sizeof(png_byte));
	if(image == NULL)
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return -1;
	}

	row_pointers = (png_bytep *)malloc(height * sizeof(png_bytep));
	if(row_pointers == NULL)
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		free(image);
		image = NULL;
		return -1;
	}

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)image);

	for (i = 0; i < height; i++)
	{
		row_pointers[i] = (png_bytep)image + (height - i) * width * 3;
	}

	png_write_image(png_ptr, row_pointers);

	png_write_end(png_ptr, info_ptr);

	png_free(png_ptr, palette);
	palette = NULL;

	png_destroy_write_struct(&png_ptr, &info_ptr);

	free(row_pointers);
	row_pointers = NULL;

	free(image);
	image = NULL;

	fclose(fp);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void Visualizer::draw2dString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
		glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
		glDisable(GL_DEPTH_TEST);

			glColor4fv(color);          // set text color
			//glRasterPos2i(x, y);        // place text position
			glPushMatrix();
				glTranslatef(x, y, 0);
				glScalef(0.2f, 0.2f, 0.2f);
				glLineWidth(2.f);

				// loop all characters in the string
				while(*str)
				{
					//glutBitmapCharacter(font, *str);
					glutStrokeCharacter(font, *str);
					++str;
				}
			glPopMatrix();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
    glPopAttrib();
}

///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void Visualizer::showInfo()
{
    // backup current model-view matrix
    //glPushMatrix();                     // save current modelview matrix
    //glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
		glLoadIdentity();                   // reset projection matrix
		gluOrtho2D(0, this->res_x, 0, this->res_y); // set to orthogonal projection
		float color[4] = {1, 1, 1, 1};

		std::stringstream ss;
		//ss << std::fixed << std::setprecision(3);

		ss << "Min value (isosurface): " << this->min_value*100 << "%" << std::ends;
		this->draw2dString(ss.str().c_str(), this->res_x*0.005, this->res_y*0.95, color, GLUT_STROKE_ROMAN);
		ss.str("");

		ss << "Triangles: " << this->vertexes->size() / 18 << std::ends;
		this->draw2dString(ss.str().c_str(), this->res_x*0.005, this->res_y*0.895, color, GLUT_STROKE_ROMAN);
		ss.str("");

		// unset floating format
		//ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

	// restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    //glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    //glPopMatrix();                   // restore to previous modelview matrix
}
