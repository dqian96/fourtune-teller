//
// Created by David on 2017-01-07.
//

#ifndef CONNECT_4_BOT_MINIMAXNODE_H
#define CONNECT_4_BOT_MINIMAXNODE_H


#include <vector>
#include <string>
#include <limits>

enum MinimaxNodeTypes {Maximizer, Minimizer};

class MinimaxNode {
public:
    MinimaxNode(MinimaxNodeTypes,
            int = -std::numeric_limits<int>::max(),
            int = std::numeric_limits<int>::max());
    virtual ~MinimaxNode();
    int getNumChildren() const;
    MinimaxNode* getChild(int) const;
    void addChild(MinimaxNode*);
    void update(int);
    bool isValid();
    int getValue() const;
    int getAlpha() const;
    int getBeta() const;
    std::string getBoard() const;
    MinimaxNodeTypes getType() const;
private:
    MinimaxNodeTypes type;
    int alpha;
    int beta;
    std::vector<MinimaxNode*> children;
};


#endif //CONNECT_4_BOT_MINIMAXNODE_H
