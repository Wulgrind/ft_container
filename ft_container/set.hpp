#ifndef SET_HPP
# define SET_HPP
# include <iostream>
# include "iterator.hpp"
# include "redblacktree.hpp"
# include <cstddef>

# define NOIR 0
# define ROUGE 1
# define FEUILLE NULL

namespace ft
{

   	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compareSet (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
  		while (first1 != last1)
  		{
    		if (first2 == last2 || first2.p->clé < first1.p->clé) return false;
    		else if (first1.p->clé < first2.p->clé) return true;
    		++first1; ++first2;
 		 }
  		return (first2!=last2);
	}


    template <typename T, class Compare> class bidirectionnalIteratorset
	{
		public :

		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type const * const_pointer;
		typedef value_type& reference;
		typedef value_type const & const_reference;
		typedef std::ptrdiff_t difference_type;
		typedef bidirectionnalIteratorset iterator;
		typedef bidirectionnal_iterator_tag iterator_category;

		bidirectionnalIteratorset ( void ) : p(NULL){};
		bidirectionnalIteratorset (noeud<value_type> *p2) : p(p2) {};
		bidirectionnalIteratorset(bidirectionnalIteratorset<T, Compare> & src){this->p = src.p;}
        template <typename C>
        bidirectionnalIteratorset(const bidirectionnalIteratorset<C, Compare> & src){this->p = reinterpret_cast<noeud<value_type> *>(src.p);}
		template <typename U>
		bidirectionnalIteratorset (noeud<U> *p2) {this->p = reinterpret_cast<noeud<value_type> *>(p2);}
		bidirectionnalIteratorset ( const bidirectionnalIteratorset & src ) {this->p = reinterpret_cast<noeud<value_type> *>(src.p);}
		~bidirectionnalIteratorset ( void ) {};
		bidirectionnalIteratorset<T, Compare> & operator=(bidirectionnalIteratorset<const T, Compare> const & rhs){this->p = rhs.p; return *this;}
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
						if (parentp->clé < this->p->clé)
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
		const value_type & operator*(void) const {return(this->p->clé);}
		const value_type * operator->(void) const {return (&this->p->clé);}
		noeud<value_type> *p;

		
		operator bidirectionnalIteratorset<const T, Compare> () const{
			return (bidirectionnalIteratorset<const T, Compare>(this->p));}
		
		private :
		
	};


