#include <iostream>
#include <chrono>
#include "ShaderLoader.h"
#include "Cube.h"
#include "Controls.h"
#include "Image.h"
#include "PS4.h"
#include "Player.h"
#include "Pistol.h"
#include "Weapon.h"


using namespace std;

//CAMERA
CCamera camera;

//Shaders
GLuint SHADER_DEFAULT;

//Gamepad
std::vector<CGamepad*> gamepads;

//The world
b2World* world;

//players
std::vector<CPlayer> Players;

//bullets
std::vector<CBullet> bullets;


//Title screen image
CImage titleScreen;
CImage indictator;
bool menu;
bool characterSelect;
int option;
int playerCount;
bool player1Ready;
bool player2Ready;
bool player3Ready;
bool player4Ready;

bool GamePlay;

//DeltaTime
float deltaTime;
auto t2 = std::chrono::high_resolution_clock::now();





//Game play loops-------------------

//Happens at the beginning of the game
void OnGameplayBegin()
{
	cout << "On Game Play Begin executing" << endl;
	cout << "----------------------------" << endl;

	//Make the world
	world = new b2World(b2Vec2(0,0));

	//First make the players
	for (unsigned int i = 0; i < playerCount; i++)
	{
		//initialise different player sprites here
		CPlayer temp;
		temp.init(*world, glm::vec2(0, 0), glm::vec2(1, 1), 2.5f, 1.3f, 0.1f);
		temp.addGamepad(*gamepads[i]);

		//if i == 0							(ctrl + F "clintwashere" to find order of sprites)
			//this sprite
		//elseif i == 1
			//this sprite
		//etc
		if (i == 0)
		{
//			temp.addSprite("Assets/Textures/Vishuu/David.png");
			temp.addSprite("Assets/Textures/Vishuu/Clint.png");

		}
		else if (i == 1)
		{
			temp.addSprite("Assets/Textures/Vishuu/Clint.png");
		}
		else if (i == 2)
		{
			temp.addSprite("Assets/Textures/Vishuu/Gilberto.png");
		}
		else if (i == 3)
		{
			temp.addSprite("Assets/Textures/Vishuu/Matt.png");
		}

		//Give a weapon
		CWeapon* weapon;
		weapon = new CPistol();
		temp.Equip(*weapon);

		Players.push_back(temp);
	}
}

void gameplayLoop(float deltaTime)
{
	//Start box2D colllisions
	float32 timeStep = 1.0f / 60.0f;
	world->Step(timeStep, 6, 2);

	//Update the camera
	camera.update();

	//Update the players
	for (unsigned int i = 0; i < Players.size(); i++)
	{
		Players[i].update(deltaTime);
	}
}

//This is now for rendering all player stuff
void gamePlayRender()
{
	for (unsigned int i = 0; i < Players.size(); i++)
	{
		//Draw bullets for each player here
		for (unsigned int j = 0; j < Players[i].bullets.size(); j++)
		{
			Players[i].bullets[j].render(SHADER_DEFAULT, camera);
		}
	}
	for (unsigned int i = 0; i < Players.size(); i++)
	{
		Players[i].render(SHADER_DEFAULT, camera);
	}
}

//--------------------------------


