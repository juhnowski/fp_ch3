#include <vector>
#include <execution>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
class person_t
{
public:
    string name;
    bool is_female;
    int age;
};

vector<person_t> persons = {
        {"Ann", true,10}, 
        {"Peter", false, 20},
        {"Jane", true, 30},
        {"Tom", false, 40},
        {"Martha", true, 50},
        {"David", false, 60},
        {"Rose", true, 70},
    };

bool older_than_42(const person_t& person)
{
    return person.age > 42;
}

class older_than {
public:
    older_than(int limit): m_limit(limit){
    }

    bool operator()(const person_t& person) const {
        return person.age > m_limit;
    }

private:
    int m_limit;
};

template <typename T>
class older_than_generic {
public:
    older_than_generic(int limit): m_limit(limit){}
    bool operator()(const T& object ) const {
        return object.age() > m_limit;
    }

private:
    int m_limit;
};

class older_than_good {
public:
    older_than_good(int limit): m_limit(limit){}
    template <typename T>
    bool operator()(T&& object ) const {
        return std::forward<T>(object).age() > m_limit;
    }

private:
    int m_limit;
};

class company_t {
public:
    std::string team_name_for(const person_t& employee) const;
    int count_team_members(const std::string& team_name) const;

private:
    std::vector<person_t> m_employees;
};

int company_t::count_team_members(const std::string& team_name) const
{
    return std::count_if(
            m_employees.cbegin(), m_employees.cend(),
            [this, &team_name] (const person_t& employee) {
                return team_name_for(employee) == team_name;
            }
    );
}

int main(int argc, char** argv)
{
    std::cout << "age>42:" <<std::count_if(persons.cbegin(), persons.cend(), older_than_42) << std::endl;

    older_than older_than_42(42);
    older_than older_than_14(14);

    std::cout << "-------------------" << endl;
    std::cout << "age>42:" << std::count_if(persons.cbegin(), persons.cend(),older_than_42) << endl;
    std::cout << "age>14:" << std::count_if(persons.cbegin(), persons.cend(),older_than_14) << endl;

    std::cout << "-------------------" << endl;

    std::cout << "age>42:" << std::count_if(persons.cbegin(), persons.cend(),older_than(42)) << endl;
    std::cout << "age>14:" << std::count_if(persons.cbegin(), persons.cend(),older_than(14)) << endl;
    
    std::cout << "generic-------------------" << endl;
    std::cout << "age>42:" << std::count_if(persons.cbegin(), persons.cend(),older_than_generic<person_t>(42)) << endl;
    
    std::cout << "good-------------------" << endl;
    older_than_good predicate(5);
    std::cout << "age>5:" << std::count_if(persons.cbegin(), persons.cend(), predicate) << endl;
    return 0;
}