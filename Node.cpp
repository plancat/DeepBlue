#include "Node.h"

vector<Node*> Node::roots;
std::queue<function<void()>> Node::delayComment;