// Prototype (Creational Design Pattern)

// A partially or fully initialized object that you copy(clone) and make use of.
// Creating duplicate objects and reusing cached objects to reduce database calls.
// Composition, creation and representation of objects should be decoupled from the system.
// Requires deep copy support.

// g++ prototype.cc -std=c++17

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory> //std::unique_ptr, std::make_unique

class Prototype
{
public:
    Prototype() {}
    Prototype (std::string name, std::uint32_t attribute):_name(name), _attribute(attribute) {}
    virtual ~Prototype() {}
    virtual std::unique_ptr<Prototype> clone() = 0;

     friend std::ostream& operator<<(std::ostream& os, const Prototype& prototype)
    {
        return os << "Name: " << prototype._name << " " << "Attribute: " << prototype._attribute;
    }

protected:
    std::string _name;
    std::uint32_t _attribute;
};

class ObjectA: public Prototype
{
public:
    ObjectA(std::string name, std::uint32_t attribute): Prototype(name, attribute) {}
    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ObjectA>(*this);
    }
};


class ObjectB: public Prototype
{
public:
    ObjectB(std::string name, std::uint32_t attribute): Prototype(name, attribute) {}
    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<ObjectB>(*this);
    }
};

enum Type
{
    A = 0,
    B
};

class ObjectFactory
{
public:
    ObjectFactory()
    {
        m_Objects[A] = std::make_unique<ObjectA>("ObjectA", 10);
        m_Objects[B] = std::make_unique<ObjectB>("ObjectB", 20);
    }

    std::unique_ptr<Prototype> createObject(Type type)
    {
        return m_Objects[type]->clone();
    }

private:
    std::unordered_map<Type, std::unique_ptr<Prototype>, std::hash<int>> m_Objects;
};


int main()
{
    ObjectFactory objectFactory;

    auto cloneObjectA = objectFactory.createObject(A);
    std::cout << *cloneObjectA << std::endl;

    auto cloneObjectB = objectFactory.createObject(B);
    std::cout << *cloneObjectB << std::endl;

    return 0;
}