#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "iterator.hpp"
# include <limits>
# include <cstddef>

namespace ft {
	template < class T, class Allocator = std::allocator<T> > class vector
	{
	public :

		typedef T value_type;
		typedef Allocator allocator_type;
		typedef size_t size_type;
		typedef typename Allocator::difference_type difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef ft::ReverseIterator <const_iterator> const_reverse_iterator;


		explicit vector (const allocator_type& alloc = allocator_type()) : allocator(alloc) {
			this->sizetab = 0;
			this->max = 0;
			this->starttab = NULL;
			this->endtab = NULL;
		};

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : allocator(alloc){
			this->sizetab = 0;
			this->endtab = NULL;
			starttab = allocator.allocate (n);
			endtab = starttab;
			max = n;
			for (size_t i = 0; i < n ; i++){
				this->push_back(val);
			}
		}

		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : allocator(alloc){
			this->sizetab = 0;
			this->max = 0;
			this->starttab = NULL;
			this->endtab = NULL;
			this->assign(first, last);
		}
		vector (const vector & x ) {
			this->starttab = NULL;
			this->endtab = NULL;
			this->sizetab = 0;
			this->max = 0;
			reserve(x.capacity());
			this->insert(this->end(), x.begin(), x.end());
		};
		virtual ~vector ( void ){};

		iterator begin(void){iterator temp(starttab); return (temp);}
		const_iterator begin(void) const {const_iterator temp(starttab); return (temp);}
		iterator end(void){iterator temp(endtab); return (temp);}
		const_iterator end(void) const {const_iterator temp(endtab); return (temp);}
		reverse_iterator rbegin(void){return(reverse_iterator((this->end())));}
		const_reverse_iterator rbegin(void) const {return(const_reverse_iterator((this->end())));}
		reverse_iterator rend(void){return(reverse_iterator((this->begin())));}
		const_reverse_iterator rend(void) const {return(const_reverse_iterator((this->begin())));}

		size_type size(void) const {return (this->sizetab);}
		size_type max_size(void) const {
			if (sizeof(value_type) == 1)
				return (allocator.max_size() / 2);
			return (allocator.max_size());

		}
		void resize (size_type n, value_type val = value_type()) // définition de cppreference, value_type si non fournie s'initialise par défaut, si fournie initialise à la valeur donnée.
		{
			if (n < this->sizetab)
			{
				for( ; this->sizetab > n; this->sizetab--)
				{
					allocator.destroy(--endtab);
				}
				return ;
			}
			 if (n > this->max)
			{
				value_type temp[this->sizetab];
				value_type *starttemp = this->starttab;
				for (size_type i = 0; i < this->sizetab; i++)
				{
					temp[i] = *starttemp;
					starttemp++;
				}
				if (n > (max * 2)){
					this->starttab = allocator.allocate (n);
					max = n;
				}
				else{
					this->starttab = allocator.allocate (max * 2);
					max = max * 2;
				}
				this->endtab = this->starttab;
				for (size_type i = 0; i < this->sizetab; i++)
				{
					allocator.construct(this->endtab, temp[i]);
					this->endtab++;
				}
			}
			if (n > this->sizetab)
			{
				for (; this->sizetab < n; this->sizetab++)
				{
					allocator.construct(this->endtab,  val);
					this->endtab++;
				}
			}
		}
		size_type capacity () const {return(this->max);}
		bool empty() const {return (this->sizetab == 0);}
		void reserve (size_type n)
		{
			if (n > this->max_size())
				throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
			else if (n > this->max)
			{
				value_type temp[this->sizetab];
				value_type *starttemp = this->starttab;
				for (size_type i = 0; i < this->sizetab; i++)
				{
					temp[i] = *starttemp;
					starttemp++;
				}
				this->starttab = allocator.allocate (n);
				max = n;
				this->endtab = this->starttab;
				for (size_type i = 0; i < this->sizetab; i++)
				{
					allocator.construct(this->endtab, temp[i]);
					this->endtab++;
				}
			}
		}

		/*void reserve (size_type n)
		{
			std::cout << "reseve" << std::endl;
			if (n > this->max_size())
				throw (std::length_error("Vector reserve asked for to much space."));
			else if (n > this->max)
			{*/
				/*value_type temp[this->sizetab];
				value_type *starttemp = this->starttab;
				for (size_type i = 0; i < this->sizetab; i++)
				{
					temp[i] = *starttemp;
					starttemp++;
				}*/
				/*if (this->sizetab == 0){
					this->starttab = allocator.allocate (n);
					this->endtab = this->starttab;
				}
				else {
					allocator.allocate(n, endtab);
				}*/

				/*for (size_type i = 0; i < this->sizetab; i++)
				{
					allocator.construct(this->endtab, temp[i]);
					this->endtab++;
				}*/
				/*this->max += n;
			}
		}*/
		
		reference operator[](size_type n) {return (*(this->starttab + n));}
		const_reference operator[](size_type n) const {return (*(this->starttab + n));}
		reference at (size_type n){
			if (n > this->sizetab)
				throw std::out_of_range("vector");
			else
				return (*(this->starttab + n));
		}
		const_reference at (size_type n) const {
			if (n >= this->sizetab)
				throw std::out_of_range("vector");
			else
				return (*(this->starttab + n));
		}
		reference front () {return (*this->starttab);}
		const_reference front () const {return (*this->starttab);}
		reference back () {return (*(this->endtab - 1));}
		const_reference back () const {return (*(this->endtab - 1));}
		
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL){
			if (this->sizetab == 0)
			{
				InputIterator temp = first;
				size_type i = 0;
				while (temp != last){
					i++;
					temp++;
				}
				starttab = allocator.allocate(i);
				max = i;
				endtab = starttab;
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
				first++;
				return ;
			}
			value_type *temp = this->starttab;
			size_t length = 0;
			InputIterator idx(first);
			while (idx != last){
				idx++;
				length++;
			}
			while (temp < this->endtab){temp->value_type::~value_type(); temp++;}
			if (length > this->max){
				// allocator.deallocate(starttab, max);
				starttab = allocator.allocate(length);
				this->max = length;
				endtab = starttab;
			}
			temp = this->starttab;
			while (first != last)
			{
				new (temp) value_type(*first);
				*temp = *first;
				first++;
				temp++;
			}
			this->endtab = temp;
			this->sizetab = length;
		}
		
