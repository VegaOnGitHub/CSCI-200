#ifndef CAT_H
#define CAT_H

#include <string>

class Cat {
    public:
        Cat();
        ~Cat();
        std::string getName() const;
        void setName(const std::string& N);
        std::string meow() const;

    private:
        std::string _name;
        double _height;
        double _weight;
};
#endif