#include "../include/domain.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
class Repository
{
    private:
        vector<Meal> meals;
    public:
        Repository()
        {
            this->meals = vector<Meal>();
        }
        vector<Meal> getMeals()
        {
            ifstream fin("../data.txt");
            string line;
            this->meals.clear();
            while(getline(fin, line))
            {
                string start, end, type, calories, description;
                stringstream ss(line);
                getline(ss, start, ';');
                getline(ss, end, ';');
                getline(ss, type, ';');
                getline(ss, calories, ';');
                getline(ss, description);
                Meal m(start, end, type, calories, description);
                this->meals.push_back(m);                
            }
            return this->meals;
        }
};