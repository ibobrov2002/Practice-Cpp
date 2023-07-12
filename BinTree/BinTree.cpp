#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
	
class BinTree {
	struct Tree {
		string key;
		Tree* left;
		Tree* right;
	};
	vector<Tree*> ListTree;
	int iV;
	Tree* root;
public:
	BinTree() {
		root = NULL;
	};
	~BinTree() {
		DeleteTree(root);
	};
	void prTree(){
		printTree(root);
	}
	void add(string str){
		addHelp(str, root);
	};
	void del(string str){
		Tree* knot=root, *knot2;
		int br=0;
		if (knot){
			while(knot->key!=str){
				if(knot){
					if (knot->key>str){
						br=1;
						knot2=knot;
						if (knot->left) knot=knot->left;
						else break;
					}else if (knot->key<str){
							br=2;
							knot2=knot;
							if (knot->right) knot=knot->right;
							else break;
						}
				}
			}
			if ((!knot)||(knot->key!=str)){
				cout << "Нет такого элемента" << endl;
			}else{
				if((knot->left)&&(knot->right)){
					Tree* knot3=knot;
					knot=knot->right;
					if (knot->left){
						while(knot->left) {
							knot3=knot;
							knot=knot->left;
						};
						knot3->left=knot->right;
					}else knot3->right=knot->right;
					if(br==0){
						knot->right=root->right;
						knot->left=root->left;
						knot3=root;
						root=knot;
						delete knot3;
					}else if (br==1){
						knot->left=knot2->left->left;
						knot->right=knot2->left->right;
						knot3=knot2->left;
						knot2->left=knot;
						delete knot3;
					}else{
						knot->left=knot2->right->left;
						knot->right=knot2->right->right;
						knot3=knot2->right;
						knot2->right=knot;
						delete knot3;
					}
				}else if (knot->left){
						if(br==0){
							root=knot->left;
							delete knot;
						}else if (br==1){
							knot2->left=knot->left;
							delete knot;
							}else{
								knot2->right=knot->left;
								delete knot;
							}
					}else if (knot->right){
							if(br==0){
							root=knot->right;
							delete knot;
						}else if (br==1){
							knot2->left=knot->right;
							delete knot;
							}else{
								knot2->right=knot->right;
								delete knot;
							}
						}else{
							if(br==0){
								root=NULL;
								delete knot;
							}else if(br==1){
								knot2->left=NULL;
								delete knot;
							}else{
								knot2->right=NULL;
								delete knot;
							}
						}
			}
		}else cout << "Невозможно удалить элемент" << endl;
	}
	int search(string str){
		Tree* knot=root;
		if (knot){
			while(knot->key!=str){
				if (knot->key>str){
					knot=knot->left;
					if (!knot) break;
				}else if (knot->key<str){
						knot=knot->right;
						if (!knot) break;
					}else break;
			}
			if ((knot)&&(knot->key==str)) return 1;
			else cout << "Нет такого элемента" << endl;
		}else cout << "Нет такого элемента" << endl;
		return 0;
	}
	void trav(){
		iV=0;
		ListCreat(root);
		if (!ListTree.empty()){
			cout << "Обход начат" << endl;
			cout<< ListTree[iV]->key << endl;
		}else{
			cout << "Обход невозможен" << endl;
		}
	}
	void next(){
		iV++;
		if(iV<int(ListTree.size())){
			cout << ListTree[iV]->key << endl;
		}else {
			ListTree.clear();
			cout<<"Обход закончен"<<endl;
		}
	}
private:
	void ListCreat(Tree* knot){
		if (knot){
			if(knot->left) ListCreat(knot->left);
			ListTree.push_back(knot);
			if(knot->right) ListCreat(knot->right);
		}
	};
	void DeleteTree(Tree* knot){
		if (knot){
			if(knot->right)	DeleteTree(knot->right);
			if(knot->left) DeleteTree(knot->left);
			delete knot;
		};
	};
	Tree* newww(Tree* leaf, string str){
		leaf = new Tree;
		leaf->key=str;
		leaf->right=NULL;
		leaf->left=NULL;
		return leaf;
	}
	void addHelp(string str, Tree* knot){
		if (knot){
			if (str>knot->key){
				if (knot->right){
					addHelp(str, knot->right);
				}else{
					knot->right=newww(knot->right, str);
				}
			}else{
				if (knot->left){
					addHelp(str, knot->left);
				}else{
					knot->left=newww((knot->left), str);
				}
			}
		}else{
			root=newww(knot, str);
		}
	}
	void printTree(Tree* knot){
		if(knot->right)	printTree(knot->right);
		if(knot->left) printTree(knot->left);
		if (knot) cout << knot->key << endl;
	}
};

int main(){
	BinTree dict;
	string str;
	ifstream f;
	int a=1;
	while(a){
		cout<<"Введите соответсвующую цифру для вызова метода"<<endl;
		cout<<"1, добавить слово"<<endl;
		cout<<"2, удалить слово"<<endl;
		cout<<"3, поиск слова"<<endl;
		cout<<"4, начать обход дерева"<<endl;
		cout<<"5, следующий элемент обхода"<<endl;
		cout<<"6, ввести данные из файла"<<endl;
		cout<<"другое, завершение программы"<<endl;
		int k;
		cin>>k;
		switch(k){
			case 1:
				cin>>str;
				dict.add(str);
				dict.prTree();
				break;
			case 2:
				cin>>str;
				dict.del(str);
				dict.prTree();
				break;
			case 3:
				cin>>str;
				if (dict.search(str)) cout<<str<<" есть в дереве"<<endl;
				break;
			case 4:
				dict.trav();
				break;
			case 5:
				dict.next();
				break;
			case 6:
				cin>>str;
				f.open(str);
				if(f.is_open()){
					while(!f.eof()){
						getline(f, str);
						if (str!="") dict.add(str);
					}
					f.close();
				}else
					cout << "Ошибка открытия файла!" << endl;
				dict.prTree();
				break;
			default:
				a=0;			
		}		
	}
	return 0;
};
