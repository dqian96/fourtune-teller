//
// Created by David on 2017-01-07.
//

#ifndef CONNECT_4_BOT_MINIMAXNODE_H
#define CONNECT_4_BOT_MINIMAXNODE_H


#include <vector>
#include <string>

enum MinimaxNodeTypes {Maximizer, Minimizer, Leaf};

class MinimaxNode {
public:
    MinimaxNode(MinimaxNodeTypes, std::string);
    virtual ~MinimaxNode();
    int getNumChildren() const;
    MinimaxNode* getChild(int) const;
    void addChild(MinimaxNode*);
private:
    std::string board;
    MinimaxNodeTypes type;
    int alpha;
    int beta;
    int value;
    std::vector<MinimaxNode*> children;
};


#endif //CONNECT_4_BOT_MINIMAXNODE_H