		void assign(size_type n, const_reference val)
		{
			//std::cout << "here" << std::endl;
			if (this->sizetab == 0){
				resize(n, val);
				return ;
			}
			value_type *temp = this->starttab;
			while (temp < this->endtab){temp->value_type::~value_type(); temp++;}
			if (n > this->max){
				//allocator.deallocate(starttab, max);
				starttab = allocator.allocate(n);
				endtab = starttab;
				max = n;
			}
			temp = this->starttab;
			for (size_type i = 0; i < n; i++)
			{
				*temp = val;
				temp++;
			}
			this->endtab = temp;
			this->sizetab = n;
		//	std::cout << "out" << std::endl;
		}

		/*void push_back (const value_type& val)
		{
			if (this->sizetab == 0)
				this->reserve (this->max + 1);
			if (this->sizetab == this->max)
				this->reserve(this->max * 2);
			if (this->sizetab == 0)
			{
				new(this->starttab) value_type(val);
				this->endtab = starttab;
			}
			if (this->sizetab == 0){

			}
			else
				new(this->endtab) value_type(val);
			this->sizetab++;
			this->endtab++;
		}*/
		
		void push_back (const value_type& val)
		{
			if (sizetab == 0)
				this->reserve(1);
			if (this->sizetab == this->max)
			{
				this->reserve(this->max * 2);
			}
			if (this->sizetab == 0)
				endtab = starttab;
			//if (this->sizetab == 0){
//
			//}
			allocator.construct(endtab, val);
			//	*endtab = val;
			this->sizetab++;
			this->endtab++;
		}

		void pop_back (void){this->endtab--; this->sizetab--; this->endtab->value_type::~value_type();}

		iterator insert (iterator position, const value_type& val)
		{
			if (this->sizetab == 0){
				for (size_type i = 0; i < 1; i++)
					this->push_back(val);
				return(--end());
			}
			value_type *it;
			if ((this->sizetab + 1) > this->max){ // si j ai besoin d utiliser reserve.
			//	std::cout << "here1" << std::endl;
				value_type *pos = starttab;
				int index = 0;
				while (pos + index < position.p)
					index++;
				if (sizetab == max)
					this->reserve(this->max * 2);
			//	value_type *tempend = endtab;
				it = starttab + index;
				value_type temp;
				temp = *it;
				value_type temp2;
				*it = val;
				it++;
				while (it < endtab + 1){
					temp2 = *it;
					*it = temp;
					temp = temp2;
					it++;
				}
				it = starttab + index;
			}
			else {             // Si je n en ai pas besoin.
				it = position.p;
				value_type temp;
				temp = *it;
				value_type temp2;
				*it = val;
				it++;
				while (it < endtab + 1){
					temp2 = *it;
					*it = temp;
					temp = temp2;
					it++;
				}
				it = position.p;
			}
			endtab += 1;
			sizetab += 1;
		//	std::cout << *(endtab - 1) << std::endl;
			return (it);
		}

		/*void insert (iterator position, size_type n, const value_type& val)
		{
			std::cout << "here" << std::endl;
			std::cout << *begin() << std::endl;
			std::cout << *--endtab << std::endl;
			if (this->sizetab == 0){
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
				return;
			}

			if ((this->sizetab + n + 1) > this->max)
				this->reserve((this->sizetab + n + 1) * 2);
			value_type *temp = this->starttab;
			temp = position.p;
			value_type *temp2 = temp + n;
			value_type *temp3 = temp2;
			value_type *temp4 = temp;
			temp = this->endtab;
			temp2 = this->endtab + n;
			this->endtab = temp2;
			while (temp >= temp4)
			{
				new(temp2) value_type(*temp);
				temp--;
				temp2--;
			}
			temp = temp4;
			while (temp != temp3)
			{
				new(temp) value_type(val);
				temp++;
			}
			this->sizetab += n;
		}*/

