#include "OrgChart.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace ariel;
using namespace std;

int isNull(OrgChart::node *n, int i = 1)
{
    if (n == nullptr)
    {
        if (i == 0)
        {
            return 1;
        }
        
        throw invalid_argument("no root");
    }
    return 0;
}

void stringCheck(const string &str)
{
    if (str == "\t" || str == "\n" || str == "\a")
    {
        throw invalid_argument("invalid string");
    }
}

OrgChart::OrgChart(OrgChart & copy){
    this->root = copy.root;
}

OrgChart::~OrgChart(){
    del(this->root);

}

OrgChart::OrgChart()
{
    this->root = nullptr;
}


void OrgChart::del(node * nd){
    if (nd == nullptr)
    {
        return;
    }
    
    for (unsigned int i = 0; i < nd->infer.size(); i++)
    {
        del(nd->infer[i]);
    }
    delete(nd);
}

OrgChart::node *OrgChart::find(const string &data) const
{
    isNull(this->root);
    stack<node *> myStack;
    myStack.push(this->root);
    while (!myStack.empty())
    {
        node *myNode = myStack.top();
        myStack.pop();
        if (myNode->name == data)
        {
            return myNode;
        }

        for (int i = (int)(myNode->infer.size()) -1; i >= 0; i--)
        {
            myStack.push(myNode->infer.at((unsigned int) i));
        }
    }
    return nullptr;
}

OrgChart::Iterator OrgChart::end() const
{
    isNull(this->root);
    return Iterator("end", nullptr);
}

OrgChart::Iterator OrgChart::end_preorder() const
{
    isNull(this->root);
    return Iterator("end", nullptr);
}

OrgChart::Iterator OrgChart::begin() const
{
    isNull(this->root);
    return Iterator("level", this->root);
}

OrgChart::Iterator OrgChart::reverse_order() const
{
    isNull(this->root);
    return Iterator("end", nullptr);
}

OrgChart::Iterator OrgChart::begin_reverse_order() const
{
    isNull(this->root);
    return Iterator("rev", this->root);
}

OrgChart::Iterator OrgChart::end_level_order() const
{
    isNull(this->root);
    return Iterator("end", nullptr);
}

OrgChart::Iterator OrgChart::begin_level_order() const
{
    isNull(this->root);
    return Iterator("level", this->root);
}

OrgChart::Iterator OrgChart::begin_preorder() const
{
    isNull(this->root);
    return Iterator("pre", this->root);
}

OrgChart &OrgChart::add_root(const string &boss)
{
    stringCheck(boss);
    if (isNull(this->root, 0) == 0)
    {
        this->root->name = boss;
    }
    else
    {
        this->root = create(boss);
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const string &Superior, const string &Inferior)
{
    stringCheck(Superior);
    stringCheck(Inferior);
    node *sup = find(Superior);
    isNull(sup);
    node *inf = create(Inferior);
    sup->infer.push_back(inf);
    return *this;
}

ostream &ariel::operator<<(ostream &myOutput, const OrgChart &myOrgChart)
{
    return myOutput;
}
