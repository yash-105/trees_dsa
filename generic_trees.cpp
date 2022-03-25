#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    vector<node*> children;

     node(int val)
    {
        this->data = val;
    }
};

node* constructor(vector<int>arr,int n)
{
    node *root = NULL;
     stack<node*> st;
    for (int i = 0; i < arr.size();i++)
    {
        if(arr[i]==-1)
        {
            st.pop();
        }else{
            node*t = new node(arr[i]);
            if(st.size()>0){
                st.top()->children.push_back(t);
            }else{
                root = t;
            }
            st.push(t);
                }
    }
    return root;
}

void display(node*root)
{
    string str = to_string(root->data) + "->";
    for(node* child:root->children)
    {
        str += to_string(child->data) + ", ";
    }
    str += '.';
    cout << str << endl;
    for (node *child : root->children)
    {
        display(child);
    }
}

//size
int size_(node*root)
{
    int ans = 0;
    for (auto child : root->children)
    {
        ans += size_(child);
   }
   return ans + 1;
}

//find maxi
int maxi(node*root)
{
    int ans = INT_MIN;
    for(auto child:root->children)
    {
        ans = max(ans, maxi(child));
    }
    ans = max(ans, root->data);
    return ans;
}
//height
int height(node*root)
{
    int h = 0;//-1 -> in terms of edges
    for(auto child:root->children)
    {
        h = max(h, height(child));
    }
    return h + 1;
}

//generic tree traversals
void traverse(node*root)
{
    cout << " node pre " << root->data << endl;
    for(auto child:root->children)
    {
        cout << "edge pre " << root->data << "-" << child->data << endl;
         traverse(child);
        cout << "edge post " << root->data <<"-"<<child->data<< endl;
    }
    cout << " node post " << root->data << endl;
}

//level order
void level(node*root)
{
    queue<node*> q;
    q.push(root);

    while(q.size()>0)
    {
        node *top = q.front();
        q.pop();
        cout << top->data << " ";
        for (auto child : top->children)
        {
            q.push(child);
        }
    } 
}

//level linewise
void levellw(node*root)
{
    queue<node*> q,cq;
    q.push(root);
    while(q.size()>0 || cq.size()>0)
    {
        if(q.size()==0)
        {
            cout << endl;
            q = cq;
            queue<node *> nq;
            cq = nq;
        }else{
            node *top = q.front();
            q.pop();
            cout << top->data << " ";
            for(auto child:top->children)
            {
                cq.push(child);
            }
        }
    }
}

void level1(node*root)
{
    queue<node *> q;
    q.push(root);
    q.push(NULL);
    while(q.size()>0)
    {
        node *top = q.front();
        q.pop();
        if(top==NULL)
        {
            if(q.size()>0)
            {
                q.push(NULL);
                cout << endl;
            }
        }else{
            cout << top->data << " ";
            for(auto child:top->children)
            {
                q.push(child);
            }
        }
    }
}

// level linewisezigzag
void levelzz(node*root)
{
    stack<node *> s;
    stack<node *> cs;
    s.push(root);
    int level = 1;
    while(s.size()>0)
    {
        node *top = s.top();
        s.pop();
        cout << top->data << " ";
        if(level%2==0)
        {
            for (int i = top->children.size()-1; i >= 0;i--)
            {
                cs.push(top->children[i]);
            }
        }else{
           for (int i = 0; i<top->children.size();i++)
            {
                cs.push(top->children[i]);
            }
        }
        if(s.size()==0)
        {
            s = cs;
            stack<node *> ns;
            cs = ns;
            cout << endl;
        }
    }
}

void mirror(node*root)
{
    for(auto child:root->children)
    {
        mirror(child);
    }
     reverse(root->children.begin(), root->children.end());
}

//remove leafs
void removeleafs(node*root)
{
    for (int i = root->children.size() - 1; i >= 0;i--)
    {

        node *child = root->children[i];
        if(child->children.size()==0)
        {
            root->children.erase(root->children.begin() + i);
        }
   }
   for(auto child:root->children)
   {
       removeleafs(child);
   }
}

