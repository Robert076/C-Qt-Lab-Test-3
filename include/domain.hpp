#include <string>

using namespace std;

class Meal
{
    private:
        string start, end, type, calories, description;
    public:
        Meal(string start, string end, string type, string calories, string description)
        {
            this->start = start;
            this->end = end;
            this->type = type;
            this->calories = calories;
            this->description = description;
        }
        string getStart()
        {
            return this->start;
        }
        string getEnd()
        {
            return this->end;
        }
        string getType()
        {
            return this->type;
        }
        string getCalories()
        {
            return this->calories;
        }
        string getDescription()
        {
            return this->description;
        }
};