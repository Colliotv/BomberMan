
#include	<cstdlib>
#include <unistd.h>
#include <map>
#include	"GameEngine.hpp"
#include <SDL/SDL.h>
#include "Joystick.hh"

InputJoystick::InputJoystick(){}

InputJoystick::~InputJoystick(){}

void		InputJoystick::ConnectJoystick()
{
	int		i;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1 )
	{
		fprintf(stderr,"Error SDL\n");
		return;
	}

	i = 0;
	for (nbr_joy = SDL_NumJoysticks();  i < nbr_joy; i++)
	{
		joystick[i] = SDL_JoystickOpen(i);
		printf("Name : %s\n",SDL_JoystickName(0));
		printf("nbre d' : %d\n",SDL_JoystickNumAxes(joystick[i]));
		printf("nbre de chapeaux : %d\n",SDL_JoystickNumHats(joystick[i]));
		printf("nbre de trackballs : %d\n",SDL_JoystickNumBalls(joystick[i]));
		printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(joystick[i]));
		printf("i = %d nbr_joy = %d\n", i, nbr_joy);
		if (joystick[i] == NULL || SDL_JoystickNumButtons(joystick[i]) != 19)
		{
			fprintf(stderr,"Error joystick[i]\n");
			return;
		}
	}
}

void	InputJoystick::GetJoystickAxes(int player)
{
	int		i;

	for (i = 0; i < SDL_JoystickNumAxes(joystick[player]); i++)
	{
		printf("Player[%d] Axe %d, valeur %d\n",player, i,SDL_JoystickGetAxis(joystick[player],i));
		button[i] = SDL_JoystickGetAxis(joystick[player],i);
	}
}

void	InputJoystick::GetJoystickButton(int player)
{
	int		i;
	int		i_button;

	i_button = 4;
	for ( i = 0 ; i < SDL_JoystickNumButtons(joystick[player]) ; i++ )
	{
		if ( SDL_JoystickGetButton(joystick[player],i) )
		{
			printf("Player[%d] Bouton %d : appuyé\n",player, i);
		}
		else
		{
			printf("Player[%d] Bouton %d n'est pas appuyé\n",player, i);
		}
		button[i_button] = SDL_JoystickGetButton(joystick[player],i);
		i_button++;
	}
}

int		InputJoystick::Wait_Event(GameEngine &engine)
{
	int	i;

	if (engine.initialize() == false)
		return (EXIT_FAILURE);
	while (engine.update() == true)
	{
		engine.draw();
		SDL_JoystickUpdate();
		for (i = 0; i < nbr_joy; i++)
		{
			GetJoystickAxes(i);
			GetJoystickButton(i);
		}
		for(i = 0; i < 24; i++)
		{
			printf("touche %d = %d\n", i, button[i]);
		}
	}
	return 1;
}

int main()
{
	GameEngine 		engine;
	InputJoystick	joy;

	joy.ConnectJoystick();
	printf("*****%d*****\n", joy.nbr_joy);
	joy.Wait_Event(engine);
}
