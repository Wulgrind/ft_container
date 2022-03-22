/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrillai <qbrillai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:29:21 by qbrillai          #+#    #+#             */
/*   Updated: 2022/03/22 14:41:32 by qbrillai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iostream>
# include "redblacktree.hpp"

namespace ft {

	template <class T1, class T2>
	struct pair{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair & operator=(const pair & src)
		{
			this->first = src.first;
			this->second = src.second;
			return (*this);
		}

		pair() : first(),second() {} // regarder std::pair::pair

		template<class U, class V>
		pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {};

		pair (const first_type& a, const second_type& b) : first(a), second(b) {};

		bool operator==(const pair & src){
			if (this->first != src.first)
				return (0);
			if (this->second != src.second)
				return (0);
			return (1);
		}

		bool operator!=(const pair & src){
			if (this->first == src.first && this->second == src.second)
				return (0);
			return (1);
		}	
	};
	
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
 	{
    	return (pair<T1,T2>(x,y) );
  	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
 		while (first1!=last1) {
    		if (!(*first1 == *first2))
     		return false;
    		++first1; ++first2;
		}
 	 	return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
  		while (first1!=last1)
  		{
    		if (first2==last2 || *first2<*first1) return false;
    		else if (*first1<*first2) return true;
    		++first1; ++first2;
 		 }
  		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compareMap (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
  		while (first1 != last1)
  		{
    		if (first2 == last2 || first2->first < first1->first || first2->second < first1->second) return false;
    		else if (first1->first < first2->first || first1->second < first2->second) return true;
    		++first1; ++first2;
 		 }
  		return (first2!=last2);
	}

	template <bool B, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T> { typedef T type; }; // type ne sera crée à partir de T que si True. Alors la suite sera exécutée. 

	template<class T>
	struct enable_if<false, T>{}; // type n'est pas crée, donc pas trouvable et une autre déclaration sera recherchée.

	template <typename>
	struct is_integral_type{static const bool value = false;};

	template <>
	struct is_integral_type<bool>{static const bool value = true;};

	template<>
	struct is_integral_type<char>{static const bool value = true;};

	template<>
	struct is_integral_type<unsigned char>{static const bool value = true;};

	template<>
	struct is_integral_type<int>{static const bool value = true;};

	template <>
	struct is_integral_type<short int>{static const bool value = true;};

	template <>
	struct is_integral_type<long int>{static const bool value = true;};

	template <>
	struct is_integral_type<long long int>{static const bool value = true;};

	template <>
	struct is_integral_type<unsigned int>{static const bool value = true;};

	template <>
	struct is_integral_type <unsigned short int>{static const bool value = true;};

	template <>
	struct is_integral_type<unsigned long int>{static const bool value = true;};

	template <>
	struct is_integral_type<unsigned long long int>{static const bool value = true;};

	template <typename T>
    struct is_integral : public is_integral_type<T> {};

	class random_access_iterator_tag {};
	class bidirectionnal_iterator_tag {};
	class input_iterator_tag {};

	template <class iter> struct iterator_traits {
        typedef typename iter::value_type            value_type;
        typedef typename iter::difference_type       difference_type;
        typedef typename iter::iterator_category     iterator_category;
        typedef typename iter::pointer               pointer;
        typedef typename iter::reference             reference;
    };

	template <class T> struct iterator_traits<T *> { // specialisation pour types donnes qui peuvent utilises comme iterateurs, int ,double etc
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

	template <class T> struct iterator_traits<const T *> { 
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };
	
	
	template <typename T> class InputIterator
	{
		public :

		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type const * const_pointer;
		typedef value_type& reference;
		typedef value_type const & const_reference;
		typedef std::ptrdiff_t difference_type;
		typedef InputIterator iterator;
		typedef input_iterator_tag iterator_category;
		value_type *p;

		InputIterator ( void ) : p(NULL){};
		InputIterator (value_type *p2) : p(p2) {};
		InputIterator ( iterator const & src ) {this->p = src.p;}
		~InputIterator( void ) {};
		
		iterator & operator=(iterator const & rhs) {this->p = reinterpret_cast<value_type *>(rhs->p); return *this;}
		iterator & operator=(value_type *src) {this->p = src; return *this;}
		iterator & operator++(void) {this->p++; return *this;}
		iterator operator++(int) {iterator temp(*this); operator++(); return (temp);}
		iterator & operator--(void) {this->p--; return *this;}
		iterator operator--(int) {iterator temp(*this); operator--(); return (temp);}
		bool operator==(iterator const& src) const {return (this->p == src->pointer);}
		bool operator!=(iterator const& src) const {return (this->p != src->pointer);}
		value_type & operator*(void) {return(*this->p);}
		value_type * operator->(void) {return (this->p.clé.second);}
		
		private :

	};

	template <typename T, class Compare> class bidirectionnalIterator
	{
		public :

		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type const * const_pointer;
		typedef value_type& reference;
		typedef value_type const & const_reference;
		typedef std::ptrdiff_t difference_type;
		typedef bidirectionnalIterator iterator;
		typedef bidirectionnal_iterator_tag iterator_category;
		typedef typename value_type::first_type first_type;

		bidirectionnalIterator ( void ) : p(NULL){};
		bidirectionnalIterator (noeud<value_type> *p2) : p(p2) {};
		bidirectionnalIterator(bidirectionnalIterator<T, Compare> & src){this->p = src.p;}
		template <typename U>
		bidirectionnalIterator (noeud<U> *p2) {this->p = reinterpret_cast<noeud<value_type> *>(p2);}
		//template <typename U>
		//bidirectionnalIterator (bidirectionnalIterator<U> const & rhs){this->p = reinterpret_cast<noeud<value_type> *>(rhs.p);}
	//	bidirectionnalIterator (bidirectionnalIterator<U> const & rhs){this->p = rhs.p;}
		bidirectionnalIterator ( const iterator & src ) {this->p = reinterpret_cast<noeud<value_type> *>(src.p);}
		~bidirectionnalIterator ( void ) {};
		/*template <typename U>
		bidirectionnalIterator<T> & operator=(bidirectionnalIterator<U> const & rhs){this->p = reinterpret_cast<noeud<value_type> *>(rhs.p); return *this;}*/
		bidirectionnalIterator<T, Compare> & operator=(bidirectionnalIterator<const T, Compare> const & rhs){this->p = rhs.p; return *this;}
		//iterator & operator=(iterator const & rhs) {this->p = rhs.p; return *this;}
		//iterator & operator=(iterator const & rhs) {this->p = reinterpret_cast<noeud<value_type> *>(rhs.p); return *this;}
		iterator & operator=(value_type *src) {this->p = src; return *this;}
		iterator & operator++(void) { // Pour itérer on prend la valeur la plus à gauche de l'enfant droit. Sinon nous devons remonter jusqu'à une valeur supérieure à notre noeud actuel, donc dont il n'est pas l'enfant droit.
			if(this->p->couleur == 10)
				return *this;
			if (this->p->droit != NULL) {
      			this->p = this->p->droit;
      			while (this->p->gauche != NULL)
       				this->p = this->p->gauche;
    		}
   			else if (this->p->parent != NULL){
     			noeud<T> *parentp = this->p->parent;
    			while (this->p == parentp->droit) {
					//std::cout << this->p->parent->clé.first << std::endl;
					if (parentp->parent == NULL){
						if (parentp->clé.first < this->p->clé.first)
							this->p = parentp;
						else if (parentp->droit)
							this->p = parentp->droit;
						break;
					}
        			this->p = parentp;
        			parentp = parentp->parent;
    			}
      			if (this->p->droit != parentp)
       				this->p = parentp;
  			}
			return *this;
		}
		iterator operator++(int) {iterator temp(*this); operator++(); return (temp);}
		iterator & operator--(void) {
			if (this->p->couleur == 10){ // pour le past the end
				this->p = this->p->parent;
				return *this;
			}
			if(this->p->gauche != NULL){
				this->p = this->p->gauche;
				while(this->p->droit != NULL)
					this->p = this->p->droit;
			}
			else if (this->p->parent != NULL){
				noeud<T> *parentp = this->p->parent;
				while (this->p == parentp->gauche) {
					this->p = parentp;
					parentp = parentp->parent;
				}
				if (this->p->gauche != parentp)
					this->p = parentp;
			}
			return *this;
		}
		iterator operator--(int) {iterator temp(*this); operator--(); return (temp);}
		bool operator==(iterator const& src) const {return (this->p == src.p);}
		//bool operator==(iterator & src) const {return (this->p == src.p);}
		bool operator!=(iterator const& src) const {return (this->p != src.p);}
		//bool operator!=(iterator & src) const {return (this->p != src.p);}
		value_type & operator*(void) const {return(this->p->clé);}
		value_type * operator->(void) const {return (&this->p->clé);}
		noeud<value_type> *p;

		
		operator bidirectionnalIterator<const T, Compare> () const{
			return (bidirectionnalIterator<const T, Compare>(this->p));}
		
		private :
		
	};

	template <typename T, typename Compare>
    bool operator!=(const ft::bidirectionnalIterator<T, Compare> lhs, const ft::bidirectionnalIterator<T, Compare> rhs)
    {
        return (lhs.p != reinterpret_cast<noeud<T> *>(rhs.p));
    }

	template <typename T, typename Compare>
    bool operator==(const ft::bidirectionnalIterator<T, Compare> lhs, const ft::bidirectionnalIterator<T, Compare> rhs)
    {
        return (lhs.p == reinterpret_cast<noeud<T> *>(rhs.p));
	}

	template <typename T> class random_access_iterator
	{
		public :

		/*typedef typename traits::value_type             value_type;
    	typedef typename traits::pointer                pointer;
    	typedef typename traits::reference              reference;
        typedef typename traits::difference_type        difference_type;
        typedef typename traits::iterator_category      iterator_category;*/

		typedef T value_type;
		typedef T* pointer;
		typedef value_type const * const_pointer;
		typedef value_type& reference;
		typedef value_type const & const_reference;
		typedef std::ptrdiff_t difference_type; // résultat de la soustraction d'iterators.
		typedef random_access_iterator_tag iterator_category;
		pointer p;

		random_access_iterator () : p(NULL){};
		random_access_iterator (value_type *p) : p(p) {};
		random_access_iterator (const random_access_iterator & src ) : p(src.p){}
		//random_access_iterator (ft::random_access_iterator<const value_type> & src){this->p = src.p;}
		//random_access_iterator (const random_access_iterator & src) : p(src.p) {};
		virtual ~random_access_iterator ( void ) {};
		random_access_iterator & operator=(random_access_iterator const & rhs) {this->p = reinterpret_cast<value_type *>(rhs.p); return *this;}
		random_access_iterator & operator=(value_type *src) {this->p = src; return *this;}
		random_access_iterator & operator++(void) {this->p++; return *this;}
		random_access_iterator operator++(int) {random_access_iterator temp(*this); operator++(); return (temp);}
		random_access_iterator & operator--(void) {this->p--; return *this;}
		random_access_iterator operator--(int) {random_access_iterator temp(*this); operator--(); return (temp);}
		bool operator==(random_access_iterator const& src) const {return (this->p == src.p);}
		bool operator!=(random_access_iterator<T> const& src) const {return (this->p != src.p);}
		value_type & operator*(void) const {return(*(this->p));}
		value_type * operator->(void) const {return (this->p);}
		random_access_iterator & operator+=(int nb){this->p += nb; return (*this);}
		random_access_iterator & operator-=(int nb){this->p -= nb; return (*this);}
		random_access_iterator operator+(int nb) const {random_access_iterator temp(*this); return (temp += nb);}
		random_access_iterator operator-(int nb) const {random_access_iterator temp(*this); return (temp -= nb);}
		//difference_type operator+(random_access_iterator const & src) const {return (this->p + src.p);}
		difference_type operator-(random_access_iterator const & src) const {return (this->p - src.p);}
		bool operator<(random_access_iterator const &src) const {return (this->p < src.p);}
		bool operator>(random_access_iterator const &src) const {return (this->p > src.p);}
		bool operator<=(random_access_iterator const & src) const {return (this->p <= src.p);}
		bool operator>=(random_access_iterator const & src) const {return (this->p >= src.p);}
		value_type & operator[](int num) {return (*(this->p + num));}


		operator random_access_iterator<const T> () const{
			return (random_access_iterator<const T>(this->p));}
	};

	template <typename T, typename T2>
	ft::random_access_iterator<T> operator+=(ft::random_access_iterator<T> lhs, ft::random_access_iterator<T2> rhs){
		ft::random_access_iterator<T> temp(lhs);
		return (lhs += rhs);
	}

	template <typename T, typename T2>
	ft::random_access_iterator<T> operator-=(ft::random_access_iterator<T> lhs, ft::random_access_iterator<T2> rhs){
		ft::random_access_iterator<T> temp(lhs);
		return (lhs -= rhs);
	}

	template <typename T>
	ft::random_access_iterator<T> operator+(int lhs, ft::random_access_iterator<T> rhs){
		ft::random_access_iterator<T> temp(rhs);
		return (temp.p += lhs);
	}

	template <typename T>
	ft::random_access_iterator<T> operator-(int lhs, ft::random_access_iterator<T> rhs){
		ft::random_access_iterator<T> temp(rhs);
		return (temp.p -= lhs);
	}

	template <typename T, typename T2>
    bool operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.p != rhs.p);
    }

	template <typename T, typename T2>
    bool operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.p == rhs.p);
    }

	template <typename T, typename T2>
    bool operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.p < rhs.p);
    }

	template <typename T, typename T2>
    bool operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.p > rhs.p);
    }

	template <typename T, typename T2>
    bool operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.p <= rhs.p);
    }

	template <typename T, typename T2>
    bool operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.p >= rhs.p);
    }




	template <typename It> class ReverseIterator
	{
		public :
	
		typedef typename It::value_type value_type;
		typedef typename It::pointer pointer;
    	//typedef typename It::const_pointer const_pointer;
    	typedef typename It::reference reference;
    	//typedef typename It::const_reference const_reference;
    	typedef typename It::difference_type difference_type;
		It it;

		ReverseIterator() {};
		ReverseIterator(It const &src) : it(src.p) {};
		ReverseIterator(ReverseIterator<It> const &src) : it(src.base()) {};
		virtual ~ReverseIterator() {};

		reference operator*() const {It temp(it); --temp; return (*temp);} // décrémentation car rbegin commence au \0;
		pointer operator->() const {It temp(it); --temp; return (&*temp);} // Dans la définition, retourne un pointeur sur l'élément pointé.
		ReverseIterator operator++(int) {It temp(it); it--; return (temp);}
		ReverseIterator & operator++() {--it; return (*this);}
		ReverseIterator operator--(int) {It temp(it); it++; return (temp);}
		ReverseIterator & operator--() {++it; return (*this);}
		value_type & operator[](difference_type num) {return (*(it - num -1));}
		ReverseIterator & operator+=(difference_type num) {it -= num; return (*this);}
		ReverseIterator & operator-=(difference_type num) {it += num; return (*this);}
		ReverseIterator operator+ (difference_type num) const {return (ReverseIterator(it - num ));}
		ReverseIterator operator- (difference_type num) const { return (ReverseIterator(it + num ));}
		difference_type operator+ (const ReverseIterator & src) const {return (this->base() - src.base());}
		//difference_type operator- (const ReverseIterator & src) const {std::cout << "-4" << std::endl; return (this->base() + src.base());}
		ReverseIterator &operator=(ReverseIterator const &other) {
			it.p = other.it.p;
			return (*this);
		}

		It base(void)const {It temp(it); return (temp);}
		/*operator ReverseIterator<const It> () const{
			return (ReverseIterator<const It>(It::p));}*/

		template <class T>
		operator ReverseIterator<T>() const{
			return (ReverseIterator<T>(it.p));}
	};


	template <typename T>
	ReverseIterator<T> operator+(int lhs, ReverseIterator<T> rhs){
		ReverseIterator<T> temp(rhs);
		return (temp.base() - lhs);
	}

	template <typename T>
	ReverseIterator<T> operator-(int lhs, ReverseIterator<T> rhs){
		ReverseIterator<T> temp(rhs);
		return (temp.base() + lhs);
	}

	template <class T, class T2>
	bool operator== (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (lhs.base() == rhs.base()); }
	
	template <class T, class T2>
	bool operator!= (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (lhs.base() != rhs.base()); }

	template <class T, class T2>
	bool operator< (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (lhs.base() > rhs.base()); }

	template <class T, class T2>
	bool operator> (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (lhs.base() < rhs.base()); }
	
	template <class T, class T2>
	bool operator<= (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (lhs.base() >= rhs.base()); }

	template <class T, class T2>
	bool operator>= (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (lhs.base() <= rhs.base()); }

	template <class T, class T2>
	std::ptrdiff_t operator- (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (-(lhs.base() - rhs.base()));}
	
	template <class T, class T2>
	std::ptrdiff_t operator+ (const ReverseIterator<T> & lhs, const ReverseIterator<T2> & rhs){
		return (+(lhs.base() + rhs.base()));}
};

#endif
