template<class T>
struct Node{
    Node* up;
    Node* left;
    Node* right;
    int key;
    T data;
    Node(int k, T d){
        up = NULL;
        left = NULL;
        right = NULL;
        key = k;
        data = d;
    }
    ~Node(){
        delete left;
        delete right;
    }
    bool operator==(const Node<T> &r){
        if(key == r.key && data == r.data){
            return ((left == NULL && r.left == NULL) || (left != NULL && r.left != NULL && *left == *r.left)) && ((right == NULL && r.right == NULL) || (right != NULL && r.right != NULL && *right == *r.right));
        }
        else{
            return false;
        }
    }
};

template<class T>
class SplayTree{
    private:
        std::string sr, sl, sp;
        Node<T>* root;
        
        void zigL(Node<T>* c){
            Node<T>* f = c->up;
            Node<T>* s = c->right;
            if(f == root){
                root = c;
            }
            else if((f->up)->left == f){
                (f->up)->left = c;
            }
            else{
                (f->up)->right = c;
            }
            if(s) s->up = f;
            c->right = f;
            c->up = f->up;
            f->up = c;
            f->left = s;
        }
        
        void zigR(Node<T>* c){
            Node<T>* f = c->up;
            Node<T>* s = c->left;
            if(f == root){
                root = c;
            }
            else if((f->up)->left == f){
                (f->up)->left = c;
            }
            else{
                (f->up)->right = c;
            }
            if(s) s->up = f;
            c->left = f;
            c->up = f->up;
            f->up = c;
            f->right = s;
        }
        
        void splay(Node<T>* c){
            while(c != root && c){
                if(c->up == root){
                    if(root->left == c){
                        zigL(c);
                    }
                    else{
                        zigR(c);
                    }
                }
                else{
                    Node<T>* f = c->up;
                    Node<T>* g = f->up;
                    if(g->left == f && f->left == c){       // zig-zigL
                        zigL(f);
                        zigL(c);
                    }
                    else if(g->right == f && f->right == c){// zig-zigR
                        zigR(f);
                        zigR(c);
                    }
                    else if(g->left == f){
                        zigR(c);
                        zigL(c);
                    }
                    else{
                        zigL(c);
                        zigR(c);
                    }
                }
            }
        }
        
        void print(std::string s1, std::string s2, Node<T>* v){
            std::string s;
            if(v){
                s = s1;
                if(s2 == sr){
                    s[s.length() - 2] = ' ';
                }
                print(s + sp, sr, v->right);
                s = s.substr(0, s1.length() - 2);
                std::cout << s << s2 << v->key << std::endl;
                s = s1;
                if(s2 == sl){
                    s[s.length() - 2] = ' ';
                }
                print(s + sp, sl, v->left);
            }
        }
        
        void copy(Node<T>* f, Node<T>* c){
            if(c->left){
                Node<T>* l = new Node<T>((c->left)->key, (c->left)->data);
                f->left = l;
                l->up = f;
                copy(l, c->left);
            }
            if(c->right){
                Node<T>* r = new Node<T>((c->right)->key, (c->right)->data);
                f->right = r;
                r->up = f;
                copy(r, c->right);
            }
        }
    public:
        SplayTree(){
            root = NULL;
            if(sr.empty()){
                sr = sl = sp = "  ";
                sr[0] = 218; sr[1] = 196;
                sl[0] = 192; sl[1] = 196;
                sp[0] = 179;
            }
        }
        
        SplayTree(SplayTree<T>* t){
            if(t){
                root = new Node<T>((t->root)->key, (t->root)->data);
                copy(root, t->root);
            }
            else{
                root = NULL;
            }
        }
        
        ~SplayTree(){
            delete root;
        }
        
        void insert(int k, T d){
            Node<T>* c;
            Node<T>* n;
            n = new Node<T>(k,d);
            c = root;
            if(!c){
                root = n;
            }
            else{
                while(true){
                    if(k < c->key){
                        if(!c->left){
                            c->left = n;
                            n->up = c;
                            break;
                        }
                        else{
                            c = c->left;
                        }
                    }
                    else if(k > c->key){
                        if(!c->right){
                            c->right = n;
                            n->up = c;
                            break;
                        }
                        else{
                            c = c->right;
                        }
                    }
                    else{
                        delete n;
                        n = c;
                        break;
                    }
                }
                splay(n);
            }
        }
        
        Node<T>* find(int k){
            Node<T>* c = root;
            Node<T>* prev = c;
            while(c){
                prev = c;
                if(c->key > k){
                    c = c->left;
                }
                else if(c->key < k){
                    c = c->right;
                }
                else{
                    prev = c;
                    break;
                }
            }
            while(prev->key > k && prev != root){
                prev = prev->up;
            }
            
            splay(prev);
            if(prev->key == k){
                return prev;
            }
            else{
                return NULL;
            }
        }
        
        void erase(int k){
            Node<T>* c = find(k);
            if(c && c->key == k){
                if(c->left){

                    root = c->left;
                    root->up = NULL;
                    find(k);
                    root->right = c->right;
                    if(c->right) (c->right)->up = root;
                    
                }
                else if(c->right){
                    root = c->right;
                    find(k);
                    root->left = c->left;
                }
                else{
                    root = NULL;
                }
                c->left = NULL;
                c->right = NULL;
                delete c;
            }
        }
        
        void printTree(){
            print("", "", root);
        }
        
        void join(SplayTree<T>* t){
            if(t->root){
                find((t->root)->key);
                root->right = t->root;
                (t->root)->up = root;
                t->root = NULL;
            }
        }
        
        SplayTree<T>* split(int k){
            find(k);
            SplayTree<T>* ntree = new SplayTree();
            if(root->key <= k){
                
            ntree->root = root->right;
            root->right = NULL;
            }
            else{
                ntree->root = root;
                root = NULL;
            }
            return ntree;
        }
        
        bool empty(){
            if(root) return true;
            return false;
        }
        
        void swap(SplayTree<T>* t){
            Node<T>* n = root;
            root = t->root;
            t->root = n;
        }
        
        bool operator==(const SplayTree<T> &r){
            return *(root) == *r.root;
        }
};
