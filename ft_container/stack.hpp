/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrillai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:29:42 by qbrillai          #+#    #+#             */
/*   Updated: 2022/03/21 10:29:43 by qbrillai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <iostream>
# include "iterator.hpp"
# include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack
	{
		public :

		typedef T value_type;
		typedef Container container_type;
		typedef	typename Container::size_type size_type;

		explicit stack (const container_type& ctnr = container_type()) : vect(ctnr) {};

		bool empty() const {
			return (vect.empty());
		}

		size_type size() const{
			return (vect.size());
		}

		value_type& top() {
			return (vect.back());
		}

		const value_type& top() const{
			return (vect.back());
		}

		void push (const value_type& val){
			vect.push_back(val);
		}

		void pop(){
			vect.pop_back();
		}

		private :

		Container vect;

	template <class T1, class T2> friend bool operator== (const stack<T1, T2>& lhs, const stack<T1, T2>& rhs);

	template <class T1, class T2> friend bool operator!= (const stack<T1, T2>& lhs, const stack<T1, T2>& rhs);

	template <class T1, class T2> friend bool operator<  (const stack<T1, T2>& lhs, const stack<T1, T2>& rhs);

	template <class T1, class T2> friend bool operator<= (const stack<T1, T2>& lhs, const stack<T1,T2>& rhs);

	template <class T1, class T2> friend bool operator>  (const stack<T1, T2>& lhs, const stack<T1, T2>& rhs);

	template <class T1, class T2> friend bool operator>= (const stack<T1, T2>& lhs, const stack<T1, T2>& rhs);
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return(lhs.vect == rhs.vect);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.vect != rhs.vect);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.vect < rhs.vect);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.vect <= rhs.vect);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.vect > rhs.vect);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.vect >= rhs.vect);
	}
}

#endif
