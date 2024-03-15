// Decorator (Structural Design Pattern)

// References
// https://refactoring.guru/design-patterns/decorator
// https://refactoring.guru/design-patterns/decorator/cpp/example#example-0
// https://medium.com/@antwang/decorator-in-c-the-right-way-9a6eacdce170
// https://www.modernescpp.com/index.php/the-decorator-pattern/

#include <iostream>

// Component
class SandwichOrder
{
public:
    virtual std::uint32_t GetCost() = 0;
    virtual std::string GetIngredient() = 0;
};

// Concrete Component
class BasicSandwich: public SandwichOrder
{
public:
    std::uint32_t GetCost() { return 10; };
    std::string GetIngredient(){ return std::string{"Basic Sandwich"}; };
};

// Concrete Decorator (Base Decorator)
class VeggieSandwich: public SandwichOrder
{
public:
    VeggieSandwich(SandwichOrder* order): m_order{order} {}
    std::uint32_t GetCost() override
    {
        return m_cost;
    }

    std::string GetIngredient() override
    {
        return m_order->GetIngredient() + " with " + m_ingredient;
    }

protected:
    SandwichOrder* m_order;
private:
    std::uint32_t m_cost {20};
    std::string m_ingredient {"Veggie"};
};

// Concrete Decorator
class GrillSandwich: public SandwichOrder
{
public:
    GrillSandwich(SandwichOrder* order): m_order{order} {}
    std::uint32_t GetCost() override
    {
        return m_cost + m_order->GetCost();
    }

    std::string GetIngredient() override
    {
        return m_ingredient + m_order->GetIngredient();
    }
protected:
    SandwichOrder* m_order;

private:
    std::uint32_t m_cost {30};
    std::string m_ingredient {"Grilled "};
};

int main()
{
    SandwichOrder* basicSandwich = new BasicSandwich;

    std::cout << basicSandwich->GetCost() << std::endl;
    std::cout << basicSandwich->GetIngredient() << std::endl;

    SandwichOrder* veggieSandwich = new VeggieSandwich(basicSandwich);
    std::cout << veggieSandwich->GetCost() << std::endl;
    std::cout << veggieSandwich->GetIngredient() << std::endl;

    SandwichOrder* grilledVeggieSandwich = new GrillSandwich(veggieSandwich);
    std::cout << grilledVeggieSandwich->GetCost() << std::endl;
    std::cout << grilledVeggieSandwich->GetIngredient() << std::endl;

    SandwichOrder* grilledBasicSandwich = new GrillSandwich(basicSandwich);
    std::cout << grilledBasicSandwich->GetCost() << std::endl;
    std::cout << grilledBasicSandwich->GetIngredient() << std::endl;

    return 0;
}