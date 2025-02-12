#ifndef __PHISIX_H__
# define __PHISIX_H__

# include "Component.hh"

namespace Component{

  /* ###################### PHISIX ############################# */
  class Phisix : public Component::Superior{
  public:
    class Vector : public Component::abstract{
    private:
      Component::Phisix	*phisix;
      
    private:
      double	x;
      double	y;

    private:
      double	speed;
      double	speedAxe[2];
    public:
      enum Direction{ Up, Down, Left, Right };
    private:
      std::array<bool, 4>	direction;

    public:
      Vector(Entity::GameObject*, Component::Phisix*);
      
    public:
      std::string serialization();
      void setBySerial(const Tokenizer&);
      static std::string	getName(void) { return (""); }
    }; /*  -- vector end --  */

  private:
    double	friction;
  public:
    Phisix(Event::Dispatcher*);

  public:
    double	getFriction();
  };
};

namespace Event{
  namespace Type{

# ifndef __ARENA_H__
    struct selfMovement : Event::Data{
      selfMovement(Component::Phisix::Vector::Direction _d, bool _b)
	: Event::Data(Event::Info::selfMovement, sizeof(struct selfMovement), false), direction(_d), state(_b) {}
      Component::Phisix::Vector::Direction	direction;
      bool					state;
    };
# endif

# ifndef __EFFECTS_H__
    struct speedModifier : Event::Data{
      speedModifier(double _s)
	: Event::Data(Event::Info::speedModifier, sizeof(struct speedModifier), false), speed(_s) {}
      double speed;
    };
# endif

# ifndef __JOYSTICK_H__
    struct speedAxeSetter : Event::Data {
      speedAxeSetter(double _s, int _a)
	: Event::Data(Event::Info::speedAxeSetter, sizeof(struct speedAxeSetter), false), speed(_s), axe(_a) {}
      double speed;
      int    axe;
    };
# endif

    struct freezeMovement : Event::Data{
      freezeMovement(bool _s)
	: Event::Data(Event::Info::freezeMovement, sizeof(struct freezeMovement), false), state(_s) {}
      bool	state;
    };

    struct setFriction : Event::Data{
      setFriction(double _f)
	: Event::Data(Event::Info::setFriction, sizeof(struct setFriction), false), friction((_f) ? ( 1.f / _f ) : (1.f)) {}
      double friction;
    };

# ifndef  __COLLIDER_H__
    struct RequireMovement :  Event::Data{
      RequireMovement(double _x, double _y, double vx, double vy)
	: Event::Data(Event::Info::RequireMovement, sizeof(struct RequireMovement), false),
	  x(_x), y(_y), vectorX(vx), vectorY(vy) {}
      double x;
      double y;
      double vectorX;
      double vectorY;
    };

    struct Colliding : Event::Data{
    Colliding(double _x, double _y, double _f)
	: Event::Data(Event::Info::Colliding, sizeof(struct Colliding), false),
	  endX(_x), endY(_y), collide(_f) {}
      double endX;
      double endY;
      double collide;
    }; 
# endif

  };
};
#endif
