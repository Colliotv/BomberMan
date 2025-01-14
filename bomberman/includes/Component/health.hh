#ifndef __HEALTH_H__
# define __HEALTH_H__

# include "Component.hh"

namespace Component{

  /* ################ Health ############## */
  class Health : public Component::abstract{
  public:
    class Dot {
    private:
      int	damage;
      int	clockLife;
      int	rTime;
      int	aTime;

    public:
      Dot(int damage, int clockLife, unsigned int timeBeetween = 0);
      Dot(int damage, int clockLife, unsigned int timeBeetween, unsigned int current);
      
    public:
      std::string	serialize();
      int	getDamage(void);
      bool	isOver(void);
    };
  private:
    Event::Callback*	_callback;
    Event::Dispatcher*	dispatcher;
    int			maxLife;
    int			life;
    std::list<Dot*>	dotList;
    bool		immunityTime;

  public:
    Health(Entity::GameObject*);
    ~Health();

  private:
    int		actualize();

  public:
    int		operator+(int n);
    int		operator-(int n);

  public:
    void	revive(unsigned int reviveLife);
    bool	isDead(void);

  public:
    void	addDot(Health::Dot*);

  public:
    bool	isInvicible(void);
    void	invincible(int time);

  public:
    std::string dotSerialisation(std::list<Dot*>::iterator);
    std::string serialization();
    void	setBySerial(const Tokenizer&);
  };

};

namespace  Event{
  namespace Type{
# ifndef __BONUS_H__
    struct Immunity : Event::Data{
      Immunity(int _t)
	: Event::Data(Event::Info::Immunity, sizeof(struct Immunity), false),
	  time(_t) {}
      int time;
    };
# endif

# ifndef __EFFECTS_H__
    struct PlaceDot : Event::Data{
      PlaceDot(int _d, unsigned int _dd)
	: Event::Data(Event::Info::PlaceDot, sizeof(struct PlaceDot), false),
	  damage(_d), duration(_dd) {}
      int	damage;
      int	duration;
      int	warmUp;
    };

    struct lifeLoss : Event::Data{
      lifeLoss(int _a)
	: Event::Data(Event::Info::lifeLoss, sizeof(struct lifeLoss), false),
	  amount(_a) {}
      int amount;
    };

    struct lifeGain : Event::Data{
      lifeGain(int _a)
	: Event::Data(Event::Info::lifeGain, sizeof(struct lifeLoss), false),
	  amount(_a) {}
      int amount;
    };
# endif

    struct revive : Event::Data{
      revive()
	: Event::Data(Event::Info::revive, sizeof(struct revive), false) {}
    };

# ifndef __ARENA_H__
    struct dead : Event::Data{
      dead()
	: Event::Data(Event::Info::dead, sizeof(struct dead), true) {}
    };
# endif

  };
};

#endif
