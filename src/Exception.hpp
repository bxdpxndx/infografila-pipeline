#ifndef Exception_hpp
#define Exception_hpp

#include <exception>
#include <sstream>

class FileNotFoundException : public std::exception {
    std::string filename;
public: 
    FileNotFoundException (std::string name) throw() : filename(name) {}
    ~FileNotFoundException() throw() {}

    const char* what() throw() {
        std::stringstream os;
        os <<"file " << filename << " not found." << std::endl;
        return os.str().c_str();
    }
};

#endif