    template <class T, class Compare> class redblacktreeset
	{
	public :
		redblacktreeset (){};
		~redblacktreeset (){};	

		noeud<T> * parent(noeud<T> * n) {
  			return n->parent;
		}

		
		noeud<T> * grandparent(noeud<T>  * n) {
			noeud<T> * p = parent(n);
			if (p == NULL)
	  			return NULL; 
			return parent(p);
		}

		noeud<T> * frere(noeud<T> * n) {
			noeud<T> * p = parent(n);
			if (p == NULL)
    			return NULL; 
			if (n == p->gauche)
    			return p->droit;
  			else 
    			return p->gauche;
		}

		noeud<T> * oncle(noeud<T> * enfant) {
			noeud<T> * p = parent(enfant);
			noeud<T> * g = grandparent(enfant);
  			if (g == NULL)
    			return NULL;
  			return frere(p);
		}

		void rotation_gauche(noeud<T> * x) {
			noeud<T> * y = x->droit;
			x->droit = y->gauche;
  			if (y->gauche != FEUILLE){
    			y->gauche->parent = x;
			}
  			y->parent = x->parent;
			if (x->parent){
  				if (x == x->parent->gauche){
  					x->parent->gauche = y;
				}
				else{
    				x->parent->droit = y;
				}
			}
			y->gauche = x;
  			x->parent = y;
		}

		void rotation_droite(noeud<T> * x) {
			noeud<T> * y = x->gauche;
			x->gauche = y->droit;
			if (y->droit != FEUILLE)
    			y->droit->parent = x;
  			y->parent = x->parent;
  			if (x->parent){
				if (x == x->parent->droit)
    				x->parent->droit = y;
  				else
    				x->parent->gauche = y;
			}
  			y->droit = x;
  			x->parent = y;
		}

		void insertion_repare_arbre(noeud<T> *n) {
	   		if (parent(n) == NULL) // La racine doit toujours etre noire.
				n->couleur = NOIR;
			else if (parent(n)->couleur == NOIR) // Rien a faire.
    			return ;
   			else if (oncle(n) && oncle(n)->couleur == ROUGE){ // Si l oncle est rouge , parent et oncle sont colories en noir. Le grand parent devient rouge.
				parent(n)->couleur = NOIR;
   				oncle(n)->couleur = NOIR;
   				noeud<T> *g = grandparent(n);
   				g->couleur = ROUGE;
   				insertion_repare_arbre(g);
 			}
   			else{ // Si l oncle est noir on effectue des rotations en fonction des positions du parent et du grand parent pour equilibrer.
	    		noeud<T> *p = parent(n);
   				noeud<T> *g = grandparent(n);
  				if (g->gauche && g->gauche->droit && n == g->gauche->droit) {
      				rotation_gauche(p);
     				n = n->gauche;
				} 
				else if (g->droit && g->droit->gauche && n == g->droit->gauche) { // parent devient grand parent qui devient oncle. Le parent est noir et le grand parent rouge.
    				rotation_droite(p);
    				n = n->droit;
					p = parent(n);
   					g = grandparent(n);
   					if (n == p->gauche){
    			 		rotation_droite(g);
					}
  					else{
						rotation_gauche(g);
					}
   					p->couleur = NOIR;
  					g->couleur = ROUGE;
				}
			}
		}

		void insertion_recursif(noeud<T> *racine, noeud<T> *n) {
			if (racine != NULL && (cmp(n->clé , racine->clé) == 1)) {
    			if (racine->gauche != FEUILLE) {
    			  insertion_recursif(racine->gauche, n);
	    		  return;
    			}
    			else
    			  racine->gauche = n;
  			} 
  			else if (racine != NULL) {
  				if (racine->droit != FEUILLE && racine->droit->couleur != 10) {
      				insertion_recursif(racine->droit, n);
      				return;
				}
    			else
      				racine->droit = n;
  			}
  			n->parent = racine;
 			n->gauche = FEUILLE; 
  			n->droit = FEUILLE; 
  			n->couleur = ROUGE;
		}

		int find(noeud<T> *racine, noeud<T> *val) const
		{
			while (racine->clé != val->clé){
				if (racine->gauche != NULL && (cmp(racine->clé , val->clé) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé , val->clé) == 1))
					racine = racine->droit;
				else
					break;
			}
			if (racine->clé != val->clé)
				return (1);
			else
				return (0);
		}

