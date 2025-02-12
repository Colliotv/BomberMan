#include "Event.hpp"
#include "Entity.hh"

namespace Event{
  /*	Data	*/

  /* Callback */
  Callback::~Callback() {}

  bool	Callback::operator==(Event::Callback::Id oth) const {
    return (oth == _id);
  }

  Event::Callback::Id	Callback::getId(void) const {
    return (_id);
  }

  /* FixedCallback */
  bool	FixedCallback::operator()(Event::Data& event) {
    if (_enable)
      _lambdaCallback(event);
    return (true);
  }

  void	FixedCallback::enable(void){
    _enable = true;
  }

  void	FixedCallback::disable(void){
    _enable = false;
  }

  /* StaticCallback */
  bool	StaticCallback::operator()(Event::Data& event) {
    _lambdaCallback(event);
    return (true);
  }

  void	StaticCallback::enable(void){}

  void	StaticCallback::disable(void){}

  /* TimedCallback */
  bool	TimedCallback::operator()(Event::Data& event) {
    _time -= 1;
    if (_enable)
      _lambdaCallback(event, _time);
    return (_time);
  }

  void	TimedCallback::enable(void){
    _enable = true;
  }

  void	TimedCallback::disable(void){
    _enable = false;
  }

  /* Gen Id */
  Event::Callback::Id CallbackIdGenerator() {
    static Event::Callback::Id genId;
    genId += 1;
    return (genId);
  }


  /* Callback Remover */
  CallbackRemover::CallbackRemover(Event::Callback::Id r)
    : _r(r) {}

  bool CallbackRemover::operator()(Callback* oth) {
    bool is = ((*oth) == _r);
    if (is) delete oth;
    return (is);
  }


  /* Dispatcher */
  Dispatcher::Dispatcher() :_isdispatching(false) {}

  Event::Callback::Id
    Dispatcher::addCallbackOnEvent(Event::Info::Type type,
				   Event::Callback* callback,
				   Event::Info::Priority prio){
    if (prio == Event::Info::high){
      if (_high.find(type) == _high.end())
	_high.
	  insert(std::pair< Event::Info::Type, std::list<Event::Callback*> >
		 (type, std::list<Event::Callback*>()));
      _high[type].push_front(callback);
    } else if (prio == Event::Info::medium) {
      if (_med.find(type) == _med.end())
	_med.
	  insert(std::pair< Event::Info::Type, std::list<Event::Callback*> >
		 (type, std::list<Event::Callback*>()));
      _med[type].push_front(callback);
    } else if (prio == Event::Info::low) {
      if (_low.find(type) == _low.end())
	_low.
	  insert(std::pair< Event::Info::Type, std::list<Event::Callback*> >
		 (type, std::list<Event::Callback*>()));
      _low[type].push_front(callback);
    }
      return (callback->getId());
  }

  void	Dispatcher::unsetCallbackForId(Event::Info::Type type,
				       Event::Callback::Id id){
    Event::CallbackRemover remove(id);

    if (!_isdispatching){
      if (_high.find(type) != _high.end())
	_high[type].remove_if(remove);
      if (_med.find(type) != _med.end())
	_med[type].remove_if(remove);
      if (_low.find(type) != _low.end())
	_low[type].remove_if(remove);
    } else {
      if (_high.find(type) != _high.end()) {
	auto arr = &(_high[type]);
	  for (auto itt = arr->begin(); itt != arr->end(); ++itt)
	    if (remove(*itt)) {
	      if (itt == currentCallback)
		currentCallback = arr->erase(itt);
	      else
		arr->erase(itt);
	      return ;
	    }
      }

      if (_med.find(type) != _med.end()){
	auto arr = &(_med[type]);
	  for (auto itt = arr->begin(); itt != arr->end(); ++itt)
	    if (remove(*itt)) {
	      if (itt == currentCallback)
		currentCallback = arr->erase(itt);
	      else
		arr->erase(itt);
	      return ;
	    }
      }
      if (_low.find(type) != _low.end()){
	auto arr = &(_low[type]);
	  for (auto itt = arr->begin(); itt != arr->end(); ++itt)
	    if (remove(*itt)) {
	      if (itt == currentCallback)
		currentCallback = arr->erase(itt);
	      else
		arr->erase(itt);
	      return ;
	    }
      }
    }
  }

  void	Dispatcher::dispatchEvent(Event::Data* event) {
    std::list< Event::Callback* >* CallbackArray;
    std::unordered_map
      < Event::Info::Type , std::list< Event::Callback* >, std::hash<int> >
      ::iterator itt;

    if (_isdispatching){
      _eventQueue.push(event);
      return ;
    }

    _isdispatching = true;
    if ((itt = _high.find(event->type)) != _high.end()){
      CallbackArray = &(itt->second);
      for (auto itt = CallbackArray->begin(); itt != CallbackArray->end(); ++itt) {
	currentCallback = itt;
        if (!(*(*itt))(*event))
	  itt = CallbackArray->erase(itt);
	itt = currentCallback;
      }
    }
    if ((itt = _med.find(event->type)) != _med.end()){
      CallbackArray = &(itt->second);
      for (auto itt = CallbackArray->begin(); itt != CallbackArray->end(); ++itt) {
	currentCallback = itt;
        if (!(*(*itt))(*event))
	  itt = CallbackArray->erase(itt);
	itt = currentCallback;
      }
    }
    if ((itt = _low.find(event->type)) != _low.end()){
      CallbackArray = &(itt->second);
      for (auto itt = CallbackArray->begin(); itt != CallbackArray->end(); ++itt) {
	currentCallback = itt;
        if (!(*(*itt))(*event))
	  itt = CallbackArray->erase(itt);
	itt = currentCallback;
      }
    }

    if (event->network){
      if ((itt = _high.find(Event::Info::Network)) != _high.end()){
	CallbackArray = &(itt->second);
	for (auto itt = CallbackArray->begin(); itt != CallbackArray->end(); ++itt)
	  if (!(*(*itt))(*event))
	    itt = CallbackArray->erase(itt);
      }
      if ((itt = _med.find(Event::Info::Network)) != _med.end()){
	CallbackArray = &(itt->second);
	for (auto itt = CallbackArray->begin(); itt != CallbackArray->end(); ++itt)
	  if (!(*(*itt))(*event))
	    itt = CallbackArray->erase(itt);
      }
      if ((itt = _low.find(Event::Info::Network)) != _low.end()){
	CallbackArray = &(itt->second);
	for (auto itt = CallbackArray->begin(); itt != CallbackArray->end(); ++itt)
	  if (!(*(*itt))(*event))
	    itt = CallbackArray->erase(itt);
      }
    }

    _isdispatching = false;
    if (!_eventQueue.empty()) {
      Event::Data* levent = _eventQueue.front();
      _eventQueue.pop();
      dispatchEvent(levent);
    }
    delete event;
  }
};
