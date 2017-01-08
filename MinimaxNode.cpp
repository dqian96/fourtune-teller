//
// Created by David on 2017-01-07.
//
#include <limits>

#include "MinimaxNode.h"

using namespace std;

MinimaxNode::MinimaxNode(MinimaxNodeTypes type, string board): type(type), board(board) {
    if (type == Maximizer) {
        alpha = numeric_limits<int>::max();
        beta = -numeric_limits<int>::max();
        value = -numeric_limits<int>::max();
    } else if (type == Minimizer) {
        alpha = -numeric_limits<int>::max();
        beta = numeric_limits<int>::max();
        value = numeric_limits<int>::max();
    }
}

MinimaxNode::~MinimaxNode() {
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
}

int MinimaxNode::getNumChildren() const {
    return children.size();
}

MinimaxNode* MinimaxNode::getChild(int i) const {
    return children[i];
}

void MinimaxNode::addChild(MinimaxNode* node) {
    children.push_back(node);
}