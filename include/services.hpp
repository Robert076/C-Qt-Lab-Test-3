#include "../include/repo.hpp"
#include <algorithm>

class Services
{
    private:
        Repository repo;
    public:
        Services()
        {
            this->repo = Repository();
        }
        vector<Meal> getMeals()
        {
            return this->repo.getMeals();
        }
        int convert(string a)
        {
            int c = 0;
            for(auto x : a)
                c = c * 10 + x - '0';
            return c;
        }
        int getSum(string mealType, string start)
        {
            int sum = 0;
            for(auto x : this->repo.getMeals())
            {
                if(mealType == x.getType() && x.getStart() > start)
                {    int c = this->convert(x.getCalories());
                    sum += c;}
            }
            return sum;
        }
};