		void insert (iterator position, size_type n, const value_type& val)
		{
			if (this->sizetab == 0){
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
				return;
			}
			value_type *it;
			if ((this->sizetab + n) > this->max){ // si j ai besoin d utiliser reserve.
				value_type *pos = starttab;
				int index = 0;
				while (pos + index < position.p)
					index++;
				this->reserve((this->sizetab + n));
				it = starttab + index;
				value_type tab[endtab - it + 1];
				int i = 0;
				while (it < endtab){
					tab[i] = *it;
					it++;
					i++;
				}
				it = starttab + index;
				for (size_type i = 0; i < n; i++){
					*it = val;
					it++;
				}
				for (size_type i = 0; it < endtab + n; i++){
					*it = tab[i];
					it++;
				}
			}
			else {             // Si je n en ai pas besoin.
				it = position.p;
				value_type tab[endtab - it + 1];
				size_type i = 0;
				while (it < endtab){
					tab[i] = *it;
					it++;
					i++;
				}
				it = position.p;
				for (size_type i = 0; i < n; i++){
					*it = val;
					it++;
				}
				for (size_type i = 0; it < endtab + n; i++){
					*it = tab[i];
					it++;
				}
			}
			endtab += n;
			sizetab += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			InputIterator temp2 = first;
			size_t l = 0;
			while (temp2 != last){
				l++;
				temp2++;
			}
			if (l > max){
				size_t i = 0;
				const_iterator temp;
				temp.p = starttab;
				while (temp < position){
					temp++;
					i++;
				}
				reserve(l + sizetab);
				position.p = starttab + i;
			}
			if (this->sizetab == 0){
				while (first != last){

					this->push_back(*first);
					first++;
				}
				return ;
			}
			while (first != last){
				position = insert(position, *first);
				position++;
				first++;
			}
		}

		iterator erase (iterator position)
		{
		//	std::cout << "here" << std::endl;
			iterator temp = position;
			while(temp != this->endtab){
				new (temp.p) value_type (*(++temp));
			}
		//	std::cout << "here" << std::endl;
			temp.p->value_type::~value_type();
		//	std::cout << "here" << std::endl;
			this->endtab--;
			this->sizetab--;
			return (position);
		}

		iterator erase (iterator first, iterator last)
		{
			iterator temp;
			while (first != last){
				temp = this->erase(first);
				last--;
			}
			return (temp);
		}

		void swap (vector& x)
		{
			value_type *temp = this->starttab;
			this->starttab = x.starttab;
			x.starttab = temp;
			temp = this->endtab;
			this->endtab = x.endtab;
			x.endtab = temp;
			size_type temp2 = this->sizetab;
			this->sizetab = x.sizetab;
			x.sizetab = temp2;
			temp2 = this->max;
			this->max = x.max;
			x.max = temp2;
		}

		void clear()
		{
			while (this->starttab != this->endtab)
			{
				this->starttab->value_type::~value_type();
				this->starttab++;
			}
			endtab = starttab;
			this->sizetab = 0;
		}

		allocator_type get_allocator() const
		{
			allocator_type temp;
			return (temp);
		}

		vector & operator=(const vector & x){
			if (*this == x)
				return (*this);
			if (sizetab > 0)
				this->clear();
			this->sizetab = 0;
			if (x.size() > this->capacity()){
				//if (starttab != NULL)
				//	allocator.deallocate (starttab, max);
				starttab = allocator.allocate(x.size());
				endtab = starttab;
				max = x.size();
			}
			
			this->insert(this->end(), x.begin(), x.end());
			return (*this);
		}; 
	private :
		allocator_type allocator;
		value_type *starttab;
		value_type *endtab;
		size_type sizetab;
		size_type max;
	};

	template <class T, class Alloc>
	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator== (const ft::vector<T, Alloc>& lhs, const  ft::vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator start1 = lhs.begin();
		typename ft::vector<T>::const_iterator start2 = rhs.begin();
		while (start1 != lhs.end()){
			if (*start1 != *start2)
				return (false);
			start1++;
			start2++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator== (ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) 
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator start1 = lhs.begin();
		typename ft::vector<T>::const_iterator start2 = rhs.begin();
		while (start1 != lhs.end()){
			if (*start1 != *start2)
				return (false);
			start1++;
			start2++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}

	template <class T, class Alloc>
	bool operator<  (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs){return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template <class T, class Alloc>
	bool operator<= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs){return (!(rhs < lhs));} // si lhs est supérieur à rhs, il ne peut pas être inférieur ou égal.}

	template <class T, class Alloc>
	bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){return (!(lhs <= rhs));}

	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){return (!(lhs < rhs));}
}

#endif