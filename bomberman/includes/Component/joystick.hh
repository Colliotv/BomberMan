#ifndef __JOYSTICK_H__
# define __JOYSTICK_H__

#include <cstdlib>
#include <SDL/SDL.h>
#include "Component.hh"

namespace Component{
  class JoystickManager {
  private:
    std::array<SDL_Joystick*, 4>	_joystick;

  public:
    class joystick : public Component::abstract{
    private:
      SDL_Joystick*		_joystick;
      std::array< std::pair< int, int>, 2>	joyState;
      std::array< std::pair< int, int>, 6 >	keyState;	

    private:
      int	_id;
    public:
      joystick(Entity::GameObject*, SDL_Joystick*, int id);
      ~joystick();

    public:
      std::string serialization();
      void	setBySerial(const Tokenizer&);
    };

  public:
SDL_Joystick*	getJoystick(int);

  public:
    JoystickManager();
    ~JoystickManager();
  };
};

namespace Event{
namespace Type{
# ifndef __ARENA_H__
    struct Keyboard : Event::Data{
      Keyboard(int k, bool s)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  key(k), state(s) {}
      int key;
      bool state;
    };
# endif
# ifndef __PHISIX_H__
    struct speedAxeSetter : Event::Data {
      speedAxeSetter(double _s, int _a)
	: Event::Data(Event::Info::speedAxeSetter, sizeof(struct speedAxeSetter), false), speed(_s), axe(_a) {}
      double speed;
      int    axe;
    };
# endif

};
};

#endif
