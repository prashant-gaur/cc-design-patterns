// Intialisation
// -------------------------
// The following steps happen during the initialization of MVC
// 1. The Model is created and initializes the data
// 2. The View is created and observes the Model
// 3. The Controller is created and gets references to the Model and the View. It observes the Model.
// 4. The application starts event processing
//
// User Input
// -------------------------
// 1. The controller accepts the user input, handles them and triggers the model
// 2. The model changes its internal data (if the user input is write operation)
// 3. The model notifies all views and controllers about the change of the internal data
// 4. The views and controller update themselves
// 5. The controller continues to process the events
//
// e.g.
// If the PIN is entered incorrectly in an ATM for the third time, this can mean. The display shows that
// your account is locked. The ATM confisccates your debit card.
//
// Reference:
// https://www.freecodecamp.org/news/model-view-architecture/ 
//
// https://www.modernescpp.com/index.php/model-view-controller/


#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdint>

using Data = std::unordered_map<std::uint32_t, std::string>;

class Model
{
public:
    
    Data getList() const
    {
        return m_data;
    }

    std::uint32_t getCount() const
    {
        return m_data.size();
    }

    std::string getValue(const std::uint32_t& key) const
    {
        return m_data[key];
    }

private:
    mutable Data m_data = { {1 , "One"},
                            {2 , "Two"},
                            {3 , "Three"} };
};

class View
{
public:
    void displayCount(std::uint32_t count) const
    {
        std::cout << "There are " << count << " in total" << std::endl;
    }

    void displayList(const Data& data) const
    {
        for(const auto& i: data)
        {
            std::cout <<"Key: " << i.first << ", Value: " << i.second << std::endl;
        }
    }

    void displayValue(const std::uint32_t& key, const std::string& value) const
    {
        std::cout <<"For Key: " << key << ", Value is: " << value << std::endl;
    }
};

class Controller
{
public:
    Controller (const Model& model, const View& view): m_model{model}, m_view(view) {}

    void value(std::uint32_t key) const
    {
        m_view.displayValue(key, m_model.getValue(key));
    }

    void list() const
    {
        m_view.displayList(m_model.getList());
    }

    void count() const
    {
        m_view.displayCount(m_model.getCount());
    }
private:
    const Model& m_model;
    const View& m_view;
};

int main()
{
    Model model;
    View view;

    Controller controller(model, view);

    controller.count();
    controller.list();

    controller.value(2);


    return 0;
}