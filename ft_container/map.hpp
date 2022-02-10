#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include "iterator.hpp"
# include "redblacktree.hpp"
# include <cstddef>

namespace ft
{
	template <class Arg1, class Arg2, class Result> // Permet à une structure d'être call comme une fonction avec l'operator() et deux valeurs.
  	struct binary_function {
   		typedef Arg1 first_argument_type;
    	typedef Arg2 second_argument_type;
    	typedef Result result_type;
  	};

	template <class T> struct less : ft::binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x < y;}
	};

	template < class Key,                                   
           class T,                                       
           class Compare = std::less<Key>,
           class Alloc = std::allocator<pair<const Key,T> >
           > class map
	{
		public :
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc  allocator_type;
			typedef typename allocator_type::reference   reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer     pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::bidirectionnalIterator<value_type, Compare> iterator;
			typedef ft::bidirectionnalIterator<const value_type, Compare> const_iterator;
			typedef ft::ReverseIterator<iterator> reverse_iterator;
			typedef ft::ReverseIterator <const_iterator> const_reverse_iterator;
			typedef typename allocator_type::size_type size_type;
			typedef typename allocator_type::difference_type difference_type;
			
			class value_compare : binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }
			};

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){
				this->cmp = comp;
				this->allocator = alloc;
				sizenode = 0;
				endnode = NULL;
				startnode = NULL;
				pend = NULL;
				createpend();
			};

			map (const map& x){
				const_iterator start = x.begin();
				const_iterator end = x.end();
				sizenode = 0;
				startnode = NULL;
				endnode = NULL;
				racine = NULL;
				while (start->first != end->first){
					insert(start.p->clé);
					start++;
				}
				createpend();
			}
			
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL){
				this->cmp = comp;
				this->allocator = alloc;
				this->sizenode = 0;
				endnode = NULL;
				startnode = NULL;
				pend = NULL;
				createpend();
				insert(first, last);
			}

			~map ( void ){};

			iterator begin(void){
				if (sizenode == 0){ // pour les comparaisons != avec end quand startnode est NULL.
					modifypend();
					return (iterator(pend));
				}
				return (iterator(startnode));
			}
			const_iterator begin(void) const {
				if (sizenode == 0){
					modifypend();
					return (const_iterator(pend));
				}
				return (const_iterator(startnode));
			}
			iterator end(void){
				/*if (this->sizenode == 0){
					iterator temp(NULL);
					temp.p = NULL;
					return (temp);
				}*/
				modifypend();
				iterator temp(pend);
				return (temp);
			}
			const_iterator end(void ) const {
				//iterator ending = end();
				/*if (this->sizenode == 0){
					iterator temp(NULL);
					temp.p = NULL;
					return (temp);
				}*/
				modifypend();
				const_iterator temp(pend);
				return (temp);
			}
			reverse_iterator rbegin(void){return(reverse_iterator(this->end()));}
			const_reverse_iterator rbegin(void) const {return(const_reverse_iterator (this->end()));}
			reverse_iterator rend(void){return(reverse_iterator(begin()));}
			const_reverse_iterator rend(void) const {return(const_reverse_iterator(begin()));}

			size_type size(void) const {return (this->sizenode);}
			bool empty() const {return (this->sizenode == 0);}
			size_type max_size(void) const {
				std::allocator<ft::noeud<value_type> > test;
				return (test.max_size());}

			mapped_type& operator[] (const key_type& k){
			//	size_t length = 0;
				if (endnode)
					endnode->droit = NULL;
				if (sizenode == 0)
					this->insert(ft::make_pair(k, mapped_type()));
				noeud<value_type> *temp = this->racine;
				while (temp->clé.first != k){
					if (temp->gauche != NULL && (cmp(temp->clé.first , k) == 0)){
						temp = temp->gauche;
					}
					else if (temp->droit != NULL && (cmp(temp->clé.first , k) == 1)){
						temp = temp->droit;
					}
					else if (temp->clé.first == k){
						endnode->droit = pend;
						return (temp->clé.second);
					}
					else if (temp->clé.first != k){
						this->insert(ft::make_pair(k, mapped_type()));
						/*if (cmp(k , temp->clé.first) == 0){
							if (temp->droit)
								temp = temp->droit;
						}
						else{
							if (temp->gauche)
								temp = temp->gauche;
						}*/
						temp = nodes.findreturn(racine, k);
						endnode->droit = pend;
						return (temp->clé.second);
					}
					/*else if(temp->clé.first != k){
						
					}*/
				}
				endnode->droit = pend;
				return (temp->clé.second);
			}

			pair<iterator,bool> insert (const value_type& val){
				if (endnode)
					endnode->droit = NULL;
				ft::noeud<value_type> *node = new ft::noeud<value_type>(val);
				 // si on ne me donne pas un noeud mais semblant une paire avec first et second.
				/*ft::noeud<value_type> *node = new ft::noeud<value_type>();
				node->clé.first = val.first;
				node->clé.second = val.second;*/
				if (this->sizenode == 0){
					node->couleur = 0;
					node->parent = NULL;
					node->droit = NULL;
					node->gauche = NULL;
					this->startnode = node;
					this->racine = node;
					this->endnode = node;
					this->sizenode++;
					iterator it;
					bool result = true;
					it.p = node;
					return (ft::make_pair(it, result));
				}
				else
				{
					noeud<value_type> *temp = this->racine;
					if (nodes.find(temp, node) == 0)
					{
						iterator test;
						test.p = nodes.findreturn(temp, node);
						bool result = false;
						delete (node);
						return (ft::make_pair(test, result));
					}
					else {
						racine = nodes.insertion(temp, node);
						if (cmp(this->startnode->clé.first , val.first) == 0)
							this->startnode = node;
						else if (cmp(this->endnode->clé.first , val.first) == 1)
							this->endnode = node;
						this->sizenode++;
						temp = this->racine;
						bool result = true;
						iterator test;
						test.p = nodes.findreturn(temp, node);
						return (ft::make_pair(test, result));
					}
				}
				endnode->droit = pend;
			}

			iterator insert (iterator position, const value_type& val){
				if (endnode)
					endnode->droit = NULL;
				ft::noeud<value_type> *node = new ft::noeud<value_type>(val);
				if (this->sizenode == 0){
					node->couleur = 0;
					node->parent = NULL;
					node->droit = NULL;
					node->gauche = NULL;
					this->startnode = node;
					this->racine = node;
					this->endnode = node;
					this->sizenode++;
					iterator it;
					it.p = node;
					return (it);
				}
				else
				{
					noeud<value_type> *temp = this->racine;
					noeud <value_type> *temp2 = position.p;
					if (nodes.find(temp, node) == 0)
					{
						iterator test;
						test.p = nodes.findreturn(temp, node);
						delete (node);
						return (test);
					}
					else if (temp2 != NULL && parentsmaller(temp2, node) == 1){
						racine = nodes.insertion(temp2, node);
						if (cmp(this->startnode->clé.first , val.first) == 0)
							this->startnode = node;
						if (cmp(this->endnode->clé.first , val.first) == 1)
							this->endnode = node;
						this->sizenode++;
						iterator test;
						test.p = node;
						return (test);
					}
					else {
						racine = nodes.insertion(temp, node);
						if (cmp(this->startnode->clé.first , val.first) == 0)
							this->startnode = node;
						else if (cmp(this->endnode->clé.first , val.first) == 1)
							this->endnode = node;
						this->sizenode++;
						iterator test;
						test.p = node;
						return (test);
					}
				}
				endnode->droit = this->pend;
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL){
				while (first != last){
					this->insert(*first);
					first++;
				}
			}

			void erase (iterator position){ // Afin de respecter les propriétés de l'arbre , après chaque erase si la valeur effacée a des enfants nous devons prendre soit la plus petite des plus grandes soit la plus grande des plus petites pour prendre son emplacement.
				noeud<value_type> *temp = position.p;
				noeud<value_type> *temp2 = temp;
				if (temp == endnode && endnode->parent == NULL)
					endnode = NULL;
				else if (temp == endnode)
					endnode = endnode->parent;
				if (endnode != NULL)
					endnode->droit = NULL;
				if (temp->gauche != NULL && temp->droit != NULL) 
				{
				/*	std::cout << temp->clé.first << std::endl;
					std::cout << temp->droit->clé.first << std::endl;
					std::cout << temp->gauche->clé.first << std::endl;
					std::cout << temp->gauche->gauche->clé.first << std::endl;
					std::cout << temp->gauche->gauche->gauche->clé.first << std::endl;*/
					//std::cout << "here" << std::endl;
					temp = temp->gauche;
					if (temp->droit != NULL){
					//	std::cout << "test2" << std::endl;
						while (temp->droit != NULL){
						//	std::cout << "TEEEEST" << std::endl; 
							temp = temp->droit;
						}
					//	std::cout << temp->clé.first << std::endl;
						if (temp->parent != NULL){
						//	std::cout << "test3" << std::endl;
							if (temp->parent->droit == temp){
								temp->parent->droit = temp->gauche;
								if (temp->gauche)
									temp->gauche->parent = temp->parent;
								temp->gauche = NULL;
							}
						//	std::cout << "test3b" << std::endl;
						}
						else{
						//	std::cout << "test4" << std::endl;
							temp->parent->gauche = temp->gauche;
							if (temp->gauche)
								temp->gauche->parent = temp->parent;
						}
						if (temp2->parent && temp2->clé.first < temp2->parent->clé.first){
							temp2->parent->gauche = temp;
							temp->parent = temp2->parent;
						}
						else if (temp2->parent && temp2->clé.first > temp2->parent->clé.first){
							temp2->parent->droit = temp;
							temp->parent = temp2->parent;
						}
					}
					else{
					//	std::cout << "test5" << std::endl;
						if (temp2->parent){
							if (temp2->clé.first < temp2->parent->clé.first)
								temp2->parent->gauche = temp;
							else if (temp2->clé.first > temp2->parent->clé.first)
								temp2->parent->droit = temp;
							temp->parent = temp2->parent;
						}
						else {
							temp->parent = NULL;
							temp->droit = temp2->droit;
							temp2->droit->parent = temp;
						}
					}
					if (temp2->gauche != temp){
						temp->gauche = temp2->gauche;
						if (temp2->gauche)
							temp2->gauche->parent = temp;
					}
					//std::cout << "test6" << std::endl;
					temp->parent = temp2->parent;
					temp->droit = temp2->droit;
					if (temp2->droit)
						temp2->droit->parent = temp;
				}
				/*else if (temp->droit != NULL){ // Même chose mais à l'inverse.
					temp = temp->droit;
					if (temp->gauche){
						while (temp->gauche != NULL)
							temp = temp->gauche;
						if (temp->parent->gauche == temp)
							temp->parent->gauche = temp->droit;
						else
							temp->parent->droit = temp->droit;
						if (temp->droit)
							temp->droit->parent = temp->parent;
						if (temp2->clé.first < temp2->parent->clé.first)
							temp2->parent->gauche = temp;
						else
							temp2->parent->droit = temp;
					}
					else{
						if (temp2->parent){
							temp2->parent->droit = temp;
							temp->parent = temp2->parent;
						}
						else {
							temp->parent = NULL;
						}
					}
					temp->parent = temp2->parent;
					temp->gauche = temp2->gauche;
					temp->couleur = temp2->couleur;
				}*/
				else if (temp->gauche == NULL && temp->droit == NULL) {
					if (temp->parent->clé.first < temp->clé.first)
						temp->parent->droit = NULL;
					else
						temp->parent->gauche = NULL;
					if (temp->parent != NULL)
						temp = temp->parent;
					else
						temp = NULL;
				}
				else {
					if (temp->droit != NULL)
						temp = temp->droit;
					else
						temp = temp->gauche;
					if (temp2->parent != NULL){
						temp->parent = temp2->parent;
						if (temp2->parent->gauche == temp2)
							temp2->parent->gauche = temp;
						else
							temp2->parent->droit = temp;
					}
					else
						temp->parent = NULL;
				}
				if (temp2 == this->endnode)
					this->endnode = temp->parent;
				if (temp2 == this->startnode)
					this->startnode = temp;
				if (temp2 == this->endnode)
					this->endnode = temp;
				if (temp2 == this->racine)
					this->racine = temp;
			//	std::cout << "here1" << std::endl;
				nodes.remove(&this->racine, temp, temp2);
			//	std::cout << "here2" << std::endl;
				if (endnode != NULL)
					endnode->droit = this->pend;
				this->sizenode--;
				delete (temp2);
			}

			size_type erase (const key_type& k)
			{
				if (endnode != NULL)
					endnode->droit = NULL;
				noeud<value_type> *temp = this->racine;
				while (temp->clé.first != k){
					if (temp->gauche != NULL && temp->clé.first > k)
						temp = temp->gauche;
					else if (temp->droit != NULL && temp->clé.first < k)
						temp = temp->droit;
					/*else if (temp->clé.first == k){
						iterator temp2;
						temp2.p = temp;
						this->erase(temp2);
						endnode->droit = pend;
						return (1);
					}*/
					else if (temp->clé.first != k){
						endnode->droit = pend;
						return (0);
					}
				}
				//std::cout << "test" << std::endl;
				iterator temp2;
				temp2.p = temp;
				this->erase(temp2);
				endnode->droit = pend;
				return (1);
			}

			void erase (iterator first, iterator last)
			{
				size_t i = 0;
				while (first != last)
				{
					iterator temp = ++first;
					--first;
					erase(first);
					first = temp;
					i++;
				}
				if (sizenode == 0){
					this->racine = NULL;
					this->startnode = NULL;
					this->endnode = NULL;
				}
			}

			void swap (map& x){
				noeud<value_type> *temp;
				size_type temps;
				allocator_type talc;

				talc = this->allocator;
				this->allocator = x.allocator;
				x.allocator = talc;
				temp = this->startnode;
				this->startnode = x.startnode;
				x.startnode = temp;
				temp = this->endnode;
				this->endnode = x.endnode;
				x.endnode = temp;
				temp = this->racine;
				this->racine = x.racine;
				x.racine = temp;
				temp = this->pend;
				this->pend = x.pend;
				x.pend = temp;
				temps = this->sizenode;
				this->sizenode = x.sizenode;
				x.sizenode = temps;
			}

			void clear(){
				if (this->sizenode == 0)
					return;
				this->erase(this->begin(), this->end());
				this->racine = NULL;
				this->startnode = NULL;
				this->endnode = NULL;
				this->sizenode = 0;

			}

			key_compare key_comp() const{ // element de comparaison avec l'element key.
				return (key_compare());
			}

			value_compare value_comp() const{ // element de comparaison avec les deux elements bien que key serve de référence pour la comparaison.
				return (value_compare(key_compare()));
			}

			iterator find (const key_type& k){
				if (nodes.find(this->racine, k) == 1)
					return (this->end());
				noeud<value_type> *temp = this->racine;
				while (temp->clé.first != k){
					if (temp->gauche != NULL && temp->clé.first >= k)
						temp = temp->gauche;
					else if (temp->droit != NULL && temp->clé.first <= k)
						temp = temp->droit;
					else
						break;
				}
				iterator it(temp);
				if (temp->clé.first == k)
					return (it);
				else
					return (end());
			}

			const_iterator find (const key_type& k) const{
				if (nodes.find(this->racine, k) == 1)
					return (this->end());
				noeud<value_type> *temp = this->racine;
				while (temp->clé.first != k){
					if (temp->gauche != NULL && temp->clé.first >= k)
						temp = temp->gauche;
					else if (temp->droit != NULL && temp->clé.first <= k)
						temp = temp->droit;
					else
						break;
				}
				const_iterator it(temp);
				if (temp->clé.first == k)
					return (it);
				else
					return (end());
			}

			size_type count (const key_type& k) const{
				if (nodes.find(this->racine, k) == 1)
					return (0);
				return (1);
			}

			iterator lower_bound (const key_type& k){
				iterator start(this->racine);
				while (start.p){
					if (cmp(start.p->clé.first, k) == false)
						return (start);
					if (start.p == this->endnode)
						break;
					start++;
				}
				return (this->end());
			}

			const_iterator lower_bound (const key_type& k) const{
				iterator start(this->racine);
				while (start.p){
					if (cmp(start.p->clé.first, k) == false)
						return (start);
					if (start.p == this->endnode)
						break;
					start++;
				}
				return (this->end());
			}

			iterator upper_bound (const key_type& k){
				iterator start(this->racine);
				while (start.p){
					if (cmp(k , start.p->clé.first))
						return (start);
					if (start.p == this->endnode)
						break;
					start++;
				}
				return (this->end());
			}

			const_iterator upper_bound (const key_type& k) const{
				iterator start(this->racine);
				while (start.p){
					if (cmp(k , start.p->clé.first))
						return (start);
					if (start.p == this->endnode)
						break;
					start++;
				}
				return (end());
			}

			pair<iterator,iterator> equal_range (const key_type& k){
				iterator it = lower_bound(k);
				iterator it2 = upper_bound(k);
				if (it != it2)
					return (ft::make_pair<iterator, iterator>(it, it2));
				else
					return (ft::make_pair<iterator, iterator>(it2 , it2)); 
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
				const_iterator it(lower_bound(k));
				const_iterator it2(upper_bound(k));
				if (it != it2)
					return (ft::make_pair<const_iterator, const_iterator>(it, it2));
				else
					return (ft::make_pair<const_iterator, const_iterator>(it2 , it2));
			}

			allocator_type get_allocator() const
			{
				allocator_type temp;
				return (temp);
			}

			map & operator=(map const & rhs){
				this->clear();
				const_iterator start = rhs.begin();
				const_iterator end = rhs.end();
				this->sizenode = 0;
				this->startnode = NULL;
				this->endnode = NULL;
				this->racine = NULL;
				if (start != NULL && end != NULL)
				{
					while (start->first != end->first){
						insert(start.p->clé);
						start++;
					}
				}
				createpend();
				return (*this);
			}; 
		
		
		private :
			allocator_type allocator;
			Compare cmp;
			noeud<value_type> *startnode;
			noeud<value_type> *pend;
			noeud<value_type> *endnode;
			noeud<value_type> *racine;
			size_t sizenode;
			ft::redblacktree<value_type, Compare> nodes;

			void createpend() const {
				ft::noeud<value_type> *ending = new ft::noeud<value_type>;
				this->pend = ending;
				ending->couleur = 10;
			}

			void createpend(){
				ft::noeud<value_type> *ending = new ft::noeud<value_type>;
				this->pend = ending;
				ending->couleur = 10;
			}

			void modifypend() const{
				if (pend->parent != NULL)
					if (pend->parent->droit == pend)
						pend->parent->droit = NULL;
				pend->parent = endnode;
				if (endnode)
					endnode->droit = pend;
			}

			void modifypend() {
				if (pend->parent != NULL)
					if (pend->parent->droit == pend)
						pend->parent->droit = NULL;
				pend->parent = endnode;
				if (endnode)
					endnode->droit = pend;
			}

			int parentsmaller(noeud<value_type> *position, noeud<value_type> *node){ // regarde si le parent correspond à l'identifiant juste avant, dans le cas contraire cela forcerait à remonter tout l'arbre et ne serait pas optimal
				iterator temp;
				temp.p = position;
				temp++;
				if ((cmp(position->clé.first , node->clé.first) == 1) && (cmp(node->clé.first, temp.p->clé.first) == 1))
					return (1);
				return (0);
			}
	};
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ){
		lhs.swap(rhs);
	}
};

template <class Key, class T>
bool operator== (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs) // Obligé de mettre ft car en dehors du namespace.
{
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::map<Key, T>::const_iterator start1 = lhs.begin();
	typename ft::map<Key, T>::const_iterator start2 = rhs.begin();
	while (start1 != lhs.end()){
		if (start1->first != start2->first)
			return (false);
		if (start1->second != start2->second)
			return (false);
		start1++;
		start2++;
	}
	return (true);
}

template <class Key, class T>
bool operator!= (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs)
{
	if (lhs == rhs)
		return (false);
	return (true);
}

template <class Key, class T>
bool operator<  (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs){return (ft::lexicographical_compareMap(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

template <class Key, class T>
bool operator<= (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs){return (!(rhs < lhs));} // si lhs est supérieur à rhs, il ne peut pas être inférieur ou égal.}

template <class Key, class T>
bool operator>  (const ft::map<Key, T>& lhs, const ft::map<Key, T>& rhs){return (!(lhs <= rhs));}

template <class Key, class T>
bool operator>= (const ft::map<Key,T>& lhs, const ft::map<Key,T>& rhs){return (!(lhs < rhs));}

#endif