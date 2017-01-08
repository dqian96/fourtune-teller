//
// Created by David on 2017-01-07.
//
#include <limits>

#include "MinimaxNode.h"

using namespace std;

MinimaxNode::MinimaxNode(MinimaxNodeTypes type,
        int alpha = -numeric_limits<int>::max(),
        int beta = numeric_limits<int>::max()) : type(type), alpha(alpha), beta(beta) {}

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

void MinimaxNode::update(int candidate) {
    if (type == Maximizer) {
        alpha = candidate > alpha ? candidate : alpha;
    } else {
        beta = candidate < beta ? candidate : beta;
    }
}

int MinimaxNode::getValue() const {
    return type == Maximizer ? alpha : beta;
}

int MinimaxNode::getAlpha() const {
    return alpha;
}

int MinimaxNode::getBeta() const {
    return beta;
}

MinimaxNodeTypes MinimaxNode::getType() const {
    return type;
}

bool MinimaxNode::isValid() {
    return alpha >= beta ? false : true;
}