#include "../vector.hpp"
#include <vector>
#include <iostream>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <poll.h>
#include <list>


#ifndef NAMESPACE
# define NAMESPACE ft
#endif


#define NB_OF_ELEMENTS 100
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

template<class T>
void print_element_i_vector(NAMESPACE::vector<T> const & the_vector, size_t index)
{
    std::cout << "value for index " << index << " : " << the_vector[index] << std::endl;
}

template<class T>
void print_vector(NAMESPACE::vector<T> const &the_vector)
{
    std::cout << "size : " << the_vector.size() << std::endl;
    std::cout << "max_size : " << the_vector.max_size() << std::endl;
    std::cout << "capacity : " << the_vector.capacity() << std::endl;
    std::cout << "empty : " << the_vector.empty() << std::endl;
    if (the_vector.empty() == FALSE)
    {
        std::cout << "front_value " << the_vector.front() << std::endl;
        std::cout << "back_value " << the_vector.back() << std::endl;
    }
    std::cout << "--------------------------------------" << std::endl;
};

template<class T>
void print_all_vectors_elements(NAMESPACE::vector<T>  const &the_vector)
{
    for (size_t i = 0 ; i < the_vector.size(); i++)
    {
        print_vector(the_vector);
        print_element_i_vector(the_vector, i);
    }
}

void push_pop_back_test()
{
    NAMESPACE::vector<int> the_vector;

    print_vector<int>(the_vector);
    for (int i=0; i < NB_OF_ELEMENTS; i++)
    {
        print_vector<int>(the_vector);
        the_vector.push_back(i);
    }
    for (int i=0; i < NB_OF_ELEMENTS; i++)
    {
        print_vector<int>(the_vector);
        the_vector.pop_back();
    }
}

template<class T>
void push_back_test_with_copy_constructor(NAMESPACE::vector<T> the_vector)
{


    print_vector<int>(the_vector);
    for (int i=0; i < NB_OF_ELEMENTS; i++)
    {
        print_vector<int>(the_vector);
        the_vector.push_back(i);
        print_element_i_vector(the_vector, i);
    }
}

void resize_vector_test()
{
    NAMESPACE::vector<int> myvector;

    // set some initial content:
    for (int i = 0 ; i < NB_OF_ELEMENTS ; i++)
        myvector.push_back(i);

    myvector.resize(5);
    std::cout << "resize(5) :\n " << std::endl;
    print_vector(myvector);
    std::cout << "resize(8, 100) :\n " << std::endl;
    myvector.resize(8,100);
    print_vector(myvector);
    std::cout << "resize(12) :\n "<< std::endl;
    myvector.resize(12);
    print_vector(myvector);

    std::cout << "myvector contains :\n";
    for (size_t i = 0 ; i < myvector.size(); i++)
    {
        print_vector(myvector);
        print_element_i_vector(myvector, i);
    }
}

void reserve_vector_test()
{
    NAMESPACE::vector<int> myvector;

    // set some initial content:
    for (int i = 0 ; i < NB_OF_ELEMENTS ; i++)
        myvector.push_back(i);

    myvector.reserve(NB_OF_ELEMENTS / 2);
    std::cout << "reserve(5) :\n " << std::endl;
    print_vector(myvector);
    std::cout << "reserve(8) :\n " << std::endl;
    myvector.reserve(NB_OF_ELEMENTS * 2);
    print_vector(myvector);
    std::cout << "reserve(12) :\n "<< std::endl;
    myvector.reserve(NB_OF_ELEMENTS * 4);
    print_vector(myvector);

    for (int i = 0 ; i < NB_OF_ELEMENTS * 8 ; i++)
        myvector.push_back(i);

    std::cout << "myvector contains :\n";
    for (size_t i = 0 ; i < myvector.size(); i++)
    {
        print_vector(myvector);
        print_element_i_vector(myvector, i);
    }
}

