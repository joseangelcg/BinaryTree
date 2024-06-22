add_library(BinaryTree STATIC)

target_sources( BinaryTree PRIVATE
    BinaryTree.c
    Node/BTNode.c
    Node/NodeQueue.c
)

target_include_directories( BinaryTree
    PUBLIC
    Node/
    .
)

