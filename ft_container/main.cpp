#include "stack.hpp"
#include "vector.hpp"
#include <vector>
#include <map>
#include "map.hpp"
#include "iterator.hpp"
#include "redblacktree.hpp"

int	main()
{
		ft::map<int, int> ft_c0;
		ft::map<int, int> std_c0;

		srand(reinterpret_cast<long unsigned int>(&std_c0));
		size_t	testSize = 20 + rand() % 10000;

		int		val;
		std::vector<int>	testValues;
		testValues.reserve(testSize);
		for (size_t i = 1; i < testSize; i++)	{
			val = rand()%4200;
			testValues.push_back(val);
			if (i % 2 == 0)	{
				ft_c0[val];
				std_c0[val];
			}
			else	{
				ft_c0[val] = i;
				std_c0[val] = i;
			}
		}

	/*	bool	success = true;
		std::vector<int>::iterator it = testValues.begin();
		std::vector<int>::iterator ite = testValues.end();
		for (int i = 0; it != ite && success == true; i++, it++)	{
			success = (ft_c0[*it] == std_c0[*it]);
		}*/

	 /*ft::vector<std::string> test;

	for (int i = 0; i < 1000000; i++)
    {
        test = new ft::vector<std::string>;
        delete test;
    }
	std::cout << "1" << std::endl;
	ft::vector<std::string>		ft_c0(4, "___");
	std::vector<std::string>	std_c0(4, "___");
	ft::vector<std::string>::iterator	ft_ret;
	std::vector<std::string>::iterator	std_ret;
	std::cout << "2" << std::endl;

	ft_ret = ft_c0.insert(ft_c0.begin(), "A");
	std_ret = std_c0.insert(std_c0.begin(), "A");
	std::cout << "ft1 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "std1 " << std::cout << *std_c0.begin() << std::endl;
std::cout << "3" << std::endl;
	std::cout << "size " <<ft_c0.size() << std::endl;
	std::cout << "capacity " << ft_c0.capacity() << std::endl;
	ft_ret = ft_c0.insert(ft_c0.begin(), "B");
	std::cout << "4" << std::endl;
	std_ret = std_c0.insert(std_c0.begin(), "B");
	std::cout << "5" << std::endl;
	std::cout << "ft2 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "6" << std::endl;
	std::cout << "std2 " << std::cout << *std_c0.begin() << std::endl;
	std::cout << "7" << std::endl;
	ft_ret = ft_c0.insert(++ft_c0.begin(), "42");
	std_ret = std_c0.insert(++std_c0.begin(), "42");
	std::cout << "ft2 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "std2 " << std::cout << *std_c0.begin() << std::endl;
	ft_ret = ft_c0.insert(--ft_c0.end(), "The End...");
	std_ret = std_c0.insert(--std_c0.end(), "The End...");
	std::cout << ft_c0.size() << std::endl;
	std::cout << std_c0.size() << std::endl;
	std::cout << "ft3 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "std3 " << std::cout << *std_c0.begin() << std::endl << std::endl;

	for (ft::vector<std::string>::iterator it = ft_c0.begin(); it < ft_c0.end(); it++){
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	for (std::vector<std::string>::iterator it = std_c0.begin(); it < std_c0.end(); it++){
		std::cout << *it << std::endl;
	}*/
	/*ft_ret = ft_c0.insert(ft_c0.end(), "End...");
	std_ret = std_c0.insert(std_c0.end(), "End...");

	std::cout << "ft4 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "std4 " << std::cout << *std_c0.begin() << std::endl;
	ft_ret = ft_c0.insert(ft_c0.begin() + ft_c0.size() / 2, "middle...");
	std_ret = std_c0.insert(std_c0.begin() + std_c0.size() / 2, "middle...");
	std::cout << "ft5 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "std5 " << std::cout << *std_c0.begin() << std::endl;
	ft_c0.insert(++ft_c0.begin(), "Return_this");
	std_c0.insert(++std_c0.begin(), "Return_this");
	std::cout << "ft6 " << std::cout << *ft_c0.begin() << std::endl;
	std::cout << "std6 " << std::cout << *std_c0.begin() << std::endl;*/
	
/*	ft::vector<int> test;
	test.push_back(10);
	test.push_back(15);
	test.push_back(9);
	std::cout << "pushed_back 10, 15, 9" << std::endl;
	ft::vector<int>::iterator it = test.begin();
	ft::vector<int>::reverse_iterator rit;
	std::cout << "begin value is : " << *it << std::endl;
	it = test.end();
	std::cout << "end value is : " << *it << std::endl;
	rit = test.rend();
	std::cout << "rend value is : " << *rit << std::endl;
	rit = test.rbegin();
	std::cout << "rbegin value is : " << *rit << std::endl;
	ft::vector<int>::const_iterator constit = test.begin();
	std::cout << "cbegin value is : " << *constit << std::endl;
	constit = test.end();
	std::cout << "cend value is : " << *constit << std::endl;
	ft::vector<int>::const_reverse_iterator rconstit = test.rbegin();
	std::cout << "crbegin value is : " << *rconstit << std::endl;
	rconstit = test.rend();
	std::cout << "crend value is : " << *rconstit << std::endl;
	std::cout << "size is : " << test.size() << std::endl;
	std::cout << "max size is : " << test.max_size() << std::endl;
	test.resize(1);
	it = test.end();
	std::cout << "resize to 1 new last element -1 is : " << *--it << std::endl;
	test.resize(3, 5);
	it = test.end();
	std::cout <<  "resize to 3 with value of 5 new last element -1 is : " << *--it << " size of the vector is : " << test.size();
	it = test.begin();
	std::cout << " first element after the resize is still : " << *it << std::endl;
	test.reserve(50);
	std::cout << "used reserve function for a value of 50 new vector capacity is : " << test.capacity() << std::endl;
	test.reserve(1);
	std::cout << "used reserve function for a value of 1 new vector capacity is : " << test.capacity();
	it = test.end();
	std::cout << " last value -1 is now : " << *--it << std::endl;
	std::cout << "testing empty function on test vector the answer is : " << test.empty() << std::endl;
	test.clear();
	std::cout << "called clear function, retesting empty function , return value is : " << test.empty() << std::endl;
	size_t n = 5;
	test.assign(n, 9);
	it = test.end();
	std::cout << "assigned 5 null terminated int for a value of 9,  new size is : " << test.size() << " new last element -1 is : " << *--it << std::endl;
	ft::vector<int>::iterator it2 = test.begin();
	ft::vector<int> test2;
	test2.assign(it2, it);
	it = test2.end();
	std::cout << "created new vector and assigned values from first vector from begin to end, new size is : " << test2.size() << " new last element -1 is : " << *--it << std::endl;
	test[2] = 87;
	std::cout << "changed test[2] to 87 through [] operator new value is : " << test[2] << std::endl;
	it = test.begin();
	it2 = test.end();
	test2.assign(it, it2);
	std::cout << "assigned to the already non empty vector test2 values from test from begin to end, new size is : " << test2.size() << " new test2[2] is : " << test2[2] << std::endl;
	test2.assign(n, 75);
	std::cout << "assigned to the already non empty vector test2 5 null terminated int of value 75 , new size is : " << test2.size() << " new test2[2] is : " << test2[2] << std::endl;
	std::cout << "accessing test first element through at function, result is : " << test.at(0) << std::endl;
	std::cout << "accessing test first element through front function, result is : " << test.front() << std::endl;
	test.push_back(54);
	std::cout<< "used push_back on test with a value of 54" << std::endl;
	std::cout << "accessing test last non null element through back function, result is : " << test.back() << std::endl;
	test.pop_back();
	std::cout << "deleted last non null element through pop_back function, last non null element now is : " << test.back() << std::endl;
	test.erase(test.begin(), test.begin() + 1);
	it = test.begin();
	std::cout << "used erase function to delete first and second elements of test, size is now : " << test.size() << " first element now is : " << *it << std::endl;
	test.erase(it);
	it = test.end();
	std::cout << "used erase function to delete first element of test , size is now : " << test.size() << " first element now is : " << *it << std::endl;
	test.push_back(105);
	it = test.end();
	std::cout << "used push_back on test with a value of 105 last non null value is : " << *--it << std::endl;
	test.swap(test2);
	it = test.end();
	std::cout << "swapped test with test2, test size now is : " << test.size() << " test last non null value is : " << *--it << std::endl;
	it = test2.end();
	std::cout << "test2 size now is : "  << test2.size() << " test2 last non null value is : " << *--it << std::endl;
	std::allocator<int> alloc = test.get_allocator();
	alloc.construct(it.p, 5);
	std::cout << "using get_allocator to get test allocator and use it to assign the iterator it the value of 5 now his value is : " << *it << std::endl;
	bool answer = test == test2;
	std::cout << "comparing == between test and test2 return value is : " << answer << std::endl;
	answer = test != test2;
	std::cout << "comparing != between test and test 2 return value is : " << answer << std::endl;
	answer = test > test2;
	std::cout << "testing test > test2 return value is : " << answer << std::endl;
	answer = test < test2;
	std::cout << "testing test < test2 return value is : " << answer << std::endl;
	answer = test <= test2;
	std::cout << "testing test <= test2 return value is : " << answer << std::endl;
	answer = test >= test2;
	std::cout << "testing test >= test2 return value is : " << answer << std::endl;
	it = test.end();
	it2 = test2.end();
	std::cout << "test current last non null value is : " << *--it << " test2 current last non null value is : " << *--it2 << std::endl;
	ft::swap(test, test2);
	it = test.end();
	it2= test2.end();
	std::cout << "used swap with non member function on test and test2, test last non null value is : " << *--it << " test2 current last non null value is : " << *--it2 << std::endl;
	test2[0] = 512;
	test2[1] = 524;
	std::cout << "used [] operator to affect 512 to test2[0] and 524 to test2[1]" << std::endl;
	n = 8;
	test.assign(n, 20);
	std::cout << "assigned 8 null terminated int of 20 value to test." << std::endl;
	ft::vector<int>::iterator it3 = test.begin();
	it3 += 2;
	it = test2.begin();
	it2 = test2.begin() + 2;
	test.insert(it3, it, it2);
	std::cout << "used insert with it and it2 position to affect values to test , its size is now " << test.size() << " new values of test are : ";
	for (int i = 0; i < test.size(); i++){
		std::cout << test[i] << " ";
	}
	std::cout << std::endl;
	test.insert(it3, 99);
	std::cout << "used insert with it3 position and the value of 99 to assign by value to the test vector. New size is : " << test.size() << " new values of test are : ";
	for (int i = 0; i < test.size(); i++){
		std::cout << test[i] << " ";
	}
	std::cout << std::endl;
	ft::vector<int> test3 = test;
	std::cout << "created a new test3 vector with first test vector as parameter , he contain these values : ";
	for (int i = 0; i < test3.size(); i++){
		std::cout << test3[i] << " ";
	}
	std::cout << std::endl;
	ft::vector<int>::reverse_iterator rv;

	rv = test3.rend();
	rv--;
	rv--;
	rv--;
	std::cout << *rv << std::endl;

	std::cout << std::endl << std::endl << std::endl;
*/

	/*ft::map<int, char> map1;
	// ITERATORS ++ PAS ENCORE IMPLEMENTE DOIT TESTER INSERT AVEC LA TROISIEME POSSIBILITE.
	map1.insert(ft::make_pair<int, char> (1, 'b'));
	map1.insert(ft::make_pair<int, char> (2, 'c'));
	map1.insert(ft::make_pair<int, char> (0, 'a'));
	map1.insert(ft::make_pair<int, char> (0, 'a'));
	std::cout << "created map1 and insert values 1,b 2,c and 0,a" << std::endl;
	ft::map<int, char>::iterator itm = map1.begin();
	ft::map<int, char>::iterator itm2 = map1.end();

	map1.insert(itm, ft::make_pair<int, char> (3, 'd'));
	std::cout << "inserted 3, d with iterator insertion method." << std::endl;
	std::cout << map1[0] << std::endl;
	std::cout << map1[1] << std::endl;
	std::cout << map1[2] << std::endl;
	std::cout << map1[3] << std::endl;
	std::cout << map1.size() << std::endl;
	itm = map1.begin();
	std::cout << "created an iterator at map1.begin he is equal to : ";
	std::cout << itm->first << " , " << itm->second << std::endl;
	map1.erase(itm);
	std::cout << "used erase on itm, map1.begin() now is : ";
	itm = map1.begin();
	std::cout << itm->first << " , " << itm->second << std::endl;
	ft::map<int, char> map2;
	std::cout << "created map2 with 10,j 9,i 11, k" << std::endl;
	map2.insert(ft::make_pair<int, char> (10 , 'j'));
	map2.insert(ft::make_pair<int, char> (9, 'i'));
	map2.insert(ft::make_pair<int, char> (11, 'k'));
	map1.swap(map2);
	std::cout << "used swap member function on map1 with map2 as parameter." << std::endl;
	itm = map1.begin();
	itm2 = map1.end(); itm2--;
	std::cout << "map1.begin() now is equal to : ";
	std::cout << itm->first << " , " << itm->second << std::endl;
	map2.insert(ft::make_pair<int, char> (6, 'f'));
	itm = map2.end(); itm--;
	std::cout << itm->first << " , " << itm->second << std::endl;
	itm--;
	std::cout << itm->first << " , " << itm->second << std::endl;
	
	std::cout << std::endl << std::endl;
	ft::map<int, char> map5;
	map5.insert(ft::make_pair<int, char> (30, 'a'));
	map5.insert(ft::make_pair<int, char> (20, 'b'));
	map5.insert(ft::make_pair<int, char> (40, 'c'));
	map5.insert(ft::make_pair<int, char> (10, 'd'));
	itm = map5.begin();
	std::cout << itm->first << std::endl;
	itm++;
	map5.erase(itm);
	itm = map5.begin();
	itm++;
	std::cout << itm->first << std::endl;

	ft::map<int, char>::iterator itm2 = map2.begin();
	ft::map<int, char>::iterator itm3 = map2.begin(); itm3++;
	for (int i = 0; i < map2.size(); i++){
		std::cout << map2[i] << std::endl;
	}
	std::cout << "created iterators itm2 and it3 equals to map2.begin() and this same value + 1" << std::endl;
	map1.insert(itm2, itm3);
	std::cout << "used map.insert(iterator first,  iterator last ) "; */
}