void at_vector_test()
{
    NAMESPACE::vector<int> myvector;
    for (int i = 0 ; i < NB_OF_ELEMENTS ; i++)
        myvector.push_back(i);

    for (int i = -1; i < NB_OF_ELEMENTS + 1 ; i++)
    {
        try
        {
            std::cout << "value number : " << myvector.at(i) << std::endl;
        }
        catch(std::out_of_range const &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}


void		ite()
{
	const int size = 5;
	NAMESPACE::vector<int> my_vector(size);
	NAMESPACE::vector<int>::iterator it = my_vector.begin();
	NAMESPACE::vector<int>::const_iterator ite = my_vector.begin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	print_all_vectors_elements(my_vector);
}

void rev_ite_construct()
{
    NAMESPACE::vector<int> my_vector;
	NAMESPACE::vector<int>::iterator it = my_vector.begin();
	NAMESPACE::vector<int>::const_iterator cit = my_vector.begin();

	NAMESPACE::vector<int>::reverse_iterator rit(it);

	NAMESPACE::vector<int>::const_reverse_iterator crit(rit);
	NAMESPACE::vector<int>::const_reverse_iterator crit_(it);
	NAMESPACE::vector<int>::const_reverse_iterator crit_2(cit);

}

void reverse_iterator()
{
    const int size = 5;
    NAMESPACE::vector<int> myvector(size);
    NAMESPACE::vector<int>::reverse_iterator rev_it = myvector.rbegin();
    NAMESPACE::vector<int>::const_reverse_iterator const_rev_it = myvector.rbegin();

    for (int i = 0; i < size; ++i)
        rev_it[i] = (size - i) * 5;

    rev_it = rev_it + 5;
    rev_it = 1 + rev_it;
    rev_it = rev_it - 4;
    std::cout << *(rev_it += 2) << std::endl;
    std::cout << *(rev_it -= 1) << std::endl;

    *(rev_it -= 2) = 42;
    *(rev_it += 2) = 21;

    std::cout << "const_ite +=/-=: " << *(const_rev_it += 2) << " | " << *(const_rev_it -= 2) << std::endl;

    std::cout << "(rev_it == const_it): " << (const_rev_it == rev_it) << std::endl;
    std::cout << "(const_ite - rev_it): " << (const_rev_it - rev_it) << std::endl;
    std::cout << "(const_rev_it + 3 == rev_it): " << (const_rev_it + 3 == rev_it) << std::endl;
    std::cout << *const_rev_it << std::endl;
    std::cout << *rev_it << std::endl;
}


void bidirect_it()
{
    std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	NAMESPACE::vector<int> my_vector(lst.begin(), lst.end());
	//printSize(my_vector);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	my_vector.assign(lst.begin(), lst.end());
	//printSize(my_vector);

	my_vector.insert(my_vector.end(), lst.rbegin(), lst.rend());
	//printSize(my_vector);
	//return (0);
}
void iterator_vector_test()
{
    std::cout << "iterator_test" << std::endl;
    NAMESPACE::vector<int> myvector;
    for (int i = 1 ; i < NB_OF_ELEMENTS ; i++)
        myvector.push_back(i);

    NAMESPACE::vector<int>::iterator it_begin;
    NAMESPACE::vector<int>::iterator it_end;

    it_begin = myvector.begin();
    it_end = myvector.end();


    std::cout << "increment test and while (it_begin != it_end)" << std::endl;
    std::cout << *it_begin << std::endl;
    while (it_begin != myvector.end())
    {
        // *it_begin = 5;
        std::cout << *it_begin << std::endl;
        it_begin++;
    }
    it_begin = myvector.begin();
    it_end--;
    std::cout << "decrement test and while (it_begin != it_end)" << std::endl;
    while (it_begin != it_end)
    {
        // *it_begin = 5;
        std::cout << *--it_end << std::endl;
    }

    it_end = myvector.end();

    it_begin += 2;
    std::cout << *(it_begin) << std::endl;
    it_begin += 5;
    std::cout << *(it_begin) << std::endl;
    it_begin -= 3;
    std::cout << *(it_begin) << std::endl;
    std::cout << *(it_begin + 3) << std::endl;
    std::cout << *(it_begin - 3) << std::endl;
    std::cout << it_begin[1] << std::endl;
    std::cout << (it_begin[1] > it_begin[0]) << std::endl;
    std::cout << (it_begin[1] < it_begin[0]) << std::endl;
    std::cout << (it_begin[1] >= it_begin[0]) << std::endl;
    std::cout << (it_begin[0] >= it_begin[0]) << std::endl;
    std::cout << (it_begin[1] <= it_begin[0]) << std::endl;
    std::cout << (it_begin[0] <= it_begin[0]) << std::endl;


}

void const_iterator_vector_test()
{
    std::cout << "iterator_test" << std::endl;
    NAMESPACE::vector<int> myvector;
    for (int i = 1 ; i < NB_OF_ELEMENTS ; i++)
        myvector.push_back(i);

    NAMESPACE::vector<int>::const_iterator it_begin;
    NAMESPACE::vector<int>::const_iterator it_end;

    it_begin = myvector.begin();
    it_end = myvector.end();


    it_begin += 2;
    std::cout << *(it_begin) << std::endl;
    it_begin += 5;
    std::cout << *(it_begin) << std::endl;
    it_begin -= 3;
    std::cout << *(it_begin) << std::endl;
    std::cout << *(it_begin + 3) << std::endl;
    std::cout << *(it_begin - 3) << std::endl;
    std::cout << it_begin[1] << std::endl;
    std::cout << (it_begin[1] > it_begin[0]) << std::endl;
    std::cout << (it_begin[1] < it_begin[0]) << std::endl;
    std::cout << (it_begin[1] >= it_begin[0]) << std::endl;
    std::cout << (it_begin[0] >= it_begin[0]) << std::endl;
    std::cout << (it_begin[1] <= it_begin[0]) << std::endl;
    std::cout << (it_begin[0] <= it_begin[0]) << std::endl;


}

void copy_constructor_time()
{
    NAMESPACE::vector<int> my_vector;

    for (int i = 0; i < NB_OF_ELEMENTS; i++)
    {
        my_vector.push_back(i);
    }

    NAMESPACE::vector<int> copy_vector(my_vector);
}

void assign_vector_test()
{


    NAMESPACE::vector<int> first;
    NAMESPACE::vector<int> second;
    NAMESPACE::vector<int> third;

    first.assign (NB_OF_ELEMENTS,100);             // 7 ints with a value of 100
    print_vector(first);
    NAMESPACE::vector<int>::iterator it;
    it=first.begin()+1;

    std::cout << "Second assign" << std::endl;
    second.assign (it,first.end()-1); // the 5 central values of first
    print_vector(second);

    int myints[] = {1776,7,4};
    third.assign (myints,myints+3);   // assigning from array.
    print_vector(third);

    std::cout << "Size of first: " << int (first.size()) << '\n';
    std::cout << "Size of second: " << int (second.size()) << '\n';
    std::cout << "Size of third: " << int (third.size()) << '\n';


}

void test_insert()
{
    NAMESPACE::vector<int> myvector (5,100);
    NAMESPACE::vector<int> tyvector;
    NAMESPACE::vector<int>::iterator it;

    myvector.push_back(5);
    it = myvector.begin();
    it = myvector.insert ( it , 200 );
    std::cout << *it << std::endl;
    it = myvector.insert ( myvector.begin() + 5 , 300 );
    std::cout << *it<< std::endl;
    myvector.clear();
    for (int i = 0; i < 8; i++)
    {
        tyvector.push_back(i);
        myvector.push_back(i);
    }
    it = tyvector.end();
     std::cout << *--it<< std::endl;
    // print_all_vectors_elements(tyvector);
    // // print_all_vectors_elements(tyvector);

    // // std::cout << *tyvector.insert (it,11,300) << std::endl;;
    // print_all_vectors_elements(tyvector);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    NAMESPACE::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());
    myvector.insert (myvector.begin(),1 , 5);

    int myarray [] = { 501,502,503 };
    print_all_vectors_elements(myvector);
    std::cout << "\n\n\n\n";
    std::cout << *myvector.insert (myvector.end(), 1) << std::endl;
    std::cout << *myvector.insert (myvector.end() - 5, 1) << std::endl;
    myvector.insert (myvector.begin(), myarray, myarray+3);
        for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    myvector.insert (myvector.begin() + 2, anothervector.begin(), anothervector.end());

    print_all_vectors_elements(myvector);
        std::cout << tyvector.begin() -  tyvector.end() << std::endl;
    myvector.insert(myvector.begin(), tyvector.begin(), tyvector.end());
    print_all_vectors_elements(myvector);
    std::cout << "myvector contains:";

    std::cout << '\n';
}


void test_str_insert()
{
    NAMESPACE::vector<std::string> myvector (5,"fiveeee");
    NAMESPACE::vector<std::string> tyvector;
    NAMESPACE::vector<std::string>::iterator it;

    myvector.push_back("five");
    it = myvector.begin();
    it = myvector.insert ( it , "deux cents" );
    std::cout << *it << std::endl;
    // std::cout << myvector.end() - it << std::endl;
    myvector.clear();
    for (int i = 0; i < 8; i++)
    {
        tyvector.push_back("boyyha");
        myvector.push_back("boyyha2");
    }
    it = tyvector.end();
     std::cout << *--it<< std::endl;
    print_all_vectors_elements(tyvector);
    print_all_vectors_elements(tyvector);
    it = myvector.begin();

    NAMESPACE::vector<std::string> anothervector (2,"bllaaaaa");
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

        print_all_vectors_elements(myvector);


    print_all_vectors_elements(myvector);
        std::cout << "\n\n\n\n";
    myvector.insert(myvector.begin(), tyvector.begin(), tyvector.end());
    print_all_vectors_elements(myvector);
}


void test_constructor()
{

  // constructors used in the same order as described above:
  NAMESPACE::vector<int> first;                                // empty vector of ints
  NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
  NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
  NAMESPACE::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  print_all_vectors_elements(second);
  print_all_vectors_elements(third);
  NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void test_const_constructor()
{

  // constructors used in the same order as described above:
    const NAMESPACE::vector<int> first;                                // empty vector of ints
    const NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
    const NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
    const NAMESPACE::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  print_all_vectors_elements(second);
  print_all_vectors_elements(third);
  NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void test_erase()
{

    NAMESPACE::vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i=1; i<=20; i++)
        myvector.push_back(i);

    std::cout << *(myvector.erase (myvector.begin()+5)) << std::endl;

    std::cout << *myvector.erase (myvector.begin()) << std::endl;


    std::cout << myvector.erase (myvector.end() - 1) - myvector.begin() << std::endl;
    print_all_vectors_elements(myvector);


    std::cout <<  *myvector.erase (myvector.begin(),myvector.begin()+3) << std::endl;
    //erase the two last
     std::cout <<  *myvector.erase (myvector.end() - 2,myvector.end()) << std::endl;

    std::cout << * myvector.erase (myvector.begin() + 3, myvector.end() - 3) << std::endl;
     print_all_vectors_elements(myvector);


}
void test_swap()
{
    NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
    NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

    std::cout << "foo size " << foo.size() << std::endl;

    foo.swap(bar);
    std::cout << "BAR" << std::endl;
    std::cout << "foo size " << foo.size() << std::endl;
    print_all_vectors_elements(foo);
    print_all_vectors_elements(bar);


    foo.swap(bar);
    std::cout << "foo" << std::endl;
    print_all_vectors_elements(foo);
    print_all_vectors_elements(bar);

}

void test_assign()
{
    NAMESPACE::vector<int> foo (3,5);
    NAMESPACE::vector<int> bar (5,5);


    bar[1] = foo[2];

    print_all_vectors_elements(bar);
}

void test_assign_str()
{
    NAMESPACE::vector<std::string> foo (102,"54959495");
    NAMESPACE::vector<std::string> bar (100,"5439459394");

    foo[5] = foo[1].insert(0, "voila");
    foo = bar;
    print_all_vectors_elements(bar);
    print_all_vectors_elements(bar);
}

void test_clear()
{
    NAMESPACE::vector<int> myvector;
    myvector.push_back (100);
    myvector.push_back (200);
    myvector.push_back (300);

    std::cout << "myvector contains:";
    print_all_vectors_elements(myvector);


    myvector.clear();
    myvector.push_back (1101);
    myvector.push_back (2202);

    std::cout << "myvector contains:";
    print_all_vectors_elements(myvector);
}

void test_get_alloc()
{
    std::vector<int> myvector;
    int * p;
    unsigned int i;

    // allocate an array with space for 5 elements using vector's allocator:
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

    std::cout << "The allocated array contains:";
    for (i=0; i<5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p,5);
}

void test_comparison()
{
    NAMESPACE::vector<int> foo (3,100);
    NAMESPACE::vector<int> bar (2,200);
    NAMESPACE::vector<int> truite(2, 100);
    NAMESPACE::vector<int> saumon(2, 100);

    std::cout << (foo == bar) << std::endl;
    std::cout << (foo == truite) << std::endl;
    std::cout << (foo == saumon) << std::endl;
    std::cout << (bar == truite) << std::endl;
    std::cout << (bar == saumon) << std::endl;
    std::cout << (truite == saumon) << std::endl;

    std::cout << (foo != bar) << std::endl;
    std::cout << (foo != truite) << std::endl;
    std::cout << (foo != saumon) << std::endl;
    std::cout << (bar != truite) << std::endl;
    std::cout << (bar != saumon) << std::endl;
    std::cout << (truite != saumon) << std::endl;

    std::cout << (foo < bar) << std::endl;
    std::cout << (foo < truite) << std::endl;
    std::cout << (foo < saumon) << std::endl;
    std::cout << (bar < truite) << std::endl;
    std::cout << (bar < saumon) << std::endl;
    std::cout << (truite < saumon) << std::endl;

    std::cout << (foo > bar) << std::endl;
    std::cout << (foo > truite) << std::endl;
    std::cout << (foo > saumon) << std::endl;
    std::cout << (bar > truite) << std::endl;
    std::cout << (bar > saumon) << std::endl;
    std::cout << (truite > saumon) << std::endl;

    std::cout << (foo >= bar) << std::endl;
    std::cout << (foo >= truite) << std::endl;
    std::cout << (foo >= saumon) << std::endl;
    std::cout << (bar >= truite) << std::endl;
    std::cout << (bar >= saumon) << std::endl;
    std::cout << (truite >= saumon) << std::endl;

    std::cout << (foo <= bar) << std::endl;
    std::cout << (foo <= truite) << std::endl;
    std::cout << (foo <= saumon) << std::endl;
    std::cout << (bar <= truite) << std::endl;
    std::cout << (bar <= saumon) << std::endl;
    std::cout << (truite <= saumon) << std::endl;
}

void test_swap_external()
{
    NAMESPACE::vector<int> foo (5,100);   // three ints with a value of 100
    NAMESPACE::vector<int> bar (3,200);   // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    print_all_vectors_elements(foo);

    std::cout << "bar contains:";
    print_all_vectors_elements(bar);

}


void test_reverse_iterator()
{
    NAMESPACE::vector<int> myvector(20);
    NAMESPACE::vector<int>::reverse_iterator rit_begin = myvector.rbegin();
    for (int i = 0; i < 20; i++)
    {
        rit_begin[i] = i;
    }
    // std::cout << *rit_begin.base() << std::endl;
    print_all_vectors_elements(myvector);


    NAMESPACE::vector<int>::reverse_iterator rit_end = myvector.rend();

    while (rit_begin != rit_end)
    {
        std::cout << *rit_begin << std::endl;
        rit_begin++;
    }
    rit_begin = myvector.rbegin();

    while (rit_begin != rit_end)
    {
        rit_end--;
        std::cout << *rit_end << std::endl;
    }
    rit_end = myvector.rend();

    while (rit_begin != rit_end)
    {
        std::cout << *rit_begin << std::endl;
        rit_begin = rit_begin + 1;
    }
    rit_begin = myvector.rbegin();
    while (rit_begin != rit_end)
    {
        rit_end = rit_end - 1;
        std::cout << *rit_end << std::endl;
    }

    rit_end = myvector.rend();
    while (rit_begin != rit_end)
    {
        rit_begin = rit_begin + 1;
        std::cout << *rit_begin.base() << std::endl;
    }

    rit_begin = myvector.rbegin();
    *(rit_begin += 2) = 4545;
    *(rit_end -= 2) = 777;
    while (rit_begin != rit_end)
    {
        rit_end = rit_end - 1;
        std::cout << rit_end[1] << std::endl;
    }
    rit_end = myvector.rend();
    std::cout << rit_end - rit_begin << std::endl;
    std::cout << *(rit_begin + 5) << std::endl;
    std::cout << *(5 + rit_begin) << std::endl;
    std::cout << *(rit_end - 5) << std::endl;
     std::cout << *(--rit_end) << std::endl;
    std::cout << *(--rit_end) << std::endl;
    std::cout << *(rit_end -= 2) << std::endl;
    std::cout << *(rit_end += 2) << std::endl;
    std::cout << *rit_end << std::endl;
    std::cout << *rit_begin << std::endl;
    std::cout << (rit_begin == rit_end) << std::endl;
    std::cout << (rit_end - rit_begin) << std::endl;
    std::cout << (rit_end - 14 == rit_begin) << std::endl;


}

void test_string()
{
    NAMESPACE::vector<std::string> my_vector(1, "test");
    std::string test = "test";

    for (int i = 0; i < 1; i++)
    {
        my_vector.push_back(test);
    }
}

int main()
{

    NAMESPACE::vector<int> myvector;

     test_constructor();
     test_const_constructor();
     copy_constructor_time();
     push_pop_back_test();
    test_insert();
     resize_vector_test();
     reserve_vector_test();
     at_vector_test();
     iterator_vector_test();
     const_iterator_vector_test();
     assign_vector_test();
     test_insert();
     test_str_insert();
     test_erase();
     test_string();
     test_assign_str();
     test_swap();
     test_clear();

     test_get_alloc();
     test_comparison();
     test_swap_external();
     test_reverse_iterator();
     bidirect_it();
     ite();
     rev_ite_construct();
     test_reverse_iterator();

}