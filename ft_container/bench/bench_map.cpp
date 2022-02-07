#include "../map.hpp"
#include <map>
#include <iostream>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <poll.h>
#include <list>


#ifndef NAMESPACE
# define NAMESPACE ft
#endif


#define NB_OF_ELEMENTS 10000
#define FALSE 0

unsigned long int	chrono_init(void)
{
	struct timeval		tv;
	unsigned long int	start_time;

	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (start_time);
}
 
unsigned long int	stamp_time(unsigned long int start_time)
{
	unsigned long int	actual_time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	actual_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - start_time;
	return (actual_time);
}

void constructor_bench()
{
    std::cout << "Constructor Bench" << std::endl;
    size_t start = chrono_init();

    NAMESPACE::map<int, std::string> *test;
    std::cout << "Constructor Default" << std::endl;
    for (int i = 0; i < NB_OF_ELEMENTS * 10; i++)
    {
        test = new NAMESPACE::map<int , std::string>;
        delete test;
    }
    std::cout << stamp_time(start) <<  "ms" <<std::endl;


    std::list<NAMESPACE::pair<int, std::string> > just_a_list;
    for (int i = 0; i < NB_OF_ELEMENTS/20; i++)
    {
        just_a_list.push_back(NAMESPACE::make_pair(NB_OF_ELEMENTS, "same"));
    }

    std::cout << "Constructor range" << std::endl;
    start = chrono_init();
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        test = new NAMESPACE::map<int, std::string>(just_a_list.begin(), just_a_list.end());
        delete test;
    }
    std::cout << stamp_time(start) << "ms" << std::endl;

    NAMESPACE::map<int, std::string> original;
    std::string blop("blop");
    for (int i = 0; i < 100; i++)
    {
        original.insert(NAMESPACE::make_pair(i, blop));
    }
    std::cout << "Constructor copy" << std::endl;
    start = chrono_init();
    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        test = new NAMESPACE::map<int, std::string>(original);
        delete test;
    }
    std::cout << stamp_time(start) << "ms" << std::endl;
}

void operator_assign()
{
    std::cout << "Operator assign bench" << std::endl;

    NAMESPACE::map<int, std::string> test;
    for (int i = 0; i < NB_OF_ELEMENTS * 100; i++)
    {
        test.insert(NAMESPACE::make_pair(i, "pair"));
    }
    NAMESPACE::map<int, std::string> ditto;
    size_t start = chrono_init();
    ditto = test;
    std::cout << stamp_time(start) <<  "ms" <<std::endl;
    start = chrono_init();
}


void swap_bench()
{
    NAMESPACE::map<int , std::string> swap_a;
    NAMESPACE::map<int , std::string> swap_b;

     for (int i = 0; i < NB_OF_ELEMENTS ;i++)
    {
        swap_a.insert(NAMESPACE::make_pair(i, "poisson"));
    }
     for (int i = 0; i < NB_OF_ELEMENTS ;i++)
    {
        swap_b.insert(NAMESPACE::make_pair(i, "poisson"));
    }
    std::cout << "Swap Bench" << std::endl;
    size_t start = chrono_init();
    for (int i = 0; i < NB_OF_ELEMENTS * 100;i++)
    {
        swap_a.swap(swap_b);
    }
    std::cout << stamp_time(start) <<  "ms" <<std::endl;
}

void lower_upper_bound_bench()
{
    NAMESPACE::map<int,std::string> test;
    std::cout << "Lower bound bench" << std::endl;
    for (int i = 0; i < NB_OF_ELEMENTS ;i++)
    {
        test.insert(NAMESPACE::make_pair(i * 2, "poisson"));
    }
    size_t start = chrono_init();
    for (int i = 0; i < NB_OF_ELEMENTS * 2 ;i++)
    {
        test.lower_bound(i);
    }
    std::cout << stamp_time(start) <<  "ms" <<std::endl;
     std::cout << "Upper bound bench" << std::endl;
     start = chrono_init();
    for (int i = 0; i < NB_OF_ELEMENTS * 2 ;i++)
    {
        test.upper_bound(i);
    }
    std::cout << stamp_time(start) <<  "ms" <<std::endl;


}
int main()
{
    constructor_bench();
    operator_assign();
    swap_bench();
    lower_upper_bound_bench();
    return 0;
}