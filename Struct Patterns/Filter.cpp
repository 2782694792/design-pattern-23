#pragma once
#include <string>
using namespace std;

class Person {
private:
    string name; // 名称
    string gender; // 性别
    string mantalStatus; // 婚姻状况

public:
    Person(string name, string gender, string mantalStatus) {
        this->name         = name;
        this->gender       = gender;
        this->mantalStatus = mantalStatus;
    }

    string getName() {
        return name;
    }

    string getGender() {
        return gender;
    }

    string getMantalStatus() {
        return mantalStatus;
    }
};

#include <list>

// 符合条件的成员列表
class Criteria {
public:
    virtual list< Person* > meetCriteria(list< Person* > persons) = 0; 
};

// 列表包含女性成员
class CriteriaFemale : public Criteria {
public:
    virtual list< Person* > meetCriteria(list< Person* > persons) {
        list< Person* > listPerson;
        for (auto it : persons) {
            if (it->getGender() == "Female") {
                listPerson.push_back(it);
            }
        }
        return listPerson;
    }
};

// 列表包含男性成员
class CriteriaMale : public Criteria {
public:
    virtual list< Person* > meetCriteria(list< Person* > persons) {
        list< Person* > listPerson;
        for (auto it : persons) {
            if (it->getGender() == "Male") {
                listPerson.push_back(it);
            }
        }
        return listPerson;
    }
};

// 列表包含单身成员
class CriteriaSingle : public Criteria {
public:
    virtual list< Person* > meetCriteria(list< Person* > persons) {
        list< Person* > listPerson;
        for (auto it : persons) {
            if (it->getMantalStatus() == "Single") {
                listPerson.push_back(it);
            }
        }
        return listPerson;
    }
};

// 符合交集的成员列表
class AndCriteria : public Criteria {
private:
    Criteria* pCriteria;
    Criteria* pOtherCriteria;

public:
    AndCriteria(Criteria* pCriteria, Criteria* pOtherCriteria) {
        this->pCriteria      = pCriteria;
        this->pOtherCriteria = pOtherCriteria;
    }

    virtual list< Person* > meetCriteria(list< Person* > persons) {
        list< Person* > listPerson1 = pCriteria->meetCriteria(persons);
        return pOtherCriteria->meetCriteria(listPerson1);
    }
};

// 符合并集的成员列表
class OrCriteria : public Criteria {
private:
    Criteria* pCriteria;
    Criteria* pOtherCriteria;

public:
    OrCriteria(Criteria* pCriteria, Criteria* pOtherCriteria) {
        this->pCriteria      = pCriteria;
        this->pOtherCriteria = pOtherCriteria;
    }
    virtual list< Person* > meetCriteria(list< Person* > persons) {
        list< Person* > listPerson1 = pCriteria->meetCriteria(persons);
        list< Person* > listPerson2 = pOtherCriteria->meetCriteria(persons);
        for (auto it : listPerson2) {
            bool bFind = false;
            for (auto it2 : listPerson1) {
                if (it2 == it) {
                    bFind = true;
                    break;
                }
            }
            if (!bFind) { // 添加不同的成员
                listPerson1.push_back(it);
            }
        }
        return listPerson1;
    }
};

#include <stdio.h>
void printPersons(list<Person*> persons)
{
	printf("\n");
	for (auto it : persons)
	{
		printf("Person: [Name: %s, Gender: %s, Matal Status:%s]\n", it->getName().c_str(), it->getGender().c_str(), it->getMantalStatus().c_str());
	}
}

void main()
{
	list<Person*> persons;
	persons.push_back(new Person("Robert", "Male", "Single"));
	persons.push_back(new Person("John", "Male", "Married"));
	persons.push_back(new Person("Laura", "Female", "Married"));
	persons.push_back(new Person("Diana", "Female", "Single"));
	persons.push_back(new Person("Mike", "Male", "Single"));
	persons.push_back(new Person("Bobby", "Male", "Married"));
	Criteria *pMale = new CriteriaMale();
	Criteria *pFeMale = new CriteriaFemale();
	Criteria *pSingle = new CriteriaSingle();
	Criteria *pSingleMale = new AndCriteria(pSingle, pMale);
	Criteria *pSingleOrFemale = new OrCriteria(pSingle, pFeMale);
 
	printf("Males: ");
	printPersons(pMale->meetCriteria(persons));
 
	printf("\nFeMales: ");
	printPersons(pFeMale->meetCriteria(persons));
 
	printf("\nSingle Males: ");
	printPersons(pSingleMale->meetCriteria(persons));
 
	printf("\nSingle or FeMales: ");
	printPersons(pSingleOrFemale->meetCriteria(persons));
 
	getchar();
}