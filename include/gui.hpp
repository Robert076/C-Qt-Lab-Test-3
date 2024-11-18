#include "../include/services.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QLineEdit>

bool cmp(Meal a, Meal b)
{
    if (a.getStart().length() < b.getStart().length())
        return true;
    return a.getStart() <= b.getStart();
}

class GUI : public QWidget
{
private:
    Services &services;
    QListWidget *mealsList;
    QLineEdit *caloriesInput;
    QLineEdit *typeMeal;
    QLineEdit *startTime;

public:
    GUI(Services &services) : services(services)
    {
        buildGUI();
        populateMeals();
    }
    void buildGUI()
    {
        QVBoxLayout *layout = new QVBoxLayout();
        setLayout(layout);

        mealsList = new QListWidget();
        layout->addWidget(mealsList);


        QLabel* caloriesLabel = new QLabel("Calories input");
        layout->addWidget(caloriesLabel);
        caloriesInput = new QLineEdit();
        layout->addWidget(caloriesInput);
        connect(caloriesInput, &QLineEdit::textChanged, [=]()
                {
                vector<Meal> meals = this->services.getMeals();
                mealsList->clear();
                for(auto m : meals)
                {
                    int c1 = this->services.convert(m.getCalories());
                    int c2 = this->services.convert(caloriesInput->text().toStdString());
                    if(c1 < c2)
                         mealsList->addItem(QString::fromStdString(m.getStart() + " -> " + m.getEnd() + " | " + m.getType() + " | " + m.getCalories() + " | " + m.getDescription()));
                } });

        QLabel* typeLabel = new QLabel("Give meal type (task 3)");
        layout->addWidget(typeLabel);
        typeMeal = new QLineEdit();
        layout->addWidget(typeMeal);
        QLabel* startTimeLabel = new QLabel("Start time (task3)");
        layout->addWidget(startTimeLabel);
        startTime = new QLineEdit();
        layout->addWidget(startTime);
        QPushButton* filterButton = new QPushButton("Filter");
        layout->addWidget(filterButton);
        connect(filterButton, &QPushButton::clicked, [=](){
            string mealType = typeMeal->text().toStdString();
            string time = startTime->text().toStdString();
            int sum = this->services.getSum(mealType, time);
            vector<Meal> meals = this->services.getMeals();
            mealsList->clear();
            bool ok = false;
            for(auto m : meals)
            {
                if(m.getType() == mealType && m.getStart() > time)
                    {mealsList->addItem(QString::fromStdString(m.getStart() + " -> " + m.getEnd() + " | " + m.getType() + " | " + m.getCalories() + " | " + m.getDescription())); ok = true;}
            }
            if(ok)
                mealsList->addItem(QString::fromStdString(to_string(sum)));
            if(!ok)
                mealsList->addItem(QString::fromStdString("No meals with specifiecd requirements"));
        });
    }
    void populateMeals()
    {
        vector<Meal> meals = this->services.getMeals();
        sort(meals.begin(), meals.end(), cmp);
        for (auto m : meals)
        {
            mealsList->addItem(QString::fromStdString(m.getStart() + " -> " + m.getEnd() + " | " + m.getType() + " | " + m.getCalories() + " | " + m.getDescription()));
        }
    }
};