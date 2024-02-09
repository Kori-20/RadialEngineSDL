#include <exception>
#include <string>
#include <sdl2/SDL.h>

//TODO:: Abstract class to allow for use in OpenGl
class InitError : public std::exception {
public:
	InitError();
	InitError(const std::string&);
	virtual ~InitError() throw();
	virtual const char* what() const throw();
private:
	std::string msg;
};