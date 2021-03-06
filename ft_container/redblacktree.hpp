/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redblacktree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrillai <qbrillai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:29:36 by qbrillai          #+#    #+#             */
/*   Updated: 2022/03/23 16:54:51 by qbrillai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <iostream>


# define NOIR 0
# define ROUGE 1
# define FEUILLE NULL


namespace ft
{
	template <typename T, class Compare> class bidirectionnalIterator;

	template <class T>
	struct noeud {
  		struct noeud<T> *gauche; 
	  	struct noeud<T> *droit;
		struct noeud<T> *parent; 
  		int couleur; 
 		T clé;


		/*noeud & operator=(const noeud & src)
		{
			this->clé = src.clé;
			this->parent = src.parent;
			this->droit = src.droit;
			this->gauche = src.gauche;
			this->couleur = src.couleur;
			return (*this);
		}*/

		noeud & operator=(const noeud<const T> & src)
		{
			this->clé = src.clé;
			this->parent = src.parent;
			this->droit = src.droit;
			this->gauche = src.gauche;
			this->couleur = src.couleur;
			return (*this);
		}

		noeud() : clé(){couleur = 1; parent = NULL; gauche = NULL; droit = NULL;} // regarder std::pair::pair

		template<class U>
		noeud (const noeud<U>& pr) : clé(pr.clé) {gauche = pr.gauche; droit = pr.droit; parent = pr.parent; couleur = pr.couleur;}
		
		template<typename T1, typename T2>
		noeud(std::pair<const T1, T2> T3) : clé(T3){
			return ;
		}

		noeud (const noeud<const T> & src ) : clé(src.clé) {gauche = src.gauche; droit = src.droit; parent = src.parent; couleur = src.couleur;}

		//noeud (const noeud<T> & src ) : clé(src.clé) {gauche = src.gauche; droit = src.droit; parent = src.parent; couleur = src.couleur;}

		noeud (const T src) : clé(src) {gauche = NULL; droit = NULL; parent = NULL; couleur = 1;}

		//noeud(ft::bidirectionnalIterator it) : clé(it.p->clé) {gauche = NULL; droit = NULL; parent = NULL; couleur = 1;}

		operator noeud<const T> () const{
			return (noeud<const T>(this->clé));}

	};

	template <class T, class Compare> class redblacktree
	{
	public :
		redblacktree (){};
		~redblacktree (){};	

		typedef typename T::first_type first_type;

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
			if (racine != NULL && (cmp(n->clé.first , racine->clé.first) == 1)) {
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
			while (racine->clé.first != val->clé.first){
				if (racine->gauche != NULL && (cmp(racine->clé.first , val->clé.first) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé.first , val->clé.first) == 1))
					racine = racine->droit;
				else
					break;
			}
			if (racine->clé.first != val->clé.first)
				return (1);
			else
				return (0);
		}

		int find(noeud<T> *racine, const first_type & val) const
		{
			while (racine->clé.first != val){
				if (racine->gauche != NULL && (cmp(racine->clé.first , val) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé.first , val) == 1))
					racine = racine->droit;
				else
					break;
			}
			if (racine->clé.first != val)
				return (1);
			else
				return (0);
		}


		noeud<T> * findreturn(noeud<T> *racine, const first_type & val) const
		{
			while (racine->clé.first != val){
				if (racine->gauche != NULL && (cmp(racine->clé.first , val) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé.first , val) == 1))
					racine = racine->droit;
				else
					break;
			}
			return (racine);
		}
		
		noeud<T> * findreturn(noeud<T> *racine, noeud<T> *val){
			while (racine->clé.first != val->clé.first){
				if (racine->gauche != NULL && (cmp(racine->clé.first , val->clé.first) == 0))
					racine = racine->gauche;
				else if (racine->droit != NULL && (cmp(racine->clé.first , val->clé.first) == 1))
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

		redblacktree & operator=(redblacktree const & rhs); 

	private :

	Compare cmp;

	};
}

#endif