//Menu loops---------------------------
void menuLoop()
{
	//Update the camera
	camera.update();

	if (menu == true)
	{
		gamepads[0]->update();
		if (gamepads[0]->isButtonPressed(5))
		{
			cout << "Down" << endl;
			option = 0;
			indictator.SetPosition(glm::vec3(-1.8, 1.3, 5));
		}
		else if (gamepads[0]->isButtonPressed(4))
		{
			option = 1;
			cout << "Up" << endl;
			indictator.SetPosition(glm::vec3(-1.8, 4.0, 5));
		}
		else if (gamepads[0]->isButtonPressed(0))
		{
			cout << "X" << endl;
			if (option == 0)
			{
				exit(0);
			}
			else if (option == 1)
			{
				menu = false;
				characterSelect = true;
				titleScreen.addSprite("Assets/Textures/Select.psd");
			}
		}
	}
	else if (characterSelect == true)
	{
		int temp;
		temp = playerCount;

		//Player one has special controls
		gamepads[0]->update();
		if (gamepads[0]->isButtonPressed(12) && !gamepads[0]->isReady)
		{
			playerCount++;
			gamepads[0]->isReady = true;
		}
		else if (gamepads[0]->isButtonPressed(0) && playerCount > 0)
		{
			//Launch us into the game!!
			GamePlay = true;
			OnGameplayBegin();
		}

		//Repeat for other controlls
		for (unsigned int i = 1; i < gamepads.size(); i++)
		{
			gamepads[i]->update();
			if (gamepads[i]->isButtonPressed(12) && !gamepads[i]->isReady)
			{
				playerCount++;
				gamepads[i]->isReady = true;
			}
		}

		//this adds each sprite in the character selection
		if (playerCount != temp)
		{
			//keep this order when selecting player sprites clintwashere
			if (playerCount == 0)
			{
				titleScreen.addSprite("Assets/Textures/Select.psd");
			}
			else if (playerCount == 1)
			{
				titleScreen.addSprite("Assets/Textures/Select_1.psd");
			}
			else if (playerCount == 2)
			{
				titleScreen.addSprite("Assets/Textures/Select_2.psd");
			}
			else if (playerCount == 3)
			{
				titleScreen.addSprite("Assets/Textures/Select_3.psd");
			}
			else if (playerCount == 4)
			{
				titleScreen.addSprite("Assets/Textures/Select_4.psd");
			}
		}
	}
}

void menuRender()
{
	if (menu)
	{
		titleScreen.render(SHADER_DEFAULT, camera);
		indictator.render(SHADER_DEFAULT, camera);
	}
	else if (characterSelect)
	{
		titleScreen.render(SHADER_DEFAULT, camera);
	}
}
//--------------------------------------


//Main display call
void render()
{
	//clear all
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0.08f, 0.08f, 0.08f, 0.0);

	if (GamePlay)
	{
		gamePlayRender();
	}
	else
	{
		menuRender();
	}
	


	//Swap out the buffers
	glutSwapBuffers();
}

//Game logic loop
void update()
{
	//DeltaTime Update
	auto t1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> fp_ms = t1 - t2;
	deltaTime = fp_ms.count();
	deltaTime = deltaTime * 0.01f;
	t2 = t1;

	if (GamePlay)
	{
		gameplayLoop(deltaTime);
	}
	else
	{
		menuLoop();
	}
	

	glutPostRedisplay();
}

void init()
{
	//Make the shaders
	CShaderLoader shaderLoader;
	SHADER_DEFAULT = shaderLoader.loadShaders("Assets/vertex_default.vs","Assets/fragment_default.fs");

	//make camera
	camera.init();

	//make players
	for (unsigned int i = 1; i < 5; i++)
	{
		CGamepad* gamePad;
		gamePad = new CGamepad(i);

		gamepads.push_back(gamePad);
	}

	//make the backdrop for the title
	titleScreen.init();
	titleScreen.addSprite("Assets/Textures/Title.psd");
	titleScreen.SetScale(glm::vec3(-13, -10, 1));

	//Indicator for title
	indictator.init();
	indictator.addSprite("Assets/Textures/YellowBird.psd");
	indictator.SetScale(glm::vec3(0.5, 0.5, 0.5));
	indictator.SetPosition(glm::vec3(-1.8, 1.3, 5));
	
	//enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//enable anti-aliasing
	glEnable(GL_MULTISAMPLE);

	menu = true;
	playerCount = 0;
	GamePlay = false;

	player1Ready = false;
	player2Ready = false;
	player3Ready = false;
	player4Ready = false;

}





//Entry point for everything
int main(int argc, char **argv)
{
	//init glut and make window
	glutInit(&argc, argv);
	glutInitWindowPosition(1200, 1);
	glutInitWindowSize(1200, 900);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutCreateWindow("QuadSquad");

	//initate glew
	glewInit();

	//initiate
	init();

	//register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);

	//enter loop
	glutMainLoop();
}