		int find(noeud<T> *racine, const T & val) const
		{
			while (racine->clé != val){
				if (racine->gauche != NULL && (cmp(racine->clé , val) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé , val) == 1))
					racine = racine->droit;
				else
					break;
			}
			if (racine->clé != val)
				return (1);
			else
				return (0);
		}


		noeud<T> * findreturn(noeud<T> *racine, const T & val) const
		{
			while (racine->clé != val){
				if (racine->gauche != NULL && (cmp(racine->clé , val) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé , val) == 1))
					racine = racine->droit;
				else
					break;
			}
			return (racine);
		}
		
		noeud<T> * findreturn(noeud<T> *racine, noeud<T> *val){
			while (racine->clé != val->clé){
				if (racine->gauche != NULL && (cmp(racine->clé , val->clé) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé , val->clé) == 1))
					racine = racine->droit;
			}
			return (racine);
		}

		noeud<T> *insertion(noeud<T> *racine, noeud<T> *n) {
			insertion_recursif(racine, n);
  			insertion_repare_arbre(n); // après insertion, on réequilibre l'arbre en comparant la nouvelle valeur aux oncles.
  			racine = n;
  			while (parent(racine) != NULL)
   		 		racine = parent(racine);
  			return racine;
		}

		noeud<T> **remove (noeud<T> **racine, noeud <T> *temp, noeud <T> *temp2){
			if ((temp2 && temp2->couleur == 1) || (temp && temp->couleur == 1)){ // si la valeur supprimée ou son enfant sont rouges, on passe noir pour garder l'équilibre sauf si double rouge.
				if (temp2 && temp2->couleur == 1 && temp && temp->couleur == 1)
					temp->couleur = 1;
				else
					temp->couleur = 0;
			}
			if (temp == *racine)
				temp->couleur = 0;
			else if (temp != *racine){ // Dans le cas ou temp n est pas la racine.
				noeud<T> * s = this->frere(temp);
				noeud<T> * p = this->parent(temp);
				noeud<T> * r; // fils rouge
				// https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
				if (s && s == s->parent->droit && s->couleur == 0 && ((s->droit && s->droit->couleur == 1) || (s->gauche && s->gauche->couleur == 1))){ // Si le frere est noir et un de ses enfants est rouge.
					if (s->droit && s->droit->couleur == 1){ // Si enfant droit est rouge decallage a gauche et l enfant gauche de sibling devient l enfant droit de l ancien parent.
						s->droit->couleur = 0;
						r = s->gauche;
						if (p == *racine)
							*racine = s;
						s->parent = p->parent;
						if (p->parent && p == p->parent->droit)
							p->parent->droit = s;
						else if (p->parent)
							p->parent->gauche = s;
						p->parent = s;
						p->droit = s->gauche;
						if (s->gauche)
							s->gauche->parent = p;
						s->gauche = p;
						if (r)
							r->parent = p;
						p->droit = r;
					}
					else{ // Le fils gauche de s prend sa place et s devient son fils droit s en suit un decallage vers la gauche.
						r = s->gauche;
						p->droit = r;
						r->parent = p;
						s->gauche = r->droit;
						if (r->droit)
							r->droit->parent = s;
						r->droit = s;
						s->parent = r;
						r->parent = p->parent;
						if (*racine == p)
							*racine = r;
						if (p->parent && p->parent->droit == p)
							p->parent->droit = r;
						else if (p->parent)
							p->parent->gauche = r;
						p->parent = r;
						p->droit = r->gauche;
						if (r->gauche)
							r->gauche->parent = p;
						r->gauche = p;
						r->couleur = 0;
					}
				}
				else if (s && s == s->parent->gauche && s->couleur == 0 && ((s->droit && s->droit->couleur == 1) || (s->gauche && s->gauche->couleur == 1))){ // Miroir de la situation au dessus.
					if (s->gauche->couleur == 1){
						s->gauche->couleur = 0;
						r = s->droit;
						if (p == *racine)
							*racine = s;
						s->parent = p->parent;
						if (p->parent && p == p->parent->droit)
							p->parent->droit = s;
						else if (p->parent)
							p->parent->gauche = s;
						p->parent = s;
						p->gauche = s->droit;
						if (s->droit)
							s->droit->parent = p;
						s->droit = p;
						if (r)
							r->parent = p;
						p->gauche = r;
					}
					else{
						r = s->droit;
						p->gauche = r;
						r->parent = p;
						s->droit = r->gauche;
						r->gauche->parent = s;
						r->gauche = s;
						s->parent = r;

						r->parent = p->parent;
						if (*racine == p)
							*racine = r;
						if (p->parent && p->parent->droit == p)
							p->parent->droit = r;
						else if (p->parent)
							p->parent->gauche = r;
						p->parent = r;
						p->gauche = r->droit;
						if (r->droit)
							r->droit->parent = p;
						r->droit = p;
						r->couleur = 0;
					}
				}
				else if (s && s->couleur == 0 && (s->droit == NULL || s->droit->couleur == 0) && (s->gauche == NULL || s->gauche->couleur == 0)){ // Si le sibling est noir et ses enfants soit noirs (une feuille est consideree comme noire) on colorie le sibling en rouge et on rappelle la fonction si le parent est noir. Pour verifier de ne pas avoir desiquilibre l arbre au niveau du parent
					s->couleur = 1;
					if (p->couleur == 1)
						p->couleur = 0;
					else
						this->remove(racine, p, temp);
				}
				else if (s && s->couleur == 1){ // Sibling est rouge. Rotation a gauche, l enfant du sibling droit prend la place du sibling et l enfant gauche de sibling devient l enfant droit de l ancien parent.
					p->couleur = 1;
					if (s == p->droit){
						s->couleur = 0;
						s->parent = p->parent;
						if (*racine == p)
							*racine = s;
						if (p->parent && p->parent->gauche == p)
							p->parent->gauche = s;
						else if (p->parent)
							p->parent->droit = s;
						p->parent = s;
						p->droit = s->gauche;
						if (s->gauche)
							s->gauche->parent = p;
						s->gauche = p;
					}
					else if (s == p->gauche){ // miroir du dessus.
						s->couleur = 0;
						s->parent = p->parent;
						if (*racine == p)
						*racine = s;
						if (p->parent && p->parent->gauche == p)
							p->parent->gauche = s;
						else if (p->parent)
							p->parent->droit = s;
						p->parent = s;
						p->gauche = s->droit;
						if (s->droit)
							s->droit->parent = p;
						s->droit = p;
					}
					this->remove(racine, temp, temp2);
				}
			}
			return (racine);
		};

		redblacktreeset & operator=(redblacktreeset const & rhs); 

	private :

	Compare cmp;

	};

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
           class Compare = std::less<Key>,
           class Alloc = std::allocator<const Key>
           > class set
	{
		public :
			typedef Key key_type;
			typedef const key_type value_type;
			typedef Compare key_compare;
			typedef Alloc  allocator_type;
			typedef typename allocator_type::reference   reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer     pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::bidirectionnalIteratorset<value_type, Compare> iterator;
			typedef ft::bidirectionnalIteratorset<const value_type, Compare> const_iterator;
			typedef ft::ReverseIterator<iterator> reverse_iterator;
			typedef ft::ReverseIterator <const_iterator> const_reverse_iterator;
			typedef typename allocator_type::size_type size_type;
			typedef typename allocator_type::difference_type difference_type;
			
			class value_compare : binary_function<value_type, value_type, bool>
			{
				friend class set<key_type, key_compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{ return (comp(x, y)); }
			};

			explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){
				this->cmp = comp;
				this->allocator = alloc;
				sizenode = 0;
				endnode = NULL;
				startnode = NULL;
				pend = NULL;
				createpend();
			};

			set (const set& x){
				const_iterator start = x.begin();
				const_iterator end = x.end();
				sizenode = 0;
				startnode = NULL;
				endnode = NULL;
				racine = NULL;
				while (start.p != end.p){
					insert(start.p->clé);
					start++;
				}
				createpend();
			}
			
			template <class InputIterator>
  			set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL){
				this->cmp = comp;
				this->allocator = alloc;
				this->sizenode = 0;
				endnode = NULL;
				startnode = NULL;
				pend = NULL;
				createpend();
				insert(first, last);
			}

			~set ( void ){};

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
				modifypend();
				iterator temp(pend);
				return (temp);
			}

			const_iterator end(void ) const {
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

			key_type& operator[] (const key_type& k){
			//	size_t length = 0;
				if (endnode)
					endnode->droit = NULL;
				if (sizenode == 0)
					this->insert(k);
				noeud<value_type> *temp = this->racine;
				while (temp->clé != k){
					if (temp->gauche != NULL && (cmp(temp->clé , k) == 0)){
						temp = temp->gauche;
					}
					else if (temp->droit != NULL && (cmp(temp->clé , k) == 1)){
						temp = temp->droit;
					}
					else if (temp->clé.first == k){
						endnode->droit = pend;
						return (temp->clé);
					}
					else if (temp->clé.first != k){
						this->insert(k);
						temp = nodes.findreturn(racine, k);
						endnode->droit = pend;
						return (temp->clé);
					}
					/*else if(temp->clé.first != k){
						
					}*/
				}
				endnode->droit = pend;
				return (temp->clé);
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
						if (cmp(this->startnode->clé , val) == 0)
							this->startnode = node;
						else if (cmp(this->endnode->clé , val) == 1)
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
						if (cmp(this->startnode->clé , val) == 0)
							this->startnode = node;
						if (cmp(this->endnode->clé , val) == 1)
							this->endnode = node;
						this->sizenode++;
						iterator test;
						test.p = node;
						return (test);
					}
					else {
						racine = nodes.insertion(temp, node);
						if (cmp(this->startnode->clé , val) == 0)
							this->startnode = node;
						else if (cmp(this->endnode->clé , val) == 1)
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
				//std::cout << "test" << std::endl;
				noeud<value_type> *temp = position.p;
				noeud<value_type> *temp2 = temp;
				if (temp == endnode && endnode->parent == NULL)
					endnode = NULL; // plus de endnode car pas de parent et donc pas de remplacant
				else if (temp == endnode)
					endnode = endnode->parent; // la valeur -1 devient parent.
				if (endnode != NULL)
					endnode->droit = NULL; // enlever le pend qui peut etre problematique.
				if (temp->gauche != NULL && temp->droit != NULL) 
				{
					temp = temp->gauche;
					if (temp->droit != NULL){
						while (temp->droit != NULL){
							temp = temp->droit;
						}
						if (temp->parent != NULL){
							if (temp->parent->droit == temp){
								temp->parent->droit = temp->gauche;
								if (temp->gauche)
									temp->gauche->parent = temp->parent;
								temp->gauche = NULL;
							}
						}
						else{
							temp->parent->gauche = temp->gauche;
							if (temp->gauche)
								temp->gauche->parent = temp->parent;
						}
						if (temp2->parent && temp2->clé < temp2->parent->clé){
							temp2->parent->gauche = temp;
							temp->parent = temp2->parent;
						}
						else if (temp2->parent && temp2->clé > temp2->parent->clé){
							temp2->parent->droit = temp;
							temp->parent = temp2->parent;
						}
					}
					else{
						if (temp2->parent){
							if (temp2->clé < temp2->parent->clé)
								temp2->parent->gauche = temp;
							else if (temp2->clé > temp2->parent->clé)
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
					temp->parent = temp2->parent;
					temp->droit = temp2->droit;
					if (temp2->droit)
						temp2->droit->parent = temp;
				}
				else if (temp->gauche == NULL && temp->droit == NULL) {
					if (temp->parent && temp->parent->clé < temp->clé)
						temp->parent->droit = NULL;
					else if (temp->parent)
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
				nodes.remove(&this->racine, temp, temp2);
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
				while (temp->clé != k){
					if (temp->gauche != NULL && temp->clé > k)
						temp = temp->gauche;
					else if (temp->droit != NULL && temp->clé < k)
						temp = temp->droit;
					/*else if (temp->clé.first == k){
						iterator temp2;
						temp2.p = temp;
						this->erase(temp2);
						endnode->droit = pend;
						return (1);
					}*/
					else if (temp->clé != k){
						endnode->droit = pend;
						return (0);
					}
				}
				iterator temp2;
				temp2.p = temp;
				this->erase(temp2);
				endnode->droit = pend;
				return (1);
			}

			void erase (iterator first, iterator last)
			{
				//std::cout << "here" << std::endl;
				size_t i = 0;
				while (first != last)
				{
					iterator temp = ++first;
					--first;
					erase(first);
					first = temp;
					i++;
				}
				//std::cout << "here3" << std::endl;
				if (sizenode == 0){
					this->racine = NULL;
					this->startnode = NULL;
					this->endnode = NULL;
				}
			}

			void swap (set& x){
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
			//	std::cout << "here" << std::endl;
		//		erase(--end());
			//	std::cout << "test9" << std::endl;
				//std::cout << "here2" << std::endl;
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
				if (sizenode == 0)
					return (end());
				if (nodes.find(this->racine, k) == 1)
					return (this->end());
				noeud<value_type> *temp = this->racine;
				while (temp->clé != k){
					
					if (temp->gauche != NULL && temp->clé >= k)
						temp = temp->gauche;
					else if (temp->droit != NULL && temp->clé <= k)
						temp = temp->droit;
					else
						break;
				}
				iterator it(temp);
				if (temp->clé == k)
					return (it);
				else
					return (end());
			}

			const_iterator find (const key_type& k) const{
				if (sizenode == 0)
					return (end());
				if (nodes.find(this->racine, k) == 1)
					return (this->end());
				noeud<value_type> *temp = this->racine;
				while (temp->clé != k){
					if (temp->gauche != NULL && temp->clé >= k)
						temp = temp->gauche;
					else if (temp->droit != NULL && temp->clé <= k)
						temp = temp->droit;
					else
						break;
				}
				const_iterator it(temp);
				if (temp->clé == k)
					return (it);
				else
					return (end());
			}

			size_type count (const key_type& k) const{
				if (sizenode == 0)
					return (0);
				if (nodes.find(this->racine, k) == 1)
					return (0);
				return (1);
			}

			iterator lower_bound (const key_type& k){
				iterator start(this->begin());
				while (start != this->end()){
					if (cmp(k , start.p->clé) || k == start.p->clé)
						return (start);
					if (start == this->end())
						break;
					start++;
				}
				return (this->end());
			}

			const_iterator lower_bound (const key_type& k) const{
				const_iterator start(this->begin());
				while (start != this->end()){
					if (cmp(k , start.p->clé) || k == start.p->clé)
						return (start);
					if (start == this->end())
						break;
					start++;
				}
				return (this->end());
			}

			iterator upper_bound (const key_type& k){
				iterator start(this->racine);
				while (start.p){
					if (cmp(k , start.p->clé))
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
					if (cmp(k , start.p->clé))
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
				//if (it != it2)
					return (ft::make_pair<const_iterator, const_iterator>(it, it2));
				//else
				//	return (ft::make_pair<const_iterator, const_iterator>(it2 , it2));
			}

			allocator_type get_allocator() const
			{
				allocator_type temp;
				return (temp);
			}

			set & operator=(set const & rhs){
			//	std::cout << "here" << std::endl;
				if (*this == rhs)
					return (*this);
				this->clear();
			//	std::cout << "here2" << std::endl;
				const_iterator start = rhs.begin();
				const_iterator end = --rhs.end();
			//	std::cout << "here3" << std::endl;
				this->sizenode = 0;
				this->startnode = NULL;
				this->endnode = NULL;
				this->racine = NULL;
				if (start != NULL && end != NULL)
				{
					while (start.p != end.p){
				//		std::cout << "here4" << std::endl;
						insert(start.p->clé);
						start++;
					}
					insert(start.p->clé);
				}
				//std::cout << "here5" << std::endl;
				createpend();
				//endnode->droit = pend;
				//std::cout << "here6" << std::endl;
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
			ft::redblacktreeset<value_type, Compare> nodes;

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
				if ((cmp(position->clé , node->clé) == 1) && (cmp(node->clé, temp.p->clé) == 1))
					return (1);
				return (0);
			}
	};
	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs ){
		lhs.swap(rhs);
	}

	template <class Key>
	bool operator== (const ft::set<Key>& lhs, const ft::set<Key>& rhs) // Obligé de mettre ft car en dehors du namespace.
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::set<Key>::const_iterator start1 = lhs.begin();
		typename ft::set<Key>::const_iterator start2 = rhs.begin();
		while (start1 != lhs.end()){
			if (start1.p->clé != start2.p->clé)
                return (false);
			start1++;
			start2++;
		}
		return (true);
	}


	template <class Key>
	bool operator!= (const ft::set<Key>& lhs, const ft::set<Key>& rhs)
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}

	template <class Key>
	bool operator<  (const ft::set<Key>& lhs, const ft::set<Key>& rhs){return (ft::lexicographical_compareSet(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template <class Key>
	bool operator<= (const ft::set<Key>& lhs, const ft::set<Key>& rhs){return (!(rhs < lhs));} // si lhs est supérieur à rhs, il ne peut pas être inférieur ou égal.}

	template <class Key>
	bool operator>  (const ft::set<Key>& lhs, const ft::set<Key>& rhs){return (!(lhs <= rhs));}

	template <class Key>
	bool operator>= (const ft::set<Key>& lhs, const ft::set<Key>& rhs){return (!(lhs < rhs));}
};

#endif