//linearise a gt
node* gettail(node*temp)
{
     while(temp->children.size()==1)
     {
         temp = temp->children[0];
     }
     return temp;
}
void linearise(node*root)
{
    for(auto child:root->children)
    {
        linearise(child);
    }
    while(root->children.size()>1)
    {
        node *lc = root->children[(root->children.size()) - 1];
        root->children.erase((root->children.begin()) + root->children.size() - 1);
        node*sl=root->children[(root->children.size()) - 1];
        node *sltail = gettail(sl);
        sltail->children.push_back(lc);
    }
}

//find element in generic tree
bool find(int val,node*root,vector<int>&a)
{
    bool ans = false;
    if(root->data==val)
    {
        return true;
    }
    for(auto child:root->children)
    {
       ans= ans | find(val, child,a);
       if(ans==true)
       {
         
           return true;
       }
    }
    return ans;
}

//node to root path
vector<int> root_node_path(int val,node*root)
{
    if(root->data==val)
    {
        vector<int> v;
        v.push_back(val);
        return v;
    }
    for(auto child:root->children)
    {
        vector<int> ans = root_node_path(val, child);
        if(ans.size()>0)
        {
            ans.push_back(root->data);
            return ans;
        }
    }
    vector<int> e;
    return e;
}

//lca
int lca(int val1,int val2,node*root)
{
    vector<int> p1 = root_node_path(val1, root);
    vector<int> p2 = root_node_path(val2, root);
    int i = p1.size() - 1, j = p2.size() - 1;
    while(p1[i]==p2[j])
    {
        i--, j--;
    }
    return p1[i + 1];
}

//dist b/w two nodes
int dist(int val1,int val2,node*root)
{
    vector<int> p1 = root_node_path(val1, root);
    vector<int> p2 = root_node_path(val2, root);
    int i = p1.size()-1, j = p2.size()-1;
    while(p1[i]==p2[j])
    {
        i--, j--;
    }
    i++, j++;
    return i + j;
}

//are trees similar in shape
bool shape(node*root1,node*root2)
{
    if(root1->children.size()!=root2->children.size())
    {
        return false;
    }
        for (int i = 0;i<root1->children.size();i++)
        {
            if(shape(root1->children[i], root2->children[i])==false)
            {
                return false;
            }
        }
        return true;
}

//mirror img in shape
bool mirrorshape(node*root1,node*root2)
{
    if(root1->children.size()!=root2->children.size())
    {
        return false;
    }
    int n = root1->children.size();
    for (int i = 0; i < root1->children.size();i++)
    {
        if (mirrorshape(root1->children[i], root2->children[n - 1 - i]) == false)
        {
            return false;
        }
    }
    return true;
}

//is gt symmetric
//-> bhai ye chemistry h : jo tree khud ki mirrorimage h wo symmetric h
bool symetric(node*root)
{
    if(mirrorshape(root,root)==true)
    {
        return true;
    }else{
        return false;
    }
}

//multisolver
int mn = INT_MAX;
int mx = INT_MIN;
int sz = 0, ht = 0;
void multisolver(node*root,int depth)
{
    sz++;
    mn = min(mn, root->data);
    mx = max(mx, root->data);
    ht = max(ht, depth);
    for(auto child:root->children)
    {
        multisolver(child,depth+1);
    }
}

//predecessor and successor in preorder
node *predecessor = NULL;
node*successor = NULL;

int state = 0;
void predecessorsuccessor(node*root,int val)
{
    
    if(state==0)
    {
        if(root->data==val)
        {
            state = 1;
        }else{
            predecessor = root;
        }
    }
    else if(state==1)
    {
        successor = root;
        state = 2;
    }
    for(auto child:root->children)
    {
        predecessorsuccessor(child,val);
    }
}

