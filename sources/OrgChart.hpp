#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

namespace ariel
{
    class OrgChart
    {
    public:
        class node
        {
        public:
            vector<node *> infer;
            string name;
            node(string name)
            {
                this->name = move(name);
            }
        };
        static node *create(string name)
        {
            node *ans = new node(move(name));
            return ans;
        }
        class Iterator
        {
        public:
            vector<string> visited;
            unsigned int i;
            void ACpreOrder(node *firstOne)
            {
                stack<node *> myStack;
                myStack.push(firstOne);
                while (!myStack.empty())
                {
                    node *myNode = myStack.top();
                    myStack.pop();
                    this->visited.push_back(myNode->name);
                    for (int i = (int)myNode->infer.size() - 1; i >= 0; i--)
                    {
                        myStack.push(myNode->infer.at((unsigned int)(i)));
                    }
                }
            }
            void AClevelOrder(node *firstOne)
            {
                queue<node *> myQueue;
                myQueue.push(firstOne);
                while (!myQueue.empty())
                {
                    unsigned int godel = myQueue.size();
                    while (godel > 0)
                    {
                        node *myNode = myQueue.front();
                        myQueue.pop();
                        this->visited.push_back(myNode->name);
                        for (int i = 0; i < myNode->infer.size(); i++)
                        {
                            myQueue.push(myNode->infer.at((unsigned int)(i)));
                        }
                        godel -= 1;
                    }
                }
            }
            void ACreverseOrder(node *firstOne)
            {
                queue<node *> myQueue;
                stack<node *> myStack;
                myQueue.push(firstOne);
                while (!myQueue.empty())
                {
                    node *myNode = myQueue.front();
                    myQueue.pop();
                    myStack.push(myNode);
                    for (int i = (int)myNode->infer.size() - 1; i >= 0; i--)
                    {
                        myQueue.push(myNode->infer.at((unsigned int)(i)));
                    }
                }
                while (!myStack.empty())
                {
                    this->visited.push_back(myStack.top()->name);
                    myStack.pop();
                }
            }
            Iterator(const string &action, node *start)
            {
                if (action == "pre")
                {
                    ACpreOrder(start);
                }
                else if (action == "level")
                {
                    AClevelOrder(start);
                }
                else if (action == "rev")
                {
                    ACreverseOrder(start);
                }

                // else if (action == "end")
                // {
                //     this->i = 0;
                //     this->visited.push_back("");
                // }
                this->i = 0;
                this->visited.push_back("");
            }
            Iterator &operator++()
            {
                this->i += 1;
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator exm = *this;
                this->i += 1;
                return exm;
            }
            bool operator!=(const Iterator &cur)
            {
                return this->visited.at(this->i) != cur.visited.at(cur.i);
            }
            const string *operator->() const
            {
                const string *ans = &(this->visited[i]);
                return ans;
            }
            string operator*() const
            {
                return this->visited.at(i);
            }
        };
        node *root;
        Iterator end() const;
        Iterator begin() const;
        Iterator begin_preorder() const;
        Iterator end_preorder() const;
        Iterator begin_reverse_order() const;
        Iterator reverse_order() const;
        Iterator end_level_order() const;
        Iterator begin_level_order() const;
        OrgChart();
        ~OrgChart();
        OrgChart(OrgChart &copy);
        OrgChart(OrgChart &&copy) noexcept;
        void del(node *nd);
        node *find(const string &data) const;
        OrgChart &add_sub(const string &Superior, const string &Inferior);
        OrgChart &add_root(const string &boss);
        OrgChart &operator=(OrgChart &&copy) noexcept;
        OrgChart &operator=(const OrgChart &copy) noexcept;
        friend ostream &operator<<(ostream &myOutput, const OrgChart &myOrgChart);
    };
}