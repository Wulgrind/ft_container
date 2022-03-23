/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrillai <qbrillai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:29:25 by qbrillai          #+#    #+#             */
/*   Updated: 2022/03/23 17:48:49 by qbrillai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <vector>
#include <map>
#include <stack>
#include "map.hpp"
#include "iterator.hpp"
#include "redblacktree.hpp"
#include "set.hpp"

template <class T>
void ft_test(typename ft::vector<T> ft_c0)
{
	typename ft::vector<T>::iterator ft_ret = ft_c0.begin();
	std::cout << "size = " << ft_c0.size() << std::endl;
	std::cout << "max size = " << ft_c0.max_size() << std::endl;
	while (ft_ret != ft_c0.end())
	{
		std::cout << *ft_ret << std::endl;
		ft_ret++;
	}
	std::cout << std::endl;
}

template <class T>
void std_test(typename std::vector<T> std_c0)
{
	typename std::vector<T>::iterator std_ret = std_c0.begin();
	std::cout << "size = " << std_c0.size() << std::endl;
	std::cout << "max size = " << std_c0.max_size() << std::endl;
	while (std_ret != std_c0.end())
	{
		std::cout << *std_ret << std::endl;
		std_ret++;
	}
	std::cout << std::endl;
}

template <class T1, class T2>
void ft_map(typename ft::map<T1, T2> map_c0)
{
	typename ft::map<T1, T2>::iterator ft_ret = map_c0.begin();
	std::cout << "size = " << map_c0.size() << std::endl;
	std::cout << "max size = " << map_c0.max_size() << std::endl;
	while (ft_ret != map_c0.end())
	{
		std::cout << "key type value is " << ft_ret->first << " mapped type value is " << ft_ret->second << std::endl;
		ft_ret++;
	}
	std::cout << std::endl;
}

template <class T1 , class T2>
void std_map(typename std::map<T1, T2> map_c1)
{
	typename std::map<T1, T2>::iterator std_ret = map_c1.begin();
	std::cout << "size = " << map_c1.size() << std::endl;
	std::cout << "max size = " << map_c1.max_size() << std::endl;
	while (std_ret != map_c1.end())
	{
		std::cout << "key type value is " << std_ret->first << " mapped type value is " << std_ret->second << std::endl;
		std_ret++;
	}
	std::cout << std::endl;
}

int	main()
{
	
	ft::vector<int>		ft_c0;
	std::vector<int>	std_c0;
	ft::vector<int>		ft_c1;
	std::vector<int>	std_c1;
	ft_c1.push_back(7);
	ft_c1.push_back(83);
	std_c1.push_back(7);
	std_c1.push_back(83);
	ft::vector<int>::iterator	ft_ret;
	ft::vector<int>::const_iterator	ft_cret;
	std::vector<int>::iterator	std_ret;
	std::vector<int>::const_iterator	std_cret;

	std::cout << "TESTS FOR VECTOR" << std::endl << std::endl;

	std::cout << "FT TEST EMPTY" << std::endl;
	std::cout << ft_c0.empty() << std::endl << std::endl;
	std::cout << "STD TEST EMPTY" << std::endl;
	std::cout << std_c0.empty() << std::endl << std::endl;

	std::cout << "FT TEST PUSH_BACK" << std::endl;
	ft_c0.push_back(42);
	ft_test(ft_c0);
	std::cout << "STD TEST PUSH_BACK" << std::endl;
	std_c0.push_back(42);	
	std_test (std_c0);

	std::cout << "FT TEST INSERT" << std::endl;
	ft_c0.insert(ft_c0.begin(), 10);
	ft_test(ft_c0);
	std::cout << "STD TEST INSERT" << std::endl;
	std_c0.insert(std_c0.begin(), 10);	
	std_test (std_c0);

	std::cout << "FT TEST INSERT MULTIPLE" << std::endl;
	ft_c0.insert(ft_c0.end(), 3, 5);
	ft_test(ft_c0);
	std::cout << "STD TEST INSERT MULTIPLE" << std::endl;
	std_c0.insert(std_c0.end(), 3,  5);	
	std_test (std_c0);

	std::cout << "FT TEST INSERT RANGE" << std::endl;
	ft_c0.insert(ft_c0.end(), ft_c1.begin(), ft_c1.begin() + 2);
	ft_test(ft_c0);
	std::cout << "STD TEST INSERT RANGE" << std::endl;
	std_c0.insert(std_c0.end(), std_c1.begin(), std_c1.begin() + 2);	
	std_test (std_c0);

	std::cout << "FT TEST POP_BACK" << std::endl;
	ft_c0.pop_back();
	ft_test(ft_c0);
	std::cout << "STD TEST POP_BACk" << std::endl;
	std_c0.pop_back();	
	std_test (std_c0);

	std::cout << "FT TEST ERASE" << std::endl;
	ft_c0.erase(ft_c0.end() - 2);
	ft_test(ft_c0);
	std::cout << "STD TEST ERASE" << std::endl;
	std_c0.erase(std_c0.end() - 2);	
	std_test (std_c0);

	std::cout << "FT TEST ERASE RANGE" << std::endl;
	ft_c0.erase(ft_c0.end() - 2, ft_c0.end());
	ft_test(ft_c0);
	std::cout << "STD TEST ERASE RANGE" << std::endl;
	std_c0.erase(std_c0.end() - 2, std_c0.end());	
	std_test (std_c0);

	std::cout << "FT TEST CLEAR" << std::endl;
	ft_c0.clear();
	ft_test(ft_c0);
	std::cout << "STD TEST CLEAR" << std::endl;
	std_c0.clear();	
	std_test (std_c0);

	std::cout << "FT TEST SWAP" << std::endl;
	ft_c0.swap(ft_c1);
	ft_test(ft_c0);
	std::cout << "STD TEST SWAP" << std::endl;
	std_c0.swap(std_c1);	
	std_test (std_c0);

	std::cout << "FT TEST GET ALLOCATOR" << std::endl;
	std::allocator<int> alloc = ft_c0.get_allocator();
	alloc.construct(&*ft_c0.begin(), 102);
	ft_test(ft_c0);
	std::cout << "STD TEST GET ALLOCATOR" << std::endl;
	std::allocator<int> alloc1 = std_c0.get_allocator();
	alloc1.construct(&*std_c0.begin(), 102);
	std_test (std_c0);

	std::cout << "FT TEST ASSIGN" << std::endl;
	ft_c0.assign(5,10);
	ft_test(ft_c0);
	std::cout << "STD TEST ASSIGN" << std::endl;
	std_c0.assign(5,10);	
	std_test (std_c0);

	ft_c1.assign(3, 2);
	std_c1.assign(3 , 2);

	std::cout << "FT TEST ASSIGN RANGE" << std::endl;
	ft_c0.assign(ft_c1.begin(), ft_c1.begin() + 2);
	ft_test(ft_c0);
	std::cout << "STD TEST ASSIGN RANGE" << std::endl;
	std_c0.assign(std_c1.begin(), std_c1.begin () + 2);	
	std_test (std_c0);

	ft_c0.push_back(8);
	std_c0.push_back(8);
	ft_c0.push_back(4);
	std_c0.push_back(4);
	ft_c0.push_back(6);
	std_c0.push_back(6);

	std::cout << "FT TEST []" << std::endl;
	std::cout << ft_c0[3] << std::endl << std::endl;
	std::cout << "STD TEST []" << std::endl;
	std::cout << std_c0[3] << std::endl << std::endl;
	
	std::cout << "FT TEST AT" << std::endl;
	std::cout << ft_c0.at(2) << std::endl << std::endl;
	std::cout << "STD TEST AT" << std::endl;
	std::cout << std_c0.at(2) << std::endl << std::endl;

	std::cout << "FT TEST FRONT" << std::endl;
	std::cout << ft_c0.front() << std::endl << std::endl;
	std::cout << "STD TEST FRONT" << std::endl;
	std::cout << std_c0.front() << std::endl << std::endl;

	std::cout << "FT TEST BACK" << std::endl;
	std::cout << ft_c0.back() << std::endl << std::endl;
	std::cout << "STD TEST BACK" << std::endl;
	std::cout << std_c0.back() << std::endl << std::endl;

	std::cout << "FT TEST CAPACITY" << std::endl;
	std::cout << ft_c0.capacity() << std::endl << std::endl;
	std::cout << "STD TEST CAPACITY" << std::endl;
	std::cout << std_c0.capacity() << std::endl << std::endl;

	std::cout << "FT TEST RESERVE" << std::endl;
	ft_c0.reserve(100);
	std::cout << ft_c0.capacity() << std::endl << std::endl;
	std::cout << "STD TEST RESERVE" << std::endl;
	std_c0.reserve(100);
	std::cout << std_c0.capacity() << std::endl << std::endl;


	std::cout << "FT TEST '='" << std::endl;
	ft_c1 = ft_c0;
	ft_test(ft_c1);
	std::cout << "STD TEST '='" << std::endl;
	std_c1 = std_c0;
	std_test(std_c1);

	ft_c0.push_back(58);
	std_c0.push_back(58);

	std::cout << "FT TEST ITERATORS" << std::endl;
	std::cout << *ft_c0.begin() << std::endl;
	std::cout << *(ft_c0.end() - 1) << std::endl;
	std::cout << *(ft_c0.rend() -1) << std::endl;
	std::cout << *ft_c0.rbegin() << std::endl << std::endl;
	ft_cret = ft_ret;
	
	std::cout << "STD TEST ITERATORS" << std::endl;
	std::cout << *std_c0.begin() << std::endl;
	std::cout << *(std_c0.end() - 1) << std::endl;
	std::cout << *(std_c0.rend() - 1) << std::endl;
	std::cout << *std_c0.rbegin() << std::endl << std::endl;
	std_cret = std_cret;

	std::cout << "FT TEST RESIZE" << std::endl;
	ft_c0.resize(3);
	ft_test(ft_c0);
	std::cout << "STD TEST RESIZE" << std::endl;
	std_c0.resize(3);
	std_test(std_c0);

	std::cout << "FT TEST RELATIONAL OPERATORS" << std::endl;
	std::cout << (ft_c0 == ft_c1) << std::endl;
	std::cout << (ft_c0 != ft_c1) << std::endl;
	std::cout << (ft_c0 <  ft_c1) << std::endl;
	std::cout << (ft_c0 <= ft_c1) << std::endl;
	std::cout << (ft_c0 > ft_c1) << std::endl;
	std::cout << (ft_c0 >= ft_c1) << std::endl << std::endl;
	std::cout << "STD TEST RELATIONAL OPERATORS" << std::endl;
	std::cout << (std_c0 == std_c1) << std::endl;
	std::cout << (std_c0 != std_c1) << std::endl;
	std::cout << (std_c0 <  std_c1) << std::endl;
	std::cout << (std_c0 <= std_c1) << std::endl;
	std::cout << (std_c0 > std_c1) << std::endl;
	std::cout << (std_c0 >= std_c1) << std::endl << std::endl;

	ft_ret = ft_c0.begin();
	std_ret = std_c0.begin();
	
	std::cout << "FT TEST ITERATOR RELATIONAL OPERATORS & INCRE/DECREMENTATION" << std::endl;
	std::cout << *(++ft_ret) << std::endl;
	std::cout << *(ft_ret++) << std::endl;
	std::cout << *(--ft_ret) << std::endl;
	std::cout << *(ft_ret--) << std::endl;
	std::cout << *++ft_ret << std::endl;
	std::cout << *--ft_ret << std::endl;
	std::cout << (ft_ret == ft_c0.begin() + 2) << std::endl;
	std::cout << (ft_ret != ft_c0.begin() + 2) << std::endl;
	std::cout << *ft_ret << std::endl;
	std::cout << *(ft_ret += 2) << std::endl;
	std::cout << (*ft_ret -= 2) << std::endl;
	std::cout << (ft_ret < ft_c0.end()) << std::endl;
	std::cout << (ft_ret > ft_c0.end()) << std::endl;
	std::cout << (ft_ret <= ft_c0.end()) << std::endl;
	std::cout << (ft_ret >= ft_c0.end()) << std::endl;
	std::cout << (ft_ret == ft_c0.end()) << std::endl;
	std::cout << (ft_ret != ft_c0.end()) << std::endl;
	std::cout << (ft_ret[2]) << std::endl << std::endl;

	std::cout << "STD TEST ITERATOR RELATIONAL OPERATORS & INCRE/DECREMENTATION" << std::endl;
	std::cout << *(++std_ret) << std::endl;
	std::cout << *(std_ret++) << std::endl;
	std::cout << *(--std_ret) << std::endl;
	std::cout << *(std_ret--) << std::endl;
	std::cout << *++std_ret << std::endl;
	std::cout << *--std_ret << std::endl;
	std::cout << (std_ret == std_c0.begin() + 2) << std::endl;
	std::cout << (std_ret != std_c0.begin() + 2) << std::endl;
	std::cout << *std_ret << std::endl;
	std::cout << *(std_ret += 2) << std::endl;
	std::cout << (*std_ret -= 2) << std::endl;
	std::cout << (std_ret < std_c0.end()) << std::endl;
	std::cout << (std_ret > std_c0.end()) << std::endl;
	std::cout << (std_ret <= std_c0.end()) << std::endl;
	std::cout << (std_ret >= std_c0.end()) << std::endl;
	std::cout << (std_ret == std_c0.end()) << std::endl;
	std::cout << (std_ret != std_c0.end()) << std::endl;
	std::cout << (std_ret[2]) << std::endl << std::endl;

	std::cout << "TESTS FOR MAP" << std::endl << std::endl;

	ft::map<int, char> map0;
	std::map<int, char> map1;
	ft::map<int, char> map2;
	std::map<int, char> map3;
	map2.insert(ft::pair<int, char>(5, 'e'));
	map2.insert(ft::pair<int, char>(6, 'f'));
	map2.insert(ft::pair<int, char>(7, 'g'));

	map3.insert(std::pair<int, char>(5, 'e'));
	map3.insert(std::pair<int, char>(6, 'f'));
	map3.insert(std::pair<int, char>(7, 'g'));

	std::cout << "FT TEST EMPTY" << std::endl;
	std::cout << map0.empty() << std::endl;
	std::cout << "STD TEST EMPTY" << std::endl;
	std::cout << map1.empty() << std::endl << std::endl;

	std::cout << "FT TEST EMPTY" << std::endl;
	std::cout << map0.empty() << std::endl;
	std::cout << "STD TEST EMPTY" << std::endl;
	std::cout << map1.empty() << std::endl << std::endl;

	std::cout << "FT TEST INSERT" << std::endl;
	map0.insert(ft::pair<int, char>(3, 'c'));
	ft_map(map0);
	std::cout << "STD TEST INSERT" << std::endl;
	map1.insert(std::pair<int, char>(3, 'c'));
	std_map(map1);

	std::cout << "FT TEST INSERT HINT" << std::endl;
	map0.insert(map0.begin(), ft::pair<int, char>(2, 'b'));
	ft_map(map0);
	std::cout << "STD TEST INSERT HINT" << std::endl;
	map1.insert(map1.begin(), std::pair<int, char>(2, 'b'));
	std_map(map1);

	std::cout << "FT TEST INSERT RANGE" << std::endl;
	map0.insert(map2.begin(), map2.end());
	ft_map(map0);
	std::cout << "STD TEST INSERT RANGE" << std::endl;
	map1.insert(map3.begin(), map3.end());
	std_map(map1);

	std::cout << "FT TEST ERASE" << std::endl;
	map0.erase(map0.begin());
	ft_map(map0);
	std::cout << "STD TEST ERASE" << std::endl;
	map1.erase(map1.begin());
	std_map(map1);

	std::cout << "FT TEST ERASE KEY" << std::endl;
	map0.erase(7);
	ft_map(map0);
	std::cout << "STD TEST ERASE KEY" << std::endl;
	map1.erase(7);
	std_map(map1);

	std::cout << "FT TEST ERASE RANGE" << std::endl;
	map0.erase(map0.begin(), --map0.end());
	ft_map(map0);
	std::cout << "STD TEST ERASE RANGE" << std::endl;
	map1.erase(map1.begin(), --map1.end());
	std_map(map1);

	std::cout << "FT TEST CLEAR" << std::endl;
	map0.clear();
	ft_map(map0);
	std::cout << "STD TEST CLEAR" << std::endl;
	map1.clear();
	std_map(map1);

	std::cout << "FT TEST KEY COMP" << std::endl;
	ft::map<int,char>::key_compare mycomp = map0.key_comp();
	std::cout << mycomp(2, 3) << std::endl;
	std::cout << "STD TEST KEY COMP" << std::endl;
	std::map<int,char>::key_compare mycomp1 = map1.key_comp();
	std::cout << mycomp1(2, 3) << std::endl;
	
	std::cout << "FT TEST INSERTION WITH []" << std::endl;
	map0[100]='x';
 	map0[50]='y';
 	map0[13]='z';
	ft_map(map0);
	std::cout << "STD TEST INSERTION WITH []" << std::endl;
	map1[100]='x';
 	map1[50]='y';
 	map1[13]='z';
	std_map(map1);

	std::cout << "FT TEST VALUE COMP" << std::endl;
	ft::pair<int,char> highest = *map0.rbegin();          // last element
	ft::map<int,char>::iterator it = map0.begin();
	do {
   	 std::cout << it->first << " => " << it->second << '\n';
	} while (map0.value_comp()(*it++, highest) );
	std::cout << std::endl;
	std::cout << "STD TEST VALUE COMP" << std::endl;
	std::pair<int,char> highest1 = *map1.rbegin();          // last element
	std::map<int,char>::iterator it1 = map1.begin();
	do {
   	 std::cout << it1->first << " => " << it1->second << '\n';
	} while (map1.value_comp()(*it1++, highest1) );
	std::cout << std::endl << std::endl;

	std::cout << "FT TEST FIND" << std::endl;
	it = map0.find(50);
	std::cout << it->first << it->second << std::endl << std::endl;
	std::cout << "STD TEST FIND" << std::endl;
	it1 = map1.find(50);
	std::cout << it1->first << it1->second << std::endl << std::endl;

	std::cout << "FT TEST COUNT" << std::endl;
	std::cout << map0.count(50) << std::endl << std::endl;
	std::cout << "STD TEST COUNT" << std::endl;
	std::cout << map1.count(50) << std::endl << std::endl;

	std::cout << "FT TEST LOWER BOUND" << std::endl;
	std::cout << map0.lower_bound(50)->first << std::endl;
	std::cout << "STD TEST LOWER BOUND" << std::endl;
	std::cout << map1.lower_bound(50)->first << std::endl << std::endl;

	std::cout << "FT TEST UPPER BOUND" << std::endl;
	std::cout << map0.upper_bound(50)->first << std::endl;
	std::cout << "STD TEST UPPER BOUND" << std::endl;
	std::cout << map1.upper_bound(50)->first << std::endl << std::endl;

	std::cout << "FT TEST EQUAL RANGE" << std::endl;
	std::cout << map0.equal_range(100).first->first << std::endl;
	std::cout << map0.equal_range(100).first->second << std::endl;
	std::cout << map0.equal_range(100).second->first << std::endl;
	std::cout << map0.equal_range(100).second->second << std::endl;
	std::cout << "STD TEST EQUAL RANGE" << std::endl;
	std::cout << map1.equal_range(100).first->first << std::endl;
	std::cout << map1.equal_range(100).first->second << std::endl;
	std::cout << map0.equal_range(100).second->first << std::endl;
	std::cout << map0.equal_range(100).second->second << std::endl;

	
	std::cout << "FT TEST GET ALLOCATOR" << std::endl;
	std::allocator<std::pair<int, char> > alloc2 = ft_c0.get_allocator();
	std::cout << alloc2.max_size() << std::endl << std::endl;
	std::cout << "STD TEST GET ALLOCATOR" << std::endl;
	std::allocator<std::pair<int, char> > alloc3 = std_c0.get_allocator();
	std::cout << alloc3.max_size() << std::endl << std::endl;

	std::cout << "FT TEST SWAP" << std::endl;
	map0.swap(map2);
	ft_map(map0);
	std::cout << "STD TEST SWAP" << std::endl;
	map1.swap(map3);
	std_map(map1);

	std::cout << "FT TEST =" << std::endl;
	map0 = map2;
	ft_map(map0);
	std::cout << "STD TEST =" << std::endl;
	map1 = map3;
	std_map(map1);

	std::cout << "FT TEST RELATIONAL OPERATORS" << std::endl;
	std::cout << (map0.begin() == map0.end()) << std::endl;
	std::cout << (map0.begin() != map0.end()) << std::endl;
	std::cout << ((*map0.begin()).first) << std::endl;
	std::cout << map0.begin()->first << std::endl;
	std::cout << "STD TEST RELATIONAL OPERATORS" << std::endl;
	std::cout << (map1.begin() == map1.end()) << std::endl;
	std::cout << (map1.begin() != map1.end()) << std::endl;
	std::cout << ((*map1.begin()).first) << std::endl;
	std::cout << map1.begin()->first << std::endl << std::endl;

	std::cout << "TESTS FOR STACK" << std::endl << std::endl;

	ft::stack<int> stack0;
	ft::stack<int> stack2;
 	std::stack<int> stack1;
	std::stack<int> stack3;

	std::cout << "FT TEST EMPTY" << std::endl;
	std::cout << stack0.empty() << std::endl;
	std::cout << "STD TEST EMPTY" << std::endl;
	std::cout << stack1.empty() << std::endl;

	std::cout << "FT TEST PUSH" << std::endl;
	stack0.push(5);
	stack0.push(9);
	std::cout << "STD TEST PUSH" << std::endl;
	stack1.push(5);
	stack1.push(9);
	
	std::cout << "FT TEST TOP" << std::endl;
	std::cout << stack0.top() << std::endl << std::endl;
	std::cout << "STD TEST TOP" << std::endl;
	std::cout << stack1.top() << std::endl << std::endl;
	
	std::cout << "FT TEST SIZE" << std::endl;
	std::cout << stack0.size() << std::endl << std::endl;
	std::cout << "STD TEST SIZE" << std::endl;
	std::cout << stack1.size() << std::endl << std::endl;

	std::cout << "FT TEST POP" << std::endl;
	stack0.pop();
	std::cout << stack0.top() << std::endl << std::endl;
	std::cout << "STD TEST POP" << std::endl;
	stack1.pop();
	std::cout << stack1.top() << std::endl << std::endl;

	std::cout << "FT TEST RELATIONAL OPERATORS" << std::endl;
	std::cout << (stack0 == stack2) << std::endl;
	std::cout << (stack0 != stack2) << std::endl;
	std::cout << (stack0 < stack2) << std::endl;
	std::cout << (stack0 <= stack2) << std::endl;
	std::cout << (stack0 > stack2) << std::endl;
	std::cout << (stack0 >= stack2) << std::endl << std::endl;
	std::cout << "STD TEST RELATIONAL OPERATORS" << std::endl;
	std::cout << (stack1 == stack3) << std::endl;
	std::cout << (stack1 != stack3) << std::endl;
	std::cout << (stack1 < stack3) << std::endl;
	std::cout << (stack1 <= stack3) << std::endl;
	std::cout << (stack1 > stack3) << std::endl;
	std::cout << (stack1 >= stack3) << std::endl << std::endl;

	std::cout << "FT TEST ITERATOR TRAITS" << std::endl;
	ft::iterator_traits<int *>::value_type i = 8; 
	std::cout << i << std::endl << std::endl;
	std::cout << "STD TEST ITERATOR TRAITS" << std::endl;
	std::iterator_traits<int *>::value_type j = 8; 
	std::cout << j << std::endl << std::endl;

	std::cout << "FT TEST IS INTEGRAL" << std::endl;
	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "STD TEST IS INTEGRAL" << std::endl;
	std::cout << "char: " << std::is_integral<char>::value << std::endl;
  	std::cout << "int: " << std::is_integral<int>::value << std::endl;
	std::cout << "float: " << std::is_integral<float>::value << std::endl;
	
 }