//ceil and floor
int ceil1 = INT_MAX;
int floor1 = INT_MIN;
void ceil_floor(node*root,int val)
{
    if(root->data>val)
    {
        ceil1 = min(ceil1, root->data);
    }else if(root->data < val)
    {
        floor1 = max(floor1, root->data);
    }

    for(auto child:root->children)
    {
        ceil_floor(child,val);
    }
}

//kth largest element
int kth_largest(node*root,int k)
{
     floor1= INT_MIN;
    int factor = INT_MAX;
    for (int i = 0; i < k;i++)
    {
        ceil_floor(root, factor);
        factor = floor1;
        floor1= INT_MIN;
    }
    return factor;
}

//maximum sum subtree
int ans = 0;
int mxs = INT_MIN;//mxs->mxsum
int mxss(node*root)
{
    int sum = 0;
    for(auto child:root->children)
    {
        sum += mxss(child);
    }
    sum += root->data;
    if(sum>mxs)
    {
        mxs = sum;
        ans = root->data;
    }
    return sum;
}

//diameter of gt
int dia = 0;
int diameter(node*root)
{
    int dch = -1, sdch = -1;
    for(auto child:root->children)
    {
        int ch = diameter(child);
        if(ch>dch)
        {
            sdch = dch;
            dch = ch;
        }else if(ch>sdch)
        {
            sdch = ch;
        }
    }
    dia = max(dia, dch + sdch + 2);
    return dch+1;
}

//itterative preorder and postorder of a gt
vector<int> pre, post;
void prepost(node*root)
{
    stack<pair<node*,int>>st;
    st.push({root, -1});
    while(st.size()>0)
    {
        pair<node *, int> top = st.top();
        st.pop();
        int val = top.first->data;
        int state = top.second;
        int cs = top.first->children.size();
        if(state==-1)
        {
            pre.push_back(val);
            state++;
            st.push({top.first, state});
        }else if(state==cs)
        {
            post.push_back(val);
            
          
        }else 
        {
            node *child = top.first->children[state];
            state++;
            st.push({top.first, state});
            st.push({child,-1});
            
        }
    }
}



int main(){
    vector<int> arr= {10, 20, 50, -1, 60, -1, -1, 30, 70, -1, 80, 110, -1, 120, -1, -1, 90, -1, -1, 40, 100, -1, -1, -1};
    // vector<int> arr1 = {10, 20, -50, -1, -60, -1, -1, 30, -70, -1, 80, -110, -1, 120, -1, -1, 90, -1, -1, 40, -100, -1, -1, -1};
    node *root = constructor(arr, arr.size());
    //  display(root);
    //  cout<<size_(root);
    //  cout << maxi(root);
    //  cout << height(root) << endl;
    //  traverse(root);
    //  level(root);
    //  levellw(root);
    //  level1(root);
    //  display(root);
    //  mirror(root);
    //  cout << "-----------" << endl;
    //  display(root);
    //  cout << "-----------" << endl;
    //  removeleafs(root);
    //  display(root);
    //  linearise(root);
    //  display(root);
    //  vector<int> a = root_node_path(110, root);
    //  for (int i = 0; i < a.size();i++)
    //  {
    //      cout << a[i] << " ";
    //  }
    //  cout<<lca(70, 110, root);
    //  cout << symetric(root);
    //-> travel and change <-
    //  multisolver(root, 0);
    //  cout << "size " << sz << endl;
    //  cout << "height " << ht << endl;
    //  cout << "min " << mn << endl;
    //  cout << "max " << mx << endl;
    //  predecessorsuccessor(root, 40);
    //  cout << predecessor->data << endl;
    //  cout << successor->data << endl;
    // ceil_floor(root,65);
    // cout << floor1 << endl;
    // cout << ceil1 << endl;
    //  cout << kth_largest(root,3);
    // mxss(root);
    // cout << mxs << endl;
    // cout << ans << endl;
    // diameter(root);
    // cout << dia << endl;
    prepost(root);
    for (int i = 0; i < pre.size();i++)
    {
        cout << pre[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < post.size();i++)
    {
        cout << post[i] << " ";
    }
}



